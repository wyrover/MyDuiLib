#include <svn_repos.h>
#include <svn_pools.h>
#include <svn_error.h>
#include <svn_client.h>
#include <svn_dso.h>
#include <svn_path.h>
#include <svn_config.h>
#include <svn_cmdline.h>
#include <svn_subst.h>
#include <svn_time.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


#if defined(WIN32)
#if defined(LUASVN_EXPORTS)
  #define LUASVN_API __declspec(dllexport)
 #else
  #define LUASVN_API
 #endif
#else
 #define LUASVN_API extern
#endif

#define IF_ERROR_RETURN(err, pool, L) do { \
	if (err) { \
	svn_string_t *sstring; \
	sstring = svn_string_create (err->message, pool); \
	svn_subst_detranslate_string (&sstring, sstring, TRUE, pool); \
	lua_pushstring(L,sstring->data); \
	svn_pool_destroy (pool); \
	return lua_error(L); \
	} \
} while (0)


/* Calls lua_error */
static int
send_error (lua_State *L, const char *message) {
	lua_pushstring (L, message);
	return lua_error (L);
}


/* Initializes the memory pool */
static int
init_pool (apr_pool_t **pool) {
	
	if (apr_initialize () != APR_SUCCESS) {
		return 1;
	}

	svn_dso_initialize ();

    *pool = svn_pool_create (NULL);

	return 0;
}


/* Indicates that an error occurred during the pool initialization */
static int
init_pool_error (lua_State *L) {
	return send_error (L, "Error initializing the memory pool\n");
}


static int
init_function (svn_client_ctx_t **ctx, apr_pool_t **pool, lua_State *L) {
	apr_allocator_t *allocator;
	svn_auth_baton_t *ab;
	svn_config_t *cfg;
	svn_error_t *err;

	if (svn_cmdline_init("svn", NULL) != EXIT_SUCCESS) {
		return send_error (L, "Error initializing svn\n");
	}
	
	if (apr_allocator_create(&allocator)) {
		return send_error (L, "Error creating allocator\n");
	}

	apr_allocator_max_free_set(allocator, SVN_ALLOCATOR_RECOMMENDED_MAX_FREE);

  	*pool = svn_pool_create_ex(NULL, allocator);
	apr_allocator_owner_set(allocator, *pool);

  	err = svn_ra_initialize(*pool);
	IF_ERROR_RETURN (err, *pool, L);

	err = svn_client_create_context (ctx, *pool);
	IF_ERROR_RETURN (err, *pool, L);

	err = svn_config_get_config(&((*ctx)->config),	NULL, *pool);
	IF_ERROR_RETURN (err, *pool, L);

	cfg = apr_hash_get((*ctx)->config, SVN_CONFIG_CATEGORY_CONFIG,
			APR_HASH_KEY_STRING);

	err = svn_cmdline_setup_auth_baton(&ab,
			FALSE,
			NULL,
			NULL,
			NULL,
			FALSE,
			cfg,
			(*ctx)->cancel_func,
			(*ctx)->cancel_baton,
			*pool);
	IF_ERROR_RETURN (err, *pool, L);

	(*ctx)->auth_baton = ab;

	return 0;
}


struct log_msg_baton
{
  const char *editor_cmd;  /* editor specified via --editor-cmd, else NULL */
  const char *message;  /* the message. */
  const char *message_encoding; /* the locale/encoding of the message. */
  const char *base_dir; /* the base directory for an external edit. UTF-8! */
  const char *tmpfile_left; /* the tmpfile left by an external edit. UTF-8! */
  svn_boolean_t non_interactive; /* if true, don't pop up an editor */
  apr_hash_t *config; /* client configuration hash */
  svn_boolean_t keep_locks; /* Keep repository locks? */
  apr_pool_t *pool; /* a pool. */
  lua_State *L;
};


svn_error_t *
make_log_msg_baton(void **baton,
		const char *message,
		const char *base_dir /* UTF-8! */,
		apr_hash_t *config,
		apr_pool_t *pool,
		lua_State *L)
{
  struct log_msg_baton *lmb = apr_palloc(pool, sizeof(*lmb));

  lmb->message = message;

  lmb->editor_cmd = NULL;;
  
  if (config)
  {
 	  svn_config_t *cfg = apr_hash_get(config, SVN_CONFIG_CATEGORY_CONFIG, 
                                       APR_HASH_KEY_STRING);
      svn_config_get(cfg, &(lmb->message_encoding),
                     SVN_CONFIG_SECTION_MISCELLANY,
                     SVN_CONFIG_OPTION_LOG_ENCODING,
                     NULL);
  } else 
  {
	  lmb->message_encoding = APR_LOCALE_CHARSET;
  }

  lmb->base_dir = base_dir ? base_dir : "";
  lmb->tmpfile_left = NULL;
  lmb->config = config;
  lmb->keep_locks = FALSE;
  lmb->non_interactive = TRUE;
  lmb->pool = pool;
  lmb->L = L;
  *baton = lmb;
  return SVN_NO_ERROR;
}

static svn_error_t *
log_msg_func2 (const char **log_msg,
		       const char **tmp_file,
			   const apr_array_header_t *commit_items,
			   void *baton,
			   apr_pool_t *pool)
{
	struct log_msg_baton *lmb = baton;

	svn_error_t *err = svn_utf_cstring_to_utf8 (log_msg, lmb->message, pool);
	
	if (err) {     
	  return err;
	} 

	*tmp_file = NULL;

	return SVN_NO_ERROR;
}


static enum svn_opt_revision_kind
get_revision_kind (const char *path) {
	if (svn_path_is_url (path))
		return svn_opt_revision_head;
	return svn_opt_revision_base;
}


static int
l_add (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	const char *path = luaL_checkstring (L, 1);
	int itable = 2;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t force = FALSE;
	svn_boolean_t no_ignore = FALSE;

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
	
		lua_getfield (L, itable, "no_ignore");
		if (lua_isboolean (L, -1)) {
			no_ignore = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	err = svn_client_add3 (path, recursive, force, no_ignore, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	svn_pool_destroy (pool);
	
	return 0;
}


static svn_error_t *
write_fn (void *baton, const char *data, apr_size_t *len) {

	svn_stringbuf_appendbytes (baton, data, *len);

	return SVN_NO_ERROR;
}


static int
l_cat (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	svn_stream_t *stream;
	svn_stringbuf_t *buffer;
	svn_opt_revision_t peg_revision;
	svn_opt_revision_t revision;

	const char *path = luaL_checkstring (L, 1);
	peg_revision.kind = svn_opt_revision_unspecified;

	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		revision.kind = get_revision_kind (path);
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 2);
	}

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	stream = svn_stream_empty (pool);
	svn_stream_set_write (stream, write_fn);

	buffer = svn_stringbuf_create ("\0", pool);

	svn_stream_set_baton (stream, buffer);

	err = svn_client_cat2 (stream, path, &peg_revision, &revision, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	lua_pushstring (L, buffer->data);

	svn_pool_destroy (pool);

	return 1;
}


static int
l_checkout (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	svn_opt_revision_t revision;
	svn_opt_revision_t peg_revision;
	svn_revnum_t rev;

	const char *path = luaL_checkstring (L, 1);
	const char *dir = luaL_checkstring (L, 2);
	int itable = 4;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t ignore_externals = FALSE;
	peg_revision.kind = svn_opt_revision_unspecified;

	if (lua_gettop (L) < 3 || lua_isnil (L, 3)) {
		revision.kind = svn_opt_revision_head;	
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 3);
	}
	
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "ignore_externals");
		if (lua_isboolean (L, -1)) {
			ignore_externals = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);
	dir = svn_path_canonicalize (dir, pool);
	
	err = svn_client_checkout2 (&rev, path, dir, &peg_revision, &revision, recursive, ignore_externals, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);
	
	lua_pushinteger (L, rev);

	svn_pool_destroy (pool);

	return 1;
}


static int
l_cleanup (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);

	init_function (&ctx, &pool, L);
	
	path = svn_path_canonicalize (path, pool);

	err = svn_client_cleanup (path, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);
	
	svn_pool_destroy (pool);

	return 0;
}


static int
l_commit (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	apr_array_header_t *array;

	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
	const char *message = (lua_gettop (L) < 2 || lua_isnil (L, 2)) ? "" : luaL_checkstring (L, 2);
	int itable = 3;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t keep_locks = FALSE;
	svn_commit_info_t *commit_info = NULL;
	
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "keep_locks");
		if (lua_isboolean (L, -1)) {
			keep_locks = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	array = apr_array_make (pool, 1, sizeof (const char *));
	(*((const char **) apr_array_push (array))) = path;

	make_log_msg_baton (&(ctx->log_msg_baton2), message, path, ctx->config, pool, L);
	
	ctx->log_msg_func2 = log_msg_func2;

	err = svn_client_commit3 (&commit_info, array, recursive, keep_locks, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);	

	if (commit_info == NULL) {
		lua_pushnil (L);
	} else {
		lua_pushinteger (L, commit_info->revision);
	}

	svn_pool_destroy (pool);

	return 1;
}


static int
l_copy (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	svn_opt_revision_t revision;

	const char *src_path = luaL_checkstring (L, 1);
	const char *dest_path = luaL_checkstring (L, 2);
	const char *message = NULL;
	svn_commit_info_t *commit_info = NULL;

	if (lua_gettop (L) < 3 || lua_isnil (L, 3)) {
		revision.kind = svn_opt_revision_unspecified;
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 3);
	}

	message = (lua_gettop (L) < 4 || lua_isnil (L, 4)) ? "" : luaL_checkstring (L, 4);

	init_function (&ctx, &pool, L);

	src_path = svn_path_canonicalize (src_path, pool);
	dest_path = svn_path_canonicalize (dest_path, pool);

	if (svn_path_is_url (dest_path)) {
		make_log_msg_baton (&(ctx->log_msg_baton2), message, NULL, ctx->config, pool, L);
		ctx->log_msg_func2 = log_msg_func2;
	}

	err = svn_client_copy3 (&commit_info, src_path, &revision, dest_path, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);	

	if (commit_info == NULL) {
		lua_pushnil (L);
	} else {
		lua_pushinteger (L, commit_info->revision);
	}

	svn_pool_destroy (pool);

	return 1;
}


static int
l_delete (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	apr_array_header_t *array;
	
	const char *path = luaL_checkstring (L, 1);
	const char *message = (lua_gettop (L) < 2 || lua_isnil (L, 2)) ? "" : luaL_checkstring (L, 2);
	int itable = 3;
	svn_boolean_t force = FALSE;
	svn_commit_info_t *commit_info = NULL;

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	array = apr_array_make (pool, 1, sizeof (const char *));
	(*((const char **) apr_array_push (array))) = path;

	lua_newtable (L);

	if (svn_path_is_url (path)) {
		make_log_msg_baton (&(ctx->log_msg_baton2), message, NULL, ctx->config, pool, L);
		ctx->log_msg_func2 = log_msg_func2;
	}

	err = svn_client_delete2 (&commit_info, array, force, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	if (commit_info == NULL) {
		lua_pushnil (L);
	} else {
		lua_pushinteger (L, commit_info->revision);
	}
	
	svn_pool_destroy (pool);

	return 1;
}


static int
l_diff (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	apr_file_t *aprout;
	apr_file_t *aprerr;
	apr_status_t status;
	apr_array_header_t *array;
	svn_opt_revision_t rev1;
	svn_opt_revision_t rev2;

	const char *path1 = NULL;
	const char *path2 = NULL;
	const char *outfile = NULL;	
	const char *errfile = NULL;
	int itable = 7;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t ignore_ancestry = TRUE;
	svn_boolean_t no_diff_deleted = FALSE;
	svn_boolean_t force = FALSE;
	
	path1 = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
		
	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		rev1.kind = get_revision_kind (path1);
	} else {
		rev1.kind = svn_opt_revision_number;
		rev1.value.number = lua_tointeger (L, 2);
	}
	
	path2 = (lua_gettop (L) < 3 || lua_isnil (L, 3)) ? path1 : luaL_checkstring (L, 3);

	if (lua_gettop (L) < 4 || lua_isnil (L, 4)) {
		if (svn_path_is_url (path2)) {
			rev2.kind = svn_opt_revision_head;
		} else {
			rev2.kind = svn_opt_revision_working;
		}
	} else {
		rev2.kind = svn_opt_revision_number;
		rev2.value.number = lua_tointeger (L, 4);
	}

	outfile = (lua_gettop (L) < 5 || lua_isnil (L, 5)) ? NULL : luaL_checkstring (L, 5);
	
	errfile = (lua_gettop (L) < 6 || lua_isnil (L, 6)) ? NULL : luaL_checkstring (L, 6);
	
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "ignore_ancestry");
		if (lua_isboolean (L, -1)) {
			ignore_ancestry = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "no_diff_deleted");
		if (lua_isboolean (L, -1)) {
			no_diff_deleted = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path1 = svn_path_canonicalize (path1, pool);
	path2 = svn_path_canonicalize (path2, pool);

	if (outfile) {
		status = apr_file_open (&aprout, outfile, APR_READ | APR_WRITE | APR_CREATE,
				                APR_OS_DEFAULT, pool);
	} else {
		status = apr_file_open_stdout(&aprout, pool);
	}
	if (status) {
		IF_ERROR_RETURN (svn_error_wrap_apr(status, "Can't open output file"), pool, L);
	}

	if (errfile) {
		status = apr_file_open (&aprerr, errfile, APR_READ | APR_WRITE | APR_CREATE,
				                APR_OS_DEFAULT, pool);
	} else {
		status = apr_file_open_stderr(&aprerr, pool);
	}
	if (status) {
		IF_ERROR_RETURN (svn_error_wrap_apr(status, "Can't open error file"), pool , L);
	}

	array = apr_array_make (pool, 0, sizeof (const char *));

	err = svn_client_diff3 (array, path1, &rev1, path2, &rev2,
			                recursive, ignore_ancestry, no_diff_deleted, force,
							APR_LOCALE_CHARSET, aprout, aprerr,
							ctx, pool);
	IF_ERROR_RETURN (err, pool, L);	

	svn_pool_destroy (pool);

	return 0;
}


static int
l_import (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	const char *path = lua_isnil (L, 1) ? "" : luaL_checkstring (L, 1);
	const char *url = luaL_checkstring (L, 2);
	const char *message = (lua_gettop (L) < 3 || lua_isnil (L, 3)) ? "" : luaL_checkstring (L, 3);
	int itable = 4;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t no_ignore = FALSE;
	svn_commit_info_t *commit_info = NULL;
	
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "no_ignore");
		if (lua_isboolean (L, -1)) {
			no_ignore = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);
	url = svn_path_canonicalize (url, pool);

	make_log_msg_baton (&(ctx->log_msg_baton2), message, NULL, ctx->config, pool, L);
	ctx->log_msg_func2 = log_msg_func2;

	err = svn_client_import2 (&commit_info, path, url, !recursive, no_ignore, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	if (commit_info == NULL) {
		lua_pushnil (L);
	} else {
		lua_pushinteger (L, commit_info->revision);
	}

	svn_pool_destroy (pool);
	
	return 1;
}


static svn_error_t *
list_func (void *baton,
		   const char *path,
		   const svn_dirent_t *dirent,
		   const svn_lock_t *lock,
		   const char *abs_path,
		   apr_pool_t *pool)
{
	lua_State *L = baton;

	if (strcmp (path, "") == 0) {
		if (dirent->kind == svn_node_file) {
			path = svn_path_basename (abs_path, pool);
		} else {
			return SVN_NO_ERROR;
		}
	} 	
	
	lua_pushfstring (L, "%s%s", path, dirent->kind == svn_node_dir ? "/" : "");
	
	lua_newtable (L);
	
	if (dirent->kind == svn_node_file)
		lua_pushinteger (L, dirent->size);
	else
		lua_pushnil (L);

	lua_setfield (L, -2, "size");

	if (dirent->last_author)
		lua_pushstring (L, dirent->last_author);
	else
		lua_pushnil (L);

	lua_setfield (L, -2, "author");
	
	lua_pushinteger (L, dirent->created_rev);
	lua_setfield (L, -2, "revision");

	lua_pushstring (L, svn_time_to_human_cstring (dirent->time, pool));
	lua_setfield (L, -2, "date");

	lua_settable (L, -3);

	return SVN_NO_ERROR;
}

static int
l_list (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	svn_opt_revision_t revision;
	svn_opt_revision_t peg_revision;

	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
	int itable = 3;
	svn_boolean_t recursive = FALSE;
	svn_boolean_t fetch_locks = FALSE;
	peg_revision.kind = svn_opt_revision_unspecified;

	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		revision.kind = get_revision_kind (path);
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 2);
	}

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "fetch_locks");
		if (lua_isboolean (L, -1)) {
			fetch_locks = lua_toboolean (L, -1);
		}
	}

	init_function (&ctx, &pool, L);
	path = svn_path_canonicalize (path, pool);
	lua_newtable (L);

	err = svn_client_list (path, &peg_revision, &revision, recursive, SVN_DIRENT_ALL,
			               fetch_locks, list_func, L, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	svn_pool_destroy (pool);

	return 1;
}


static svn_error_t *
log_receiver (void *baton,
			  apr_hash_t *changed_paths,
			  svn_revnum_t revision,
			  const char *author,
			  const char *date,
			  const char *message,
			  apr_pool_t *pool) 
{

	lua_pushinteger ((lua_State*)baton, revision);
	
	lua_newtable ((lua_State*)baton);

	lua_pushstring ((lua_State*)baton, date);

	lua_setfield ((lua_State*)baton, -2, "date");

	lua_pushstring ((lua_State*)baton, message);

	lua_setfield ((lua_State*)baton, -2, "message");

	lua_pushstring ((lua_State*)baton, author);

	lua_setfield ((lua_State*)baton, -2, "author");

	lua_settable ((lua_State*)baton, -3);

	return NULL;
}


static int
l_log (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	apr_array_header_t *array;
	svn_opt_revision_t start, end;
	svn_opt_revision_t peg_revision;

	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
	int itable = 5;
	int limit = 0; 
	svn_boolean_t discover_changed_paths = FALSE;
	svn_boolean_t stop_on_copy = FALSE;
	peg_revision.kind = svn_opt_revision_unspecified;
	start.kind = svn_opt_revision_number;
	
	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		start.value.number = 0;
	} else {
		start.value.number = lua_tointeger (L, 2);
	}

	if (lua_gettop (L) < 3 || lua_isnil (L, 3)) {
		end.kind = get_revision_kind (path);
	} else {
		end.kind = svn_opt_revision_number;
		end.value.number = lua_tointeger (L, 3);
	}

	if (lua_gettop (L) >= 4) {
		limit = lua_tointeger (L, 4);
	}
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "discover_changed_paths");
		if (lua_isboolean (L, -1)) {
			discover_changed_paths = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "stop_on_copy");
		if (lua_isboolean (L, -1)) {
			stop_on_copy = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	array = apr_array_make (pool, 1, sizeof (const char *));
	(*((const char **) apr_array_push (array))) = path;

	lua_newtable (L);

	err = svn_client_log3 (array, &peg_revision, &end, &start, limit, 
					discover_changed_paths, stop_on_copy, log_receiver, L, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	svn_pool_destroy (pool);

	return 1;
}


static int
l_merge (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	svn_opt_revision_t rev1;
	svn_opt_revision_t rev2;

	const char *source1 = NULL;
	const char *source2 = NULL;
	const char *wcpath = NULL;
	int itable = 6;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t ignore_ancestry = FALSE;
	svn_boolean_t force = FALSE;
	svn_boolean_t dry_run = FALSE;

	source1 = luaL_checkstring (L, 1);
		
	if (lua_isnil (L, 2)) {
		rev1.kind = svn_opt_revision_head;
	} else {
		rev1.kind = svn_opt_revision_number;
		rev1.value.number = lua_tointeger (L, 2);
	}

	source2 = luaL_checkstring (L, 3);

	if (lua_isnil (L, 4)) {
		rev2.kind = svn_opt_revision_head;
	} else {
		rev2.kind = svn_opt_revision_number;
		rev2.value.number = lua_tointeger (L, 4);
	}

	if (lua_gettop (L) < 5 || lua_isnil (L, 5)) {
		wcpath = "";
	} else {
		wcpath = luaL_checkstring (L, 5);
	}

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "ignore_ancestry");
		if (lua_isboolean (L, -1)) {
			ignore_ancestry = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "dry_run");
		if (lua_isboolean (L, -1)) {
			dry_run = lua_toboolean (L, -1);
		}
	}

	init_function (&ctx, &pool, L);

	source1 = svn_path_canonicalize (source1, pool);
	source2 = svn_path_canonicalize (source2, pool);
	wcpath = svn_path_canonicalize (wcpath, pool);

	err = svn_client_merge2 (source1, &rev1, source2, &rev2, wcpath,
			recursive, ignore_ancestry, force, dry_run, NULL, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);	

	svn_pool_destroy (pool);

	return 0;
}


static int
l_mkdir (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	apr_array_header_t *array;
	
	const char *path = luaL_checkstring (L, 1);
	const char *message = (lua_gettop (L) < 2 || lua_isnil (L, 2)) ? "" : luaL_checkstring (L, 2);
	svn_commit_info_t *commit_info = NULL;

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	array = apr_array_make (pool, 1, sizeof (const char *));
	(*((const char **) apr_array_push (array))) = path;

	if (svn_path_is_url (path)) {
		make_log_msg_baton (&(ctx->log_msg_baton2), message, NULL, ctx->config, pool, L);
		ctx->log_msg_func2 = log_msg_func2;
	}

	err = svn_client_mkdir2 (&commit_info, array, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	if (commit_info == NULL) {
		lua_pushnil (L);
	} else {
		lua_pushinteger (L, commit_info->revision);
	}

	svn_pool_destroy (pool);

	return 1;
}


static int
l_move (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	const char *src_path = luaL_checkstring (L, 1);
	const char *dest_path = luaL_checkstring (L, 2);
	const char *message = (lua_gettop (L) < 3 || lua_isnil (L, 3)) ? "" : luaL_checkstring (L, 3);
	int itable = 4;
	svn_boolean_t force = FALSE;
	svn_commit_info_t *commit_info = NULL;
	
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	src_path = svn_path_canonicalize (src_path, pool);
	dest_path = svn_path_canonicalize (dest_path, pool);
	
	if (svn_path_is_url (dest_path)) {
		make_log_msg_baton (&(ctx->log_msg_baton2), message, NULL, ctx->config, pool, L);
		ctx->log_msg_func2 = log_msg_func2;
	}

	err = svn_client_move4 (&commit_info, src_path, dest_path, force, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);	

	if (commit_info == NULL) {
		lua_pushnil (L);
	} else {
		lua_pushinteger (L, commit_info->revision);
	}

	svn_pool_destroy (pool);

	return 1;
}


static int
l_propget (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	apr_hash_t *props;
	const char *propname_utf8;
	const void *key;
	void *val;
	apr_hash_index_t *hi;
	svn_opt_revision_t peg_revision;
	svn_opt_revision_t revision;

	const char *path = luaL_checkstring (L, 1);
	const char *propname = luaL_checkstring (L, 2);
	int itable = 4;
	svn_boolean_t recursive = FALSE;
	peg_revision.kind = svn_opt_revision_unspecified;

	if (lua_gettop (L) < 3 || lua_isnil (L, 3)) {
		revision.kind = svn_opt_revision_unspecified;
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 3);
	}

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);
	
	err = svn_utf_cstring_to_utf8 (&propname_utf8, propname, pool);
	IF_ERROR_RETURN (err, pool, L);

	err = svn_client_propget2 (&props, propname_utf8, path, &peg_revision, &revision, recursive, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	lua_newtable (L);

	for (hi = apr_hash_first (pool, props); hi; hi = apr_hash_next (hi)) {
	  svn_string_t *s;
	  apr_hash_this (hi, &key, NULL, &val);
	  s = (svn_string_t *) val;
	  
	  lua_pushstring (L, s->data);
	  lua_setfield (L, -2, (char *) key);
	}

	svn_pool_destroy (pool);

	return 1;
}


static int
l_proplist (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	apr_array_header_t *props;
	svn_opt_revision_t peg_revision;
	svn_opt_revision_t revision;
	int is_url;
	int i;

	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
	int itable = 3;
	svn_boolean_t recursive = FALSE;
	peg_revision.kind = svn_opt_revision_unspecified;

	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		revision.kind = svn_opt_revision_unspecified;
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 2);
	}	

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}
	}

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	is_url = svn_path_is_url (path);

	err = svn_client_proplist2 (&props, path, &peg_revision, &revision, recursive, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	lua_newtable (L);

	for (i = 0; i < props->nelts; ++i)
	{
		const void *key;
		void *val;
		svn_client_proplist_item_t *item = ((svn_client_proplist_item_t **)props->elts)[i];
		apr_hash_index_t *hi;
		const char *name_local;

		if (is_url) {
			name_local = svn_path_local_style (item->node_name->data, pool);
		} else {
			name_local = item->node_name->data;
		}

		lua_pushstring (L, name_local);

		lua_newtable (L);

		for (hi = apr_hash_first (pool, item->prop_hash); hi; hi = apr_hash_next (hi)) {
			const char *pname;
			svn_string_t *pval;
			
			apr_hash_this (hi, &key, NULL, &val);

			pname = key;
			pval = (svn_string_t *) val;

			err = svn_cmdline_cstring_from_utf8 (&pname, pname, pool);
			IF_ERROR_RETURN (err, pool, L);

			lua_pushstring (L, pval->data);
			lua_setfield (L, -2, pname);
		}

		lua_settable (L, -3);

	}

	svn_pool_destroy (pool);

	return 1;
}

static int
l_propset (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	const char *path = luaL_checkstring (L, 1);
	const char *propname = luaL_checkstring (L, 2);
	const char *propval = lua_isnil (L, 3) ? NULL : luaL_checkstring (L, 3);
	const char *propname_utf8 = NULL;
	int itable = 4;
	svn_boolean_t recursive = FALSE;
	svn_boolean_t force = FALSE;

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	err = svn_utf_cstring_to_utf8 (&propname_utf8, propname, pool);
	IF_ERROR_RETURN (err, pool, L);

	if (propval != NULL) {
		svn_string_t *sstring = svn_string_create (propval, pool);

		err = svn_client_propset2 (propname_utf8, sstring, path, recursive, force, ctx, pool);
	} else {
		err = svn_client_propset2 (propname_utf8, NULL, path, recursive, force, ctx, pool);
	}
	IF_ERROR_RETURN (err, pool, L);
	
	svn_pool_destroy (pool);

	return 0;
}


static int
l_repos_create (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_repos_t *repos_p;
	
	const char *path = luaL_checkstring (L, 1);

	if (init_pool (&pool) != 0) {
		return init_pool_error (L);
	}

	path = svn_path_canonicalize (path, pool);

	err = svn_repos_create (&repos_p, path, NULL, NULL, NULL, NULL, pool);
	IF_ERROR_RETURN (err, pool, L);

	return 0;
}


static int
l_repos_delete (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	
	const char *path = luaL_checkstring (L, 1);

	if (init_pool (&pool) != 0) {
		return init_pool_error (L);
	}
	
	path = svn_path_canonicalize (path, pool);

	err = svn_repos_delete (path, pool);
	IF_ERROR_RETURN (err, pool, L);

	return 0;
}


static int
l_revprop_get (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	svn_opt_revision_t revision;
	svn_string_t *propval;
	svn_revnum_t rev;
	svn_string_t *printable_val;

	const char *url = luaL_checkstring (L, 1);
	const char *propname = luaL_checkstring (L, 2);
	const char *propname_utf8 = NULL;
		
	if (lua_gettop (L) < 3 || lua_isnil (L, 3)) {
		revision.kind = get_revision_kind (url);
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 3);
	}

	init_function (&ctx, &pool, L);

	url = svn_path_canonicalize (url, pool);

	err = svn_utf_cstring_to_utf8 (&propname_utf8, propname, pool);
	IF_ERROR_RETURN (err, pool, L);

	err = svn_client_revprop_get (propname_utf8, &propval, url, &revision, &rev, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	printable_val = propval;
	if (svn_prop_needs_translation (propname_utf8)) {
		err = svn_subst_detranslate_string (&printable_val, propval, TRUE, pool);
		IF_ERROR_RETURN (err, pool, L);
	}

	lua_pushstring (L, printable_val->data);

	svn_pool_destroy (pool);

	return 1;
}


static int
l_revprop_list (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	apr_hash_t *entries;
	apr_hash_index_t *hi;
	void *val;
	const void *key;
	svn_revnum_t rev;
	svn_opt_revision_t revision;
	
	const char *url = luaL_checkstring (L, 1);

	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		revision.kind = get_revision_kind (url);
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 2);
	}

	init_function (&ctx, &pool, L);

	url = svn_path_canonicalize (url, pool);
	err = svn_client_revprop_list (&entries, url, &revision, &rev, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	lua_newtable (L);

	for (hi = apr_hash_first (pool, entries); hi; hi = apr_hash_next (hi)) {
		const char *pname;
		svn_string_t *pval;

		apr_hash_this (hi, &key, NULL, &val);
	
		pname = key;

		pval = (svn_string_t *) val;
		if (svn_prop_needs_translation (pname)) {
			err = svn_subst_translate_string (&pval, pval, APR_LOCALE_CHARSET, pool);
			IF_ERROR_RETURN (err, pool, L);
		}

		err = svn_cmdline_cstring_from_utf8 (&pname, pname, pool);
		IF_ERROR_RETURN (err, pool, L);

		lua_pushstring (L, pval->data);
		lua_setfield (L, -2, pname);
	}

	svn_pool_destroy (pool);

	return 1;
}


static int
l_revprop_set (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	svn_opt_revision_t revision;
   	svn_revnum_t rev;	
	
	const char *url = luaL_checkstring (L, 1);
	const char *propname = luaL_checkstring (L, 2);
	const char *propval = lua_isnil (L, 3) ? NULL : luaL_checkstring (L, 3);
	const char *propname_utf8 = NULL;
	int itable = 5;
	svn_boolean_t force = FALSE;

	if (lua_gettop (L) < 4 || lua_isnil (L, 4)) {
		revision.kind = get_revision_kind (url);
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 4);
	}

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "force");
		if (lua_isboolean (L, -1)) {
			force = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	url = svn_path_canonicalize (url, pool);

	err = svn_utf_cstring_to_utf8 (&propname_utf8, propname, pool);
	IF_ERROR_RETURN (err, pool, L);

	if (propval != NULL) {
		svn_string_t *sstring = svn_string_create (propval, pool);

		if (svn_prop_needs_translation (propname_utf8)) {
			err = svn_subst_translate_string (&sstring, sstring, APR_LOCALE_CHARSET, pool);
			IF_ERROR_RETURN (err, pool, L);
		}
	
		err = svn_client_revprop_set (propname_utf8, sstring, url, &revision, &rev, force, ctx, pool);
	} else {
		err = svn_client_revprop_set (propname_utf8, NULL, url, &revision, &rev, force, ctx, pool);
	}
	IF_ERROR_RETURN (err, pool, L);
	
	svn_pool_destroy (pool);

	return 0;
}


typedef struct status_bt {
	lua_State *L;
	svn_boolean_t detailed;
	svn_boolean_t show_last_committed;
	svn_boolean_t repos_locks;
	apr_pool_t *pool;
} status_bt;


/* ====================================================================
 * Copyright (c) 2000-2004 CollabNet.  All rights reserved.
 * 
 * The code of "generate_status_code" is from status.c
 * "print_status" is based on the code of the function with the
 * same name in status.c
 */


/* Return the single character representation of STATUS */
static char
generate_status_code(enum svn_wc_status_kind status)
{
  	switch (status)
  	{
	  	case svn_wc_status_none:        return ' ';
		case svn_wc_status_normal:      return ' ';
		case svn_wc_status_added:       return 'A';
		case svn_wc_status_missing:     return '!';
		case svn_wc_status_incomplete:  return '!';
		case svn_wc_status_deleted:     return 'D';
		case svn_wc_status_replaced:    return 'R';
		case svn_wc_status_modified:    return 'M';
		case svn_wc_status_merged:      return 'G';
		case svn_wc_status_conflicted:  return 'C';
		case svn_wc_status_obstructed:  return '~';
		case svn_wc_status_ignored:     return 'I';
		case svn_wc_status_external:    return 'X';
		case svn_wc_status_unversioned: return '?';
		default:                        return '?';
	}
}


/* Print STATUS and PATH in a format determined by DETAILED and
   SHOW_LAST_COMMITTED. */
static svn_error_t *
print_status(const char *path,
             svn_boolean_t detailed,
             svn_boolean_t show_last_committed,
             svn_boolean_t repos_locks,
             svn_wc_status2_t *status,
             lua_State *L,
			 apr_pool_t *pool)
{	
	const char *info;
	
	if (detailed)
	{
		char ood_status, lock_status;
		const char *working_rev;

		if (! status->entry)
			working_rev = "";
		else if (! SVN_IS_VALID_REVNUM(status->entry->revision))
			working_rev = " ? ";
		else if (status->copied)
			working_rev = "-";
		else
			working_rev = apr_psprintf(pool, "%ld", status->entry->revision);

		if (status->repos_text_status != svn_wc_status_none
				|| status->repos_prop_status != svn_wc_status_none)
			ood_status = '*';
		else
			ood_status = ' ';

		if (repos_locks)
		{
		   	if (status->repos_lock)
		   	{
			 	if (status->entry && status->entry->lock_token)
			 	{
			   		if (strcmp(status->repos_lock->token, status->entry->lock_token)
					 		== 0)
						lock_status = 'K';
					else
						lock_status = 'T';
				}
				else
					lock_status = 'O';
			}
			else if (status->entry && status->entry->lock_token)
				lock_status = 'B';
			else
				lock_status = ' ';
		}
		else
			lock_status = (status->entry && status->entry->lock_token) ? 'K' : ' ';


		if (show_last_committed)
		{
		   	const char *commit_rev;
			const char *commit_author;

			if (status->entry && SVN_IS_VALID_REVNUM(status->entry->cmt_rev))
				commit_rev = apr_psprintf(pool, "%ld", status->entry->cmt_rev);
			else if (status->entry) 
				commit_rev = " ? ";
			else 
				commit_rev = "";


			if (status->entry && status->entry->cmt_author)
				commit_author = status->entry->cmt_author;
			else if (status->entry)
				commit_author = " ? ";
			else
				commit_author = "";


			info = apr_psprintf(pool, 			
					"%c%c%c%c%c%c %c   %6s   %6s %-12s %s",
					generate_status_code(status->text_status),
					generate_status_code(status->prop_status),
					status->locked ? 'L' : ' ',
					status->copied ? '+' : ' ',
					status->switched ? 'S' : ' ',
					lock_status,
					ood_status,
					working_rev,
					commit_rev,
					commit_author,
					path);

		}
		else {
			info = apr_psprintf(pool, 
					"%c%c%c%c%c%c %c   %6s   %s\n",
					generate_status_code(status->text_status),
					generate_status_code(status->prop_status),
					status->locked ? 'L' : ' ',
					status->copied ? '+' : ' ',
					status->switched ? 'S' : ' ',
					lock_status,
					ood_status,
					working_rev,
					path);
		}
	}
	else {
		info = apr_psprintf(pool,
			   	"%c%c%c%c%c%c %s\n",
				generate_status_code(status->text_status),
				generate_status_code(status->prop_status),
				status->locked ? 'L' : ' ',
				status->copied ? '+' : ' ',
				status->switched ? 'S' : ' ',
				((status->entry && status->entry->lock_token)
				 ? 'K' : ' '),
				path);
	}

	lua_pushstring (L, info);
	lua_setfield (L, -2, path);

	return SVN_NO_ERROR;
}


static void
status_func (void *baton, const char *path, svn_wc_status2_t *status) {
	struct status_bt *sb = baton;
	apr_pool_t *pool = ((status_bt *)baton)->pool;
	
	print_status (svn_path_local_style (path, pool), 
			      sb->detailed, sb->show_last_committed, sb->repos_locks,
				  status, ((status_bt *) baton)->L, pool);			
}


static int
l_status (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	svn_revnum_t rev;	
	status_bt baton;
	svn_opt_revision_t revision;
	
	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
	int itable = 3;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t verbose = FALSE;
	svn_boolean_t show_updates = FALSE;
	svn_boolean_t no_ignore = FALSE;
	svn_boolean_t ignore_externals = FALSE;

	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		revision.kind = svn_opt_revision_head;
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 2);
	}

	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "verbose");
		if (lua_isboolean (L, -1)) {
			verbose = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "show_updates");
		if (lua_isboolean (L, -1)) {
			show_updates = lua_toboolean (L, -1);
		}

		lua_getfield (L, itable, "no_ignore");
		if (lua_isboolean (L, -1)) {
			no_ignore = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "ignore_externals");
		if (lua_isboolean (L, -1)) {
			ignore_externals = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	baton.L = L;
	baton.detailed = (verbose || show_updates);
	baton.show_last_committed = verbose;
	baton.repos_locks = show_updates;
	baton.pool = pool;

	lua_newtable (L);

	err = svn_client_status2 (&rev, path, &revision, status_func, &baton, 
			                  recursive, verbose, show_updates, no_ignore, ignore_externals, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);

	svn_pool_destroy (pool);

	return 1;
}


static int
l_update (lua_State *L) {
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;
	
	apr_array_header_t *array;
	svn_opt_revision_t revision;
	
	const char *path = (lua_gettop (L) < 1 || lua_isnil (L, 1)) ? "" : luaL_checkstring (L, 1);
	int itable = 3;
	svn_boolean_t recursive = TRUE;
	svn_boolean_t ignore_externals = FALSE;
	apr_array_header_t *result_revs = NULL;

	if (lua_gettop (L) < 2 || lua_isnil (L, 2)) {
		revision.kind = svn_opt_revision_head;
	} else {
		revision.kind = svn_opt_revision_number;
		revision.value.number = lua_tointeger (L, 2);
	}
	if (lua_gettop (L) >= itable && lua_istable (L, itable)) {
		
		lua_getfield (L, itable, "recursive");
		if (lua_isboolean (L, -1)) {
			recursive = lua_toboolean (L, -1);
		}
		
		lua_getfield (L, itable, "ignore_externals");
		if (lua_isboolean (L, -1)) {
			ignore_externals = lua_toboolean (L, -1);
		}
	} 

	init_function (&ctx, &pool, L);

	path = svn_path_canonicalize (path, pool);

	array = apr_array_make (pool, 1, sizeof (const char *));
	(*((const char **) apr_array_push (array))) = path;

	err = svn_client_update2 (&result_revs, array, &revision, recursive, ignore_externals, ctx, pool);
	IF_ERROR_RETURN (err, pool, L);	

	if (result_revs == NULL) {
		lua_pushnil (L);
	} else {
		int rev = (int) ((int **) (result_revs->elts))[0];
		lua_pushinteger (L, rev);
	}

	svn_pool_destroy (pool);

	return 1;
}


static const struct luaL_Reg svn [] = {
	{"add", l_add},
	{"cat", l_cat},
	{"checkout", l_checkout},
	{"commit", l_commit},
	{"cleanup", l_cleanup},
	{"copy", l_copy},
	{"delete", l_delete},
	{"diff", l_diff},
	{"import", l_import},
	{"list", l_list},
	{"log", l_log},
	{"merge", l_merge},
	{"mkdir", l_mkdir},
	{"move", l_move},
	{"propget", l_propget},
	{"proplist", l_proplist},
	{"propset", l_propset},
	{"repos_create", l_repos_create},
	{"repos_delete", l_repos_delete},
	{"revprop_get", l_revprop_get},
	{"revprop_list", l_revprop_list},
	{"revprop_set", l_revprop_set},
	{"status", l_status},
	{"update", l_update},
	{NULL, NULL}
};

LUASVN_API
luaopen_svn (lua_State *L) {
	luaL_register (L, "svn", svn);
	return 1;
}


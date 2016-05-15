#ifndef IOBase__H_
#define IOBase__H_

#pragma once

namespace DuiLib
{
#ifndef FILE_BEGIN
    #define FILE_BEGIN        0
#endif

#ifndef FILE_CURRENT
    #define FILE_CURRENT    1
#endif

#ifndef FILE_END
    #define FILE_END        2
#endif

	class UILIB_API IOBase
	{
	public:
		static const int NORMAL_SUCCESS = 0;
		static const int NORMAL_FAILED = -1;
		struct io_pos_info
		{
		public:
			io_pos_info(unsigned int n_begin = 0, unsigned int n_len = 0);
			virtual ~io_pos_info();
			unsigned int get_begin() const;
			unsigned int get_len() const;
			unsigned int get_end() const;
			void set_info(unsigned int n_begin, unsigned int n_len);
			bool valid() const;
			unsigned int size() const;
			bool is_sub_pos(const io_pos_info& pos) const;
			bool is_equal_pos(const io_pos_info& pos) const;
		private:
			unsigned int mn_begin;
			unsigned int mn_len;
		};
	public:
		IOBase() {}
		virtual ~IOBase() {}
		virtual bool is_dir_exists(const char* p_dir) = 0;
		virtual int make_dir(const char* p_dir) = 0;
		virtual bool is_file_exists(const char* p_name) = 0;
	    virtual int open(const char* p_name, bool b_readonly) = 0;
	    virtual int close() = 0;								
	    // read / write, will change current position
		//return : 0 for success, -1 for failed
	    virtual int read(void* p_buffer, unsigned int n_bytes_2_read, unsigned int* p_bytes_read) = 0;
	    virtual int write(const void* p_buffer, unsigned int n_bytes_2_write, unsigned int* p_bytes_written) = 0;
		virtual int readAll(void** p_buffer, unsigned int* p_bytes_read) = 0;
	    // seek
	    virtual int seek(int n_distance, unsigned int n_move_mode) = 0;		
	    // creation / destruction
	    virtual int create(const char* p_name) = 0;		
		virtual int destroy() = 0;
	    virtual int set_eof() = 0;
	    virtual int get_position() = 0;
	    virtual int get_size() = 0;
	    virtual int get_name(char* p_buffer) = 0;
		virtual bool is_open() = 0;
		virtual int flush() = 0;
		virtual int get_lasterror() = 0;
	};

	
	typedef std::vector<IOBase::io_pos_info> position_container;
	typedef position_container::iterator position_iter;

	class UILIB_API IOHelper
	{
	public:
		IOHelper(){ mp_io = NULL; }
		IOHelper(IOBase* p_io);
		~IOHelper();

		template<typename T>
		static inline T* newIO()
		{
			return new T();
		}
		template<typename T>
		static inline void delIO(T*& p_io)
		{
			if (p_io)
			{
				delete p_io;
				p_io = NULL;
			}
		}
	public:
		virtual bool is_dir_exists(const char* p_dir);
		virtual int make_dir(const char* p_dir);
		virtual bool is_file_exists(const char* p_name);
	    virtual int open(const char* p_name, bool b_readonly);
	    virtual int close();
	    // read / write, will change current position
		//return : 0 for success, -1 for failed
	    virtual int read(void* p_buffer, unsigned int n_bytes_2_read, unsigned int* p_bytes_read);
	    virtual int write(const void* p_buffer, unsigned int n_bytes_2_write, unsigned int* p_bytes_written);
		virtual int readAll(void** p_buffer, unsigned int* p_bytes_read);

	    virtual int seek(int n_distance, unsigned int n_move_mode);
	    
	    virtual int create(const char* p_name);
		virtual int destroy();
	    virtual int set_eof();
	    virtual int get_position();
	    virtual int get_size();
	    virtual int get_name(char* p_buffer);
		virtual bool is_open();
		virtual int flush();
		virtual int get_lasterror();
	private:
		IOBase* mp_io;
	};

}

#endif//IOBase__H_

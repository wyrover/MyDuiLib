#ifndef WinIO__H_
#define WinIO__H_

#pragma once

namespace DuiLib
{
	class UILIB_API WinIO : public IOBase
	{
	public:
		WinIO();
		virtual ~WinIO();
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
		// seek
	    virtual int seek(int n_distance, unsigned int n_move_mode);		
	    // creation / destruction
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
		HANDLE	mh_file;
	    char	ms_file_name[MAX_PATH];
	    bool	mb_read_only;
	};
}

#endif//WinIO__H_
#include "UIlib.h"
#include "WinIO.h"

#include <windows.h>
#include <cassert>
#include <sys/types.h>  
#include <sys/stat.h>
#include <direct.h>

namespace DuiLib
{
	WinIO::WinIO()
	{
		mh_file = INVALID_HANDLE_VALUE;
    	memset(ms_file_name, 0x0, MAX_PATH * sizeof(char));
    	mb_read_only = false;
	}
	WinIO::~WinIO()
	{
		close();
	}
	bool WinIO::is_dir_exists(const char* p_dir)
	{
		assert(p_dir != NULL);
		bool b_result = false;
		WIN32_FIND_DATAA wfd;
		memset(&wfd, 0x0, sizeof(wfd));
		HANDLE hFind = FindFirstFileA(p_dir, &wfd);
		if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			b_result = true;   
		}
		if (hFind != INVALID_HANDLE_VALUE)
			FindClose(hFind);

		return b_result;
	}
	int WinIO::make_dir(const char* p_dir)
	{
		if(is_dir_exists(p_dir))
			return IOBase::NORMAL_SUCCESS;
		return _mkdir(p_dir) ? IOBase::NORMAL_SUCCESS : IOBase::NORMAL_FAILED;
	}
	bool WinIO::is_file_exists(const char* p_name)
	{
		assert(p_name);
		if (p_name != NULL && strlen(p_name) > 0)
		{
			struct _stat32 stat_info;
			return _stat32(p_name, &stat_info) == 0;
		}
		else
			return false;
	}
    int WinIO::open(const char* p_name, bool b_readonly)
    {
    	assert(p_name != NULL);
		assert(strlen(p_name) < MAX_PATH);
	    close();
		mb_read_only = b_readonly;
		if (mb_read_only)
			mh_file = ::CreateFileA(p_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		else
			mh_file = ::CreateFileA(p_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		
		if (mh_file == INVALID_HANDLE_VALUE) 
			 return IOBase::NORMAL_FAILED;
		strcpy_s(ms_file_name, MAX_PATH, p_name);		//?????ļ???
		return IOBase::NORMAL_SUCCESS;
    }
    int WinIO::close()
    {
    	if (mh_file != INVALID_HANDLE_VALUE)
		{
			BOOL bret = ::CloseHandle(mh_file);
			assert(bret);
			mh_file = INVALID_HANDLE_VALUE;
		}
		return IOBase::NORMAL_SUCCESS;
    }
    // read / write, will change current position
	//return : 0 for success, -1 for failed
    int WinIO::read(void* p_buffer, unsigned int n_bytes_2_read, unsigned int* p_bytes_read)
    {
    	unsigned int n_total_bytes_read = 0;
	    int n_bytes_left = n_bytes_2_read;
	    BOOL b_result = TRUE;
	    unsigned char* p_buf = (unsigned char*)p_buffer;

	    *p_bytes_read = 1;
		//??????whileΪ?˽???ʲô?IO?????
	    while ((n_bytes_left > 0) && (*p_bytes_read > 0) && b_result)		//??????????ʣ?? && ?ϴζ?>0 && ?ϴζ?????
	    {
	        b_result = ::ReadFile(mh_file, &p_buf[n_bytes_2_read - n_bytes_left], n_bytes_left, (unsigned long*)p_bytes_read, NULL);
	        if (b_result == TRUE)
	        {
	            n_bytes_left -= *p_bytes_read;
	            n_total_bytes_read += *p_bytes_read;
	        }
	    }
	    *p_bytes_read = n_total_bytes_read;
		return b_result == FALSE ? IOBase::NORMAL_FAILED : IOBase::NORMAL_SUCCESS;
    }
    int WinIO::write(const void* p_buffer, unsigned int n_bytes_2_write, unsigned int* p_bytes_written)
    {
    	BOOL b_result = ::WriteFile(mh_file, p_buffer, n_bytes_2_write, (unsigned long*)p_bytes_written, NULL);
	    if ((b_result == FALSE) || (*p_bytes_written != n_bytes_2_write))
			return IOBase::NORMAL_FAILED;
	    else
			return IOBase::NORMAL_SUCCESS;
    }
    
    int WinIO::seek(int n_distance, unsigned int n_move_mode)
    {
    	::SetFilePointer(mh_file, n_distance, NULL, n_move_mode);
		return IOBase::NORMAL_SUCCESS;
    }
    
    int WinIO::create(const char* p_name)
    {
    	close();
		//?????ļ?
		mh_file = ::CreateFileA(p_name, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	    if (mh_file == INVALID_HANDLE_VALUE) 
			return IOBase::NORMAL_FAILED;
	    mb_read_only = false;
		strcpy_s(ms_file_name, MAX_PATH, p_name);
		return IOBase::NORMAL_SUCCESS;
    }
	int WinIO::destroy()
	{
		close();
		return ::DeleteFileA(ms_file_name) ? IOBase::NORMAL_SUCCESS : IOBase::NORMAL_FAILED;
	}
    int WinIO::set_eof()
    {
    	BOOL b_result = ::SetEndOfFile(mh_file);			//???????ض??ļ?,????????,ֱ??Ӱ??Ӳ???ļ?
		return b_result == FALSE ? IOBase::NORMAL_FAILED : IOBase::NORMAL_SUCCESS;
    }
    int WinIO::get_position()
    {
    	return static_cast<int>(::SetFilePointer(mh_file, 0, NULL, FILE_CURRENT));
    }
    int WinIO::get_size()
    {
    	return static_cast<int>(::GetFileSize(mh_file, NULL));
    }
    int WinIO::get_name(char* p_buffer)
    {
    	strcpy_s(p_buffer, MAX_PATH, ms_file_name);
		return IOBase::NORMAL_SUCCESS;
    }
	bool WinIO::is_open()
	{
		return mh_file != INVALID_HANDLE_VALUE;
	}
	int WinIO::flush()
	{
		return ::FlushFileBuffers(mh_file) ? IOBase::NORMAL_SUCCESS : IOBase::NORMAL_FAILED;
	}
	int WinIO::get_lasterror()
	{
		return (int)::GetLastError();
	}
}
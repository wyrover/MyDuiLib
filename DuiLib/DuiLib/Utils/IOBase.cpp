#include "UIlib.h"
#include "IOBase.h"


namespace DuiLib
{

	IOBase::io_pos_info::io_pos_info(unsigned int n_begin, unsigned int n_len)
	{
		mn_begin = n_begin;
		mn_len = n_len;
	}

	IOBase::io_pos_info::~io_pos_info()
	{
	}

	unsigned int IOBase::io_pos_info::get_begin() const
	{
		return mn_begin;
	}

	unsigned int IOBase::io_pos_info::get_len() const
	{
		return mn_len;
	}

	unsigned int IOBase::io_pos_info::get_end() const
	{
		return get_begin() + get_len();
	}

	void IOBase::io_pos_info::set_info(unsigned int n_begin, unsigned int n_len)
	{
		mn_begin = n_begin;
		mn_len = n_len;
	}

	bool IOBase::io_pos_info::valid() const
	{
		return mn_len > 0;
	}

	unsigned int IOBase::io_pos_info::size() const
	{
		return get_len();
	}

	bool IOBase::io_pos_info::is_sub_pos(const io_pos_info& pos) const
	{
		bool b_result = false;
		if (pos.get_begin() >= get_begin() && pos.size() <= size() && pos.get_end() <= get_end())
			b_result = true;
		return b_result;
	}

	bool IOBase::io_pos_info::is_equal_pos(const io_pos_info& pos) const
	{
		return pos.get_begin() == get_begin() && pos.size() == size();
	}

	////////////////////////////////////
	IOHelper::IOHelper(IOBase* p_io)
	{
	//	destroy();
		mp_io = p_io;
	}
	IOHelper::~IOHelper()
	{
		//destroy();
		//mp_io = NULL;
	}
	bool IOHelper::is_dir_exists(const char* p_dir)
	{
		if (mp_io)
			return mp_io->is_dir_exists(p_dir);
		return false;
	}
	int IOHelper::make_dir(const char* p_dir)
	{
		if (mp_io)
			return mp_io->make_dir(p_dir);
		return -1;
	}
	bool IOHelper::is_file_exists(const char* p_name)
	{
		if (mp_io)
			return mp_io->is_file_exists(p_name);
		return false;
	}
    int IOHelper::open(const char* p_name, bool b_readonly)
    {
    	if (mp_io)
			return mp_io->open(p_name,b_readonly);
    	return -1;
    }
    int IOHelper::close()
    {
    	if (mp_io)
			return mp_io->close();
    	return 0;
    }
    // read / write, will change current position
	//return : 0 for success, -1 for failed
    int IOHelper::read(void* p_buffer, unsigned int n_bytes_2_read, unsigned int* p_bytes_read)
    {
    	if (mp_io)
			return mp_io->read(p_buffer,n_bytes_2_read,p_bytes_read);
    	return -1;
    }
    int IOHelper::write(const void* p_buffer, unsigned int n_bytes_2_write, unsigned int* p_bytes_written)
    {
    	if (mp_io)
			return mp_io->write(p_buffer,n_bytes_2_write,p_bytes_written);
    	return -1;
    }
	int IOHelper::readAll(void** p_buffer, unsigned int* p_bytes_read)
	{
		if (mp_io)
		{
			return mp_io->readAll(p_buffer, p_bytes_read);
		}
		*p_buffer = NULL;
		*p_bytes_read = 0;
		return -1;
	}
    
    int IOHelper::seek(int n_distance, unsigned int n_move_mode)
    {
    	if (mp_io)
			return mp_io->seek(n_distance,n_move_mode);
    	return 0;
    }
    
    int IOHelper::create(const char* p_name)
    {
    	if (mp_io)
			return mp_io->create(p_name);
    	return -1;
    }
	int IOHelper::destroy()
	{
		if (mp_io)
			return mp_io->destroy();
		return 0;
	}
    int IOHelper::set_eof()
    {
    	if (mp_io)
			return mp_io->set_eof();
    	return 0;
    }
    int IOHelper::get_position()
    {
    	if (mp_io)
			return mp_io->get_position();
    	return 0;
    }
    int IOHelper::get_size()
    {
    	if (mp_io)
			return mp_io->get_size();
    	return 0;
    }
    int IOHelper::get_name(char* p_buffer)
    {
    	if (mp_io)
			return mp_io->get_name(p_buffer);
    	return 0;
    }
	bool IOHelper::is_open()
	{
		if (mp_io)
			return mp_io->is_open();
		return false;
	}
	int IOHelper::flush()
	{
		if (mp_io)
			return mp_io->flush();
		return 0;
	}
	int IOHelper::get_lasterror()
	{
		if (mp_io)
			return mp_io->get_lasterror();
		return 0;
	}

}

#ifndef DuiLock__H_
#define DuiLock__H_
#pragma once

namespace DuiLib
{
	//轻量级锁，不能用于waitforXXXobject，不能跨进程，非内核对象
	class UILIB_API critical_session : public ILock
	{
	public:
		critical_session(/*CLogObj* p_log = NULL*/);
		virtual ~critical_session();
		virtual bool lock();
		virtual bool unlock();
		bool try_lock();
		int get_ref() const;
		virtual int lock_ex();
		virtual int unlock_ex();
	private:
		struct critical_impl;
		critical_impl* mp_impl;
		volatile int mn_ref;
	/*	CLogObj* mp_log;*/
	};

	//互斥锁
	class UILIB_API mutex_lock : public ILock
	{
	public:
		mutex_lock();
		virtual ~mutex_lock();
		virtual bool lock();
		virtual bool unlock();
		//返回true为等待到信号，false为超时
		bool wait(unsigned int n_seconds);
		virtual int lock_ex();
		virtual int unlock_ex();
	private:
		struct mutex_impl;
		mutex_impl* mp_impl;
	};

	//信号事件锁
	class UILIB_API signal_event
	{
	public:
		signal_event(bool b_signal = false, const TCHAR* p_name = NULL);
		~signal_event();
		void set_signal();
		void reset_signal();
		//返回true为发信号，返回false为超时
		bool wait(unsigned int n_mill_seconds);
		void* get_handle();
	private:
		struct event_impl;
		event_impl* mp_impl;
	};
}

#endif//DuiLock__H_
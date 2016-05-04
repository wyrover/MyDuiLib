#ifndef TC_Thread_H
#define TC_Thread_H
#pragma once

#include <exception>
#include <string>

#include <pthread.h>

namespace TC
{
	/////////////////////////////////////////////////
	class TC_Exception : public std::exception
	{
	public:
		TC_Exception(const char* err) : std::exception(err){};
		TC_Exception(std::string& err) : std::exception(err.c_str()){};
	};

	class TC_ThreadMutex
	{
	public:
		TC_ThreadMutex()
		{
			pthread_mutex_init(&mtx, NULL);
		}

		~TC_ThreadMutex()
		{
			pthread_mutex_destroy(&mtx);
		}

		inline void Lock()
		{
			pthread_mutex_lock(&mtx);
		}

		inline void UnLock()
		{
			pthread_mutex_unlock(&mtx);
		}

	private:
		pthread_mutex_t mtx;
	};

	class TC_ThreadLock
	{
	public:
		TC_ThreadLock(TC_ThreadMutex* mtx) :_mutex(mtx)
		{
			_mutex->Lock();
		}
		~TC_ThreadLock()
		{
			_mutex->UnLock();
		}
	private:
		TC_ThreadMutex* _mutex;
	};

	class TC_ThreadControl
	{
	public:
		TC_ThreadControl(pthread_t tid) : _tid(tid){};
	private:
		pthread_t _tid;
	};

	class TC_Runable
	{
	public:
		virtual ~TC_Runable(){};
		virtual void run() = 0;
	};

	/**
	* TC_Thread
	* 线程基类，所有自定义线程继承于该类，同时实现run接口即可
	*
	*/
	class TC_Thread : public TC_Runable
	{
	public:

		/**
		* @brief  构造函数
		*/
		TC_Thread(const char* name = "") : _running(false)
		{
			memset(_name, 0, sizeof(_name));
			memcpy(_name, name, sizeof(_name));
		}

		/**
		* @brief  析构函数
		*/
		virtual ~TC_Thread(){};

		/**
		* @brief  线程运行
		*/
		TC_ThreadControl start(){
			TC_ThreadLock sync(&_mutex);
			{
				if (_running)
				{
					throw TC_Exception("[TC_Thread::start] thread has start");
				}
				int ret = pthread_create(&_tid, 0, (void *(*)(void *))& threadEntry, (void *) this);

				if (ret != 0)
				{
					throw TC_Exception("[TC_Thread::start] thread start error");
				}
			}

			return TC_ThreadControl(_tid);
		}

		/**
		* @brief  获取线程控制类
		*
		* @return ThreadControl
		*/
		TC_ThreadControl getThreadControl() const{
			return TC_ThreadControl(_tid);
		}

		/**
		* @brief  线程是否存活.
		*
		* @return bool 存活返回true，否则返回false
		*/
		bool isAlive() const{
			return _running;
		}

		/**
		* @brief  获取线程id.
		*
		* @return pthread_t 线程id
		*/
		pthread_t id() { return _tid; }

	protected:

		/**
		* @brief  静态函数, 线程入口.
		*
		* @param pThread 线程对象
		*/
		static void threadEntry(TC_Thread *pThread){
			TC_ThreadLock lock(&pThread->_mutex);
			{
				pThread->_running = true;
				try
				{
					pThread->run();
				}
				catch (...)
				{
					pThread->_running = false;
					throw;
				}
				pThread->_running = false;
			}
		}

		/**
		* @brief  运行
		*/
		virtual void run() = 0;

	protected:
		/**
		* 线程名字
		*/
		char            _name[256];
		/**
		* 是否在运行
		*/
		bool            _running;

		/**
		* 线程ID
		*/
		pthread_t       _tid;

		/**
		* 线程锁
		*/
		TC_ThreadMutex  _mutex;
	};

}
#endif//

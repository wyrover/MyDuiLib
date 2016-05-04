
#include <pthread.h>
#pragma comment(lib,"x64/pthreadVC2.lib")


class TC_Runable
{
public:
	virtual ~TC_Runable(){};
	virtual void run() = 0;
};

class TC_ThreadControl;
class TC_ThreadLock;

/**
* 线程基类.
* 线程基类，所有自定义线程继承于该类，同时实现run接口即可,
* 可以通过TC_ThreadContorl管理线程。
*/
class TC_Thread : public TC_Runable
{
public:

	/**
	* @brief  构造函数
	*/
	TC_Thread() : : _running( false), _tid(-1)
	{}

	/**
	* @brief  析构函数
	*/
	virtual ~TC_Thread(){};

	/**
	* @brief  线程运行
	*/
	TC_ThreadControl start(){
		TC_ThreadLock::Lock sync(_lock);
		if(_running)
	    {
	        throw TC_ThreadThreadControl_Exception("[TC_Thread::start] thread has start");
	    }
	    int ret = pthread_create(&_tid , 0, ( void *(*)( void *))& threadEntry, ( void *) this);

	    if(ret != 0)
	    {
	        throw TC_ThreadThreadControl_Exception("[TC_Thread::start] thread start error", ret);
	    }
	    _lock.wait();

	    return TC_ThreadControl(_tid);
	}

	/**
	* @brief  获取线程控制类.
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
		pThread->_running = true;

		{
        	TC_ThreadLock::Lock sync(pThread-> _lock);
        	pThread-> _lock.notifyAll();
    	}
    	
    	try
    	{
    		pThread->run();
    	}
    	catch(...)
    	{
    		pThread-> _running = false;
    		throw;
    	}
    	pThread->_running = false;
	}

	/**
	* @brief  运行
	*/
	virtual void run() = 0;

protected:
	/**
	* 是否在运行
	*/
	bool            _running;

	/**
	* 线程ID
	*/
	pthread_t      _tid;

	/**
	* 线程锁
	*/
	TC_ThreadLock   _lock;
};

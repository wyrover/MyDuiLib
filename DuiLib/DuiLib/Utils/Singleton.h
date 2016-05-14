#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#pragma once

using namespace std;

namespace DuiLib
{
#define DECLARE_SINGLETON_CLASS( type ) \
	friend class auto_ptr< type >; \
	friend class Singleton< type >;

	template <class T>
	class Singleton
	{
	public:
		static inline T* Instance()
		{
			if (0 == _instance.get())
			{
				LockHelper lock(m_pcs);
				{
					if (0 == _instance.get())
					{
						_instance.reset(new T);
					}
				}
			}
			return _instance.get();
		}
		Singleton(void)
		{
			if (NULL == m_pcs)
			{
				m_pcs = LockHelper::newLock<critical_session>();
			}
		}
		virtual ~Singleton(void)
		{
			LockHelper::delLock(m_pcs);
			//if( 0 != _instance.get() ) _instance.reset();
		}
	private:

		Singleton(const Singleton&) {}
		Singleton& operator= (const Singleton&) { return *this; }
	protected:
#pragma warning(push)
#pragma warning(disable:4251)
#pragma warning(disable:4661)
		static auto_ptr<T> _instance;
#pragma warning(pop) 

		static ILock* m_pcs;
	};

	template <class T>
	auto_ptr<T> Singleton<T>::_instance;

	template <class T>
	ILock* Singleton<T>::m_pcs = NULL;
}
#endif
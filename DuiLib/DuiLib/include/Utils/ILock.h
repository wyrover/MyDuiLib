#ifndef ILock__H_
#define ILock__H_

#pragma once

namespace DuiLib
{
	class UILIB_API ILock
	{
	public:
		ILock() {}
		virtual ~ILock() {}
		virtual bool lock() = 0;
		virtual bool unlock() = 0;
		virtual int lock_ex() { return 0; }
		virtual int unlock_ex() { return 0; }
	};

	class UILIB_API LockHelper
	{
	public:
		LockHelper(ILock* p_lock);
		~LockHelper();
		void unlock();

		template<typename T>
		static inline T* newLock()
		{
			return new T();
		}
		template<typename T>
		static inline void delLock(T*& p_lock)
		{
			if (p_lock)
			{
				delete p_lock;
				p_lock = NULL;
			}
		}
	private:
		ILock* mp_lock;
	};

}


#endif//ILock__H_
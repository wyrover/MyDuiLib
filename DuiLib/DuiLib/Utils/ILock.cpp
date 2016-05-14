#include "UIlib.h"
#include "ILock.h"

namespace DuiLib
{
	LockHelper::LockHelper(ILock* p_lock)
	{
		mp_lock = p_lock;
		if (mp_lock != NULL)
			mp_lock->lock();
	}

	LockHelper::~LockHelper()
	{
		unlock();
	}

	void LockHelper::unlock()
	{
		if (mp_lock != NULL)
		{
			mp_lock->unlock();
			mp_lock = NULL;
		}
	}
	
}
// PThread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma comment(lib,"pthreadVC2.lib")

#include "include/TC_Thread.h"
#include <iostream>
using namespace std;

class TC_Thread_User : public TC::TC_Thread
{
public:
	TC_Thread_User() : TC::TC_Thread() {};
protected:
	void run()
	{
		cout << "Hello PThread" << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	TC_Thread_User* pUserThread = new TC_Thread_User;
	pUserThread->start();

	return 0;
}


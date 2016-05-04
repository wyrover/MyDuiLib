#ifndef  TASK_H
#define TASK_H
#pragma once
#include <vector>
using namespace std;

class MakeTaskId
{
public:
	MakeTaskId();
	operator int() const;
private:
	static int id;
};

enum EM_STATUS
{
	Waiting,
	Running,
};

enum EM_RESULT
{
	None,
	Error,
	Cancled,
	Finished,
};

class ITaskRespond;

class Task
{
private:
	int taskId;
	void*data;
	bool working;
	EM_STATUS status;
	ITaskRespond* respond;
public:
	Task();
	Task(int id,void* d,ITaskRespond* res = 0);
	virtual ~Task();
public:
	int TaskID() const;
	bool IsWorking() const;
	void SetWorking(bool bWorking);
	EM_STATUS Status() const;
	void SetStatus(EM_STATUS status);
};

class ITaskRespond
{
public:
	virtual void onTaskError(int id,Task* task) = 0;
	virtual void onTaskFinish(int id,Task* task) = 0;
	virtual void onTaskBegin(int id,Task* task) = 0;
};


class TaskHelper
{
public:
	int AddTask(Task& task);
	int StartTask(int id);
	int CancleTask(int id);
protected:
	int _RemoveTask(int id);
	int _FindTask(int id);
private:
	std::vector<Task> m_taskList;
};

#endif//TASK_H

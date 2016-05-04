#include "Task.h"

//////////////////////////////////////////////////////////
int MakeTaskId::id = 0;

MakeTaskId::MakeTaskId()
{
	id++;
}

MakeTaskId::operator int() const
{
	return id;
}
//////////////////////////////////////////////////////////
Task::Task()
{
	taskId = 0;
	data = 0;
	respond = 0;
	working = false;
}
Task::Task(int id,void* d,ITaskRespond* res)
{
	taskId = id;
	data = d;
	respond = res;
	working = false;
}
Task::~Task()
{
}
int Task::TaskID() const
{
	return taskId;
}
bool Task::IsWorking() const
{
	return working;
}
void Task::SetWorking(bool bWorking)
{
	working = bWorking;
}
EM_STATUS Task::Status() const
{
	return status;
}
void Task::SetStatus(EM_STATUS status)
{
	this->status = status;
}
//////////////////////////////////////////////////////////
int TaskHelper::AddTask(Task& task)
{
	m_taskList.push_back(task);
}

int TaskHelper::_RemoveTask(int id)
{
	std::vector<Task>::iterator it = m_taskList.begin();
	for(;it!=m_taskList.end();++it)
	{
		Task task = *it;
		if(task.TaskID() == id)
		{
			m_taskList.erase(it);
			break;
		}
	}
}

int TaskHelper::_FindTask(int id)
{
	int nPos = -1;
	std::vector<Task>::iterator it = m_taskList.begin();
	for(;it!=m_taskList.end();++it)
	{
		nPos ++;
		if(it->TaskID() == id)
		{
			break;
		}
	}	
	return nPos;
}

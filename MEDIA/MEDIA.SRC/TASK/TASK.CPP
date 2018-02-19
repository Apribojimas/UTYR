#include "proto.hpp"
#include "vcmd.hpp"

extern int isSystemInfo;

#ifndef _TASK
#define _TASK

#include "bag.hpp"
#include "filter.hpp"

class Task
{
  Bag *TaskBag;
  unsigned int FilterNumber;
 public:
  Task(void);
  ~Task();

  void Run(void);
  int Add(Filter *NewFilter);
  void Terminate(int FilterNr);
  int GetFilterCount(void);
  int GetFilterPercent(int i);
};
#endif

Task :: Task(void)
{
 TaskBag = new Bag(DELETE);
 FilterNumber = 0;
}

Task :: ~Task()
{
 delete TaskBag;
}

int Task :: Add(Filter *NewFilter)
{
 *TaskBag + NewFilter;
 NewFilter -> RegisterNumber = ++FilterNumber;

 if(isSystemInfo)
  SendMSGCmd(TASK_CHANGE_FILTER);
 return  NewFilter -> RegisterNumber;
}

void Task :: Run(void)
{
 static int i = 0;
 Filter *pFilter;

 if(TaskBag->GetBagSize())
 {
  pFilter = (Filter*)TaskBag->GetItem(0);
  pFilter->Run();
  TaskBag->PutToTail(0);

  if(isSystemInfo)
   {
    if(i >= TaskBag->GetBagSize())
     {
      SendMSGCmd(TASK_CHANGE_FILTER);
      i = 0;
     }
    i ++;
   }
 }
}

void Task :: Terminate(int FilterNr)
{
 int i;
 int size=TaskBag->GetBagSize();

 if(size == 0)
  FilterNumber = 0;

 for(i=0;i<size;i++)
  if(TaskBag->GetItem(i)->RegisterNumber == FilterNr )
  {
   *TaskBag - i;

   if(isSystemInfo)
    SendMSGCmd(TASK_CHANGE_FILTER);
   break;
  }
}

int Task :: GetFilterCount(void)
{
 if(TaskBag)
  return TaskBag->GetBagSize();
return 0;
}

int Task :: GetFilterPercent(int i)
{
 Filter *pFilter;

 pFilter = (Filter*)TaskBag->GetItem(i);
 if(pFilter)
   return pFilter->GetPercent();

return 0;
}

Task *FilterTask = 0l;

void InitTask(void)
{
  FilterTask = new Task;
}

void CloseTask(void)
{
  if(FilterTask != 0)
  {
   delete FilterTask;
   FilterTask = 0l;
  }
}

int GetFilterCount(void)
{
 if(FilterTask != 0l)
  return FilterTask->GetFilterCount();
 else
  return 0;
}

int GetFilterPercent(int i)
{
 if(FilterTask != 0l)
  return FilterTask->GetFilterPercent(i);
 else
  return 0;
}

int RegisterFilter(Filter *NewFilter)
{
 if(FilterTask != 0l)
  return FilterTask->Add(NewFilter);
 else
  return 0;
}

void TerminateFilter(int FilterNr)
{
 if(FilterTask != 0l)
  FilterTask->Terminate(FilterNr);
}

void TaskRun(void)
{
 if(FilterTask != 0l)
  FilterTask->Run();
}

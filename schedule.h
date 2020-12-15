#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED
#include <iostream>
#include "Result.h"
#include "Job.h"
using namespace std;   // 使用c++的string,可以引入<iostream>或<string>

void FCFS(Result &result, int job_num);
void highPriorityNoPree(Result &result, int job_num);
void highPriorityPree(Result &result, int job_num);
void HRRN(Result &result, int job_num);
void SJF(Result &result, int job_num);

#endif // SCHEDULE_H_INCLUDED

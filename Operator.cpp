#include <iostream>
#include "Operator.h"
#include "Result.h"
#include "schedule.h"
#include "readFile.h"
//#include "Print.h"
#include "writeFile.h"
using namespace std;

void Operator(string readfile, string writefile, int type){
    int job_num;
    Result result = readFile(readfile, job_num);
    switch(type){
    case 1:
        FCFS(result, job_num);
        break;
    case 2:
        SJF(result, job_num);
        break;
    case 3:
        HRRN(result, job_num);
        break;
    case 4:
        highPriorityNoPree(result, job_num);
        break;
    case 5:
        highPriorityPree(result, job_num);
        break;
    case 6:
        {
            int time_slice;
            cout<<"please input time slice:\n";
            cin>>time_slice;
            //  ....
        }

    }
    Print(result, job_num);
    writeFile(writefile, result, job_num);
}

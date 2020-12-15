#include <iostream>
#include <stdio.h>
#include "Operator.h"
#include "schedule.h"
using namespace std;

int main()
{
    char *readfile = "C:/Users/27424/Desktop/test2.txt";
    char *writefile = "C:/Users/27424/Desktop/answer2.txt";
    printf("1:FCFS\n2:SJF\n3:HRRN\n4:highPriorityNoPree\n5:highPriorityPree\n");
    int type;
    cin>>type;
    Operator(readfile, writefile, type);
}

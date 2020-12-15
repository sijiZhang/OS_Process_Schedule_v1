#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Parse.h"
#include "Job.h"
using namespace std;

void Parse(char *line, Job *job, int j){

    char *parse;
    parse = strtok(line, "\t");     // strtok��ͷ�ļ�<string.h>
    int i = 0;
    while(parse){
        //printf("%s\n", parse);
        if(i==0){
            job[j].name = (char *)malloc(20);
            strcpy(job[j].name, parse);
        }
        else if(i==1){
            int a;
            sscanf(parse,"%d",&a);
            job[j].arrive_time = a;
        }
        else if(i==2){
            int a;
            sscanf(parse,"%d",&a);      // sscanf��ͷ�ļ�<stdio.h>,���ܣ�����ֵ���ַ���parseת��Ϊ���Σ��浽a
            job[j].service_time = a;
            job[j].remain_time = a;
        }
        else if(i==3){
            int a;
            sscanf(parse, "%d", &a);
            job[j].priority = a;
        }
        parse = strtok(NULL, "\t");
        i++;
    }
}

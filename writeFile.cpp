#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include "writeFile.h"
#include "Result.h"
using namespace std;

void writeFile(string path, Result result, int job_num){
    fstream file;
    string title = "��ҵ\t���ʱ��\t��תʱ��\n";
    file.open(path, ios::out);
    if(!file){
        printf("file open or creat failed\n");
        return ;
    }
    file << title;
    for(int i=0; i<job_num; i++){
        file << result.job[i].name << '\t' << result.job[i].complete_time << '\t' << result.job[i].turn_time << '\n';
    }
    file << "ƽ����תʱ�䣺" << result.avg_turn_time;
}


void Print(Result result, int job_num){
    string title = "��ʼʱ��\t���ʱ��\t��תʱ��\n";
    cout<<title;
    for(int i=0; i<job_num; i++){
        printf("%d\t%d\t%d\n", result.job[i].start_time, result.job[i].complete_time, result.job[i].turn_time);
    }
    printf("ƽ����תʱ�䣺%.2f\n", result.avg_turn_time);
}



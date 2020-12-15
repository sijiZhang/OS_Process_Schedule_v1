#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include "writeFile.h"
#include "Result.h"
using namespace std;

void writeFile(string path, Result result, int job_num){
    fstream file;
    string title = "作业\t完成时间\t周转时间\n";
    file.open(path, ios::out);
    if(!file){
        printf("file open or creat failed\n");
        return ;
    }
    file << title;
    for(int i=0; i<job_num; i++){
        file << result.job[i].name << '\t' << result.job[i].complete_time << '\t' << result.job[i].turn_time << '\n';
    }
    file << "平均周转时间：" << result.avg_turn_time;
}


void Print(Result result, int job_num){
    string title = "开始时间\t完成时间\t周转时间\n";
    cout<<title;
    for(int i=0; i<job_num; i++){
        printf("%d\t%d\t%d\n", result.job[i].start_time, result.job[i].complete_time, result.job[i].turn_time);
    }
    printf("平均周转时间：%.2f\n", result.avg_turn_time);
}



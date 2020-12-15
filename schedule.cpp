#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "schedule.h"
#include "writeFile.h"
#define inf 1e9
using namespace std;

void FCFS(Result &result, int job_num){  //�����ȷ���
    double sum_turn_time = 0;
    for(int i=0; i<job_num; i++){
        if(i==0){
            result.job[i].start_time = result.job[i].arrive_time;
        }
        else{
            if(result.job[i].arrive_time<=result.job[i-1].complete_time){
                result.job[i].start_time = result.job[i-1].complete_time;
            }
            else{
                result.job[i].start_time = result.job[i].arrive_time;
            }
        }
        result.job[i].complete_time = result.job[i].start_time + result.job[i].service_time;
        result.job[i].turn_time = result.job[i].complete_time - result.job[i].arrive_time;
        sum_turn_time += result.job[i].turn_time;
    }
    result.avg_turn_time = sum_turn_time / job_num;
}

void highPriorityNoPree(Result &result, int job_num){     // ������Ȩ�����㷨������ռʽ��
    bool isask[job_num] = {false};
    int first_job_num = 1;   // ���ȵ����ҵ���ʱ����ͬ��������
    int indexs[job_num];     // ���ȵ����ҵ���ʱ����ͬ�����������
    int j = 0;
    indexs[j++] = 0;
    for(int i=1; i<job_num; i++){
        if(result.job[i].arrive_time == result.job[0].arrive_time){
            first_job_num ++;
            indexs[j++] = i;
        }
        else
            break;
    }
    int  priority = inf;  // ���ȼ�(���ȼ���ֵԽС�����ȼ�Խ��)
    int index = 0;
    for(int i=0; i<first_job_num; i++){
        if(result.job[indexs[i]].priority <= priority){
            index = indexs[i];
            priority = result.job[indexs[i]].priority;
        }
    }
    for(int i=0; i<job_num; i++){
        priority = inf;
        int next_index = 0;
        if(i==0){
            result.job[index].start_time = result.job[index].arrive_time;
            result.job[index].complete_time = result.job[index].start_time + result.job[index].service_time;
            isask[index] = true;
        }
        else{
            for(int j=0; j<job_num; j++){
                if(!isask[j] && result.job[j].arrive_time <= result.job[index].complete_time){
                    if(result.job[j].priority <= priority){
                        next_index = j;
                        priority = result.job[j].priority;
                    }
                }
            }
            result.job[next_index].start_time = result.job[index].complete_time;
            result.job[next_index].complete_time = result.job[next_index].start_time + result.job[next_index].service_time;
            isask[next_index] = true;
            index = next_index;
        }
    }
    double sum_turn_time = 0;
    for(int i=0; i<job_num; i++){
        result.job[i].turn_time = result.job[i].complete_time - result.job[i].arrive_time;
        sum_turn_time += result.job[i].turn_time;
    }
    result.avg_turn_time = sum_turn_time / job_num;
    return ;
}

void highPriorityPree(Result &result, int job_num){       // �����ȼ������㷨����ռʽ��
    bool isask[job_num] = {false};
    bool isSST[job_num] = {false};        // ��¼�Ƿ��Ѿ������˿�ʼʱ��
    int counter = 0;    // ��¼�����������
    int index = 0;
    bool ischange = false;  // �ж������Ƿ��л���
    int priority;       // ��ǰ��������ȼ�
    int initfirst = 0;
    while(true){
        if(counter==job_num){
            break;
        }
        if(initfirst==0){  // ��ʼ����һ������Ŀ�ʼʱ��
            result.job[index].start_time = result.job[index].arrive_time;
            isSST[index] = true;
            initfirst++;
        }
        ischange = false;
        priority = result.job[index].priority;
        int i;
        for(i=0; i<result.job[index].service_time; i++){
            result.job[index].remain_time--;
            for(int k=0; k<job_num; k++){
                if(k!=index && isSST[k])
                    result.job[k].wait_time++;
            }
            if(result.job[index].remain_time==0){
                isask[index] = true;
                counter++;
                result.job[index].complete_time = result.job[index].start_time + result.job[index].service_time + result.job[index].wait_time;
                int temp = index;
                int priority_2 = inf;
                for(int j=0; j<job_num; j++){
                    if(!isask[j] && result.job[j].arrive_time <= result.job[temp].complete_time){
                        if(result.job[j].priority < priority_2){
                            index = j;
                            priority_2 = result.job[j].priority;
                            ischange = true;

                        }
                    }
                }
                if(ischange && !isSST[index]){
                    result.job[index].start_time = result.job[temp].complete_time;
                    isSST[index] = true;
                    break;
                }
                break;
            }
            else{
                //int priority = inf;
                int temp = index;
                for(int j=0; j<job_num; j++){
                    if(!isask[j] && result.job[j].arrive_time <= (result.job[temp].start_time + (result.job[temp].service_time - result.job[temp].remain_time))){
                        if(result.job[j].priority < priority){
                            index = j;
                            priority = result.job[j].priority;
                            ischange = true;

                        }
                    }
                }

                if(ischange && !isSST[index]){
                    result.job[index].start_time = result.job[temp].start_time + (result.job[temp].service_time - result.job[temp].remain_time);
                    isSST[index] = true;
                    break;
                }
            }
        }
    }
    double sum_turn_time = 0;
    for(int i=0; i<job_num; i++){
        result.job[i].turn_time = result.job[i].complete_time - result.job[i].arrive_time;
        sum_turn_time += result.job[i].turn_time;
    }
    result.avg_turn_time = sum_turn_time / job_num;
}

void HRRN(Result &result, int job_num){   // ����Ӧ�����ȵ����㷨
    bool isask[job_num] = {false};
    int index = 0;
    for(int i=0; i<job_num; i++){
        int next_index = 0;
        double responseRatio = -1;    // ��Ӧ��
        if(i==0){
            result.job[i].start_time = result.job[i].arrive_time;
            result.job[i].complete_time = result.job[i].start_time + result.job[i].service_time;
            isask[i] = true;
        }
        else{
            for(int j=1; j<job_num; j++){
                if(!isask[j] && result.job[j].arrive_time <= result.job[index].complete_time){
                    double x = (result.job[index].complete_time - result.job[j].arrive_time + result.job[j].service_time) / result.job[j].service_time;
                    if(x >= responseRatio){
                        next_index = j;
                        responseRatio = x;
                    }
                }
            }
            result.job[next_index].start_time = result.job[index].complete_time;
            result.job[next_index].complete_time = result.job[next_index].start_time + result.job[next_index].service_time;
            isask[next_index] = true;
            index = next_index;
        }
    }
    double sum_turn_time = 0;
    for(int i=0; i<job_num; i++){
        result.job[i].turn_time = result.job[i].complete_time - result.job[i].arrive_time;
        sum_turn_time += result.job[i].turn_time;
    }
    result.avg_turn_time = sum_turn_time / job_num;
}

void SJF(Result &result, int job_num){      // ����ҵ����
    bool isask[job_num] = {false};
    int first_job_num = 1;   // ���ȵ����ҵ���ʱ����ͬ��������
    int indexs[job_num];     // ���ȵ����ҵ���ʱ����ͬ�����������
    int j = 0;
    indexs[j++] = 0;
    for(int i=1; i<job_num; i++){
        if(result.job[i].arrive_time == result.job[0].arrive_time){
            first_job_num ++;
            indexs[j++] = i;
        }
        else
            break;
    }
    int server_time = inf;
    int index = 0;
    for(int i=0; i<first_job_num; i++){
        if(result.job[indexs[i]].service_time <= server_time){
            index = indexs[i];
            server_time = result.job[indexs[i]].service_time;
        }
    }
    for(int i=0; i<job_num; i++){
        server_time = inf;
        int next_index = 0;
        if(i==0){
            result.job[index].start_time = result.job[index].arrive_time;
            result.job[index].complete_time = result.job[index].start_time + result.job[index].service_time;
            isask[index] = true;
        }else{
            for(int j=0; j<job_num; j++){
                if(!isask[j] && result.job[j].arrive_time <= result.job[index].complete_time){
                    if(result.job[j].service_time <= server_time){
                        next_index = j;
                        server_time = result.job[j].service_time;
                    }
                }
            }
            result.job[next_index].start_time = result.job[index].complete_time;
            result.job[next_index].complete_time = result.job[next_index].start_time + result.job[next_index].service_time;
            isask[next_index] = true;
            index = next_index;
        }
    }
    double sum_turn_time = 0;
    for(int i=0; i<job_num; i++){
        result.job[i].turn_time = result.job[i].complete_time - result.job[i].arrive_time;
        sum_turn_time += result.job[i].turn_time;
    }
    result.avg_turn_time = sum_turn_time / job_num;
    return ;
}





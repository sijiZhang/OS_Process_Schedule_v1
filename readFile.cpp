#include <iostream>
#include <stdio.h>
#include <fstream>

#include <iomanip>
#include "readFile.h"
#include "Result.h"
#include "Parse.h"
using namespace std;

Result readFile(string path, int &job_num){
    Result result;
    result.job = new Job[10];
    fstream file;
    char buf[100];
    file.open(path);
    if(!file){
        cout<<"file failed open \n";
        return result;
    }

    int i = -1;
    while(file){
        file.getline(buf, sizeof(buf));
        if (i!=-1){
            Parse(buf, result.job, i);
        }
        i++;
    }
    job_num = i-1;
    return result;
}


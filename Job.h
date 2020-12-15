#ifndef JOB_H_INCLUDED
#define JOB_H_INCLUDED

class Job{
public:
    char *name;
    int arrive_time;
    int service_time;
    int start_time;
    int complete_time;
    int turn_time;
    int priority;  // 优先级
    int remain_time;    // 剩余时间
    int wait_time = 0;  // 等待时间


};


#endif // JOB_H_INCLUDED

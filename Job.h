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
    int priority;  // ���ȼ�
    int remain_time;    // ʣ��ʱ��
    int wait_time = 0;  // �ȴ�ʱ��


};


#endif // JOB_H_INCLUDED

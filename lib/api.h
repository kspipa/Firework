#include <libnetfilter_queue/libnetfilter_queue.h>
#define SUCCESS 1
#define FAILURE 0

struct shmemCell{
    void * cell;
    int lastid;
};

extern int get_answer_code(struct shmemCell cell){
};
extern int send_packet(struct shmemCell cell, int data[3000]){
};
extern struct shmemCell init_module(char * nameof){

};

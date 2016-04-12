/* Author: Andrew Cooper
*  This program consists of three files: CooperA3PT2.c, CooperA3FuncPT2.c, and CooperA3PT2.h.
*  Its purpose was to demonstrate the use of semaphors with six child processes accessing shared memory.
*/

#include "CooperA3PT2.h"
#include <sys/shm.h>

#define MAXCOUNTERVAL 1000000

typedef struct{
    int value;
}shared_mem; 

shared_mem *counter;

key_t semkey;
int id;

main(){
    
    //	shared memory key, ID, and allocation
    key_t key = IPC_PRIVATE;
    int shmid;
    shared_mem *shmat1;
    
    if ((semkey = ftok("/tmp", 'a')) == (key_t) -1) {
          perror("IPC error: ftok"); 
          exit(1);
    }

    id = initsem(semkey);
        
    pid_t pid;	
    
    // process ids for children
    int child1;
    int child2;	
    int child3;
    int child4;
    int child5;
    int child6;

    int idx1 = 0;
    int idx2 = 0;
    int idx3 = 0;
    int idx4 = 0;
    int idx5 = 0;
    int idx6 = 0;


    //	attempts to attach to an existing memory segment
    if (( shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget"); 
        exit(1);
    }

    // attempts to access the shared memory segment
    if((counter = (shared_mem *)shmat(shmid, NULL, 0)) == (shared_mem *) -1)
    {
        perror("shmat"); 
        exit(1);
    }

    //	initializing shared memory to 0
    counter->value = 0;

    //	fork the first process
    pid = fork();

    if (pid == -1){
        
        printf("Error creating first child.\n");
        exit(0);

    }else if (pid == 0){

        child1 = getpid();
        fprintf(stderr,"Hello from Child 1, my pid is %d the counter is at %d currently\n", child1, counter->value);
        waitsem(id);

        while(idx1 < MAXCOUNTERVAL){
            counter->value = counter->value + 1;
            idx1++;
        }
    
        fprintf(stderr,"Child 1 (pid %d) signing off. Counter is at %d\n", child1, counter->value);
        signalsem(id);
        exit(0);
    }

    //	fork the second process
    pid = fork();

    if (pid == -1){
    
        printf("Error creating second child.\n");
        exit(0);

    }else if (pid == 0){
        
        child2 = getpid();
        fprintf(stderr,"Hello from Child 2, my pid is %d the counter is at %d currently\n", child2, counter->value);
        waitsem(id);
        
        while(idx2 < MAXCOUNTERVAL){
            counter->value = counter->value + 1;
            idx2++;
        }
    
        fprintf(stderr,"Child 2 (pid %d) signing off. Counter is at %d\n", child2, counter->value); 
        signalsem(id);	
        exit(0);
    }

    //	fork the third process
    pid = fork();

    if (pid == -1){
        
        printf("Error creating third child.\n");
        exit(0);

    }else if (pid == 0){
         
         child3 = getpid();
         fprintf(stderr,"Hello from Child 3, my pid is %d the counter is at %d currently\n", child3, counter->value);
         waitsem(id);
        
         while(idx3 < MAXCOUNTERVAL){
            counter->value = counter->value + 1;
            idx3++;
         }
        
         fprintf(stderr,"Child 3 (pid %d) signing off. Counter is at %d\n", child3, counter->value);
         signalsem(id);         
         exit(0);
    }

    //	fork the fourth process
    pid = fork();

    if (pid == -1){
    
        printf("Error creating fourth child.\n");
        exit(0);

    }else if (pid == 0){
    
        child4 = getpid();
        fprintf(stderr,"Hello from Child 4, my pid is %d the counter is at %d currently\n", child4, counter->value);
        waitsem(id);
        
        while(idx4 < MAXCOUNTERVAL){
            counter->value = counter->value - 1;
            idx4++;
        }

        fprintf(stderr,"Child 4 (pid %d) signing off. Counter is at %d\n", child4, counter->value);
        signalsem(id);      
        exit(0);
    }

    //	fork the fifth process
    pid = fork();

    if (pid == -1){
    
        printf("Error creating fifth child.\n");
        exit(0);
    
    }else if (pid == 0){
        
        child5 = getpid();
        fprintf(stderr,"Hello from Child 5, my pid is %d the counter is at %d currently\n", child5, counter->value);
        waitsem(id);

        while(idx5 < MAXCOUNTERVAL){
            counter->value = counter->value - 1;
            idx5++;
         }

         fprintf(stderr,"Child 5 (pid %d) signing off. Counter is at %d\n", child5, counter->value);
         signalsem(id);       
         exit(0);
    }

    //	fork the sixth process
    pid = fork();
    
    if (pid == -1){
    
        printf("Error creating sixth child.\n");
        exit(0);

    }else if (pid == 0){
        
        child6 = getpid();
        fprintf(stderr,"Hello from Child 6, my pid is %d the counter is at %d currently\n", child6, counter->value);
        waitsem(id);

        while(idx6 < MAXCOUNTERVAL){
            counter->value = counter->value - 1;
            idx6++;
        }

        fprintf(stderr,"Child 6 (pid %d) signing off. Counter is at %d\n", child6, counter->value);
        signalsem(id);       
        exit(0);
    }

    // parent waits for child processes
    if (pid > 0){
        
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();

        fprintf(stderr,"I'm the parent, I have a pid of %d.\n", getpid());
        fprintf(stderr,"Counter value is: %d\n", counter->value);
        exit(0);

    }else{

        fprintf(stderr,"Forking error\n");
    }
    
    //	deallocate shared memory
    if(shmctl(shmid, IPC_RMID, (struct shmid_ds *)0)== -1){ 
        
        perror("shmctl");
        exit(-1);

    }

semrem(id);
exit(0);

}//	end main




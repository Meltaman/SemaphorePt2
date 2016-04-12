/* Author: Andrew Cooper
*  This program consists of three files: CooperA3PT2.c, CooperA3FuncPT2.c, and CooperA3PT2.h.
*  Its purpose was to demonstrate the use of semaphors with six child processes accessing shared memory.
*/


#include "CooperA3PT2.h"

//  Create and initialize a semaphore with a value of 1
int initsem(key_t semkey){
    int semid;
    int status = 0;

    //  Creates a semaphore set containing a single semaphore
    if((semid = semget(semkey, 1, SEMPERM|IPC_CREAT|IPC_EXCL)) == -1)	{
        if(errno == EEXIST)
            semid = semget(semkey, 1, 0);
    }else{
        semun arg;
        arg.val = 1;

        //  Sets the semval parameter of the semaphore to 1
        status = semctl(semid, 0, SETVAL, arg);
    }

    if(semid == -1 || status == -1){
        perror("initsem failed");
        return -1;
    }

    return(semid);

}// end initsem

void semrem(int semid){
     semctl(semid, 0, IPC_RMID, NULL);

}// end semrem

//  Semaphore wait() function 
int waitsem(int semid){
    struct sembuf p_buf;

    //	Set p_buf parameter values*/
    p_buf.sem_num = 0;
    p_buf.sem_op = -1;
    p_buf.sem_flg = SEM_UNDO;


    //	semaphore wait operation
    if(semop(semid, &p_buf, 1) == -1){
        perror("semop - Wait1");
        exit(1);
    }

    //printf("Wait - Locked\n");
        
    return 0;

}// end waitsem

//  Semaphore signal() function 
int signalsem(int semid){

    struct sembuf v_buf;
    
    //	Set v_buf parameter values
    v_buf.sem_num = 0;
    v_buf.sem_op = 1;
    v_buf.sem_flg = SEM_UNDO;

    //  semaphore signal operation
    if(semop(semid, &v_buf, 1) == -1){
        perror("semop - Signal");
        exit(1);
    }

    // printf("Signal - Unlocked\n");

    return 0;

}// end signalsem


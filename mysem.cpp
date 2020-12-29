#define KEY 0x1111
#include "mysem.h"
/*union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};
*/
#include <pthread.h>
int id;
union semun u;
int  MAXSEM1=1;
pthread_mutex_t lockt;
void myseminit( int val)
{
     pthread_mutex_lock(&lockt);
    id = semget(KEY, 1, 0666 | IPC_CREAT);
    if(id < 0)
    {
        perror("semget"); exit(11);
    }
    u.val = val;
    MAXSEM1=val;
    if(semctl(id, 0, SETVAL, u) < 0)
    {
        perror("semctl"); exit(12);
    }
    pthread_mutex_unlock(&lockt);
    return ;
}
void mysemp(unsigned short nthsems)
{
    pthread_mutex_lock(&lockt);
	struct sembuf p = { nthsems, -1, SEM_UNDO};
	if(semop(id, &p, 1) < 0)
	{
		perror("semop p"); exit(13);
	}
    pthread_mutex_unlock(&lockt);
    return;
}

void mysemv(unsigned short nthsems)
{
    pthread_mutex_lock(&lockt);
	struct sembuf v = { nthsems, +1, SEM_UNDO};
	if(semop(id, &v, 1) < 0)
	{
		perror("semop p"); exit(14);
	}
    pthread_mutex_unlock(&lockt);
    return;
}

int mysemval(int semNum)
{
    pthread_mutex_lock(&lockt);
    int i=semctl(id, semNum, GETVAL, u);
    pthread_mutex_unlock(&lockt);
    return i;

}

int getMAXSEM1()
{
    return MAXSEM1;
}

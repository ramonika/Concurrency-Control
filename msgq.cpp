/*
 * msgq.cpp
 *
 *  Created on: 21-May-2020
 *      Author: admin
 */





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <time.h>

#include <pthread.h>
pthread_mutex_t lock,lock3,lock2;


#define KEY 0x2222

#define PERMS 0644

#include "msgq.h"

Servstatpacket::Servstatpacket()
{
    CustReqNo = 0;
    memset(CustReqTime,0,50);
    ServPerAllocated=0;
    memset(SerStartTime,0,50);
    memset(SerEndTime,0,50);
    memset(msgstr,0,200);
}


char * getLocalTime(char * curtime)
{
    pthread_mutex_lock(&lock2);
    memset(curtime,0,100);

    //strcpy(curtime,asctime(gmtime(&time(NULL))));
    struct tm* ptr;
    time_t localt;
    localt = time(NULL);
    ptr = localtime(&localt);
    sprintf(curtime,"%s", asctime(ptr));
    pthread_mutex_unlock(&lock2);
    return curtime;
}

struct my_msgbuf {
   long mtype;
   char mtext[354];
};

int msgsend(char * msgstr) {
   // pthread_mutex_lock(&lock);
   struct my_msgbuf buf;
   int msqid;
   int len;
/*    key_t key;
   //system("touch msgq.txt");

  if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }*/

   if ((msqid = msgget(KEY, PERMS | IPC_CREAT)) == -1) {
      perror("Inside send msgget error");
      //exit(1);
   }

   static int CustReqNo = 1;
   Servstatpacket oServstatpacket;
   char ct[100];
   printf("%s",getLocalTime(ct));
   strcpy(oServstatpacket.CustReqTime,ct);
   oServstatpacket.CustReqNo = CustReqNo++;
   strcpy(oServstatpacket.msgstr,msgstr);




   buf.mtype = 1; /* we don't really care in this case */

   memcpy(buf.mtext, &oServstatpacket,sizeof(oServstatpacket));
   //len = strlen(buf.mtext);
   if (msgsnd(msqid, &buf,sizeof(buf), 0) == -1){ /* +1 for '\0' */
       perror("msgsnd");
   }

   /*if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
   */
   //pthread_mutex_unlock(&lock);
   return 0;
}


/*Following is the code from message receiving process (retrieving message from queue) */



void msgreceive(Servstatpacket &oServstatpacket) {
    pthread_mutex_lock(&lock3);
    struct my_msgbuf buf1;
   int msqid;
  // int toend;
 /*  key_t key;

 if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
*/
   if ((msqid = msgget(KEY, PERMS)) == -1) { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
 //  printf("message queue: ready to receive messages.\n");

   //for(;;) { /* normally receiving never ends but just to make conclusion
             /* this program ends wuth string of end */
      if (msgrcv(msqid, &buf1, sizeof(buf1), 0, 0) == -1) {
         perror("Inside recv msgrcv error");
         //exit(1);
      }

      memcpy(&oServstatpacket, buf1.mtext,sizeof(buf1.mtext));
     // printf("recvd: \"%s\"\n", buf.mtext);
     // toend = strcmp(buf.mtext,"end");
     // if (toend == 0)
     // break;
  // }
  // printf("message queue: done receiving messages.\n");
  // system("rm msgq.txt");
   pthread_mutex_unlock(&lock3);
   return ;
}

/*
 * msgq.h
 *
 *  Created on: 21-May-2020
 *      Author: admin
 */

#ifndef MSGQ_H_
#define MSGQ_H_


class Servstatpacket {
public:
    int CustReqNo;
    char CustReqTime[50];
    int ServPerAllocated;
    char SerStartTime[50];
    char SerEndTime[50];
    char msgstr[200];
    Servstatpacket();

};


extern char * getLocalTime(char * curtime);

extern int msgsend(char * msgstr);

extern void msgreceive(Servstatpacket &oServstatpacket);



#endif /* MSGQ_H_ */

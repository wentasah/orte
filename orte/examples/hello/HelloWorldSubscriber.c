/*
 *  $Id: HelloWorldSubscriber.c,v 0.0.0.1 2003/12/26
 *
 *  DEBUG:  section                     HelloWorldSubscriber
 *  AUTHOR: Petr Smolik                 petr.smolik@wo.cz
 *
 *  ORTE - OCERA Real-Time Ethernet     http://www.ocera.org/
 *  --------------------------------------------------------------------
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */
#ifdef HAVE_CONFIG_H
  #include <orte_config.h>
#endif
#include "orte_api.h"
#ifdef CONFIG_ORTE_RTL
  #include <linux/module.h>
  #include <posix/pthread.h>
  #define printf rtl_printf
#elif defined CONFIG_ORTE_RTAI
  #include <linux/module.h>
  #include <rtai/compat.h>  
  #define printf rt_printk
#else
  #include <stdio.h>
#endif


ORTEDomain        *d = NULL;
char              instance2Recv[64];

void
recvCallBack(const ORTERecvInfo *info,void *vinstance, void *recvCallBackParam) {
  char *instance=(char*)vinstance;

  switch (info->status) {
    case NEW_DATA:
      printf("%s\n",instance);
      break;
    case DEADLINE:
      printf("deadline occured\n");
      break;
  }
}


void *
subscriberCreate(void *arg) {
  ORTESubscription    *s;
  NtpTime             deadline,minimumSeparation;

  ORTETypeRegisterAdd(d,"HelloMsg",NULL,NULL,64);
  NTPTIME_BUILD(deadline,20);
  NTPTIME_BUILD(minimumSeparation,0);
  s=ORTESubscriptionCreate(
       d,
       IMMEDIATE,
       BEST_EFFORTS,
       "Example HelloMsg",
       "HelloMsg",
       &instance2Recv,
       &deadline,
       &minimumSeparation,
       recvCallBack,
       NULL);
  return arg;
}


#ifndef CONFIG_ORTE_RT

int
main(int argc, char *args[]) {
  ORTEInit();
  d=ORTEDomainAppCreate(ORTE_DEFAULT_DOMAIN,NULL,NULL,ORTE_FALSE);
  if (!d) {
    printf("ORTEDomainAppCreate failed!\n");
    return 0;
  }
  subscriberCreate(NULL);
  while (1)
    ORTESleepMs(1000);
  return 0;
}

#else

char manager[MAX_STRING_IPADDRESS_LENGTH]="127.0.0.1";
MODULE_PARM(manager,"s");
MODULE_PARM_DESC(manager,"IP address of local manager");
MODULE_LICENSE("GPL");
pthread_t thread;

void *
domainDestroy(void *arg) {
  if (!d) return NULL;
  ORTEDomainAppDestroy(d);
  return arg;
}

int
init_module(void) {
  ORTEDomainProp      dp;

  ORTEDomainPropDefaultGet(&dp);
  dp.appLocalManager=StringToIPAddress(manager);
  d=ORTEDomainAppCreate(ORTE_DEFAULT_DOMAIN,&dp,NULL,ORTE_FALSE);
  if (d) 
    pthread_create(&thread,NULL,&subscriberCreate,NULL);
  else
    printf("ORTEDomainAppCreate failed!\n");
  return 0;
}


void
cleanup_module(void) {
  if (!d) return;
  pthread_join(thread,NULL);
  pthread_create(&thread,NULL,&domainDestroy,NULL);
  pthread_join(thread,NULL);
}

#endif







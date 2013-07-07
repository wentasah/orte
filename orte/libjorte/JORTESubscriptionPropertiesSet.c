/* JORTESubscriptionPropertiesSet.c */

/**
  * This code provides conversion between JAVA a C environments.
  * The C functions are calling here and results are send to JAVA
  * native functions. It uses the header pregenerated by JAVA
  * (by command 'javah -jni class_with_native_function')
  *
  * @author Lukas Pokorny (lukas_pokorny@centrum.cz)
  * @author CTU FEE Prague - Department of Control Engineering (dce.felk.cvut.cz)
  * @author Project ORTE - OCERA Real Time Ethernet (www.ocera.org)
  * @author dedication to Kj
  * @version 0.1
  *
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  */

#include <string.h>
#include <stdlib.h>
// library header file's path
#include "orte.h"
// getNtpTime function
#include "jorte/jorte_protos_api.h"
// enable TEST_STAGE run level
#include "jorte/4all.h"
// pregenerated header
#include "jorte/org_ocera_orte_Subscription.h"


JNIEXPORT jboolean JNICALL
Java_org_ocera_orte_Subscription_jORTESubscriptionPropertiesSet
(JNIEnv *env, jobject obj, jlong j_appDomain_handle, jobject obj_sp)
{
  // jni types
  jclass         cls_sp = NULL;
  jfieldID       fid = NULL;
  jobject        j_minSeparation = NULL;
  jobject        j_deadline = NULL;
  jobject        obj_str = NULL;
  //
  int            b = 0;
  int            flag_ok = 0;
  const char    *str = NULL;
  ORTESubsProp   sp;
  ORTESubsProp  *subs_prop = &sp;

  #ifdef TEST_STAGE
    printf(":c: jORTESubscriptionPropertiesSet() called.. \n");
  #endif

  do
  {
    // get SubsProp instance's class
    cls_sp = (*env)->GetObjectClass(env, obj_sp);
    // second way how to get 'SubProp' instance's class
    //cls_sp = (*env)->FindClass(env,"org/ocera/orte/types/SubsProp");
    if(cls_sp == 0)
    {
      printf(":!c: class 'org.ocera.orte.types.SubsProp' not found! \n");
      break;
    }
    // ///////////////////////////////////////////////
    // setting object's fields
    /////////////////////////////////////////////////
    // set topic
    fid = (*env)->GetFieldID(env,
                             cls_sp,
                             "topic",
                             "Ljava/lang/String;");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    obj_str = (*env)->GetObjectField(env, obj_sp, fid);
    if(obj_str == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: obj_str = NULL \n");
      #endif
      break;
    }
    str = (*env)->GetStringUTFChars(env,obj_str,0);
    // Set the structure field.
    strncpy((char *)subs_prop->topic, (const char*)str, strlen(str) + 1);
    #ifdef TEST_STAGE
      printf(":c: topic = %s, subs_prop->topic = %s \n",
             str, subs_prop->topic);
    #endif
    // free the memory
    (*env)->ReleaseStringUTFChars(env, obj_sp, str);
    /////////////////////////////////////////////////
    // set topic - typeName
    fid = (*env)->GetFieldID(env,
                             cls_sp,
                             "typeName",
                             "Ljava/lang/String;");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    obj_str = (*env)->GetObjectField(env, obj_sp, fid);
    if(obj_str == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: obj_str = NULL \n");
      #endif
      break;
    }
    str = (*env)->GetStringUTFChars(env,obj_str,0);
    // Set the structure field.
    strncpy((char *)subs_prop->typeName, (const char*)str, strlen(str) + 1);
    #ifdef TEST_STAGE
      printf(":c: typeName = %s, subs_prop->typeName = %s \n",
             str, subs_prop->typeName);
    #endif
    // free the memory
    (*env)->ReleaseStringUTFChars(env, obj_sp, str);
    /////////////////////////////////////////////////
    // set topic - typeChecksum
    fid = (*env)->GetFieldID(env,cls_sp,"typeChecksum","I");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    subs_prop->typeChecksum = (TypeChecksum) (*env)->GetIntField(env, obj_sp, fid);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->typeChecksum = %d\n",
             subs_prop->typeChecksum);
    #endif
    /////////////////////////////////////////////////
    // set topic - minimumSeparation
    fid = (*env)->GetFieldID(env,
                             cls_sp,
                             "minSeparation",
                             "Lorg/ocera/orte/types/NtpTime;");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    j_minSeparation = (*env)->GetObjectField(env, obj_sp, fid);
    subs_prop->minimumSeparation = getNtpTime(env, j_minSeparation);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->minimumSeparation: sec = %d, fract = %d \n",
             subs_prop->minimumSeparation.seconds,
             subs_prop->minimumSeparation.fraction);
    #endif
    /////////////////////////////////////////////////
    // set topic - recvQueueSize
    fid = (*env)->GetFieldID(env,cls_sp,"recvQueueSize","J");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    subs_prop->recvQueueSize = (uint32_t) (*env)->GetLongField(env, obj_sp, fid);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->recvQueueSize = %d \n",
             subs_prop->recvQueueSize);
    #endif
    /////////////////////////////////////////////////
    // set topic - reliabilityRequested
    fid = (*env)->GetFieldID(env,cls_sp,"reliabilityRequested","J");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    subs_prop->reliabilityRequested = (uint32_t) (*env)->GetLongField(env, obj_sp, fid);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->reliabilityRequested = %d \n",
             subs_prop->reliabilityRequested);
    #endif
    /////////////////////////////////////////////////
    // set topic - deadline
    fid = (*env)->GetFieldID(env,
                             cls_sp,
                             "deadline",
                             "Lorg/ocera/orte/types/NtpTime;");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    j_deadline = (*env)->GetObjectField(env, obj_sp, fid);
    subs_prop->deadline = getNtpTime(env, j_deadline);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->deadline: sec = %d, fract = %d  \n",
             subs_prop->deadline.seconds, subs_prop->deadline.fraction);
    #endif
    /////////////////////////////////////////////////
    // set topic - mode
    fid = (*env)->GetFieldID(env,cls_sp,"mode","I");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    subs_prop->mode = (uint32_t) (*env)->GetIntField(env, obj_sp, fid);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->mode = %d \n",
             subs_prop->mode);
    #endif
/*
    /////////////////////////////////////////////////
    // set topic - multicastIPAddr READ-ONLY!!
    fid = (*env)->GetFieldID(env,cls_sp,"multicastIPAddr","J");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      break;
    }
    subs_prop->multicast = (IPAddress) (*env)->GetLongField(env, obj_sp, fid);
    #ifdef TEST_STAGE
      printf(":c: check: subs_prop->multicast = %d \n",
             subs_prop->multicast);
    #endif
*/
    // calling original native method
    b = ORTESubscriptionPropertiesSet((ORTESubscription *) j_appDomain_handle, subs_prop);
    if (b == ORTE_BAD_HANDLE)
    {
      printf(":c!: cannot set new Subscription Properties! [bad sub handle] \n");
      break;
    }
    // set flag
    flag_ok = 1;
  } while(0);

  if(flag_ok == 0)
  {
    return 0;
  }

  return 1;
}

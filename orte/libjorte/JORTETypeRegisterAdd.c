/* JORTETypeRegisterAdd.c */

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


// library header file's path
#include "orte.h"
// pregenerated header
#include "jorte/org_ocera_orte_Domain.h"


JNIEXPORT jint JNICALL
Java_org_ocera_orte_Domain_jORTETypeRegisterAdd
(JNIEnv *env, jclass cls, jint handle, jstring jname, jlong jlength)
{
  const char 	*name;
  int            b;

  /* get type name from JAVA env */
  name = (*env)->GetStringUTFChars(env,jname,0);

  /* call original orte function  */
  b = ORTETypeRegisterAdd((ORTEDomain *) handle, name, NULL, NULL, NULL,(unsigned int) jlength);

  /* free memmory space  */
  (*env)->ReleaseStringUTFChars(env,jname,name);

/*
  if (b == ORTE_OK) return ORTE_TRUE;

  return ORTE_FALSE;
*/

  printf(":c: jORTETypeRegisterAdd vraci %d [%d = ORTE_OK, %d = ORTE_BAD_HANDLE] \n",
  b,ORTE_OK,ORTE_BAD_HANDLE);

   return b;

/*
ORTETypeRegisterAdd(ORTEDomain *d,const char *typeName,ORTETypeSerialize ts,
                    ORTETypeDeserialize ds,unsigned int gms);
*/
}


/* JGetORTEConstant.c */
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
/* pregenerated header */
#include "jorte/org_ocera_orte_tools_GetORTEConstant.h"
/* library header file's path */
#include "orte.h"

/* macro for comparing 2 strings */
/* if(a==b) -> strcmp = 0 */
#define compare(a,b) ((strcmp((a),(b)) == 0) ? 1 : 0)


/* global variables */
/*
JNIEnv    *globalJavaEnv;
jclass     javaClass;
jobj       javaObject;
jmethodID  globalMid;
*/


/* native function - prototype declared in pregenerated header */
JNIEXPORT jint JNICALL
Java_org_ocera_tools_GetORTEConstant_getConstant
(JNIEnv *env, jobject jobj, jstring jname)
{
  const char    *constant;
  int            const_value = 0;

  /* get the constant name from JAVA Enviromnent*/
  constant = (*env)->GetStringUTFChars(env,jname,0);




  /* check if the name of the constant is correct *
   * if yes, return the constant value            *
   */

  /* RTPS_HEADER_LENGTH */
  #ifdef RTPS_HEADER_LENGTH
    if (compare(constant,"RTPS_HEADER_LENGTH"))
      const_value = RTPS_HEADER_LENGTH;
  #endif


  /* MAX_PATHNAME */
  #ifdef MAX_PATHNAME
    if (compare(constant,"MAX_PATHNAME"))
      const_value = MAX_PATHNAME;
  #endif


  /* MAX_TYPENAME */
  #ifdef MAX_TYPENAME
    if (compare(constant,"MAX_TYPENAME"))
      const_value = MAX_TYPENAME;
  #endif


  /* ORTE_TRUE */
  #ifdef ORTE_TRUE
    if (compare(constant,"ORTE_TRUE"))
      const_value = ORTE_TRUE;
  #endif


  /* ORTE_FALSE */
  #ifdef ORTE_FALSE
    if (compare(constant,"ORTE_FALSE"))
      const_value = ORTE_FALSE;
  #endif

/*
HID_UNKNOWN

AID_UNKNOWN

MANAGEDAPPLICATION

MANAGER

OID_UNKNOWN

OID_APP

OID_WRITE_APPSELF


*/


  /* return the result value*/
  if (const_value == 0) return (-1);

  return (const_value);

}



/*
X 10

int main(void) {

const char *c = "MAX";

#ifdef c
 printf("je definovano \n");
 return(1);
#endif

 printf("neni definovano \n");
 return(0);

}

int get_const(char *konstanta)
{
#define xxx(name) if (strcmp(konstanta, #name )) return name
        xxx(MAX);
        xxx(MIN);
}


// command cpp c_file
// napoveda cpp

*/




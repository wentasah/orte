/*
 *  $Id: ORTETypeRegister.c,v 0.0.0.1   2003/08/21 
 *
 *  DEBUG:  section 26                  Type register
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

#include "orte_all.h"

GAVL_CUST_NODE_INT_IMP(ORTEType, TypeEntry, TypeNode, const char *,
    types, node, typeRegister.typeName, gavl_cmp_str)
    

/*****************************************************************************/
Boolean
ORTETypeRegisterFind(ORTEDomain *d,const char *typeName) {
  Boolean            result=ORTE_FALSE;
  
  if (!d) return ORTE_FALSE;  //bat handle
  pthread_rwlock_rdlock(&d->typeEntry.lock);    
  if (ORTEType_find(&d->typeEntry,&typeName)) 
    result=ORTE_TRUE;
  pthread_rwlock_unlock(&d->typeEntry.lock);    
  return result;
}

/*****************************************************************************/
int
ORTETypeRegisterAdd(ORTEDomain *d,const char *typeName,ORTETypeSerialize ts,
                    ORTETypeDeserialize ds,unsigned int gms) {
  TypeNode           *tn;
  
  if (!d) return ORTE_BAD_HANDLE;       //bat handle
  if (gms>d->domainProp.wireProp.userMaxSerDeserSize) return -2;
  pthread_rwlock_wrlock(&d->typeEntry.lock);    
  tn=ORTEType_find(&d->typeEntry,&typeName);
  if (!tn) {
    tn=(TypeNode*)MALLOC(sizeof(TypeNode));
    tn->typeRegister.typeName=strdup(typeName);
    ORTEType_insert(&d->typeEntry,tn);
    debug(26,3) ("ORTETypeRegisterAdd: created\n");
  }
  tn->typeRegister.serialize=ts;
  tn->typeRegister.deserialize=ds;
  tn->typeRegister.getMaxSize=gms;
  pthread_rwlock_unlock(&d->typeEntry.lock);    
  debug(26,3) ("ORTETypeRegisterAdd: registered type:%s\n",typeName);
  return ORTE_OK;
}

/*****************************************************************************/
int
ORTETypeRegisterDestroyAll(ORTEDomain *d) {
  TypeNode           *tn;
  
  if (!d) return ORTE_BAD_HANDLE;  //bat handle
  pthread_rwlock_wrlock(&d->typeEntry.lock);    
  while((tn=ORTEType_cut_first(&d->typeEntry))) {
    free((char*)tn->typeRegister.typeName);
    FREE(tn);
  }
  pthread_rwlock_unlock(&d->typeEntry.lock);    
  return ORTE_OK;
}






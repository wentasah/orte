/*
 *  $Id: ORTEInit.c,v 0.0.0.1           2003/08/21 
 *
 *  DEBUG:  section 20                  Initialization of ORTE
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

#include "orte.h"
#ifdef __RTL__
#include <rtl.h>
#endif
#ifdef CONFIG_ORTE_RT
MODULE_LICENSE("GPL");
#endif

/*****************************************************************************/
void
ORTEInit(void) {
  SEQUENCE_NUMBER_NONE(noneSN);
  NTPTIME_ZERO(zNtpTime);
  NTPTIME_INFINITE(iNtpTime);
  sock_start();
  db_init(NULL,"");              //no debug info
}







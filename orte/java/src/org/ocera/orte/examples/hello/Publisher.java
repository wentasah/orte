/** Publisher.java */
import org.ocera.orte.*;
import org.ocera.orte.types.*;

/*
import org.ocera.orte.types.ORTEConstant;
import org.ocera.orte.types.NtpTime;
*/


/**
  * Class Publisher provides methods for creating and working
  * with the ORTE publisher.
  *
  * @author Lukas Pokorny (lukas_pokorny@centrum.cz)
  * @author CTU FEE Prague - Department of Control Engineering (dce.felk.cvut.cz)
  * @author Project ORTE - OCERA Real Time Ethernet (www.ocera.org)
  * @author dedication to Kj
  * @version 0.1
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


public class Publisher {

   /** load native library 'libjorte.so' */
   static {
   	System.loadLibrary("jorte");      
   }


  public static void main(String[] args)
  {
    // create a new domain
    Domain od = new Domain(ORTEConstant.ORTE_DEFAULT_DOMAIN,
                           DomainProp.defaultPropsCreate(),
			               DomainEvents.init(),
			               false);
    if (od == null)
	{
      System.out.println(":!j:PUB: cannot create default domain!");
      return;
	}
    System.out.println(":j:PUB: creating new Publication..");
    // HelloMsg(Domain d, String type, int maxLength)
	HelloMessage instance =  new HelloMessage(od,/* "HelloMsg",*/ 64);
    // set publisher's time parameter
    NtpTime persistence = new NtpTime(3);
    int strength        = 1;
    // create a publication    
    Publication pub = od.createPublication("Example HelloMsg",
                                           instance,
										   persistence,
                                           strength);	
	while(true)
	{
	  JOrte.sleepMs(1000);
    }
  } // end main()

}

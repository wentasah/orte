/* Subscription.java */

/**
 * Class Subscription provides methods for creating and working
 * with the ORTE subscribtion.
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

package org.ocera.orte;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import  org.ocera.orte.types.*;


public class Subscription {

   private long handle;
   private long callbackContextHandle = 0;

  /**
   * Get Subscription's handle.
   * @return Handle of the subscription.
   */
   public long getHandle()
   {
     return this.handle;
   }


  /**
   * constructor 
   */
  /* PROC protected??? - aby sel volat jen z tridy Domain */
  protected Subscription(Domain appDomain,
                         SubsProp subsProp,                         
						 MessageData message,
						 SubscriptionCallback subsCallback)
  {
  	this.handle = jORTESubscriptionCreate(appDomain.handle,
	                                      subsProp.getMode(),
	                                      subsProp.getType(),
	                                      subsProp.getTopic(),
	                                      subsProp.getTypeName(),
	                                      message.getBuffer(),
                                              message.getBuffer().order().equals(ByteOrder.BIG_ENDIAN) ? 0 : 1,
	                                      message,
										  subsProp.getDeadline(),
					                      subsProp.getMinSeparation(),
					                      subsCallback,
                                       // callBackParam 
					                      subsProp.getMulticastIPAddr());
  }

 /**
  * Removes a Subscription.
  * @return False if bad Publication handle, True if  succesful
  */
  public
  boolean destroy()
  {
  	/* TODO vyradit vypis na nasledujici radce */
  	System.out.println(":j: subscription destroy called..");
  	// destroy subscription
  	if(!jORTESubscriptionDestroy(this.handle)) 
  	{
  	    System.out.println(":j!: subscription destroy fault!");
  	    return false;              	
  	}
    System.out.println(":j: subscription destroy successfull..");
    return true;
    
  }
 
  /**
   * Get Subscription properties.
   * @return Subscription properties.
   */
  public SubsProp getProperties()
  {
  	SubsProp sp = new SubsProp();
    sp = jORTESubscriptionPropertiesGet(this.handle);	
  	return sp;
  }
  
  /**
   * Set Subscription properties.
   * @return True - setting new properties Ok, False - setting new properties fault.  
   */
  public boolean setProperties(SubsProp sp)
  {
  	boolean  b;

  	// modify SubsProp object - sp    
  	b = jORTESubscriptionPropertiesSet(this.handle, sp);	
  	if(b == false) 
  	{
        System.out.println(":j!: set SubsProp failed! (bad Subs. handle)"); 
  		return false; 
  	} 
  	return true;
  }
  
  
  /**
   * Get Subscription status.
   * @return Status of Subscription.  
   */
  public Status getStatus()
  {
    Status ss = new Status();
   	ss = jORTESubscriptionGetStatus(this.handle);
  	return ss;
  }

 
  /**
   * Waits for given number of publications.
   * @param Time how long to wait.
   * @param Number of retries if specified number of publications not reached.
   * @param Desired number of publications.
   * @return ORTE_OK if succesful, ORTE_BAD_HANDLE if bad subscription handle, 
   *         ORTE_TIMEOUT if number of retries has been exhausted.   
   */
  public int waitForPublications(NtpTime wait,
  		                         long retries,
			     				 long noPublication)   
  { 
    int i;
  	i = jORTESubscriptionWaitForPublications(this.handle,
  			                                 wait,
  			                                 retries,
							 				 noPublication);
    return i; 
  }
  
  /**
   * Read data
   * @param Time how long to wait.
   * @param Number of retries if specified number of publications not reached.
   * @param Desired number of publications.
   * @return ORTE_OK if succesful, ORTE_BAD_HANDLE if bad subscription handle, 
   *         ORTE_TIMEOUT if number of retries has been exhausted.   
   */
  public boolean pull(long subsHandle)
  { 
    int b = jORTESubscriptionPull(subsHandle);
    if (b == ORTEConstant.ORTE_BAD_HANDLE) 
    {
      System.out.println(":j!: method pull failed  [bad subsHandle]!");
      return false;
    }	
    return true; 
  }
  
  /* TODO - dodelat!! */
  public void patternCreate()
  {}
  /* TODO - dodelat!! */
  public void patternRemove()
  {}
  /* TODO - dodelat!! */
  public void patternDelete()
  {}
  
  
  
/* ****************************************************************** *
 *                                                                    *
 *                         native methods                             *
 *                                                                    *
 * ****************************************************************** */

  private native
  long jORTESubscriptionCreate(long appDomainHandle,
                               int subsmode,  /*! union */
                               int substype,  /*! union */
                               String topic,
                               String typeName,
                               ByteBuffer buffer,
                               int byte_order,
                               MessageData message,
		 					  NtpTime deadline,
                               NtpTime minSeparation,
                               SubscriptionCallback cb,
                             // recvCallBackParam
                               long multicastIPAddress);

  private native
  boolean jORTESubscriptionDestroy(long subsHandle);

  private native
  SubsProp jORTESubscriptionPropertiesGet(long subsHandle);
  
  private native
  boolean jORTESubscriptionPropertiesSet(long subsHandle, SubsProp subProps);

  private native
  Status jORTESubscriptionGetStatus(long subsHandle);

  private native
  int jORTESubscriptionWaitForPublications(long subsHandle, 
  	                                       NtpTime wait,
	                					   long retries,
										   long noPublications);  
  private native
  int jORTESubscriptionPull(long subsHandle);  
 
  
  
}


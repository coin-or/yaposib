/* $Id: OSSolverAgent.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** \file OSSolverAgent.h
 * 
 *
 * @author  Robert Fourer,  Jun Ma, Kipp Martin, 
 * @version 1.0, 10/05/2005
 * @since   OS1.0
 *
 * \remarks
 * Copyright (C) 2005, Robert Fourer, Jun Ma, Kipp Martin,
 * Northwestern University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in OS root directory for terms.
 */ 
 
#ifndef	OSSOLVERAGENT_H
#define OSSOLVERAGENT_H

#include "OShL.h"
using std::string;

/*! \class OSSolverAgent OSSolverAgent.h "OSSolverAgent.h"
 *  \brief Used by a client to invoke a remote solver.
 *
 * \remarks 
	<p> This is an implementation of the virtual class OShL. We 
	need to implement the following virtual methods. </p>

	<p><b>The following key methods are invoked:</b> </p>
	<ol>
	<li> solve </li>
	<li> kill </li>
	<li> send </li>
	<li> retrieve </li>
	<li> knock </li>
	<li> getJobID </li>
	</ol>
 *
 * 
 */

class OSSolverAgent : public OShL{
public:

	/**
	 * Default constructor. 
	 * @param solverURI is the location of remote solver or scheduler
	 */
	OSSolverAgent(string solverURI) ;
	
	/**
	 * Class destructor. 
	 */	
	~OSSolverAgent();
	
   	/**
   	 * implement the solve() method which is a virtual function in OShL, this is synchronous
   	 * 
   	 * <p>
   	 * @param osil a string that holds the problem instance
   	 * @param osol is a string of options for the solver  
   	 * @return osrl which is a string with the result.
	 * </p> 
   	 */	
	string solve(string osil, string osol);
	
   	/**
   	 * implement the getJobID() method which is a virtual function in OShL
	 *
   	 * <p>
   	 * @param osol is the string with the options in OSoL format
   	 * @return a string which is the jobID
	 * </p> 
   	 */	
	string getJobID(string osol);
	
   	/**
   	 * implement the send() method which is a virtual function in OShL
	 *
   	 * <p>
   	 * @param osil is the string with the instance in OSiL format
   	 * @param osol is the string with the options in OSoL format
   	 * @return a bool which is true if the job is successfuly submitted
	 * </p> 
   	 */	
	bool send(string osil, string osol);
	
   	/**
   	 * implement the kill() method which is a virtual function in OShL
	 *
   	 * <p>
   	 * @param osol is the string with the options in OSoL format
   	 * @return a string which is in OSpL format
	 * </p> 
   	 */	
	string kill(string osol);
	
   	/**
   	 * implement the retrieve() method which is a virtual function in OShL
	 *
   	 * <p>
   	 * @param osol is the string with the options in OSoL format
   	 * @return a string which is in the result of the optimization is OSrL fomrat
	 * </p> 
   	 */	
	string retrieve(string osol);
	
   	/**
   	 * implement the knock() method which is a virtual function in OShL
	 *
   	 * <p>
   	 * @param ospl is the string with the process information in OSpL format
   	 * @param osol is the string with the options in OSoL format
   	 * @return a string which is the knock result in OSpL format.
	 * </p> 
   	 */	
	string knock(string ospl, string osol);
	
   	/**
   	 * implement the fileUpload() method which is a virtual function in OShL
	 *
   	 * <p>
   	 * @param osilFileName is the name of the file 
   	 * with the OSiL instance to be written on the server
   	 * @param osil is a string with the OSiL problem instance
	 * </p> 
   	 */	
	string fileUpload(string osilFileName, string osil);
	
private:
	
	/** solverAddress is the URI for the solver*/
	string solverAddress;
	
	/** solverPortNumber is the port number for the sovler */
	unsigned short solverPortNumber;
	
	/** postURI is the path to the solver that follows the first
	 * / in the solverAddress
	 */
	string postURI;
	
}; //class OSSolverAgent

#endif

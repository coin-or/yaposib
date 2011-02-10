/* $Id: OSrLWriter.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSrLWriter.h
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
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */


#ifndef OSrLWRITER_H
#define OSrLWRITER_H

#include "OSResult.h"
#include <string>



/*! \class OSrLWriter OSrLWriter.h "OSrLWriter.h"
 *  \brief Take an OSResult object and write a string that validates against OSrL.
 *
 * 
 */
class OSrLWriter{  
private:
	/** 
	 * m_OSResult is an object in the class OSResult, the data
	 * in m_OSResult are written to a string that validates against OSrL
	 */
	OSResult *m_OSResult;
public:

	/**
	 *
	 * Default constructor. 
	 */
	OSrLWriter( );
	
	/**
	 *
	 * Class destructor. 
	 */
	~OSrLWriter();
	
   	/**
   	 * create an osrl string from an OSResult object
   	 * <p>
   	 * @param theosresult is a pointer to an OSResult object 
   	 * @return a string with the OSResult data that validates against the OSrL schema.
	 * </p> 
   	 */	
	std::string writeOSrL( OSResult *theosresult);
	
   	/**
   	 * create an osrl char* from an OSResult object
   	 * necessary kludge since on Linux the catch doesn't like strings
   	 * <p>
   	 * @param theosresult is a pointer to an OSResult object 
   	 * @return a string with the OSResult data that validates against the OSrL schema.
	 * </p> 
   	 */	
	//char* writeOSrLWrap( OSResult *theosresult);
};
#endif

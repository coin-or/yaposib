/* $Id: OSrLReader.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSrLReader.h
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
 
 
#ifndef _OSRLREADER_H
#define _OSRLREADER_H


#include "OSResult.h"
#include "OSrLParserData.h"
#include "OSErrorClass.h"


#include <string>


/*! \class OSrLReader
 *  \brief The OSrLReader Class.
 * 
 * @author Robert Fourer, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for parsing an OSrL string and creating an
 * OSResult object from the string.
 */
class OSrLReader{  


public:

	/**
	 *
	 * OSrL class constructor. 
	 */
	OSrLReader( );
	
	/**
	 *
	 * OSrL class destructor. 
	 */
	~OSrLReader();
	
	
	/**
	 * Get an OSResult object from an OSrL string. 
	 * 
	 * @param osrl an OSrL string. 
	 * @return the OSResult object corresponding to the OSrL string. 
	 */		
	OSResult *readOSrL(const std::string& posrl) throw(ErrorClass);
	
private:
	/** m_osresult is the OSResult object returned by 
	 * the OSrLReader
	 */
	OSResult *m_osresult;
	
	/** m_parserData is the object used in the parser to 
	 * temporarily store data. 
	 */
	OSrLParserData *m_parserData;
};
#endif

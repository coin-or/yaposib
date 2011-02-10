/* $Id: OSoLWriter.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSoLWriter.h
 * 
 *
 * @author  Gus Gassmann, Jun Ma, Kipp Martin, 
 * @version 1.0, 17/July/2008
 * @since   OS1.1
 *
 * \remarks
 * Copyright (C) 2005-2008, Robert Fourer, Gus Gassmann, Jun Ma, Kipp Martin,
 * Northwestern University, Dalhousie University and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */


#ifndef OSoLWRITER_H
#define OSoLWRITER_H

#include "OSOption.h"
#include <string>

/*! \class OSoLWriter OSoLWriter.h "OSoLWriter.h"
 *  \brief Take an OSOption object and write 
 * a string that validates against the OSoL schema.
 *
 * 
 */
class OSoLWriter{  
private:
	/** 
	 * m_OSOption is an object in the class OSOption
	 */
	const OSOption *m_OSOption;
public:

	/**
	 *
	 * Default constructor. 
	 */
	OSoLWriter( );

	/**
	 *
	 * Class destructor. 
	 */	
	~OSoLWriter();

   	/**
   	 * create an osol string from an OSOption object
   	 * <p>
   	 * @param theosoption is a pointer to an OSOption object 
   	 * @return a string with the OSOption data that validates against the OSoL schema.
	 * </p> 
   	 */		
	std::string writeOSoL( OSOption *theosoption);
	
	/** m_bWhiteSpace is set to true if we write white space in the file
	 */
	bool m_bWhiteSpace;
};
#endif

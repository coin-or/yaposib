/* $Id: OSoLReader.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSoLReader.h
 * 
 *
 * @author  Horand Gassmann, Jun Ma, Kipp Martin, 
 * @version 1.0, 17/07/2008
 * @since   OS1.1
 *
 * \remarks
 * Copyright (C) 2005, Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin,
 * Northwestern University, Dalhousie University and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */
 
 
#ifndef OSOLREADER_H
#define OSOLREADER_H



#include "OSOption.h"
#include "OSoLParserData.h"
#include "OSErrorClass.h"
#include <string>


/*! \class OSoLReader
 *  \brief Used to read an OSoL string.
 *
 * \remarks 
 * <p> This class wraps around the OSoL parser and sends
 * the parser an OSoL string and is returned an OSOption
 * object. </p>
 */
class OSoLReader{  

public:

	/**
	 * Default constructor. 
	 */
	OSoLReader( );
	
	/**
	 * Class destructor. 
	 */	
	~OSoLReader();
	
   	/**
   	 * parse the OSoL solver options.
   	 * 
   	 * <p>
   	 * @param osol is a string that holds the solver options. 
   	 * @return the instance as an OSOption object.
	 * </p> 
   	 */	
	OSOption *readOSoL(const std::string& osol) throw(ErrorClass);

private:
	/** m_osoption is the OSOption object returned by 
	 * the OSoLReader
	 */
	OSOption *m_osoption;
	
	/** m_parserData is the object used in the parser to temporarily store data 
	 */
	OSoLParserData *m_parserData;
};


#endif

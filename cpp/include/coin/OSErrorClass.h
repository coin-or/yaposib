/* $Id: OSErrorClass.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file ErrorClass.h
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
 
#ifndef ERRORCLASS_H
#define ERRORCLASS_H

#include <string>
 
/*! \class ErrorClass
 *  \brief used for throwing exceptions.
 * 
 * @author Robert Fourer, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * when an error is encountered in a try-catch block
 * we throw an ErrorClass with the errormsg_
 */
class ErrorClass{
	public:
		
		/** the class constructor it has a single
		 *  @param errormsg_ hods the error message as a string.
		 */
		ErrorClass( std::string errormsg_);
		
		/** errormsg is the error that is causing the exception
		 * to be thrown */
		std::string errormsg;
	
};
#endif

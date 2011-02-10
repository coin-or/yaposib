/* $Id: OSBase64.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file Base64.h
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


#ifndef BASE64_H
#define BASE64_H

#include<string>

/*! \class Base64
 *  \brief use this class to read and write data in base64.
 * 
 * @author Robert Fourer, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * it possible to save memory by eliminating the need for all the <el>
 * tabs by writing a long string of numbers in b64 format
 * 
 */
class Base64{
public:
	
	
	/** Base64 class constructior */
	Base64();
	
	/** Base64 class destructor */
	~Base64();
	
   	/**
   	 * encode the data in base 64 
   	 * 
   	 * @param bytes is the input to be encoded. 
   	 * @param size is the size of the pointer in bytes
   	 * @return a string in base 64 format. 
   	 */	
	static std::string encodeb64(char* bytes, int size);
	
   	/**
   	 * dencode the data in base 64 
   	 * 
   	 * @param b64bytes is the input to be decoded
   	 * @return a string that is decoded. 
   	 */	
	static std::string decodeb64(char* b64bytes);
};//class Base64


#endif


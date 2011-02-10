/* $Id: OSnl2osil.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSnl2osil.h
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
 

#ifndef OSNL2OSIL_H
#define OSNL2OSIL_H



#include "OSInstance.h"
#include "OSnLNode.h"
#include <string>


/*! \class OSnl2osil
 *  \brief The OSnl2osil  Class.
 * 
 * @author Robert Fourer, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * the OSnl2osil class is used for reading an instance
 * in AMPL nl format and creating an OSInstance object in OSiL format
 * 
 */

struct ograd;
struct ASL;
struct expr;


class OSnl2osil
{
public:
	/** the OSnl2osil class constructor */
	OSnl2osil( std::string nlfilename);

	/** the OSnl2osil class destructor */
	~OSnl2osil();
	
   	/**
   	 * create an OSInstance from the AMPL nl instance representation
   	 * 
   	 * @return whether the instance is created successfully. 
   	 */
	bool createOSInstance();
	
   	/**
   	 * parse an nl tree structure holding a nonlinear expression
   	 * 
   	 * @return the AMPL nonlinear structure as an OSnLNode. 
   	 */
	OSnLNode* walkTree(expr *e);
	
	/** osinstance is a pointer to the OSInstance object that gets
	 * created from the instance represented in MPS format
	 */
	OSInstance *osinstance;
private:
	
	/** og is a pointer to the AMPL data structure holding the
	 * objective function coefficients
	 */
	ograd *og;
	
	/** asl is a pointer to basic AMPL data structure
	 */
	ASL *asl;
	
	/** nl is a pointer to the file with the nl instance
	 */
	FILE *nl;
	
	/** stub is the name of the file with the nl instance
	 */
	char *stub;

};
#endif

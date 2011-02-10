/* $Id: OSOptionsStruc.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file osssparservariables.h
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


 
#ifndef OSOPTIONSSTRUC_H
#define OSOPTIONSSTRUC_H

/*! \struct osOptionsStruc
 *  \brief This structure is used to store options for the 
 * OSSolverService executable.
 * 
 * @author Robert Fourer, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * the OSSolverService requires numerous options and these
 * options are stored in the osOptionsStruc
 */
struct osOptionsStruc{
	/**  configFile is the name of the file that holds the configuration options
	 * if the OSSolverService reads its options from a file rather than command
	 * line inputs
	 */
	std::string configFile;
	
	/** osilFile is the name of the file that holds the model
	 * instance in OSiL format
	 */
	std::string osilFile;
	
	/** osil is the flag that tells OSSolverService that the next
	 * input is the instance in OSiL format
	 * e.g. -osil ../data/osilFiles/wayneQuadratic.osil
	 */
	std::string osil;
	
	/** osolFile is the name of the file that holds the solver options
	 */	
	std::string osolFile;
	
	/** osil is the flag that tells OSSolverService that the next
	 * input is a file with  solver options
	 * e.g. -osol ../data/osolFiles/demo.osol
	 */
	std::string osol;
	
	/** osrlFile is the name of the file where the solver should write
	 * the result in OSrL format
	 */
	std::string osrlFile;
	
	/** osrl is the flag that tells OSSolverService that the next
	 * input is the file name wher the solver should write the result
	 * e.g. -osrl ../data/osrlFiles/test.osrl
	 */	
	std::string  osrl;
	
	/** name of the file where the instance is in a LINDO instruction
	 * list format
	 */
	std::string insListFile;
	
	/** osrl is the flag that tells OSSolverService that the next
	 * input is the file name wher the instance is a LINDO instruction
	 * list -- this is not implemented 
	 */		
	std::string insList;
	
	/** serviceLocation is the URL of the remote solver when
	 * a local solver is not use
	 */
	std::string serviceLocation;
	
	/** the service method the OSSolverService should execute, e.g
	 * solve, send, getJobID, kill, knock, or retrieve
	 */
	std::string serviceMethod;
	 
	/** name of an input file with xml in OS Process language format,
	 * used for example to knock on a server, for example
	 * -osplInput ../data/osplFiles/demo.ospl
	 */
	std::string osplInputFile;
	
	/** name of an output file where the solver should write the result of a
	 * knock or kill service request
	 * 
	 */	
	std::string osplOutputFile;
	
	/** osplInput is the flag that tells OSSolverService that the next
	 * input is the file name of the file holding the OSpL that
	 * the OSSolverService sends to the solver
	 * e.g. -osplInput ../data/osplFiles/demo.ospl
	 */		
	std::string osplInput;

	/** osplOutput is the flag that tells OSSolverService that the next
	 * input is the file name of the file holding the OSpL that
	 * the solver should write to
	 * e.g. -osplOutput ../data/osplFiles/test.ospl
	 */		
	std::string osplOutput;
	
	/** the name of the mpsFile that holds an instance in mps format */
	std::string mpsFile;
	
	/** the name of the nlFile that holds an instance in AMPL nl format */
	std::string nlFile;  
	
	/** the name of the solver to be invoked, 
	 * e.g -solver Ipopt
	 */
	std::string solverName;
	
	/** this paramater is a path to the browser on the local machine. 
	 * If this optional parameter is specified then the solver result 
	 * in OSrL format is transformed using XSLT into HTML and displayed 
	 * in the browser, e.g.
	 * -browser /Applications/Firefox.app/Contents/MacOS/firefox
	 */
	std::string browser;

	/** if this parameter is true we print the contents of the file
	 * help.txt and return 
	 */
	bool invokeHelp;
	
	/** if this parameter is true we print the current version
	 * of the OS project 
	 */
	bool writeVersion;
	
};


#endif

/*  end header file */ 

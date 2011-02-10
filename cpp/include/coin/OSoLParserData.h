/* $Id: OSoLParserData.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSoLParserData.h
 * 
 * @author  Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin, 
 * @version 1.0, 29/08/2008
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
#ifndef OSOLPARSERDATA_H
#define OSOLPARSERDATA_H

#include "OSnLNode.h"
#include <vector> 





/*! \class OSoLParserData
 *  \brief The OSoLParserData  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 08/29/2008
 * @since OS 1.1
 * 
 * \remarks
 * the OSoLParserData class is used to temporarily 
 * hold data found in parsing the OSoL instance
 * we do this so we can have a reentrant parser.
 */
class OSoLParserData{
public:
	/** track which child elements are present */
	bool osolgeneralPresent;
	bool osolsystemPresent;
	bool osolservicePresent;
	bool osoljobPresent;
	bool osoloptimizationPresent;


	/** children of the <general> element */
	bool serviceURIPresent;
	bool serviceNamePresent;
	bool instanceNamePresent;
	bool instanceLocationPresent;
	bool instanceLocationTypeattON;
	bool jobIDPresent;
	bool solverToInvokePresent;
	bool licensePresent;
	bool usernamePresent;
	bool passwordPresent;
	bool contactPresent;
	bool transportTypeattON;

	bool otherGeneralOptionsPresent;
      int numberOfOtherGeneralOptions;


	/** children of the <system> element */
	bool minDiskSpacePresent;
	bool minDiskSpaceUnitPresent;

	bool minMemorySizePresent;
	bool minMemorySizeUnitPresent;

	bool minCPUSpeedPresent;
	bool minCPUSpeedUnitPresent;

	bool minCPUNumberPresent;

	bool otherSystemOptionsPresent;
      int numberOfOtherSystemOptions;


	/** children of the <service> element */
	bool serviceTypePresent;

	bool otherServiceOptionsPresent;
      int numberOfOtherServiceOptions;


	/** children of the <job> element */
	bool maxTimePresent;
	std::string maxTimeUnit;
	bool maxTimeUnitPresent;
	double maxTimeValue;

	bool requestedStartTimePresent;
	std::string requestedStartTime;

	bool dependenciesPresent;
	int numberOfDependencies;

	bool requiredDirectoriesPresent;
	int numberOfRequiredDirectories;

	bool requiredFilesPresent;
	int numberOfRequiredFiles;

	bool directoriesToMakePresent;
	int numberOfDirectoriesToMake;

	bool filesToMakePresent;
	int numberOfFilesToMake;

	bool pathPairFromPresent;
	bool pathPairToPresent;
	bool pathPairMakeCopyPresent;

	bool inputDirectoriesToMovePresent;
	int numberOfInputDirectoriesToMove;

	bool inputFilesToMovePresent;
	int numberOfInputFilesToMove;

	bool outputDirectoriesToMovePresent;
	int numberOfOutputDirectoriesToMove;

	bool outputFilesToMovePresent;
	int numberOfOutputFilesToMove;

	bool directoriesToDeletePresent;
	int numberOfDirectoriesToDelete;

	bool filesToDeletePresent;
	int numberOfFilesToDelete;

	bool processesToKillPresent;
	int numberOfProcessesToKill;

	bool otherJobOptionsPresent;
      int numberOfOtherJobOptions;
	
	/** children of the <optimization> element */
	int numberOfVariables;
	bool numberOfVariablesPresent;
	int numberOfObjectives;
	bool numberOfObjectivesPresent;
	int numberOfConstraints;
	bool numberOfConstraintsPresent;
	bool variablesPresent;
	bool objectivesPresent;
	bool constraintsPresent;
	bool solverOptionsPresent;
	bool idxAttributePresent;
	bool valAttributePresent;
	bool lbvalAttributePresent;
	bool ubvalAttributePresent;
	int  numberOfOtherVariableOptions;
	bool initialVariableValuesPresent;
	int  numberOfVar;
	bool initialVariableValuesStringPresent;
	int  numberOfVarStr;
	bool initialBasisStatusPresent;
	int  numberOfBasVar;
	bool sosIdxAttributePresent;
	bool grpWgtAttributePresent;
	bool nOfVarAttributePresent;
	int  numberOfIntWt;
	int  numberOfSOS;
	int  numberOfSOSVar;
	int  numberOfOtherObjectiveOptions;
	bool initialObjectiveValuesPresent;
	int numberOfObjValues;
	bool initialObjectiveBoundsPresent;
	int numberOfObjBounds;
	int numberOfOtherConstraintOptions;
	bool initialConstraintValuesPresent;
	int numberOfCon;
	bool initialDualVariableValuesPresent;
	int numberOfDuals;
	int numberOfSolverOptions;

	int numberOfObj;

	/** attributes of <other> options */
	bool otherOptionNumberPresent;
	bool otherOptionNamePresent;
	bool otherOptionValuePresent;
	bool otherOptionSolverPresent;
	bool otherOptionCategoryPresent;
	bool otherOptionTypePresent;
	bool otherOptionDescriptionPresent;

	/** attributes of <solverOptions> element */
	bool solverOptionNamePresent;
	bool solverOptionValuePresent;
	bool solverOptionSolverPresent;
	bool solverOptionCategoryPresent;
	bool solverOptionTypePresent;
	bool solverOptionDescriptionPresent;


	/** the OSoLParserData class constructor */
	OSoLParserData( );
	
	//** the OSoLParserData class destructor */
	~OSoLParserData() ;
	
	
	/**  the status type of the result */ 
	std::string statusType;
	
	/** the status Description of the solution */
	std::string statusDescription;

	/** scanner is used to store data in a reentrant lexer 
	 * we use this to pass an OSoLParserData object to the parser*/
	void* scanner;
	
	
	/**  if the parser finds invalid text it is held here and we delete
	 * if the file was not valid
	 */
	char *errorText;
};//OSoLPArserData

#endif /*OSOLPARSERDATA_H_*/

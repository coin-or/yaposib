/* $Id: OSResult.h 2852 2009-07-29 05:04:05Z kmartin $ */
/** @file OSResult.h
 * 
 *
 * @author  Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin, 
 * @version 2.0, 19/07/2009
 * @since   OS1.0
 *
 * \remarks
 * Copyright (C) 2005-2009, Robert Fourer, Jun Ma, Horand Gassmann, Kipp Martin,
 * Northwestern University, Dalhousie University and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */

#ifndef OSRESULT_H
#define OSRESULT_H
//#define DEBUG
#include <string>
#include <vector>
#include "OSDataStructures.h"


/*! \class GeneralSubstatus
 *  \brief The GeneralSubstatus  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 11/03/2008
 * @since OS 2.0
 * 
 * \remarks
 * A data structure class that corresponds to an xml element in 
 * the OSrL schema.  
 */
class GeneralSubstatus {

public:
 
	/** the name of the substatus */
	std::string name;

	/** the description of the substatus */	
	std::string description;
	
	/**
	 *
	 * Default constructor. 
	 */
	GeneralSubstatus();
	/**
	 *
	 * Class destructor. 
	 */
	~GeneralSubstatus();
		
};//GeneralSubstatus


/*! \class GeneralStatus
 *  \brief The GeneralStatus  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A data structure class that corresponds to an xml element in 
 * the OSrL schema.  
 */
class GeneralStatus {

public:
 
	/** the number of substatuses */
	int numberOfSubstatuses;

	/** the type of status */	
	std::string type;
	
	/** the description of the status */	
	std::string description;
	
	/** the array of substatuses */
	std::vector<GeneralSubstatus*> substatus;

	/**
	 *
	 * Default constructor. 
	 */
	GeneralStatus();
	/**
	 *
	 * Class destructor. 
	 */
	~GeneralStatus();
		
};//GeneralStatus


/*! \class GeneralResult
 *  \brief The GeneralResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the general information 
 * that is defined in the OSrL schema.  
 */
class GeneralResult{
public:

	/** a pointer to the GeneralStatus class */
	GeneralStatus *generalStatus;
	
	/** the serviceURI is the URI of the solver service
	 * that did the optimiation 
	 */
	std::string serviceURI;
	
	/** the serviceName is the name of the sovler service
	 * that did the optimization
	 */
	std::string serviceName;
	
	/** the name of the instance that was solved */
	std::string instanceName;
	
	/** the jobID is the ID associated with the solution
	 * of this instance
	 */
	std::string jobID;
	
	/** the time when solution was complete 
	 * kippster -- verify this
	 */
	std::string time;
	
	/** any general message associated with the optimization */
	std::string message;
	
	/**
	 *
	 * Default constructor. 
	 */
	GeneralResult();
	/**
	 *
	 * Class destructor. 
	 */
	~GeneralResult();
};//class GeneralResult


/*! \class SystemResult
 *  \brief The SystemResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the system information 
 * that is defined in the OSrL schema.  
 */
class SystemResult{
public:
	
	/**
	 *
	 * Default constructor. 
	 */
	SystemResult();
	/**
	 *
	 * Class destructor. 
	 */
	~SystemResult();
};//class SystemResult


/*! \class ServiceResult
 *  \brief The ServiceResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the system information 
 * that is defined in the OSrL schema.  
 */
class ServiceResult{
public:
	
	/**
	 *
	 * Default constructor. 
	 */
	ServiceResult();
	/**
	 *
	 * Class destructor. 
	 */
	~ServiceResult();
};//class ServiceResult


/*! \class Time
 *  \brief The Time  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides an array of individual time measurements
 * that are defined in the OSrL schema.  
 */
class Time{
public:

	/** 
	 *
	 * The type of timer used (cpuTime/elapsedTime/other)
	 */
	std::string type;

	/** 
	 *
	 * The category of time (total/input/preprocessing/optimization/postprocessing/output/other)
	 */
	std::string category;

	/** 
	 *
	 * The unit of time (tick/millisecond/second/minute/hour/day/week/month/year)
	 */
	std::string unit;

	/** 
	 *
	 * Further description on the timer used
	 */
	std::string description;

	/**
	 *
	 * The time measurement
	 */
	double value;

	/**
	 *
	 * Default constructor. 
	 */
	Time();
	/**
	 *
	 * Class destructor. 
	 */
	~Time();
};//class Time


/*! \class TimingInformation
 *  \brief The TimingInformation  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the timer information 
 * that is defined in the OSrL schema.  
 */
class TimingInformation{
public:

	/** 
	 *
	 * An array of time measurements
	 */
	Time** time;

	/**
	 *
	 * The number of elements in the time array
	 */
	int numberOfTimes;

	/**
	 *
	 * Default constructor. 
	 */
	TimingInformation();
	/**
	 *
	 * Class destructor. 
	 */
	~TimingInformation();
};//class TimingInformation


/*! \class JobResult
 *  \brief The JobResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the system information 
 * that is defined in the OSrL schema.  
 */
class JobResult{
public:
	
	TimingInformation* timingInformation;
	/**
	 *
	 * Default constructor. 
	 */
	JobResult();
	/**
	 *
	 * Class destructor. 
	 */
	~JobResult();
};//class JobResult




/*! \class OptimizationSolutionSubstatus
 *  \brief The OptimizationSolutionSubstatus Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for holding various attributes of a solution
 * status
 */	
class OptimizationSolutionSubstatus {
public:
	
	/** the name of the solution substatus */
	std::string namee;
	
	/** a description of the solution substatus */
	std::string description;
	
	
	/**
	 * Default constructor. 
	 */
	OptimizationSolutionSubstatus();
	/**
	 *
	 * Class destructor. 
	 */
	~OptimizationSolutionSubstatus();
		
};//OptimizationSolutionSubstatus


/*! \class OptimizationSolutionStatus
 *  \brief The OptimizationSolutionStatus Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for holding various attributes of a solution
 * status
 */	
class OptimizationSolutionStatus {
public:
	
	/** the number of substatus objects */
	int numberOfSubstatuses;

	/** the type of solution status */
	std::string type;
	
	/** a description of the solution status type */
	std::string description;
	
	/** a pointer to an array of substatus objects */
	std::vector<OptimizationSolutionSubstatus*> substatus;

	/**
	 * Default constructor. 
	 */
	OptimizationSolutionStatus();
	/**
	 *
	 * Class destructor. 
	 */
	~OptimizationSolutionStatus();
		
};//OptimizationSolutionStatus


/*! \class VarValue
 *  \brief VarValue  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that is used to provide the value and index
 * associated with the variables in the solution.  
 */
class VarValue{
public:

	/** idx is the index on variable in the solution */
	int idx;
	
	/* value is the value of the variable indexed by idx
	 * in the solution
	 */	
	double value;

	/**
	 *
	 * Default constructor. 
	 */
	VarValue();
	/**
	 *
	 * Class destructor. 
	 */
	~VarValue();

};// class VarValue


/*! \class VariableValues
 *  \brief The VariableValues Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that cotnains values for all the variables
 */	
class VariableValues{
public:

	/** the number of variable values that are in the solution
	 */
	int numberOfVar;

	/** a vector of VarValue objects, there will be one
	 * for each variable in the solution
	 */
	std::vector<VarValue*> var;

	
	/**
	 *
	 * Default constructor. 
	 */
	VariableValues();
	
	/**
	 *
	 * Class destructor. 
	 */
	~VariableValues();

};// class VariableValues


/*! \class VarStringValue
 *  \brief VarStringValue  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that is used to provide the value and index
 * associated with the string-valued variables in the solution.  
 */
class VarStringValue{
public:

	/** idx is the index on variable in the solution */
	int idx;
	
	/* value is the value of the variable indexed by idx
	 * in the solution
	 */	
	std::string value;

	/**
	 *
	 * Default constructor. 
	 */
	VarStringValue();

	/**
	 *
	 * Class destructor. 
	 */
	~VarStringValue();

};// class VarStringValue


/*! \class VariableStringValues
 *  \brief The VariableStringValues Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that contains values for all the string-valued variables
 */	
class VariableStringValues{
public:

	/** the number of variable values that are in the solution
	 */
	int numberOfVar;

	/** a vector of VarValue objects, there will be one
	 * for each variable in the solution
	 */
	std::vector<VarStringValue*> var;

	
	/**
	 *
	 * Default constructor. 
	 */
	VariableStringValues();
	
	/**
	 *
	 * Class destructor. 
	 */
	~VariableStringValues();

};// class VariableStringValues


/*! \class OtherVarResult
 *  \brief OtherVarResult Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks A class used to provide solution information
 * associated with the variables.
 */
class OtherVarResult {
public:
	
	/** the index of a variable in the solution */
	int idx;
	
	/** value holds a general value for a variable,
	 * for example, rather than the value of a variable
	 * we may wish to store the variable name associated
	 * with the vairable with index idx, hence we want
	 * a string here and not a double
	 */
	std::string value;
	
	/**
	 *
	 * Default constructor. 
	 */
	OtherVarResult();
	/**
	 *
	 * Class destructor. 
	 */
	~OtherVarResult();
	
};//OtherVarResult



/*! \class OtherVariableResult
 *  \brief The OtherVariableResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that allows the solver to report an
 * arbitrary result associated with variables 
 */
class OtherVariableResult {
public:

	/** the number of variables which have values for this
	    particular type of result
	 */
	int numberOfVar;

	/** this element allows a specific value associated with this
	    particular type of result
	 */
	std::string value;

	/** the name of the result the user is defining */
	std::string name;
	
	/** a brief description of the type of result */
	std::string description;
	
	/* a pointer to OtherVarResult objects that will
	 * give for each variable the index and value for 
	 * this user defined variable result
	 */
	std::vector<OtherVarResult*> var;

	/**
	 *
	 * Default constructor. 
	 */
	OtherVariableResult();
	
	/**
	 *
	 * Class destructor. 
	 */
	~OtherVariableResult();
	
};//OtherVariableResult


/*! \class VariableSolution
 *  \brief The VariableSolution Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for reporting all of the types of solution values
 * associated with variables.
 */
class VariableSolution{
public:

	/** the number of types of variable results other
	 * than the value of the variable
	 */
	int numberOfOtherVariableResults;

	/** a pointer to an array of VariableValues objects */
	VariableValues *values;
	
	/** a pointer to an array of VariableStringValues objects */
	VariableStringValues *valuesString;
	

	/** a pointer to an array of other pointer objects for 
	 * variables
	 */
	OtherVariableResult** other;

	/**
	 *
	 * Default constructor. 
	 */
	VariableSolution();
	
	/**
	 *
	 * Class destructor. 
	 */
	~VariableSolution();

};// class VariableSolution


/*! \class ObjValue
 *  \brief The ObjValue  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the value of an objective
 * function
 */
class ObjValue {
public:	

	/** idx is the index on an objective function */
	int idx;
	
	/** the value of the objective indexed by idx */
	double value;
	
	/**
	 *
	 * Default constructor. 
	 */
	ObjValue();

	/**
	 *
	 * Class destructor. 
	 */
	~ObjValue();
};//ObjValue

/*! \class ObjectiveValues
 *  \brief The ObjectiveValues  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for reporting objective function values 
 */
class ObjectiveValues {
public:

	/** record the number of objective rows for which values are given
	 */
	int numberOfObj;

	/** obj is a pointer to an array of ObjValue objects that
	 * give an index and objective function value for
	 * each objective function.
	 */
	std::vector<ObjValue*> obj;
	
	/**
	 *
	 * Default constructor. 
	 */
	ObjectiveValues();
	
	/**
	 *
	 * Class destructor. 
	 */
	~ObjectiveValues();
	
};//ObjectiveValues


/*! \class OtherObjResult
 *  \brief The OtherObjResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides general result information
 * for objective functions. 
 */
class OtherObjResult {
public:
	
	/** idx is the index on a objective function */
	int idx;
	
	
	/** value is a value associated with an objective function
	 * indexed by idx
	 */
	std::string value;
	
	/**
	 *
	 * Default constructor. 
	 */
	OtherObjResult();

	/**
	 *
	 * Class destructor. 
	 */
	~OtherObjResult();
	
};//OtherObjResult




/*! \class OtherObjectiveResult
 *  \brief The OtherObjectiveResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that allows the solver to report an
 * arbitrary result associated with objective functions 
 */
class OtherObjectiveResult {
public:

	/** the number of objectives which have values for this
	    particular type of result
	 */
	int numberOfObj;

	/** this element allows a specific value associated with this
	    particular type of result
	 */
	std::string value;


	/** the name of the result the user is defining */
	std::string name;
	
	/** a brief description of the type of result */
	std::string description;

	/* a pointer to OtherObjResult objects that will
	 * give for each objective function the index and 
	 * value for this user defined objective function result
	 */	
	std::vector<OtherObjResult*> obj;
	
	/**
	 *
	 * Default constructor. 
	 */
	OtherObjectiveResult();
	
	/**
	 *
	 * Class destructor. 
	 */
	~OtherObjectiveResult();
	
};//OtherObjectiveResult



/*! \class ObjectiveSolution
 *  \brief The ObjectiveSolution Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for reporting all of the types of solution values
 * associated with objective functions.
 */
class ObjectiveSolution {
public:

	/** the number of types of objective function results other
	 * than the basic objective function values
	 */
	int numberOfOtherObjectiveResults;
	
	/** a pointer to an array of ObjectiveValues objects */	
	ObjectiveValues *values;

	/** a pointer to an array of other pointer objects for 
	 * objective functions
	 */	
	OtherObjectiveResult** other; 

	/**
	 *
	 * Default constructor. 
	 */
	ObjectiveSolution();
	
	/**
	 *
	 * Class destructor. 
	 */
	~ObjectiveSolution();

};//ObjectiveSolution



/*! \class DualVarValue
 *  \brief The DualVarValue  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides the dual value of a constraint 
 */
class DualVarValue {
public:	

	/** idx is the index on a constraint */
	int idx;

	/** lbValue is the value of dual variable on
	 * the constraint indexed by idx if the constraint
	 * is at its lower bound
	 */		
	//double lbValue;
	
	
	/** ubValue is the value of dual variable on
	 * the constraint indexed by idx if the constraint
	 * is at its upper bound
	 */	
	//double ubValue;
	
	/** value of dual variable on
	 * the constraint indexed by idx if the constraint
	 */
	double value;
	
	/**
	 *
	 * Default constructor. 
	 */
	DualVarValue();

	/**
	 *
	 * Class destructor. 
	 */
	~DualVarValue();
	
};//DualVarValue



/*! \class DualVariableValues
 *  \brief The DualVariableValues Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for reporting dual variable values 
 */
class DualVariableValues {
public:

	/** record the number of constraints for which values are given
	 */
	int numberOfCon;

	/** con is a vector of DualVarValue objects that
	 * give an index and dual variable value for
	 * each constraint function.
	 */
	std::vector<DualVarValue*> con;
	
	/**
	 *
	 * Default constructor. 
	 */
	DualVariableValues();
	
	/**
	 *
	 * Class destructor. 
	 */
	~DualVariableValues();
	
};//DualVariableValues


/*! \class OtherConResult
 *  \brief The OtherConResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that provides general result information
 * for constraints. 
 */
class OtherConResult {
public:
	
	/** idx is the index on the constraint */
	int idx;
	
	/** value is a value associated with the constraint
	 * indexed by idx, for example value might be the 
	 * value of a dual variable or it might be the name
	 * of the constraint.
	 */
	std::string value;
	
	/**
	 *
	 * Default constructor. 
	 */
	OtherConResult();

	/**
	 *
	 * Class destructor. 
	 */
	~OtherConResult();
	
};//OtherConResult





/*! \class OtherConstraintResult
 *  \brief The OtherConstraintResult  Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that allows the solver to report an
 * arbitrary result associated with constraints. 
 */
class OtherConstraintResult {
public:

	/** the number of constraints which have values for this
	    particular type of result
	 */
	int numberOfCon;

	/** this element allows a specific value associated with this
	    particular type of result
	 */
	std::string value;

	/** the name of the result the user is defining */
	std::string name;
	
	/** a brief description of the type of result */
	std::string description;
	
	
	/* a vector of OtherConResult objects that will
	 * give for each constraint the index and 
	 * value for this user defined objective function result
	 */	
	std::vector<OtherConResult*> con;

	/**
	 *
	 * Default constructor. 
	 */
	OtherConstraintResult();
	
	/**
	 *
	 * Class destructor. 
	 */
	~OtherConstraintResult();
	
};//OtherConstraintResult

	


/*! \class ConstraintSolution
 *  \brief The ConstraintSolution Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for reporting all of the types of solution values
 * associated with objective functions.
 */
class ConstraintSolution {

public:

	/** the number of types of constraint function results other
	 * than the basic constraint function values
	 */
	int numberOfOtherConstraintResults;
	
	/** a pointer to an array of DualVariableValues objects */
	DualVariableValues *dualValues;
	
	/** a pointer to an array of other pointer objects for 
	 * constraint functions
	 */	 
	OtherConstraintResult** other;
	
	/**
	 *
	 * Default constructor. 
	 */
	ConstraintSolution();
	
	/**
	 *
	 * Class destructor. 
	 */
	~ConstraintSolution();
	
};//ConstraintSolution




/*! \class OtherSolutionResult
 *  \brief The OtherSolutionResult  Class.
 * 
 * @author Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that allows the solver to report an
 * arbitrary result associated with the solution. 
 */
class OtherSolutionResult {
public:

	/** the name of the result the user is defining */
	std::string name;
	
	/** this element allows a specific category to be associated with this
	    particular type of result
	 */
	std::string category;

	/** a brief description of the type of result */
	std::string description;

	/** the number of items contained in this otherSolutionResult
	 */
	int numberOfItems;

	/** an array of items (string-valued)
	 */
	std::string *item;

	/**
	 *
	 * Default constructor. 
	 */
	OtherSolutionResult();
	
	/**
	 *
	 * Class destructor. 
	 */
	~OtherSolutionResult();
	
};//OtherOptimizationResult




/*! \class OtherSolutionResults
 *  \brief The OtherSolutionResults  Class.
 * 
 * @author Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class that allows the solver to report an
 * arbitrary result associated with the solution. 
 */
class OtherSolutionResults {
public:

	/** the number of elements in the pointer of OtherSolutionResult objects */
	int numberOfOtherSolutionResults;
	
	/** otherSolutionResult is a pointer to an array of OtherSolutionResult
	 * objects
	 */
	OtherSolutionResult **otherSolutionResult;

	/**
	 *
	 * Default constructor. 
	 */
	OtherSolutionResults();
	
	/**
	 *
	 * Class destructor. 
	 */
	~OtherSolutionResults();
	
};//OtherOptimizationResult

	


/*! \class OptimizationSolution
 *  \brief The OptimizationSolution Class.
 * 
 * @author Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for reporting the various components of
 * an optimization solution.
 */
class OptimizationSolution{
public:

	/** the index of the objective function for which we are 
	 * reporting solution information 
	 */
	int targetObjectiveIdx;

	/** the number of other results associated with this solution */
	int numberOfOtherResults;

	/** status is a pointer to an OptimizationSolutionStatus
	 *  object associated with this optimization solution
	 */
	OptimizationSolutionStatus *status;
	
	/** a message associated with this solution */
	std::string message;
	
	/** variables holds the solution information for
	 *  the variables
	 */
	VariableSolution *variables;
	
	/** objectives holds the solution information
	 *  for the objectives
	 */
	ObjectiveSolution *objectives;
	
	/** constraints holds the solution information
	 *  for the constraints
	 */
	ConstraintSolution *constraints;
	
	/** otherSolutionResults is a pointer to an OtherSolutionResults
    * object that is associated with this optimization solution
	 */
	OtherSolutionResults *otherSolutionResults;

	/**
	 *
	 * Default constructor. 
	 */
	OptimizationSolution();

	/**
	 *
	 * Class destructor. 
	 */
	~OptimizationSolution();

};// class OptimizationSolution


/*! \class OptimizationResult
 *  \brief The OptimizationResult Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for holding information that might be associated
 * with an optimization solution.
 */
class OptimizationResult{
public:
	
	/** numberOfVariables is the number of variables reported 
	 * in the solution.
	 */
	int numberOfVariables;
	
	/** numberOfObjectives is the number of objective functions
	 * reported in the solution.
	 */
	int numberOfObjectives;

	/** numberOfConstrants is the number of constraint functions
	 * reported in the solution.
	 */
    int numberOfConstraints;

	/** numberOfSolubitons is the number of objective functions
	 * reported.
	 */	
	int numberOfSolutions;

	/** solution is an array of pointers to OptimizationSolution
	 * objects
	 */
	OptimizationSolution **solution;
	
	/**
	 *
	 * Default constructor. 
	 */
	OptimizationResult();

	/**
	 *
	 * Class destructor. 
	 */
	~OptimizationResult();

};// class OptimizationResult



/*! \class OSResult
 *  \brief The Result Class.
 * 
 * @author Robert Fourer, Horand Gassmann, Jun Ma, Kipp Martin
 * @version 1.0, 03/14/2004
 * @since OS 1.0
 * 
 * \remarks
 * A class for holding all the solution information.
 */
class OSResult{

public:

	/**
	 * general holds the first child of the OSResult specified by the OSrL Schema. 
	 */
	GeneralResult *general;

	/**
	 * system holds the second child of the OSResult specified by the OSrL Schema. 
	 */
	SystemResult *system;

	/**
	 * service holds the third child of the OSResult specified by the OSrL Schema. 
	 */
	ServiceResult *service;

	/**
	 * job holds the fourth child of the OSResult specified by the OSrL Schema. 
	 */
	JobResult *job;

	/**
	 * optimization holds the fifth child of the OSResult specified by the OSrL Schema. 
	 */
	OptimizationResult *optimization;

	/**
	 *
	 * Default constructor. 
	 */
	OSResult(); 

	/**
	 *
	 * Class destructor. 
	 */
	~OSResult();
public:	
	
	/**
	 * m_iVariableNumber holds the variable number. 
	 */
	int m_iVariableNumber;
	
	/**
	 * m_iObjectiveNumber holds the objective number. 
	 */
	int m_iObjectiveNumber;
	
	/**
	 * m_iConstraintNumber holds the constraint number. 
	 */
	int m_iConstraintNumber;
	
	/**
	 * m_iNumberOfOtherVariableResults holds the number of OtherVariableResult objects. 
	 */	
	int m_iNumberOfOtherVariableResults;
	
	/**
	 * m_mdPrimalValues a vector of primal variables. 
	 */
	double *m_mdPrimalValues;
	
	/**
	 * m_mdDualValues a vector of dual variables. 
	 */
	double *m_mdDualValues;
	
	
	std::vector<IndexValuePair*> primalVals;
	
	std::vector<IndexValuePair*> dualVals;
	
	


public:

   	/**
	 * Get the general status.
	 * 
	 * @return the general status. 
	 */
	GeneralStatus* getGeneralStatus();
	
  	/**
	 * Get the general status type, which can be: 
	 * success, error, warning. 
	 * 
	 * @return the general status type, null if none. 
	 */
	std::string getGeneralStatusType();
	
   	/**
	 * Get the general status description. 
	 * 
	 * @return the general status description, null or empty std::string if none. 
	 */
	std::string getGeneralStatusDescription();

   	/**
	 * Get service name.
	 * 
	 * @return the service name. 
	 */
	std::string getServiceName();
	
  	/**
	 * Get service uri.
	 * 
	 * @return the service uri. 
	 */
	std::string getServiceURI();
	
  	/**
	 * Get instance name.
	 * 
	 * @return the instance name. 
	 */
	std::string getInstanceName();
	
  	/**
	 * Get the job id.
	 * 
	 * @return the job id. 
	 */
	std::string getJobID(); 
	
   	/**
	 * Get the general message. 
	 * 
	 * @return the general message. 
	 */
	std::string getGeneralMessage();

	/**
	 *  Get the number of time measurements. 
	 *
	 *  @return the number of time measurements
	 */
	int getTimeNumber();

	/**
	 *  Get the time measurement. In the first instance, assume that there is only
	 *  a single measure, which is the total elapsed time in seconds
	 *
	 *  @return the time measurement
	 */
	double getTimeValue();

	/**
	 * Get one solution of optimal primal variable values. 
	 * 
	 * @param solIdx holds the solution index the optimal solution corresponds to. 
	 * @return a vector of variable indexes and values, an empty vector if no optimal value. 
	 */
	std::vector<IndexValuePair*>  getOptimalPrimalVariableValues(int solIdx);
	
	/**
	 * Get one solution of optimal objective values. 
	 * 
	 * @param objIdx holds the objective index the optimal value corresponds to. 
	 * @param solIdx holds the solution index the optimal value corresponds to.
	 * @return a double with the optimal objective function value. 
	 */
	double getOptimalObjValue(int objIdx, int solIdx);

	/**
	 * Get one solution of optimal dual variable values. 
	 * 
	 * @param solIdx holds the solution index the optimal solution corresponds to. 
	 * @return a vector of variable indexes and values, an empty vector if no optimal value. 
	 */	
	std::vector<IndexValuePair*>   getOptimalDualVariableValues(int solIdx);
	
	//Solution getSolution(int solIdx);

	/**
	 * Get the [i]th optimization solution status, where i equals the given solution index.   
	 * The solution status includes the status type, optional descriptions and possibly substatuses.
	 *  
	 * @param solIdx holds the solution index to get the solution status. 
	 * @return the optimization solution status that corresponds to solIdx, null if none.
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OptimizationSolutionStatus
	 */	
	OptimizationSolutionStatus* getSolutionStatus( int solIdx);

	/**
	 * Get the [i]th optimization solution status type, where i equals the given solution index.   
	 * The solution status type can be: 
	 * unbounded, globallyOptimal, locallyOptimal, optimal, bestSoFar, feasible, infeasible, 
	 * stoppedByLimit, unsure, error, other 
	 * 
	 * @param solIdx holds the solution index to get the solution status type. 
	 * @return the optimization solution status type that corresponds to solIdx, null or empty std::string if none.
	 */	
	std::string getSolutionStatusType(int solIdx);

	/**
	 * Get the [i]th optimization solution status description, where i equals the given solution index.   
	 * 
	 * @param solIdx holds the solution index to get the solution status description. 
	 * @return the optimization solution status description that corresponds to solIdx, null or empty std::string if none.
	 */	
	std::string getSolutionStatusDescription(int solIdx);
	
	/**
	 * Get the [i]th optimization solution message, where i equals the given solution index.  
	 * 
	 * @param solIdx holds the solution index to get the solution message. 
	 * @return the optimization solution message that corresponds to solIdx, null or empty if none.
	 */	
	std::string getSolutionMessage(int solIdx);
	

	
	
	/**
	 * Get variable number. 
	 * 
	 * @return variable number, -1 if no information. 
	 */
	int getVariableNumber();
	
	/**
	 * Get objective number. 
	 * 
	 * @return objective number, -1 if no information. 
	 */
	int getObjectiveNumber();
	
	/**
	 * Get constraint number. 
	 * 
	 * @return constraint number, -1 if no information. 
	 */
	int getConstraintNumber();
	
	/**
	 * get the number of solutions. 
	 * 
	 * @return the number of solutions, 0 if none.  
	 */
	int getSolutionNumber();	
	
	/**
	 * Get numberOfOtherVariableResult. 
	 * 
	 * @return numberOfOtherVariableResult, -1 if no information. 
	 */
	int getNumberOfOtherVariableResults( int solIdx);
	

	/**
	 * Get getAnOtherVariableResultNumberOfVar. 
	 * 
	 * @return the number of variables in the i'th other variable result, -1 if no information. 
	 */
	int getAnOtherVariableResultNumberOfVar(int solIdx, int iOther);


	// set() methods
	//
	
   	/**
	 * Set the general status
	 * 
	 * @param status holds the general status.
	 * @return whether the general status is set successfully. 
	 */
	bool setGeneralStatus(GeneralStatus *status);
			
   	/**
	 * Set the general status type, which can be: 
	 * success, error, warning. 
	 * 
	 * @param type holds the general status type
	 * @return whether the general status type is set successfully or not. 
	 */
	bool setGeneralStatusType(std::string type);	
	
   	/**
	 * Set the general status description. 
	 * 
	 * @param description holds the general status description.
	 * @return whether the general status description is set successfully or not. 
	 */
	bool setGeneralStatusDescription(std::string description);
	
   	/**
	 * Set the general message. 
	 * 
	 * @param message holds the general message. 
	 * @return whether process message is set successfully. 
	 */
	bool setGeneralMessage(std::string message);

   	/**
	 * Set service name.
	 * 
	 * @param serviceName holds the name of the service. 
	 * @return whether the service name is set successfully. 
	 */
	bool setServiceName(std::string serviceName);
	
   	/**
	 * Set service uri.
	 * 
	 * @param serviceURI holds the uri of the service. 
	 * @return whether the service uri is set successfully. 
	 */
	bool setServiceURI(std::string serviceURI);	
	
   	/**
	 * Set instance name.
	 * 
	 * @param instanceName holds the name of the instance. 
	 * @return whether the instance name is set successfully. 
	 */
	bool setInstanceName(std::string instanceName);
		
   	/**
	 * Set job id.
	 * 
	 * @param jobID holds the job id. 
	 * @return whether the job id is set successfully. 
	 */
	bool setJobID(std::string jobID);
		
   	/**
	 * Set time.
	 * 
	 * @param time holds the time. 
	 * @return whether the time is set successfully. 
	 */
	bool setTime(double time);
		
   	/**
	 * Add timing information.
	 * 
	 * @param type holds the timer type (cpuTime/elapsedTime/other). 
	 * @param category holds the timer category (total/input/preprocessing, etc.)
	 * @param unit holds the timer unit (tick/milliscond/second/minute/etc.) 
	 * @param description holds further information about the timer. 
	 * @param value holds the time measurement. 
	 * @return whether the time is set successfully. 
	 */
	bool addTimingInformation(std::string type, std::string category,
							  std::string unit, std::string description, double value);
	
	/**
	 * Set the number of time measurements. 
	 * 
	 * @param timeNumber holds the number of measurements
	 * @return whether the time number is set successfully or not. 
	 */
	bool setTimeNumber(int timeNumber);
	
	/**
	 * Set the variable number. 
	 * 
	 * @param variableNumber holds the number of variables
	 * @return whether the variable number is set successfully or not. 
	 */
	bool setVariableNumber(int variableNumber);
	
	/**
	 * Set the objective number. 
	 * 
	 * @param objectiveNumber holds the number of objectives
	 * @return whether the objective number is set successfully or not. 
	 */
	bool setObjectiveNumber(int objectiveNumber);
	
	/**
	 * Set the constraint number. 
	 * 
	 * @param constraintNumber holds the number of constraints
	 * @return whether the constraint number is set successfully or not. 
	 */
	bool setConstraintNumber(int constraintNumber);
		
	/**
	 * set the number of solutions. This method must be called before setting other optimization solution 
	 * related results.  
	 * Before this method is called, the setVariableNumber(int), setObjectiveNumber(int), setConstraintNumber(int) methods 
	 * have to be called first. 
	 * 
	 * @param number holds the number of solutions to set. 
	 * @return whether the solution number is set successfully.   
	 * @see #setVariableNumber(int)
	 * @see #setObjectiveNumber(int)
	 * @see #setConstraintNumber(int)
	 */
	bool setSolutionNumber(int number);
	
	
	/**
	 * Set the [i]th optimization solution status, where i equals the given solution index.   
	 * The solution status includes the status type, optional descriptions and possibly substatuses. 
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * 
	 * @param solIdx holds the solution index to set the solution status.
	 * @param status holds the optimization solution status to set.  
	 * 
	 * @return whether the optimization solution status is set successfully or not. 
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OptimizationSolutionStatus
	 * @see #setSolutionNumber(int)
	 */
	bool setSolutionStatus(int solIdx, std::string type, std::string description);

	/**
	 * Set the [i]th optimization solution's objective index, where i equals the given solution index.   
	 * The first objective's index should be -1, the second -2, and so on.  
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * 
	 * @param solIdx holds the solution index to set the objective index.
	 * @param objectiveIdx holds the objective index to set.  
	 * All the objective indexes are negative starting from -1 downward. 
	 * 
	 * @return whether the optimization objective index is set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setSolutionTargetObjectiveIdx(int solIdx, int objectiveIdx);
	
	/**
	 * Set the [i]th optimization solution's message, where i equals the given solution index.   
	 * The first objective's index should be -1, the second -2, and so on.  
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * 
	 * @param solIdx holds the solution index to set the objective index.
	 * @param msg holds the solution message to set.  
	 * 
	 * @return whether the optimization objective index is set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setSolutionMessage(int solIdx, std::string msg);

	/**
	 * Set the [i]th optimization solution's number of primal variable values, where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the primal variable values. 
	 * @param n holds the number of elements in the array x
	 * 
	 * @return whether primal variable values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setNumberOfPrimalVariableValues(int solIdx, int n);
	
	/**
	 * Set the [i]th optimization solution's primal variable values, where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the primal variable values. 
	 * @param x holds a vector of type IndexValuePair; the idx component holds the index of the variable; 
	 * the value component holds its value. The vector could be null if all variables are 0.
	 * 
	 * @return whether primal variable values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setPrimalVariableValuesSparse(int solIdx, std::vector<IndexValuePair*> x);

	/**
	 * Set the [i]th optimization solution's primal variable values, where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the primal variable values. 
	 * @param x holds the a double dense array of variable values to set; it could be null if all variables are 0.
	 * 
	 * @return whether primal variable values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setPrimalVariableValuesDense(int solIdx, double *x);

	/**
	 * Set the [i]th optimization solution's other (non-standard/solver specific)variable-related results, 
	 * where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * This method then allocates the memory for the new OtherVariableResult objects
	 * @param solIdx is the solution index 
	 * @param numberOfOtherVariableResult holds the number of OtherVariableResult objects
	 * Each other variable result contains the name (required), an optional description (std::string) and an optional
	 * value (std::string). Each other variable result can also optionally contain an array OtherVarResult for each variable. 
	 * The OtherVarResult contains a variable idx (required) and an optional std::string value.   
	 * 
	 * @return whether the other variable results are set successfully or not. 
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OtherVariableResult
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OtherVarResult
	 * @see #setSolutionNumber(int)
	 */
	bool setNumberOfOtherVariableResults(int solIdx, int numberOfOtherVariableResults);
		
	/**
	 * Set the [i]th optimization solution's other (non-standard/solver specific)variable-related results, 
	 * where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index  
	 * @param otherIdx holds the index of the new OtherVariableResult object
	 * @param name holds the name of the other element
	 * @param value holds the value of the other element
	 * @param idx holds a pointer to the indexes of the var element
	 * @param s holds a pointer to the array of values of the var element
	 * @param n holds the number of elements of the array
	 *
	 * @return whether the other variable results are set successfully or not. 
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OtherVariableResult
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OtherVarResult
	 * @see #setSolutionNumber(int)
	 */
	bool setAnOtherVariableResultSparse(int solIdx, int otherIdx, std::string name, std::string value, std::string description, int *idx,  std::string *s, int n);

	/**
	 * Set the [i]th optimization solution's other (non-standard/solver specific)variable-related results, 
	 * where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index  
	 * @param otherIdx holds the index of the new OtherVariableResult object
	 * @param name holds the name of the other element
	 * @param value holds the value of the other element
	 * @param s holds a pointer to the array of values of the var element
	 *
	 * @return whether the other variable results are set successfully or not. 
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OtherVariableResult
	 * @see org.optimizationservices.oscommon.datastructure.osresult.OtherVarResult
	 * @see #setSolutionNumber(int)
	 */
	bool setAnOtherVariableResultDense(int solIdx, int otherIdx, std::string name, std::string value, std::string description, std::string *s);
	
	/**
	 * Set the [i]th optimization solution's number of objective values, where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the objective values. 
	 * @param n holds the number of elements in the array x
	 * 
	 * @return whether objective values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setNumberOfObjectiveValues(int solIdx, int n);

	
	/**
	 * Set the [i]th optimization solution's objective values, where i equals the given solution index.   
	 * Usually one of the objective is what the solution was solved for (or based on). Its index should be indicated 
	 * in the solution's objectiveIdx attribute. Based on this objective's solution, the rest of the objective 
	 * values are (optionally) calculated. 
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the objective values. 
	 * @param x holds a vector of type IndexValuePair; the idx component holds the index of the objective; 
	 * the value component holds its value. The vector could be null if all ojectives are 0.
	 * Possibly only the objective that the solution is based on has the value, and the rest of the objective
	 * values all get a Double.NaN value, meaning that they are not calculated.   
	 * 
	 * @return whether objective values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setObjectiveValuesSparse(int solIdx, std::vector<IndexValuePair*> x);
	
	/**
	 * Set the [i]th optimization solution's objective values, where i equals the given solution index.   
	 * Usually one of the objective is what the solution was solved for (or based on). Its index should be indicated 
	 * in the solution's objectiveIdx attribute. Based on this objective's solution, the rest of the objective 
	 * values are (optionally) calculated. 
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the objective values. 
	 * @param objectiveValues holds the double sparse array of objective values to set.
	 * Possibly only the objective that the solution is based on has the value, and the rest of the objective
	 * values all get a Double.NaN value, meaning that they are not calculated.   
	 * 
	 * @return whether objective values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setObjectiveValuesDense(int solIdx, double *objectiveValues);

	/**
	 * Set the [i]th optimization solution's number of dual variable values, where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the dual variable values. 
	 * @param n holds the number of elements in the array x
	 * 
	 * @return whether dual variable values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setNumberOfDualVariableValues(int solIdx, int n);
		

	/**
	 * Set the [i]th optimization solution's dual variable values, where i equals the given solution index. 
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the dual variable values. 
	 * @param x holds a vector of type IndexValuePair; the idx component holds the index of the constraint; 
	 * the value component holds its value. The vector could be null if all dual variables are 0.
	 * 
	 * @return whether dual variable values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */	
	bool setDualVariableValuesSparse(int solIdx, std::vector<IndexValuePair*> x);


	/**
	 * Set the [i]th optimization solution's dual variable values, where i equals the given solution index. 
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the dual variable values. 
	 * @param y holds a double dense array of variable dual values; it could be NULL if all values are 0.
	 * @return whether dual variable values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */	
	bool setDualVariableValuesDense(int solIdx, double *y);
	
	/**
	 * Set the [i]th optimization solution's constraint values, where i equals the given solution index.   
	 * Before this method is called, the setSolutionNumber(int) method has to be called first. 
	 * @param solIdx holds the solution index to set the constraint values. 
	 * @param constraintValues holds the a double dense array of constraint values to set; it could be null if all constraint values are 0.
	 * 
	 * @return whether constraint values are set successfully or not. 
	 * @see #setSolutionNumber(int)
	 */
	bool setConstraintValuesDense(int solIdx, double *constraintValues);



};
#endif

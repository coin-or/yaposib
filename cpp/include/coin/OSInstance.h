/* $Id: OSInstance.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSInstance.h
 * \brief This file defines the OSInstance class along with its supporting classes.
 *
 * @author  Robert Fourer, Gus Gassmann, Jun Ma, Kipp Martin, 
 * @version 2.0, 12/21/2007 
 * @since   OS1.0
 *
 * \remarks
 * Copyright (C) 2005-2007, Robert Fourer, Gus Gassmann, Jun Ma, Kipp Martin,
 * Northwestern University, Dalhousie University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 * 
<p> 1. Elements become objects of class type (the ComplexType is the class) </p>

<p> 2. The attributes, children of the element, and text correspond to members of the class.  </p>
(Note text does not have a name and becomes .value)

<p> 3. Model groups such as choice and sequence and all correspond to arrays </p>

<p><b>Exceptions:</b> </p>
<ol>
<li> anything specific to XML such as base64, multi, incr do not go into classes </li>
<li> The root OSnLNode of each <nl> element is called ExpressionTree </li>
<li> Root is not called osil; it is called osinstance </li>
</ol>
 */
 
 

#ifndef OSINSTANCE_H
#define OSINSTANCE_H
#include "OSParameters.h"
#include "OSDataStructures.h"
#include "OSnLNode.h"
#include "OSExpressionTree.h"
#include <string>
#include <map>


/*! \class InstanceHeader
 * \brief The in-memory representation of the 
 * <b><instanceHeader></b> element.
 */
class InstanceHeader{
public:

	/** The InstanceHeader class constructor */
	InstanceHeader();
	
	/** The InstanceHeader class destructor */
	~InstanceHeader();
	
	/** the problem instance description */
	std::string description;
	
	/** the name of the problem instance */
	std::string name;
	
	/** the source of the problem instance */
	std::string source;		
};//class InstanceHeader



/*! \class Variable
 * \brief The in-memory representation of the <b>variable</b> element.
 */
class Variable{
public:
	/** The Variable class constructor */
	Variable();
	
	/** The Variable class destructor */
	~Variable();

	/** lb corresponds to the optional attribute that holds the variable lower bound, 
	 * the default value is 0
	 */
	double lb;

	/** ub corresponds to the optional attribute that holds the variable upper bound,
	 * the default value is OSINFINITY 
	 */
	double ub;
	
	/** init corresponds to the optional attribute that holds the variable initial value,
	 * the default value is OSNAN  -- now deprecated
	 */
	//double init;
	
	/** type corresponds to the attribute that holds the variable type: C (Continuous),
	 * B (binary), I (general integer), or S (string). The default is C
	 */
	char type;
	
	/** name corresponds to the optional attribute that holds the variable name, the 
	 * default value is empty 
	 */ 
	std::string name;
	
	/** initString corresponds to the optional attribute that holds the name std::string 
	 * -- now deprecated
	 */
	//std::string initString;
}; // class Variable


/*! \class Variables
 * \brief The in-memory representation of the <b>variables</b> element.
 */
class Variables{
public:

	/** The Variables class constructor */
	Variables();
	
	/** The Variables class destructor */
	~Variables();
	
	/** numberOfVariables is the number of variables in the instance */
	int numberOfVariables;
	
	/** Here we define a pointer to an array of var pointers */
	Variable **var;
}; // class Variables


/*! \class ObjCoef
 * \brief The in-memory representation of the objective
 * function <b><coef></b> element.
 */
class ObjCoef{
public:

	/** The ObjCoef class constructor */
	ObjCoef();
	
	/** The ObjCoef class destructor */
	~ObjCoef();
	
	/** idx is the index of the variable corresponding
	 * to the coefficient
	 */
	int idx;
	
	/** value is the value of the objective function coefficient
	 * corresponding to the variable with index idx
	 */
	double value;
};//class Coef

/*! \class Constraint
 * \brief The in-memory representation of the 
 * <b><con></b> element.
 */
class Constraint{
public:

	/** The Constraint class constructor */
	Constraint();
	
	/** The Constraint class destructor */
	~Constraint();
	
	/** name is the name of the constraint */
	std::string name;
	
	/** constant is a value that is added to the constraint */
	double constant;
	
	/** lb is the lower bound on the constraint */
	double lb;
	
	/** ub is the upper bound on the constraint */
	double ub;
};//class Constraint


/*! \class Constraints
 * \brief The in-memory representation of the 
 * <b><constraints></b> element.
 */
class Constraints{
public:

	/** The Constraints class constructor */
	Constraints();
	
	/** The Constraints class destructor */
	~Constraints();
	
	/** numberOfConstraints is the number of 
	 * constraints in the instance
	 */
	int numberOfConstraints;
	
	/** con is pointer to an array of Constraint
	 * object pointers */
	Constraint **con;
};//class Constraints



/*! \class Objective
 * \brief The in-memory representation of the 
 * <b><obj></b> element.
 */
class Objective{
public:

	/** The Objective class constructor */
	Objective();
	
	/** The Objective class destructor */
	~Objective();
	
	/** the name of the objective function */
	std::string name;
	
	/** declare the objective function to be
	 * a max or a min 
	 */
	std::string maxOrMin;
	
	/** constant is the constant term added to the
	 * objective function, 0 by default
	 */
	double constant;
	
	/** weight is the weight applied to the given
	 * objective function, 1.0 by default
	 */
	double weight;
	
	/** numberOfObjCoef is the number of variables
	 * with a nonzero objective function coefficient
	 */
	int numberOfObjCoef;
	
	/** coef is pointer to an array of ObjCoef
	 * object pointers */	
	ObjCoef **coef;
};//class Objective

/*! \class Objectives
 * \brief The in-memory representation of the 
 * <b><objectives></b> element.
 */
class Objectives{
public:

	/** The Objectives class constructor */	
	Objectives();
	
	/** The Objectives class destructor */
	~Objectives();
	
	/** numberOfObjectives is the number of objective 
	 * functions in the instance
	 */
	int numberOfObjectives;
	
	/** coef is pointer to an array of ObjCoef
	 * object pointers */	
	Objective **obj;
};//class Objectives

/*! \class LinearConstraintCoefficients
 * \brief The in-memory representation of the 
 * <b><linearConstraintCoefficients></b> element.
 * 
 * \remarks
 * if a large part of the problem is linear, then
 * store this is the standard sparse format, either by
 * column or row. There are three arrays, an array of 
 * nonzero values, an array of either column or row indices
 * and then a pointer to the start of each column or row.
 */
class LinearConstraintCoefficients{
public:

	/** The LinearConstraintCoefficients class constructor */	
	LinearConstraintCoefficients();
	
	/** The LinearConstraintCoefficients class destructor */
	~LinearConstraintCoefficients();
	
	/** numberOfValues is the number of nonzero elements stored
	 * in the <linearConstraintCoefficients> element
	 */
	int numberOfValues;
	
	/** a pointer to the start of each row or column stored in
	 * sparse format
	 */
	IntVector *start;
	
	/** a pointer of row indices if the problem is stored by column */
	IntVector *rowIdx;
	
	/** a pointer of column indices if the problem is stored by row */
	IntVector *colIdx;
	
	/** a pointer to the array of nonzero values being stored */
	DoubleVector *value;
	/**
	 * iNumberOfStartElements counts the number of elements in the <start>
	 * section of <linearConstraintCoefficients> this is useful for the parser in
	 * checking consistency of the number of start elements with variables or
	 * rows
	 */
	int iNumberOfStartElements;
};//class LinearConstraintCoefficients


/*! \class QuadraticTerm
 * \brief The in-memory representation of the 
 * <b><qTerm></b> element.
 * 
 * \remarks
 * quadratic terms can be stored efficiently by storing
 * the index of each variable, the coefficient of the
 * quadratic term, and the row in which it appears
 */
class QuadraticTerm{
public:
    
	/** The QuadraticTerm class constructor */
	QuadraticTerm();
	
	/** The QuadraticTerm class destructor */
	~QuadraticTerm();
	
	/** idx is the index of the row in which the
	 * quadratic term appears
	 */
	int idx;
	
	/** idxOne is the index of the first variable in
	 * the quadratic term
	 */
    int idxOne;
    
    /** idxTwo is the index of the second variable in
     * the quadratic term
     */
    int idxTwo;
    
    /** coef is the coefficient of the quadratic term */
    double coef;
}; // QuadraticTerm




/*! \class QuadraticCoefficients
 * \brief The in-memory representation of the 
 * <b><quadraticCoefficients></b> element.
 * 
 */
class QuadraticCoefficients {
public:
    
    /** The QuadraticCoefficients class constructor */
	QuadraticCoefficients();
	
	/** The QuadraticCoefficients class destructor */
	~QuadraticCoefficients();
	
	/** numberOfQuadraticTerms is the number of quadratic
	 * terms in the <b><quadraticCoefficients></b> element.
	 */
	int numberOfQuadraticTerms;
	
	/** qTerm is a pointer to an array of QuadraticTerm
	 * object pointers */	
    QuadraticTerm** qTerm;
}; // QuadraticCoefficients


/*! \class Nl
 * \brief The in-memory representation of the 
 * <b><nl></b> element.
 */ 
class Nl{  
public:	
	/** idx holds the row index of the nonlinear expression */
	int idx;

	/** m_bDeleteExpressionTree is true, if in garbage collection, we
	 * should delete the osExpression tree object, if the OSInstance class
	 * created a map of the expression trees this should be false since the
	 * osExpressionTree is deleted by the OSInstance object 
	 */	
	bool m_bDeleteExpressionTree;
	
	/** osExpressionTree contains the root of the OSExpressionTree */
	OSExpressionTree *osExpressionTree;
	
	/**
	 * default constructor.
	 */
	Nl();

	/**
	 * default destructor.
	 */	
	~Nl();
};//end Nl

/*! \class NonlinearExpressions
 * \brief The in-memory representation of the 
 * <b><nonlinearExpressions></b> element.
 */
class NonlinearExpressions {
public:
    
    /** The NonlinearExpressions class constructor */
	NonlinearExpressions();
	
	/** The NonlinearExpressions class destructor */
	~NonlinearExpressions();
	
	/** numberOfNonlinearExpression is the number of
	 * <nl> elements in the 
	 * <b><nonlinearExpressions></b> element.
	 */
	int numberOfNonlinearExpressions;
	
	/** nl is pointer to an array of Nl
	 * object pointers */	
    Nl **nl;
}; // NonlinearExpression



/*! \class TimeDomainStageVar
 * \brief The in-memory representation of the 
 * <b><var></b> element.
 */
class TimeDomainStageVar {
public:
    
    /** The TimeDomainStageVar class constructor */
	TimeDomainStageVar();
	
	/** The TimeDomainStageVar class destructor */
	~TimeDomainStageVar();
	
	/** idx gives the index of this variable */
	int idx;
}; // TimeDomainStageVar

/*! \class TimeDomainStageVariables
 * \brief The in-memory representation of the 
 * <b><variables></b> child of the <stage> element.
 */
class TimeDomainStageVariables {
public:
    
    /** The TimeDomainStageVariables class constructor */
	TimeDomainStageVariables();
	
	/** The TimeDomainStageVariables class destructor */
	~TimeDomainStageVariables();
	
	/** numberOfVariables gives the number of variables contained in this stage */
	int numberOfVariables;

	/** startdIdx gives the number of the first variable contained in this stage */
	int startIdx;

	/** var is a pointer to an array of TimeDomainStageVar object pointers */
	TimeDomainStageVar** var;
}; // TimeDomainStageVariables


/*! \class TimeDomainStageCon
 * \brief The in-memory representation of the 
 * <b><con></b> element.
 */
class TimeDomainStageCon {
public:
    
    /** The TimeDomainStageCon class constructor */
	TimeDomainStageCon();
	
	/** The TimeDomainStageCon class destructor */
	~TimeDomainStageCon();
	
	/** idx gives the index of this constraint */
	int idx;
}; // TimeDomainStageCon

/*! \class TimeDomainStageConstraints
 * \brief The in-memory representation of the 
 * <b><constraints></b> child of the <stage> element.
 */
class TimeDomainStageConstraints {
public:
    
    /** The TimeDomainStageConstraints class constructor */
	TimeDomainStageConstraints();
	
	/** The TimeDomainStageConstraints class destructor */
	~TimeDomainStageConstraints();
	
	/** numberOfConstraints gives the number of constraints contained in this stage */
	int numberOfConstraints;

	/** startdIdx gives the number of the first constraint contained in this stage */
	int startIdx;

	/** con is a pointer to an array of TimeDomainStageCon object pointers */
	TimeDomainStageCon** con;
}; // TimeDomainStageConstraints


/*! \class TimeDomainStageObj
 * \brief The in-memory representation of the 
 * <b><obj></b> element.
 */
class TimeDomainStageObj {
public:
    
    /** The TimeDomainStageObj class constructor */
	TimeDomainStageObj();
	
	/** The TimeDomainStageObj class destructor */
	~TimeDomainStageObj();
	
	/** idx gives the index of this variable */
	int idx;
}; // TimeDomainStageObj

/*! \class TimeDomainStageObjectives
 * \brief The in-memory representation of the 
 * <b><objectives></b> child of the <stage> element.
 */
class TimeDomainStageObjectives {
public:
    
    /** The TimeDomainStageObjectives class constructor */
	TimeDomainStageObjectives();
	
	/** The TimeDomainStageObjectives class destructor */
	~TimeDomainStageObjectives();
	
	/** numberOfObjectives gives the number of objectives contained in this stage */
	int numberOfObjectives;

	/** startdIdx gives the number of the first objective contained in this stage */
	int startIdx;

	/** obj is a pointer to an array of TimeDomainStageObj object pointers */
	TimeDomainStageObj** obj;
}; // TimeDomainStageObjectives


/*! \class TimeDomainStage
 * \brief The in-memory representation of the 
 * <b><stage></b> element.
 */
class TimeDomainStage {
public:
    
    /** The TimeDomainStage class constructor */
	TimeDomainStage();
	
	/** The TimeDomainStage class destructor */
	~TimeDomainStage();
	
	/** name corresponds to the optional attribute that holds
	 * the name of the stage; the default value is empty
	 */
	std::string name;
	
	/** variables is a pointer to a TimeDomainVariables object */
	TimeDomainStageVariables *variables;

	/** constraints is a pointer to a TimeDomainConstraints object */
	TimeDomainStageConstraints *constraints;

	/** objectives is a pointer to a TimeDomainObjectives object */
	TimeDomainStageObjectives *objectives;
}; // TimeDomainStage
 
/*! \class TimeDomainStages
 * \brief The in-memory representation of the 
 * <b><stages></b> element.
 */
class TimeDomainStages {
public:
    
    /** The Stages class constructor */
	TimeDomainStages();
	
	/** The Stages class destructor */
	~TimeDomainStages();
	
	/** numberOfStages is the number of stages
	 * in the <b><stages></b> element.
	 */
	int numberOfStages;
	
	/** stage is pointer to an array of stage object pointers */	
    TimeDomainStage **stage;
}; // Stages
 
/*! \class Interval
 * \brief The in-memory representation of the 
 * <b><interval></b> element.
 */
class TimeDomainInterval {
public:
    
    /** The Interval class constructor */
	TimeDomainInterval();
	
	/** The Interval class destructor */
	~TimeDomainInterval();
	
	/** start is the start of the planning period
	 * in the <b><interval></b> element.
	 */
	double start;
	
	/** horizon is the end of the planning period
	 * in the <b><interval></b> element.
	 */
	double horizon;
}; // Interval
 
/*! \class TimeDomain
 * \brief The in-memory representation of the 
 * <b><timeDomain></b> element.
 */
class TimeDomain {
public:
    
    /** The TimeDomain class constructor */
	TimeDomain();
	
	/** The TimeDomain class destructor */
	~TimeDomain();

	/** stages is a pointer to a Stages object 
	 */
	TimeDomainStages *stages;

	/** interval is a pointer to an Interval object 
	 */
	TimeDomainInterval *interval;
}; // TimeDomain

/*! \class InstanceData
 * \brief The in-memory representation of the 
 * <b><instanceData></b> element.
 * \remarks 
 * The InstanceData object contains the objects
 * that define the instance --
 * <ul>
 * <li><b>Variables</b> object</li>
 * <li><b>Objectives</b> object</li>
 * <li><b>Constraints</b> object</li>
 * <li><b>LinearConstraintCoefficients</b> object</li>
 * <li><b>QuadraticCoefficients</b> object</li>
 * <li><b>NonlinearExpressions/b> object</li>
 * <li><b>TimeDomain/b> object</li>
 * </ul>
 */
class InstanceData{
public:

	/** The InstanceData class constructor */
	InstanceData();
	
	/** The InstanceData class destructor */
	~InstanceData();
	
	/** variables is a pointer to a Variables object */
	Variables *variables;
	
	/** objectives is a pointer to a Objectives object */
	Objectives *objectives;
	
	/** constraints is a pointer to a Constraints object */
	Constraints *constraints;
	
	/** linearConstraintCoefficients is a pointer to a 
	 * LinearConstraintCoefficients object
	 */
	LinearConstraintCoefficients *linearConstraintCoefficients;
	
	/** quadraticCoefficients is a pointer to a 
	 * QuadraticCoefficients object
	 */
	QuadraticCoefficients* quadraticCoefficients;
	
	/** nonlinearExpressions is a pointer to a 
	 * NonlinearExpressions object
	 */	
	NonlinearExpressions* nonlinearExpressions;
	
	/** timeDomain is a pointer to a 
	 * TimeDomain object
	 */	
	TimeDomain* timeDomain;
}; // class InstanceData


/*! \class OSInstance OSInstance.h "OSInstance.h"
 *  \brief The in-memory representation of an OSiL instance..
 *
 * \remarks 
 * <p> 1. Elements become objects of class type 
 *  (the ComplexType is the class) </p>
 *
 * <p> 2. The attributes, children of the element, and text 
 * correspond to members of the class.  
 * (Note text does not have a name and becomes .value) </p>
 *
 * <p> 3. Model groups such as choice and sequence 
 *  and all correspond to arrays </p>
 *
 * <ol>
 * <li> anything specific to XML such as base64, multi, 
 * incr do not go into classes </li>
 * <li> The root OSnLNode of each <nl> element is called ExpressionTree </li>
 * <li> Root is not called osil it is called osinstance </li>
 * </ol>
 * 
 * The OSInstance class is composed of two objects: an InstanceHeader object
 * and and InstanceData object
 *
 * 
 */
class OSInstance {
public:

	/** The OSInstance class constructor */
	OSInstance(); 
	
	/** The OSInstance class destructor */
	~OSInstance();
	
	/** A pointer to an InstanceHeader object */
	InstanceHeader *instanceHeader;
	
	/** A pointer to an InstanceData object */
	InstanceData *instanceData;
	
	/**
	 * bVariablesModified is true if the variables data has been modified. 
	 */
	bool bVariablesModified ;
	
	/**
	 * bObjectivesModified is true if the objective function data has been modified. 
	 */
	bool bObjectivesModified ;
	
	/**
	 * bConstraintsModified is true if the constraints data has been modified. 
	 */
	bool bConstraintsModified ;
	
	/**
	 * bAMatrixModified is true if the A matrix data has been modified. 
	 */
	bool bAMatrixModified ;
	


private:
	/**
	 * m_sInstanceName holds the instance name. 
	 */
	std::string m_sInstanceName;
	/**
	 * m_sInstanceSource holds the instance source. 
	 */
	std::string m_sInstanceSource;	
	/**
	 * m_sInstanceDescription holds the instance description. 
	 */
	std::string m_sInstanceDescription;
	
	/**
	 * m_bProcessVariables holds whether the variables are processed. 
	 */
	bool m_bProcessVariables ;
	
	/**
	 * m_iVariableNumber holds the variable number. 
	 */
	int m_iVariableNumber;
	
	/**
	 * m_iNumberOfIntegerVariables holds the number of integer variables. 
	 */
	int m_iNumberOfIntegerVariables;
	
	/**
	 * m_iNumberOfBinaryVariables holds the number of binary variables. 
	 */
	int m_iNumberOfBinaryVariables;
	
	/**
	 * m_iNumberOfStringVariables holds the number of integer variables. 
	 */
	int m_iNumberOfStringVariables;
	
	/**
	 * m_iNumberOfQuadraticRowIndexes holds the number of distinct rows and objectives with quadratic terms. 
	 */
	int m_iNumberOfQuadraticRowIndexes;
	
	/**
	 * m_bQuadraticRowIndexesProcessed is true if getQuadraticRowIndexes() has been called. 
	 */
	bool m_bQuadraticRowIndexesProcessed;

	/**
	 * m_miQuadRowIndexes is an integer pointer to the distinct rows indexes with a quadratic term. 
	 */	
	int *m_miQuadRowIndexes;
	
	/**
	 * m_iNumberOfNonlinearExpressionTreeIndexes holds the number of distinct rows and objectives with nonlinear terms. 
	 */
	int m_iNumberOfNonlinearExpressionTreeIndexes;
	
	/**
	 * m_bNonlinearExpressionTreeIndexesProcessed is true if getNonlinearExpressionTreeIndexes has been called. 
	 */
	bool m_bNonlinearExpressionTreeIndexesProcessed;

	/**
	 * m_miNonlinearExpressionTreeIndexes is an integer pointer to the distinct rows indexes in the nonlinear expression 
	 * tree map. 
	 */	
	int *m_miNonlinearExpressionTreeIndexes;
	
	/**
	 * m_iNumberOfNonlinearExpressionTreeModIndexes holds the number of distinct rows and objectives with nonlinear terms
	 * including quadratic terms added to the nonlinear expression trees. 
	 */
	int m_iNumberOfNonlinearExpressionTreeModIndexes;
	
	/**
	 * m_bNonlinearExpressionTreeModIndexesProcessed is true if getNonlinearExpressionTreeModIndexes has been called. 
	 */
	bool m_bNonlinearExpressionTreeModIndexesProcessed;

	/**
	 * m_miNonlinearExpressionTreeModIndexes is an integer pointer to the distinct rows indexes in the modified
	 * expression tree map. 
	 */	
	int *m_miNonlinearExpressionTreeModIndexes;
	
	/**
	 * m_msVariableNames holds an array of variable names. 
	 */
	std::string* m_msVariableNames;
	
	/**
	 * m_mdVariableInitialValues holds a double array of the initial variable values.
	 * -- now deprecated 
	 */
	//double* m_mdVariableInitialValues ;

	/**
	 * m_msVariableInitialStringValues holds a std::string array of the initial variable values.
	 * -- now deprecated 
	 */
	//std::string* m_msVariableInitialStringValues;

	/**
	 * m_mcVariableTypes holds a char array of variable types (default = 'C').
	 * (C for Continuous; B for Binary; I for Integer; S for String)
	 */
	char* m_mcVariableTypes;

	/**
	 * m_mdVariableLowerBounds holds a double array of variable lower bounds (default = 0.0).
	 */
	double* m_mdVariableLowerBounds;

	/**
	 * m_mdVariableUpperBounds holds a double array of variable upper bounds (default = INF).
	 */
	double* m_mdVariableUpperBounds;

	/**
	 * m_bProcessObjectives holds whether the objectives are processed. 
	 */
	bool m_bProcessObjectives;

	/**
	 * m_iObjectiveNumber is the number of objective functions. 
	 */
	int m_iObjectiveNumber;
	
	/**
	 * m_iObjectiveNumber is the number of objective functions with a nonlinear term. 
	 */
	int m_iObjectiveNumberNonlinear;
	
	/**
	 * m_msObjectiveNames holds an array of objective names. 
	 */
	std::string* m_msObjectiveNames;
	
	/**
	 * m_msMaxOrMins holds a std::string array of objective maxOrMins ("max" or "min").  
	 */
	std::string* m_msMaxOrMins;
	
	/**
	 * m_miNumberOfObjCoef holds an integer array of number of objective coefficients (default = 0.0). 
	 */
	int* m_miNumberOfObjCoef;
	
	/**
	 * m_mdObjectiveConstants holds an array of objective constants (default = 0.0). 
	 */
	double* m_mdObjectiveConstants;
	
	/**
	 * m_mdObjectiveWeights holds an array of objective weights (default = 1.0).
	 */
	double* m_mdObjectiveWeights;
	
	/**
	 * m_mObjectiveCoefficients holds an array of objective coefficients, one set of objective 
	 * coefficients for each objective. 
	 */
	SparseVector** m_mObjectiveCoefficients;
	
	/**
	 * m_bGetDenseObjectives holds whether the dense objective functions are processed. 
	 */
	bool m_bGetDenseObjectives;
	
	/**
	 * m_mmdDenseObjectiveCoefficients holds an array of pointers, each pointer points 
	 * to a vector of dense objective function coefficients 
	 */
	double** m_mmdDenseObjectiveCoefficients;

	/**
	 * m_bProcessConstraints holds whether the constraints are processed. 
	 */
	bool m_bProcessConstraints;
	
	/**
	 * m_iConstraintNumber is the number of constraints. 
	 */
	int m_iConstraintNumber;
	
	/**
	 * m_iConstraintNumberNonlinear is the number of constraints that have a nonlinear term. 
	 */
	int m_iConstraintNumberNonlinear;

	/**
	 * m_msConstraintNames holds an array of constraint names. 
	 */
	std::string* m_msConstraintNames;
	
	/**
	 * m_mdConstraintLowerBounds holds an array of constraint lower bounds (default = -INF). 
	 */
	double* m_mdConstraintLowerBounds;

	/**
	 * m_mdConstraintUpperBounds holds an array of constraint upper bounds (default = INF). 
	 */
	double* m_mdConstraintUpperBounds;
	
	/**
	 * m_mdConstraintConstants holds an array of constraint constants (default = 0.0). 
	 */

	double* m_mdConstraintConstants;

	/**
	 * m_mcConstraintTypes holds a char array of constraint types
	 * (R for range; L for <=; G for >=; E for =; U for unconstrained)
	 */
	char* m_mcConstraintTypes;
	
	/**
	 * m_bProcessLinearConstraintCoefficients holds whether the linear constraint coefficients are processed. 
	 */
	bool m_bProcessLinearConstraintCoefficients;
	
	/**
	 * m_iLinearConstraintCoefficientNumber holds the number of specified 
	 * (usually nonzero) linear constraint coefficient values. 
	 */
	int m_iLinearConstraintCoefficientNumber;

	/**
	 * m_bColumnMajor holds whether the linear constraint coefficients are stored in column major. 
	 */
	bool m_bColumnMajor;
	
	/**
	 * m_binitForAlgDiff  is true if initForAlgDiff() has been called.
	 */	
	bool m_binitForAlgDiff;


	/**
	 * m_linearConstraintCoefficientsInColumnMajor holds the standard 3 array data structure for linear constraint coefficients 
	 * (starts, indexes and values) in column major. 
	 */
	SparseMatrix* m_linearConstraintCoefficientsInColumnMajor ;

	/**
	 * m_linearConstraintCoefficientsInRowMajor holds the standard 3 array data structure for linear constraint coefficients 
	 * (starts, indexes and values) in row major. 
	 */
	SparseMatrix* m_linearConstraintCoefficientsInRowMajor ;

	
	/**
	 * m_bProcessQuadraticTerms holds whether the quadratic terms are processed. 
	 */
	bool m_bProcessQuadraticTerms ;

	/**
	 * m_iQuadraticTermNumber holds the number of specified 
	 * (usually nonzero) qTerms in the quadratic coefficients. 
	 */
	int m_iQuadraticTermNumber ;

	/**
	 * m_mdConstraintFunctionValues holds a double array of constraint function values -- the size of the array is equal to getConstraintNumber().  
     */
    double *m_mdConstraintFunctionValues;
    
    /**
	 * m_mdObjectiveFunctionValues holds a double array of objective function values -- the size of the array is equal to getObjectiveNumber().  
     */
    double *m_mdObjectiveFunctionValues;

    /**
	 * m_iJacValueSize is the number of nonzero partial derivates in the Jacobian.  
     */    
 	int m_iJacValueSize;
    
    /**
	 * m_miJacStart holds a int array of starts for the Jacobian matrix in sparse form (row major).  
     */    
 	int *m_miJacStart;
 	
     /**
	 * m_miJacIndex holds a int array of variable indices for the Jacobian matrix in sparse form (row major).  
     */    
 	int *m_miJacIndex;
 	
     /**
	 * m_mdJacValue holds a double array of partial derivatives for the Jacobian matrix in sparse form (row major).  
     */    
 	double *m_mdJacValue;
 	
 	
 	/**
	 * m_miJacNumConTerms holds a int array of the number of constant
	 * terms (gradient does not change) for the Jacobian matrix in sparse form (row major).  
     */    
 	int *m_miJacNumConTerms;
 
  	/**
	 * m_sparseJacMatrix is the Jacobian matrix stored in sparse matrix format
     */  	
 	SparseJacobianMatrix *m_sparseJacMatrix;
 	
 	/**
	 * m_iHighestTaylorCoeffOrder is the order of highest calculated
	 * Taylor coefficient  
	 */	 
	 int m_iHighestTaylorCoeffOrder;
	
	/**
	 * m_quadraticTerms the data structure for all the quadratic terms in the instance. `
	 * (rowIdx, varOneIdx, varTwoIdx, coef)
	 */
	 QuadraticTerms* m_quadraticTerms;
	 
	/** m_bQTermsAdded is true if we add the quadratic terms to the expression tree
	 */
	 bool m_bQTermsAdded;
	 
	/**
	 * m_iNumberOfNonlinearVariables is the number of variables that appear 
	 * in a nonlinear expression.
	 */
	unsigned int m_iNumberOfNonlinearVariables ;
	 
	/**
	 * m_bProcessNonlinearExpressions holds whether the nonlinear expressions are processed. 
	 */
	bool m_bProcessNonlinearExpressions ;
	
	/**
	 * m_iNonlinearExpressionNumber holds the number of nonlinear expressions. 
	 */
	int m_iNonlinearExpressionNumber;

	/**
	 * m_miNonlinearExpressionIndexes holds an integer array of nonlinear expression indexes,
	 * negative indexes correspond to objectives.  
	 */
	int* m_miNonlinearExpressionIndexes ;
	
	/**
	 * m_bProcessExpressionTrees is true if the expression trees have been processed. 
	 */
	bool m_bProcessExpressionTrees;
	
	/**
	 * m_bProcessExpressionTreesMod is true if the modified expression trees have been processed. 
	 */
	bool m_bProcessExpressionTreesMod;
	
	/**
	 * m_mapExpressionTrees holds a hash map of expression tree pointers, with the key being the row index
	 * and value being the expression tree representing the nonlinear expression of that row.
	 */
	std::map<int, OSExpressionTree*> m_mapExpressionTrees ;
	
	
	
	std::map<int, int> m_mapOSADFunRangeIndex ;
	
	/**
	 * m_LagrangianExpTree is an OSExpressionTree object that is the expression tree
	 * for the Lagrangian function.
	 */
	OSExpressionTree *m_LagrangianExpTree ;
	
	/**
	 * m_bLagrangianHessionCreated is true if a Lagrangian function for the Hessian has been created
	 */ 
	bool m_bLagrangianExpTreeCreated ;
	
	/**
	 *m_LagrangianSparseHessian is the Hessian Matrix of the Lagrangian function in sparse format
	 */ 	
	SparseHessianMatrix* m_LagrangianSparseHessian;
	
	/**
	 * m_bLagrangianSparseHessianCreated is true if the sparse Hessian Matrix for the 
	 * Lagrangian was created
	 */ 
	bool m_bLagrangianSparseHessianCreated;
	
	/**
	 * m_mapAllNonlinearVariablesIndexMap is a map of the variables in the Lagrangian function
	 */ 	
	 std::map<int, int> m_mapAllNonlinearVariablesIndex;

	/**
	 * m_miNonLinearVarsReverseMap maps the nonlinear variable number back into the original variable space
	 */ 	 
	int *m_miNonLinearVarsReverseMap;
	 
	/**
	 * m_bAllNonlinearVariablesIndexMap is true if the map of the variables in the 
	 * Lagrangian function has been constructed
	 */ 	
	 bool m_bAllNonlinearVariablesIndex;
	
	/**
	 * m_mapExpressionTreesMod holds a map of expression trees, with the key being the row index
	 * and value being the expression tree representing a modification of the nonlinear expression of that row.
	 * We incorporate the linear and quadratic term for a variable into the corresponding expression tree before
	 * gradient and Hessian calculations
	 */
	std::map<int, OSExpressionTree*> m_mapExpressionTreesMod ;
	
	/**
	 * m_bOSADFunIsCreated is true if we have created the OSInstanc
	 * OSAD Function
	 */	  
	 bool m_bOSADFunIsCreated;
	
	/**
	 * is true if a CppAD Expresion Tree has been built for each row and objective 
	 * with a nonlinear expression.
	 */
	bool m_bCppADTapesBuilt;
	
	/**
	 * is true if a CppAD Expresion Tree has an expression that can change depending on
	 * the value of the input, e.g. an if statement -- false by default
	 */
	bool m_bCppADMustReTape;
	
	/**
	 * m_bDuplicateExpressionTreeMap is true if m_mapExpressionTrees was duplicated. 
	 */
	bool m_bDuplicateExpressionTreesMap;
	
	/**
	 * m_bNonLinearStructuresInitialized is true if initializeNonLinearStructures( ) has been called. 
	 */
	bool m_bNonLinearStructuresInitialized;

	/**
	 * m_bSparseJacobianCalculated is true if getJacobianSparsityPattern() has been called. 
	 */
	bool m_bSparseJacobianCalculated;
	
	/**
	 * m_mapExpressionTrees holds a hash map of expression trees in postfix format, with the key being the row index
	 * and value being the expression tree representing the nonlinear expression of that row.
	 */
	std::map<int, std::vector<OSnLNode*> > m_mapExpressionTreesInPostfix ;
	 
	
	/**
	 * m_iHighestOrderEvaluated is the highest order derivative
	 * of the current iterate
	 */	 
	 int m_iHighestOrderEvaluated;
	 
	/**
	 * m_mdObjGradient holds an array of pointers, each pointer points 
	 * to gradient of each objective function
	 */
	double **m_mmdObjGradient;
	
	//define the vectors	

	/**
	 * m_vdX is a vector of primal variables at each iteration
	 *   
	 */		
	std::vector<double> m_vdX;
	
	/**
	 * m_vdYval is a vector of function values
	 *   
	 */	
	std::vector<double> m_vdYval;
	
	/**
	 * m_vbLagHessNonz is a boolean vector holding the nonzero pattern
	 * of the Lagrangian of the Hessian
	 *   
	 */	
	std::vector<bool> m_vbLagHessNonz;
	
	/**
	 * m_vdYval is a vector equal to a column or row of the Jacobian
	 *   
	 */	
	std::vector<double> m_vdYjacval;

	/**
	 * m_vdYval is a vector of derivatives -- output  from a reverse sweep
	 *   
	 */		
	std::vector<double> m_vdw;
	
	/**
	 * m_vdYval is a vector of Lagrange multipliers
	 *   
	 */		
	std::vector<double> m_vdLambda;
	
	
	/**
	 * m_vdDomainUnitVec is a unit vector in the domain space
	 *   
	 */		
	std::vector<double> m_vdDomainUnitVec;
	
	/**
	 * m_vdRangeUnitVec is a unit vector in the range space
	 *   
	 */		
	std::vector<double> m_vdRangeUnitVec;
	

	/**
	 * m_bProcessTimeDomain holds whether the time domain has been processed. 
	 */
	bool m_bProcessTimeDomain;

	/**
	 * m_bProcessTimeStages holds whether the time stages have been processed. 
	 */
	bool m_bProcessTimeStages;

	/**
	 * m_bProcessTimeInterval holds whether a time interval has been processed. 
	 */
	bool m_bProcessTimeInterval;

	/**
	 * m_bFiniteTimeStages holds whether the time domain has the form of finite (discrete) stages. 
	 */
	bool m_bFiniteTimeStages;

	/**
	 * m_iNumberOfTimeStages holds the number of discrete stages
	 */
	int m_iNumberOfTimeStages;

	/**
	 * m_sTimeDomainFormat holds the format ("stages"/"interval") of the time domain.
	 */
	std::string m_sTimeDomainFormat;

	/**
	 * m_msTimeDomainStageNames holds the names of the time stages.
	 *
	 */
	std::string* m_msTimeDomainStageNames;

	/**
	 * m_miTimeDomainStageVariableNumber holds the number of variables in each stage.
	 *
	 */
	int* m_miTimeDomainStageVariableNumber;

	/**
	 * m_mmiTimeDomainStageVarList holds the list of variables in each stage.
	 *
	 */
	int** m_mmiTimeDomainStageVarList;

	/**
	 * m_miTimeDomainStageConstraintNumber holds the number of constraints in each stage.
	 *
	 */
	int* m_miTimeDomainStageConstraintNumber;

	/**
	 * m_mmiTimeDomainStageConList holds the list of constraints in each stage.
	 *
	 */
	int** m_mmiTimeDomainStageConList;

	/**
	 * m_miTimeDomainStageObjectiveNumber holds the number of objectives in each stage.
	 *
	 */
	int* m_miTimeDomainStageObjectiveNumber;

	/**
	 * m_mmiTimeDomainStageObjList holds the list of objectives in each stage.
	 *
	 */
	int** m_mmiTimeDomainStageObjList;


	/**
	 * process variables. 
	 * 
	 * @return true if the variables are processed. 
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 */
	bool processVariables()	;
	
	/**
	 * process objectives. 
	 * 
	 * @return true if the objectives are processed. 
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	bool processObjectives();
	
	
	/**
	 * process constraints. 
	 * 
	 * @return true if the constraints are processed. 
	 * @throws Exception if the elements in constraints are logically inconsistent. 
	 */
	bool processConstraints();
	
	
	/**
	 * process linear constraint coefficients. 
	 * 
	 * @return true if the linear constraint coefficients are processed. 
	 * @throws Exception if the elements in linear constraint coefficients are logically inconsistent. 
	 */
	bool processLinearConstraintCoefficients();
	
	
public:

	/**
	 * Get instance name. 
	 * @return instance name. Null or empty std::string ("") if there is no instance name. 
	 */
	std::string getInstanceName();
		

	/**
	 * Get instance source. 
	 * @return instance source. Null or empty std::string ("") if there is no instance source. 
	 */
	std::string getInstanceSource();
	
	
	/**
	 * Get instance description. 
	 * 
	 * @return instance description. Null or empty std::string ("") if there is no instance description. 
	 */
	std::string getInstanceDescription();
	
	/**
	 * Get variable number. 
	 * 
	 * @return variable number. 
	 */
	int getVariableNumber();
	
	/**
	 * Get variable names. 
	 * 
	 * @return a std::string array of variable names, null if no variable names.
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 */
	std::string* getVariableNames();
	
	/**
	 * Get variable initial values. 
	 * 
	 * @return a double array of variable initial values, null if no initial variable values.
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 * -- now deprecated
	 */
	//double* getVariableInitialValues();
	
	/**
	 * Get variable initial std::string values. 
	 * 
	 * @return a std::string array of variable initial values, null if no initial variable std::string values.
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 * -- now deprecated
	 */
	//std::string* getVariableInitialStringValues();
	
	/**
	 * Get variable types. 
	 * <ul>
	 * <li>C for Continuous </li>
	 * <li>B for Binary </li> 
	 * <li>I for Integer</li> 
	 * <li>S for String</li>
	 * </ul>
	 * @return a char array of variable types. 
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 */
	char* getVariableTypes();
	
	/**
	 * getNumberOfIntegerVariables
	 * @return an integer which is the number of I variables. 
	 */
	int getNumberOfIntegerVariables();
	
	/**
	 * getNumberOfBinaryVariables
	 * @return an integer which is the number of B variables. 
	 */
	int getNumberOfBinaryVariables();
	
	/**
	 * getNumberOfStringVariables
	 * @return an integer which is the number of S variables. 
	 */
	int getNumberOfStringVariables();
	
	/**
	 * Get variable lower bounds. 
	 * 
	 * @return a double array of variable lower bounds. 
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 */
	double* getVariableLowerBounds();
	
	/**
	 * Get variable upper bounds. 
	 * 
	 * @return a double array of variable upper bounds. 
	 * @throws Exception if the elements in variables are logically inconsistent. 
	 */
	double* getVariableUpperBounds();
	
	/**
	 * Get objective number. 
	 * 
	 * @return objective number. 
	 */
	int getObjectiveNumber();
	
	
	/**
	 * Get objective names. 
	 * 
	 * @return a std::string array of objective names. Null if no objective names.
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	std::string* getObjectiveNames();

	/**
	 * Get objective maxOrMins. One maxOrMin for each objective.
	 * 
	 * @return a std::string array of objective maxOrMins ("max" or "min"), null if no objectives. 
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	std::string* getObjectiveMaxOrMins();
	
	/**
	 * Get objective coefficient number. One number for each objective.
	 * 
	 * @return an integer array of size of which is equal to number of objectives, 
	 * each element of the array is the number of nonzero coefficients in that
	 * objective function, null if no objectives. 
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	int* getObjectiveCoefficientNumbers();
	
	/**
	 * Get objective constants. One constant for each objective.
	 * 
	 * @return a double array of objective constants, null if no objectives. 
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	double* getObjectiveConstants();
	
	/**
	 * Get objective weights. One weight for each objective.
	 * 
	 * @return a double array of objective weights, null if no objectives. 
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	double* getObjectiveWeights();
	
	/**
	 * Get objective coefficients. One set of objective coefficients for each objective.
	 * 
	 * @see org.optimizationservices.oscommon.datastructure.SparseVector
	 * @return an array of objective coefficients, null if objective coefficients. 
	 * Each member of the array is of type
	 * ObjectiveCoefficients. The ObjectiveCoefficients class contains two arrays:
	 * variableIndexes is an integer array and values is a double array of coefficient values. 
	 * @throws Exception if the elements in objectives are logically inconsistent. 
	 */
	SparseVector** getObjectiveCoefficients();
	
	/**
	 * getDenseObjectiveCoefficients. 
	 * 
	 * @return an vector of pointers, each pointer points to a dense vector of 
	 * ObjectiveCoefficients. 
	 */
	double** getDenseObjectiveCoefficients();
	
	/**
	 * Get constraint number. 
	 * 
	 * @return constraint number. 
	 */
	int getConstraintNumber();
	
	/**
	 * Get constraint names. 
	 * 
	 * @return a std::string array of constraint names, null if no constraint names.
	 * @throws Exception if the elements in constraints are logically inconsistent. 
	 */
	std::string* getConstraintNames();
	
	/**
	 * Get constraint lower bounds. 
	 * 
	 * @return a double array of constraint lower bounds, null if no constraints.
	 * @throws Exception if the elements in constraints are logically inconsistent. 
	 */
	double* getConstraintLowerBounds();
	
	/**
	 * Get constraint upper bounds. 
	 * 
	 * @return a double array of constraint upper bounds, null if constraints. 
	 * @throws Exception if the elements in constraints are logically inconsistent. 
	 */
	double *getConstraintUpperBounds();
	
	/**
	 * Get constraint types. 
	 * <ul>
	 * <li>R for range constraint lb <= constraint <= ub </li>
	 * <li>L for less than constraint  -INF <= con <= ub or con <= ub</li>
	 * <li>G for greater than constraint lb <= con <= INF or con >= lb </li>
	 * <li>E for equal to constraint  lb <= con <= ub where lb = ub  or con = lb/ub </li>
	 * <li>U for unconstrained constraint -INF <= con <= INF</li>
	 * </ul>
	 * @return a char array of constraint types, null if constraints.
	 * @throws Exception if the elements in constraints are logically inconsistent. 
	 */
	char* getConstraintTypes();
	
	/**
	 * Get number of specified (usually nonzero) linear constraint coefficient values. 
	 * 
	 * @return number of specified (usually nonzero) linear constraint coefficient values. 
	 */
	int getLinearConstraintCoefficientNumber();
	

	/**
	 * Get whether the constraint coefficients is in column major (true) or row major (false). 
	 * 
	 * @return whether the constraint coefficients is in column major (true) or row major (false).
	 * @throws Exception if the elements in linear constraint coefficients are logically inconsistent. 
	 */
	bool getLinearConstraintCoefficientMajor();
	
	
	/**
	 * Get linear constraint coefficients in column major. 
	 * @return a sparse matrix reprsentation of linear constraint coefficients in column major, null if no linear constraint coefficients. 
	 * @throws Exception if the elements in linear constraint coefficients are logically inconsistent. 
	 * @see org.optimizationservices.oscommon.datastructure.SparseMatrix	 
	 */
	SparseMatrix* getLinearConstraintCoefficientsInColumnMajor();
	
	/**
	 * Get linear constraint coefficients in row major. 
	 * @return a sparse matrix reprsentation of linear constraint coefficients in row major, null if no linear constraint coefficients. 
	 * @throws Exception if the elements in linear constraint coefficients are logically inconsistent. 
	 * @see org.optimizationservices.oscommon.datastructure.SparseMatrix
	 */
	SparseMatrix* getLinearConstraintCoefficientsInRowMajor();
	
	/**
	 * Get the number of specified (usually nonzero) qTerms in the quadratic coefficients. 
	 * 
	 * @return qTerm number. 
	 */
	int getNumberOfQuadraticTerms();
	
	/**
	 * Get all the quadratic terms in the instance. 
	 * 
	 * @return the QuadraticTerms data structure for all quadratic terms in the instance, null if no quadratic terms. 
	 * The QuadraticTerms contains four arrays: rowIndexes, varOneIndexes, varTwoIndexes, coefficients.
	 * @throws Exception if the elements in quadratic coefficients are logically inconsistent. 
	 * @see org.optimizationservices.oscommon.datastructure.QuadraticTerms
	 */
	QuadraticTerms* getQuadraticTerms();
	
	/**
	 * Get the indexes of rows which have a quadratic term. 
	 * 
	 * @return an integer pointer to the row indexes of rows with quadratic terms,
	 * objectives functions have index < 0
	 * NULL if there are no quadratic terms. 
	 */
	int* getQuadraticRowIndexes();
	
	/**
	 * Get the number of rows which have a quadratic term. 
	 * 
	 * @return an integer which is the number of distinct rows (including obj) with quadratic terms, 
	 */
	int getNumberOfQuadraticRowIndexes();
	
	/**
	 * Get number of nonlinear expressions. 
	 * 
	 * @return the number of nonlinear expressions. 
	 */
	int getNumberOfNonlinearExpressions();
	
	
	/**
	 * Get the expression tree for a given row index  
	 * 
	 * @return an expression tree
	 */
	OSExpressionTree* getNonlinearExpressionTree(int rowIdx);
	
	/**
	 * Get the expression tree for a given row index for
	 * the modified expression trees (quadratic terms added) 
	 * 
	 * @return an expression tree
	 */
	OSExpressionTree* getNonlinearExpressionTreeMod(int rowIdx);
	
	/**
	 * Get the postfix tokens for a given row index.  
	 * 
	 * @return a vector of pointers to OSnLNodes in postfix, if rowIdx
	 * does not index a row with a nonlinear term throw an exception
	 */
	std::vector<OSnLNode*> getNonlinearExpressionTreeInPostfix( int rowIdx); 
	
	/**
	 * Get the postfix tokens for a given row index for the modified
	 * Expression Tree (quadratic terms added).
	 * 
	 * @return a vector of pointers to OSnLNodes in postfix, if rowIdx
	 * does not index a row with a nonlinear term throw an exception
	 */
	std::vector<OSnLNode*> getNonlinearExpressionTreeModInPostfix( int rowIdx);  
	
	/**
	 * Get the prefix tokens for a given row index.  
	 * 
	 * @return a vector of pointers to OSnLNodes in prefix, if rowIdx
	 * does not index a row with a nonlinear term throw an exception
	 */
	std::vector<OSnLNode*> getNonlinearExpressionTreeInPrefix( int rowIdx); 
	
	/**
	 * Get the infix representation for a given row (or objective function) index.  
	 
	 * @param rowIdx is the index of the row we want to express in infix.
	 * @return a string representation of the tree, if rowIdx
	 * does not index a row with a nonlinear term throw an exception
	 */
	std::string getNonlinearExpressionTreeInInfix( int rowIdx);  
	
	
	/**
	 * Print the infix representation of the problem.  
	 * @return a string with the infix representation
	 */
	std::string printModel( ); 
	
	
	/**
	 * Print the infix representation of the row (which could be an
	 * an objective function row) indexed by rowIdx.  
	 *
	 * @param rowIdx is the index of the row we want to express in infix.
	 * @return a string with the infix representation
	 */
	std::string printModel( int rowIdx); 
	
	/**
	 * Get the prefix tokens for a given row index for the modified
	 * Expression Tree (quadratic terms added).  
	 * 
	 * @return a vector of pointers to OSnLNodes in prefix, if rowIdx
	 * does not index a row with a nonlinear term throw an exception
	 */
	std::vector<OSnLNode*> getNonlinearExpressionTreeModInPrefix( int rowIdx); 	

	
	/**
	 * @return the number of Objectives with a nonlinear term
	 */	
	int getNumberOfNonlinearObjectives();

	/**
	 * @return the number of Constraints with a nonlinear term
	 */		
	int getNumberOfNonlinearConstraints();
	
	/**
	 * @return a map: the key is the row index and the value is the corresponding expression tree
	 */		
	std::map<int, OSExpressionTree* > getAllNonlinearExpressionTrees();
	
	
	/**
	 * @return a map: the key is the row index and the value is the corresponding expression tree
	 */		
	std::map<int, OSExpressionTree* > getAllNonlinearExpressionTreesMod();
	
	 /**
   	 * Get all the nonlinear expression tree indexes, i.e. indexes of rows (objectives or constraints) that contain nonlinear expressions. 
   	 * 
   	 * @return a pointer to an integer array of nonlinear expression tree indexes. 
   	 */
	int* getNonlinearExpressionTreeIndexes(); 
	
	
	 /**
   	 * Get the number of unique Nonlinear expression tree indexes. 
   	 * 
   	 * @return the number of unique nonlinear expression tree indexes. 
   	 */
	int getNumberOfNonlinearExpressionTreeIndexes(); 
	
	
	 /**
   	 * Get all the nonlinear expression tree indexes, i.e. indexes of rows (objetives or constraints) that contain nonlinear expressions
   	 * after modifying the expression tree to contain quadratic terms. 
   	 * 
   	 * @return a pointer to an integer array of nonlinear expression tree indexes (including quadratic terms). 
   	 */
	int* getNonlinearExpressionTreeModIndexes(); 
	
	
	 /**
   	 * Get the number of unique Nonlinear expression tree indexes after
   	 * modifying the expression tree to contain quadratic terms. 
   	 * 
   	 * @return the number of unique nonlinear expression tree indexes (including quadratic terms). 
   	 */
	int getNumberOfNonlinearExpressionTreeModIndexes(); 
	
	
	 /**
   	 * Get the format of the time domain ("stages"/"interval")
   	 * 
   	 * @return the format of the time domain. 
   	 */
	std::string getTimeDomainFormat(); 
	
	 /**
   	 * Get the number of stages that make up the time domain
   	 * 
   	 * @return the number of time stages. 
   	 */
	int getTimeDomainStageNumber(); 
	
	 /**
   	 * Get the names of the stages (NULL or empty string ("") if a stage has not been given a name
   	 * 
   	 * @return the names of time stages. 
   	 */
	std::string* getTimeDomainStageNames(); 
	
	 /**
   	 * Get the number of variables contained in each time stage
   	 * 
   	 * @return a vector of size numberOfStages. 
   	 */
	int* getTimeDomainStageNumberOfVariables(); 
	
	 /**
   	 * Get the number of constraints contained in each time stage
   	 * 
   	 * @return a vector of size numberOfStages. 
   	 */
	int* getTimeDomainStageNumberOfConstraints(); 
	
	 /**
   	 * Get the number of objectives contained in each time stage
   	 * 
   	 * @return a vector of size numberOfStages. 
   	 */
	int* getTimeDomainStageNumberOfObjectives(); 
	
	 /**
   	 * Get the list of variables in each stage
   	 * 
   	 * @return one array of integers for each stage. 
   	 */
	int** getTimeDomainStageVarList(); 
	
	 /**
   	 * Get the list of constraints in each stage
   	 * 
   	 * @return one array of integers for each stage. 
   	 */
	int** getTimeDomainStageConList(); 
	
	 /**
   	 * Get the list of objectives in each stage
   	 * 
   	 * @return one array of integers for each stage. 
   	 */
	int** getTimeDomainStageObjList(); 

	 /**
   	 * Get the start for the time domain interval
   	 * 
   	 * @return start end of the time interval. 
   	 */
	double getTimeDomainIntervalStart(); 

	 /**
   	 * Get the horizon for the time domain interval
   	 * 
   	 * @return the end of the time interval. 
   	 */
	double getTimeDomainIntervalHorizon(); 
	
	
	
	// the set() methods
	
	
   	/**
   	 * set the instance source. 
   	 * 
   	 * @param source holds the instance source. 
   	 * @return whether the instance source is set successfully. 
   	 */
   	bool setInstanceSource(std::string source);
	
 	/**
   	 * set the instance description. 
   	 * 
   	 * @param description holds the instance description. 
   	 * @return whether the instance description is set successfully. 
   	 */
   	bool setInstanceDescription(std::string description);
	
					
   	/**
   	 * set the instance name. 
   	 * 
   	 * @param name holds the instance name. 
   	 * @return whether the instance name is set successfully. 
   	 */
   	bool setInstanceName(std::string name);
	
   	/**
   	 * set the variable number. 
   	 * 
   	 * @param number holds the variable number. 
   	 * @return whether the variable number is set successfully. 
  	 */
   	bool setVariableNumber(int number);
	
   	/**
   	 * add a variable. In order to use the add method, the setVariableNumber must first be called
   	 * so that the variable number is known ahead of time to assign appropriate memory.  
   	 * If a variable with the given variable index already exists, the old variable will be replaced. 
   	 * 
   	 * <p>
   	 * 
   	 * @param index holds the variable index. It is required.  
   	 * @param name holds the variable name; use null or empty std::string ("") if no variable name. 
   	 * @param lowerBound holds the variable lower bound; use Double.NEGATIVE_INFINITY if no lower bound. 
   	 * @param upperBound holds the variable upper bound; use Double.POSITIVE_INFINITY if no upper bound. 
   	 * @param type holds the variable type character, B for Binary, I for Integer, S for String, C or any other char for Continuous)
   	 * @param init holds the double variable initial value; use Double.NaN if no initial value -- deprecated
   	 * @param initString holds the std::string variable initial value; use null or empty std::string ("") 
   	 * if no initial std::string value -- deprecated
   	 * @return whether the variable is added successfully. 
   	 */
   	bool addVariable(int index, std::string name, double lowerBound, double upperBound, char type);
	
   	/**
   	 * set all the variable related elements. All the previous variable-related elements will be deleted. 
   	 * 
   	 * <p>
   	 * 
   	 * @param number holds the number of variables. It is required.  
   	 * @param names holds a std::string array of variable names; use null if no variable names. 
   	 * @param lowerBounds holds a double array of variable lower bounds; use null if all lower bounds are 0; 
	 *  use Double.NEGATIVE_INFINITY if no lower bound for a specific variable in the array. 
   	 * @param upperBounds holds a double array of variable upper bounds; use null if no upper bounds; 
	 *  use Double.POSITIVE_INFINITY if no upper bound for a specific variable in the array. 
   	 * @param types holds a char array of variable types; use null if all variables are continuous; 
   	 * for a specfic variable in the array use B for Binary, I for Integer, S for String, C or any other char for Continuous,)  
   	 * @param inits holds a double array of varible initial values; use null if no initial values. -- deprecated
   	 * @param initsString holds a std::string array of varible initial values; use null
   	 *  if no initial std::string values.  -- deprecated
   	 * @return whether the variables are set successfully. 
   	 */
   	bool setVariables(int number, std::string* names, double* lowerBounds, 
		double* upperBounds, char* types);

   	/**
   	 * set the objective number. 
   	 * 
   	 * @param number holds the objective number. 
   	 * @return whether the objective number is set successfully. 
   	 */
   	bool setObjectiveNumber(int number);
	
  	/**
   	 * add an objective. In order to use the add method, the setObjectiveNumber must first be called
   	 * so that the objective number is known ahead of time to assign appropriate memory.  
   	 * If a objective with the given objective index already exists, the old objective will be replaced.
   	 * Objective index will start from -1, -2, -3, ... down, with -1 corresponding to the first objective.  
   	 * 
   	 * <p>
   	 * 
   	 * @param index holds the objective index. Remember the first objective index is -1, second -2, ...
   	 * @param name holds the objective name; use null or empty std::string ("") if no objective name. 
   	 * @param maxOrMin holds the objective sense or direction; it can only take two values: "max" or "min". 
   	 * @param constant holds the objective constant; use 0.0 if no objective constant. 
   	 * @param weight holds the objective weight; use 1.0 if no objective weight.
   	 * @param objectiveCoefficients holds the objective coefficients (null if no objective coefficients) in a sparse 
   	 * representation that holds two arrays: index array and a value array.  
   	 * @return whether the objective is added successfully. 
   	 */
   	bool addObjective(int index, std::string name, std::string maxOrMin, double constant, double weight, SparseVector* objectiveCoefficients);

   	/**
   	 * set all the objectives related elements. All the previous objective-related elements will be deleted. 
   	 * 
   	 * <p>
   	 * 
   	 * @param number holds the number of objectives. It is required.  
   	 * @param names holds a std::string array of objective names; use null if no objective names. 
   	 * @param maxOrMins holds a std::string array of objective objective senses or directions: "max" or "min"; use null if all objectives are "min".   
   	 * @param constants holds a double array of objective constants; use null if all objective constants are 0.0. 
   	 * @param weights holds a double array of objective weights; use null if all objective weights are 1.0. 
     * @param objectitiveCoefficients holds an array of objective coefficients, (null if no objective have any coefficeints)
     * For each objective, the coefficients are stored in a sparse representation that holds two arrays: index array and a value array.  
     * If for a specific objective, there are no objecitve coefficients, use null for the corresponding array member. 
  	 * @return whether the objectives are set successfully. 
   	 */
   	bool setObjectives(int number, std::string *names, std::string *maxOrMins, double *constants, double *weights, SparseVector **objectitiveCoefficients);
					
  	/**
   	 * set the constraint number. 
   	 * 
   	 * @param number holds the constraint number. 
   	 * @return whether the constraint number is set successfully. 
   	 */
   	bool setConstraintNumber(int number);

/**
 * add a constraint. In order to use the add method, the setConstraintNumber must first be called
 * so that the constraint number is known ahead of time to assign appropriate memory.  
 * If a constraint with the given constraint index already exists, the old constraint will be replaced. 
 * 
 * <p>
 * 
 * @param index holds the constraint index. It is required.  
 * @param name holds the constraint name; use null or empty std::string ("") if no constraint name. 
 * @param lowerBound holds the constraint lower bound; use Double.NEGATIVE_INFINITY if no lower bound. 
 * @param upperBound holds the constraint upper bound; use Double.POSITIVE_INFINITY if no upper bound. 
 * @return whether the constraint is added successfully. 
 */
bool addConstraint(int index, std::string name, double lowerBound, double upperBound, double constant);

/**
 * set all the constraint related elements. All the previous constraint-related elements will be deleted. 
 * 
 * <p>
 * 
 * @param number holds the number of constraints. It is required.  
 * @param names holds a std::string array of constraint names; use null if no constraint names. 
 * @param lowerBounds holds a double array of constraint lower bounds; use null if no lower bounds; use Double.NEGATIVE_INFINITY if no lower bound for a specific constraint in the array. 
 * @param upperBounds holds a double array of constraint upper bounds; use null if no upper bounds; use Double.POSITIVE_INFINITY if no upper bound for a specific constraint in the array. 
 * @return whether the constraints are set successfully. 
 */
bool setConstraints(int number, std::string* names, double* lowerBounds, double* upperBounds, double* constants);

/**
 * set linear constraint coefficients
 * 
 * <p>
 * 
 * @param numberOfValues holds the number of specified coefficient values (usually nonzero) in the coefficient matrix. 
 * @param isColumnMajor holds whether the coefficient matrix is stored in column major (true) or row major (false).
 * @param values holds a double array coefficient values in the matrix. 
 * @param valuesBegin holds the begin index of the values array to copy from (usually 0). 
 * @param valuesEnd holds the end index of the values array to copy till (usually values.lenght - 1). 
 * @param indexes holds an integer array column/row indexes for each value in the values array.
 * @param indexesBegin holds the begin index of the indexes array to copy from (usually 0).
 * @param indexesEnd holds the end index of the indexes array to copy till (usually indexes.lenght - 1).
 * @param starts holds an integer array start indexes in the matrix; the first value of starts should always be 0. 
 * @param startsBegin holds the begin index of the starts array to copy from (usually 0).
 * @param startsEnd holds the end index of the starts array to copy till (usually starts.lenght - 1). 
 * @return whether the linear constraint coefficients are set successfully.  
 */
bool setLinearConstraintCoefficients(int numberOfValues, bool isColumnMajor, 
	double* values, int valuesBegin, int valuesEnd, 
	int* indexes, int indexesBegin, int indexesEnd,   			
	int* starts, int startsBegin, int startsEnd);
	
	/**
	 * set quadratic terms
	 * 
	 * <p>
	 * 
	 * @param number holds the number of quadratic terms. 
	 * @param rowIndexes holds an integer array of row indexes of all the quadratic terms. 
	 * A negative integer corresponds to an objective row, e.g. -1 for 1st objective and -2 for 2nd.
	 * @param varOneIndexes holds an integer array of the first varialbe indexes of all the quadratic terms.
	 * @param varTwoIndexes holds an integer array of the second varialbe indexes of all the quadratic terms.
	 * @param coefficients holds a double array all the quadratic term coefficients.
	 * @param begin holds the begin index of all the arrays to copy from (usually = 0). 
	 * @param end holds the end index of all the arrays to copy till (usually = array length -1).
	 * @return whether the quadratic terms are set successfully.  
	 */
	bool setQuadraticTerms(int number, 
		int* rowIndexes, int* varOneIndexes, int* varTwoIndexes, double* coefficients,
		int begin, int end);
		
	/**
	 * set quadratic terms in nonlinearExpressions 
	 * 
	 * <p>
	 * 
	 * @param number holds the number of quadratic terms. 
	 * @param rowIndexes holds an integer array of row indexes of all the quadratic terms. 
	 * A negative integer corresponds to an objective row, e.g. -1 for 1st objective and -2 for 2nd.
	 * @param varOneIndexes holds an integer array of the first varialbe indexes of all the quadratic terms.
	 * @param varTwoIndexes holds an integer array of the second varialbe indexes of all the quadratic terms.
	 * @param coefficients holds a double array all the quadratic term coefficients.
	 * @return whether the quadratic terms are set successfully.  
	 */
	bool setQuadraticTermsInNonlinearExpressions(int number, 
		int* rowIndexes, int* varOneIndexes, int* varTwoIndexes, double* coefficients);
		
		
		
	// nonlinear API methods
	
	
	/**
	 * Initialize the data structures for the nonlinear API
	 * 
	 * @return true if we have initialized the nonlinear data strucutres.  
	 */
	bool initializeNonLinearStructures( );
	
	/**
	 * Calculate the function value for function (constraint or objective) 
	 * indexed by idx
	 * 
	 * <p>
	 * 
	 * @param idx is the index on the constraint (0, 1, 2, 3, ...) or objective function (-1, -2, -3, ...). 
	 * @param x is a pointer (double array) to the current variable values
 	 * @param new_x is false if any evaluation method was previously called for the current x
	 * has been evaluated for the current iterate x
	 * use a value of false if not sure
	 * @return the function value as a double.  
	 */
	double calculateFunctionValue(int idx, double* x, bool new_x);
	
	/**
	 * Calculate all of the constraint function values
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @param new_x is false if any evaluation method was previously called for the current x
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a double array of constraint function values -- the size of the array is equal to getConstraintNumber().  
	 */
	double *calculateAllConstraintFunctionValues(double* x, double *objLambda, double *conLambda,
		bool new_x, int highestOrder);
		
	/**
	 * Calculate all of the constraint function values, we are overloading this function
	 * and this version of the method will not use any AD and will evaluate function
	 * values from the OS Expression Tree
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @return a double array of constraint function values -- 
	 * the size of the array is equal to getConstraintNumber().  
	 */
	double *calculateAllConstraintFunctionValues(double* x, bool new_x);
	
	/**
	 * Calculate all of the objective function values
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a double array of objective function values -- the size of the array
	 *  is equal to getObjectiveNumber().  
	 */
	double *calculateAllObjectiveFunctionValues(double* x, double *objLambda, double *conLambda,
		bool new_x, int highestOrder);
	
	/**
	 * Calculate all of the objective function values, we are overloading this function
	 * and this version of the method will not use any AD and will evaluate function
	 * values from the OS Expression Tree
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @return a double array of objective function values -- 
	 * the size of the array is equal to getObjectiveNumber().  
	 */
	double *calculateAllObjectiveFunctionValues(double* x, bool new_x);	
		
	
	/**
	 * Calculate the gradient of all constraint functions  
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a pointer a SparseJacobianMatrix. 
	 */
	SparseJacobianMatrix *calculateAllConstraintFunctionGradients(double* x, double *objLambda, 
		double *conLambda, bool new_x, int highestOrder);		
		

	/**
	 * Calculate the gradient of the constraint function indexed by idx
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @parma idx is the index of the constraint function gradient
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a pointer to a sparse vector of doubles.  
	 */
	SparseVector *calculateConstraintFunctionGradient(double* x, double *objLambda, double *conLambda,
		int idx, bool new_x, int highestOrder);
		
	/**
	 * Calculate the gradient of the constraint function indexed by idx
	 * this function is overloaded
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @parma idx is the index of the constraint function gradient
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a pointer to a sparse vector of doubles.  
	 */
	SparseVector *calculateConstraintFunctionGradient(double* x, int idx, bool new_x );
	
	/**
	 * Calculate the gradient of all objective functions
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return an array of pointer to dense objective function gradients.  
	 */		
	double **calculateAllObjectiveFunctionGradients(double* x, double *objLambda, double *conLambda,
		bool new_x, int highestOrder);		

	/**
	 * Calculate the gradient of the objective function indexed by objIdx
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @parma objIdx is the index of the objective function being optimized
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a pointer to a dense vector of doubles.  
	 */
	double *calculateObjectiveFunctionGradient(double* x, double *objLambda, double *conLambda,
		int objIdx, bool new_x, int highestOrder);
		
	/**
	 * Calculate the gradient of the objective function indexed by objIdx
	 * this function is overloaded
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objIdx is the index of the objective function being optimized
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @return a pointer to a dense vector of doubles.  
	 */
	double *calculateObjectiveFunctionGradient(double* x, int objIdx, bool new_x );

	/**
	 * Calculate the Hessian of the Lagrangian Expression Tree
	 * This method will build the CppAD expression tree for only the first iteration
	 * Use this method on if the value of x does not affect the operations sequence.  
	 * 
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param objLambda is the Lagrange multiplier on the objective function
	 * @param conLambda is pointer (double array) of Lagrange multipliers on
	 * the constratins
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @param highestOrder is the highest order of the derivative being calculated
	 * @return a pointer a SparseHessianMatrix. 
	 * Each array member corresponds to one constraint gradient.
	 */
	SparseHessianMatrix *calculateLagrangianHessian( double* x, double *objLambda, double *conLambda,
		bool new_x, int highestOrder);
		
	/**
	 * Calculate the Hessian of a constraint or objective function
	 * <p>
	 * 
	 * @param x is a pointer (double array) to the current variable values
	 * @param new_x is false if any evaluation method was previously called
	 * for the current iterate
	 * @parma idx is the index of the either a constraint or objective
	 * function Hessian
	 * @return a pointer a SparseVector. 
	 * Each array member corresponds to one constraint gradient.
	 */
	SparseHessianMatrix *calculateHessian( double* x, int idx, bool new_x);
	
				
	/**
	 * 
	 * @return true if successful in generating the constraints gradient.
	 */
	bool getSparseJacobianFromColumnMajor();
	
	/**
	 * 
	 * @return true if successful in generating the constraints gradient.
	 */
	bool getSparseJacobianFromRowMajor();
	
	/**
	 * @return a pointer to the ExpressionTree for the Lagrangian function of current instance
	 * we only take the Lagrangian of the rows with nonlinear terms 
	 */
	OSExpressionTree* getLagrangianExpTree( );

	/**
	 * @return a pointer to a map of the indices of all of the variables
	 * that appear in the Lagrangian function 
	 */
	std::map<int, int> getAllNonlinearVariablesIndexMap( );	
	
	/**
	 * @return a pointer to a SparseHessianMatrix with the nonzero structure 
	 * of the Lagrangian Expression Tree
	 */
	SparseHessianMatrix* getLagrangianHessianSparsityPattern();
	
	/**
	 * 
	 * @return true if successful in adding the qTerms to the ExpressionTree.
	 */ 
	bool addQTermsToExressionTree();
	
	/**
	 * 
	 * @return pointer to a SparseJacobianMatrix.
	 */ 
	SparseJacobianMatrix *getJacobianSparsityPattern();
	
	/**
	 * 
	 *  duplicate the map of expression trees.
	 */	 
	void duplicateExpressionTreesMap();
	
#ifdef COIN_HAS_CPPAD  	 
	 /**
	  * F is a CppAD function the range space is the objective +
	  * constraints functions, x is the domeain space
	  */
	CppAD::ADFun<double> *Fad;
#endif
	/**
	 * Create the a CppAD Function object: this is a function where the domain is
	 * the set of variables for the problem and the range is the objective function 
	 * plus constraints
	 * 
	 * <p>
	 * 
	 * @param vdX is a vector of doubles holding the current primal variable values
	 * the size of x should equal instanceData->variables->numberOfVariables
	 * @return if successfully created
	 */	
	bool createOSADFun(std::vector<double> vdX );
	
	/**
	 * Perform an AD forward sweep  
	 * 
	 * <p>
	 * @param p is the highest order Taylor coefficient 
	 * @param vdX is a vector of doubles of the current primal variable values
	 * the size of vdX m_iNumberOfNonlinearVariables
	 * @return a double vector equal to the dimension of the range space
	 * the result of the forward p sweep 
	 */
	std::vector<double> forwardAD(int p, std::vector<double> vdX);

	/**
	 * Perform an AD reverse sweep  
	 * 
	 * <p>
	 * 
	 * @param p is the order of the sweep
	 * @param vdlambda is a vector of doubles of the current dual (lagrange) variable values
	 * the size of lambda should equal number of objective functions plus number of constraints
	 * @return a double vector equal to the n*p 
	 */	
	std::vector<double> reverseAD(int p, std::vector<double> vdlambda);
	 
	 /**
	  * end revised AD code
	  */
	
	
	/**
	 * Call the AD routine to fill in m_vbLagHessNonz and determine the nonzeros.
	 * 
	 * <p>
	 * 
	 * @return the number of nonzeros in the Hessian 
	 */	
	int  getADSparsityHessian();
	 
	 /**
	  * end revised AD code
	  */
	
	/**
	 * Get the information for each iteration. Get the functions values, Jacobian
	 * and Hessian of the Lagrangian   
	 * 
	 * <p>
	 * 
	 * @param x is a pointer of doubles of primal values  for the current iteration
	 * @param objLambda is is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the objective functions
	 * @param conLambda is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the constraints
	 * @param new_x is false if any evaluation method was previously called
	 * @param highestOrder is the highest order derivative to be calculated
	 * @return true if successful 
	 */		 
	bool getIterateResults(double *x, double *objLambda, double *conLambda,  
			bool new_x, int highestOrder);
			
			
			
	/**
	 * Calculate function values
	 * 
	 * <p>
	 * 
	 * @param x is a pointer of doubles of primal values  for the current iteration
	 * @param objLambda is is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the objective functions
	 * @param conLambda is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the constraints
	 * @return true if successful 
	 */		 
	bool getZeroOrderResults(double *x, double *objLambda, double *conLambda);
			
	/**
	 * Calculate first derivatives
	 * 
	 * <p>
	 * 
	 * @param x is a pointer of doubles of primal values  for the current iteration
	 * @param objLambda is is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the objective functions
	 * @param conLambda is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the constraints
	 * @return true if successful 
	 */		 
	bool getFirstOrderResults(double *x, double *objLambda, double *conLambda );
			
	/**
	 * Calculate second derivatives
	 * 
	 * <p>
	 * 
	 * @param x is a pointer of doubles of primal values  for the current iteration
	 * @param objLambda is is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the objective functions
	 * @param conLambda is a pointer of doubles of the current dual (Lagrange) multipliers
	 *  on the constraints
	 * @return true if successful 
	 */		 
	bool getSecondOrderResults(double *x, double *objLambda, double *conLambda );
			

	/**
	 * This should be called by nonlinear solvers using callback functions  
	 * 
	 * <p>
	 * 
	 * initForAlgDiff will initialize the correct nonlinear structures in preparation
	 * for using the algorithmic differentiation routines.
	 * @return true if successful 
	 */		 
	bool initForAlgDiff();
	
	/**
	 * This should be called by initForAlgDiff()
	 * 
	 * <p>
	 * 
	 * initObjGradients will initialize the objective function gradients to be equal to the 
	 * coefficients given in the <coef> section of the OSiL instance
	 * @return true if successful 
	 */		 
	bool initObjGradients();


	/**
	 * bUseExpTreeForFunEval is set to true if you wish to use the OS Expression Tree for
	 * function evaluations instead of AD -- false by default. 
	 */
	bool bUseExpTreeForFunEval;
	
	
	/**
	 * This sets the format of the time domain ("stages"/"interval"/"none")
	 */
	bool setTimeDomain(std::string format);
	
	/**
	 * This sets the number (and optionally names) of the time stages
	 */
	bool setTimeDomainStages(int number, std::string *names);

	/**
	* This sets the variables associated with each time domain stage in temporal order.
	* (I.e., for each stage numberOfVariables gives the number of variables accociated 
	* with this stage and startIdx gives the first variable in this stage.)
	*/
	bool setTimeDomainStageVariablesOrdered(int numberOfStages, int *numberOfVariables, int *startIdx);

	/**
	* This sets the variables associated with each time domain stage in srbitrary order.
	* (I.e., for each stage numberOfVariables gives the number of variables accociated 
	* with this stage and varIndex[i] gives the index of each variable in stage[i].)
	*/
	bool setTimeDomainStageVariablesUnordered(int numberOfStages, int *numberOfVariables, int **varIndex);

	/**
	* This sets the constraints associated with each time domain stage in temporal order.
	* (I.e., for each stage numberOfConstraints gives the number of constraints accociated 
	* with this stage and startIdx gives the first constraint in this stage.)
	*/
	bool setTimeDomainStageConstraintsOrdered(int numberOfStages, int *numberOfConstraints, int *startIdx);

	/**
	* This sets the constraints associated with each time domain stage in srbitrary order.
	* (I.e., for each stage numberOfConstraints gives the number of constraints accociated 
	* with this stage and conIndex[i] gives the index of each constraint in stage[i].)
	*/
	bool setTimeDomainStageConstraintsUnordered(int numberOfStages, int *numberOfConstraints, int **conIndex);

	/**
	* This sets the objectives associated with each time domain stage in temporal order.
	* (I.e., for each stage numberOfObjectives gives the number of objectives accociated 
	* with this stage and startIdx gives the first objective in this stage.)
	*/
	bool setTimeDomainStageObjectivesOrdered(int numberOfStages, int *numberOfObjectives, int *startIdx);

	/**
	* This sets the objectives associated with each time domain stage in arbitrary order.
	* (I.e., for each stage numberOfObjectives gives the number of objectives accociated 
	* with this stage and objIndex[i] gives the index of each objective in stage[i].)
	*/
	bool setTimeDomainStageObjectivesUnordered(int numberOfStages, int *numberOfObjectives, int **varIndex);

	/**
	 * This sets the start and end of the time interval
	 */
	bool setTimeDomainInterval(double start, double horizon);


}; //class OSInstance

#endif


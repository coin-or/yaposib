/* $Id: OSBonminSolver.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OSBonmnSolver.h
 * 
 * @author  Jun Ma, Gus Gassmann, Kipp Martin, 
 * @version 1.0, 07/05/2008
 * @since   OS1.0
 *
 * \remarks
 * Copyright (C) 2008, Jun Ma, Kipp Martin,
 * Northwestern University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */ 
 
#ifndef BONMINSOLVER_H 
#define BONMINSOLVER_H

#include "OSConfig.h" 
#include "OSDefaultSolver.h"
#include "OSrLWriter.h"
#include "OSInstance.h"
#include "OSParameters.h"
#include "OSnLNode.h"
#include "OSiLReader.h"
#include "OSrLReader.h"
#include "OSoLReader.h"
#include "OSInstance.h"
#include "OSExpressionTree.h"
#include "OSnLNode.h"
#include "OSDataStructures.h"
#include "OSFileUtil.h"  
#include "OSErrorClass.h"

#include "OSResult.h"
#include "OSInstance.h"
#include "OSOption.h"

# include <cstddef>
# include <cstdlib>
# include <cctype>
# include <cassert>
# include <stack>
#include <string>
# include <cppad/cppad.hpp>
#include<iostream>

#ifdef HAVE_CTIME
# include <ctime>
#else
# ifdef HAVE_TIME_H
#  include <time.h>
# else
#  error "don't have header file for time"
# endif
#endif 

 
#ifdef HAVE_CMATH
# include <cmath>
#else
# ifdef HAVE_MATH_H
#  include <math.h>
# else
#  error "don't have header file for math"
# endif
#endif
#include<vector>
#include <map>  



#include "BonCbc.hpp"
#include "BonTMINLP.hpp"
#include "BonBonminSetup.hpp"


using namespace  Ipopt;
using namespace Bonmin;




// for Stefan
class BonminProblem : public TMINLP{  


	
public:
	
	/** the BonminProblemclass constructor */
	BonminProblem(OSInstance *osinstance_ , OSOption *osoption_);
	
	/** the BonminProblem class destructor */
	virtual ~BonminProblem();
		
	OSInstance *osinstance;

	OSOption *osoption;

	TMINLP::SolverReturn status;


	/** now for some pure Bonmin methods */
	
	  
	  /** \name Overloaded functions specific to a TMINLP.*/
	  //@{
	  /** Pass the type of the variables (INTEGER, BINARY, CONTINUOUS) to the optimizer.
	     \param n size of var_types (has to be equal to the number of variables in the problem)
	  \param var_types types of the variables (has to be filled by function).
	  */
	  virtual bool get_variables_types(Index n, VariableType* var_types);
	 
	  /** Pass info about linear and nonlinear variables.*/
	  virtual bool get_variables_linearity(Index n, Ipopt::TNLP::LinearityType* var_types);

	  /** Pass the type of the constraints (LINEAR, NON_LINEAR) to the optimizer.
	  \param m size of const_types (has to be equal to the number of constraints in the problem)
	  \param const_types types of the constraints (has to be filled by function).
	  */
	  virtual bool get_constraints_linearity(Index m, Ipopt::TNLP::LinearityType* const_types);
	//@}  
	    
	  /** \name Overloaded functions defining a TNLP.
	     * This group of function implement the various elements needed to define and solve a TNLP.
	     * They are the same as those in a standard Ipopt NLP problem*/
	  //@{
	  /** Method to pass the main dimensions of the problem to Ipopt.
	        \param n number of variables in problem.
	        \param m number of constraints.
	        \param nnz_jac_g number of nonzeroes in Jacobian of constraints system.
	        \param nnz_h_lag number of nonzeroes in Hessian of the Lagrangean.
	        \param index_style indicate wether arrays are numbered from 0 (C-style) or
	        from 1 (Fortran).
	        \return true in case of success.*/
	  virtual bool get_nlp_info(Index& n, Index&m, Index& nnz_jac_g,
	                            Index& nnz_h_lag, TNLP::IndexStyleEnum& index_style);	
	

	
	/** Bonmin specific methods for defining the nlp problem */
	//virtual bool get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
     //                       Index& nnz_h_lag, IndexStyleEnum& index_style);

	/** Method to return the bounds for my problem */
	virtual bool get_bounds_info(Index n, Number* x_l, Number* x_u,
								Index m, Number* g_l, Number* g_u);

	/** Method to return the starting point for the algorithm */
	virtual bool get_starting_point(Index n, bool init_x, Number* x,
									bool init_z, Number* z_L, Number* z_U,
									Index m, bool init_lambda,
									Number* lambda);

	/** Method to return the objective value */
	virtual bool eval_f(Index n, const Number* x, bool new_x, Number& obj_value);

	/** Method to return the gradient of the objective */
	virtual bool eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f);

	/** Method to return the constraint residuals */
	virtual bool eval_g(Index n, const Number* x, bool new_x, Index m, Number* g);

	/** Method to return:
	*   1) The structure of the jacobian (if "values" is NULL)
	*   2) The values of the jacobian (if "values" is not NULL)
	*/
	virtual bool eval_jac_g(Index n, const Number* x, bool new_x,
							Index m, Index nele_jac, Index* iRow, Index *jCol,
							Number* values);

	/** Method to return:
	*   1) The structure of the hessian of the lagrangian (if "values" is NULL)
	*   2) The values of the hessian of the lagrangian (if "values" is not NULL)
	*/
	virtual bool eval_h(Index n, const Number* x, bool new_x,
						Number obj_factor, Index m, const Number* lambda,
						bool new_lambda, Index nele_hess, Index* iRow,
						Index* jCol, Number* values);

	//@}
	
	
	virtual bool get_scaling_parameters(Number& obj_scaling,
                                    bool& use_x_scaling, Index n,
                                    Number* x_scaling,
                                    bool& use_g_scaling, Index m,
                                    Number* g_scaling);

	/** @name Solution Methods */
	  /** Method called by Ipopt at the end of optimization.*/  
	  virtual void finalize_solution(TMINLP::SolverReturn status_,
	                                 Index n, const Number* x, Number obj_value);
	//@}

	  virtual const SosInfo * sosConstraints() const{return NULL;}
	  virtual const BranchingInfo* branchingInfo() const{return NULL;}
	  
	  void printSolutionAtEndOfAlgorithm(){
	  printSol_ = true;}
	  
	  

	  
	  
private:
   bool printSol_;
	
private:
  /**@name Methods to block default compiler methods.
   * The compiler automatically generates the following three methods.
   *  Since the default compiler implementation is generally not what
   *  you want (for all but the most simple classes), we usually 
   *  put the declarations of these methods in the private section
   *  and never implement them. This prevents the compiler from
   *  implementing an incorrect "default" behavior without us
   *  knowing. (See Scott Meyers book, "Effective C++")
   *  
   */
  //@{
  //  HS071_NLP();

  //@}
	

	
	std::string bonminErrorMsg;

	
};


/*! \class BonminSolver
 *  \brief The BonminSolver class solves problems using Ipopt.
 * 
 * @author Jun Ma, Guss Gassmann, Kipp Martin
 * @version 1.0, 07/05/2008
 * @since OS 1.0
 * 
 * \remarks
 * this class takes an OSiL instance and optimizes it using
 * the COIN-OR Ipopt solver
 * 
 */


class BonminSolver : public DefaultSolver{ 	
public:
	


	/** the BonminSolver class constructor */
	BonminSolver();
	
	/** the IpoptSolver class destructor */
	~BonminSolver();
	
	
	
	SmartPtr<BonminProblem> tminlp;
		
	// this is a Bonmin BonCbc object;
	Bab bb;
	
	TMINLP::SolverReturn status;
	
	//SmartPtr<IpoptApplication> app;
	
	
	/** solve results in an instance being read into the Bonmin
	 * data structrues and optimized */ 
	virtual void  solve() throw (ErrorClass) ;
	
	/*! \fn void CoinSolver::buildSolverInstance() 
	 *  \brief The implementation of the virtual functions. 
	 *  \return void.
	 */	
	virtual void  buildSolverInstance() throw(ErrorClass);
	
	/*! \fn void setSolverOptions() 
	 *  \brief The implementation of the virtual functions. 
	 *  \return void.
	 */	
	virtual void  setSolverOptions() throw(ErrorClass);
	
   	/**
   	 * use this for debugging, print out the instance that
   	 * the solver thinks it has and compare this with the OSiL
   	 * file
   	 */	
	void dataEchoCheck();
	
	/** 
	 * m_osilreader is an OSiLReader object used to create an osinstance from an
	 * osil string if needed	 
	 */		
	OSiLReader *m_osilreader;

	/** 
	 * m_osolreader is an OSoLReader object used to create an osoption from an
	 * osol string if needed	 
	 */		
	OSoLReader *m_osolreader;
	
	
	
   	/**
   	 * use this to write the solution information to an 
   	 * OSResult  object
   	 */		
	void writeResult();


private:
	OSrLWriter  *osrlwriter;

	BonminSetup bonminSetup;

	std::string bonminErrorMsg;
};


#endif /*BONMINSOLVER_H*/

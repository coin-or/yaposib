/* $Id: exprSin.hpp 154 2009-06-16 18:52:53Z pbelotti $ */
/*
 * Name:    exprSin.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the sine of a function
 *
 * (C) Carnegie-Mellon University, 2006-08.
 * This file is licensed under the Common Public License (CPL)
 */

#ifndef COUENNE_EXPRSIN_HPP
#define COUENNE_EXPRSIN_HPP

#include <math.h>
#include <assert.h>

#include "exprUnary.hpp"
#include "exprConst.hpp"


/// specify which trigonometric function is dealt with in trigEnvelope
enum cou_trig {COU_SINE, COU_COSINE};


/// normalize angle within [0,b] (typically, pi or 2pi)
inline CouNumber modulo (register CouNumber a, register CouNumber b)
  {return a - b * floor (a/b);}


/// generalized procedure for both sine and cosine
CouNumber trigSelBranch (const CouenneObject *obj, 
			 const OsiBranchingInformation *info,
			 expression * &var,
			 double * &brpts,
			 double * &brDist, // distance of current LP
				           // point to new convexifications
			 int &way,
			 enum cou_trig type);


/// generalized implied bound procedure for sine/cosine
bool trigImpliedBound (enum cou_trig, int, int, CouNumber *, CouNumber *, t_chg_bounds *);


/// class for sin f(x)
class exprSin: public exprUnary {

 public:

  /// Constructors, destructor
  exprSin (expression *al): 
    exprUnary (al) {} //< non-leaf expression, with argument list

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprSin (argument_ -> clone (d));}

  //// the operator's function
  inline unary_function F () 
  {return sin;}

  /// print operator
  std::string printOp () const
  {return "sin";}

  /// return l-2 norm of gradient at given point
  inline CouNumber gradientNorm (const double *x) {
    return (argument_ -> Index () < 0) ? 
      0. : fabs (cos (x [argument_ -> Index ()]));
  }

  /// differentiation
  expression *differentiate (int index); 

  /// Get lower and upper bound of an expression (if any)
  void getBounds (expression *&, expression *&);

  /// Get value of lower and upper bound of an expression (if any)
  void getBounds (CouNumber &lb, CouNumber &ub);

  /// generate equality between *this and *w
  void generateCuts (expression *w, const OsiSolverInterface &si, 
		     OsiCuts &cs, const CouenneCutGenerator *cg, 
		     t_chg_bounds * = NULL, int = -1, 
		     CouNumber = -COUENNE_INFINITY, 
		     CouNumber =  COUENNE_INFINITY);

  /// code for comparisons
  virtual enum expr_type code () 
  {return COU_EXPRSIN;}

  /// implied bound processing
  bool impliedBound (int index, CouNumber *l, CouNumber *u, t_chg_bounds *chg) {

    bool impl = trigImpliedBound (COU_SINE, index, argument_ -> Index (), l, u, chg);

    if (impl && argument_ -> isInteger ()) {

      int ind = argument_ -> Index ();
      assert (ind >= 0);
      l [ind] = ceil  (l [ind] - COUENNE_EPS);
      u [ind] = floor (u [ind] + COUENNE_EPS);
    }

    return impl;
  }

  /// Set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj, 
				  const OsiBranchingInformation *info,
				  expression * &var, 
				  double * &brpts, 
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way)

  {return trigSelBranch (obj, info, var, brpts, brDist, way, COU_SINE);}

  /// closest feasible points in function in both directions
  virtual void closestFeasible (expression *varind, expression *vardep,
				CouNumber& left, CouNumber& right) const;

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side
  virtual bool isCuttable (CouenneProblem *problem, int index) const
  {return false;}
};

#endif

/* $Id: OSDataStructures.h 2698 2009-06-09 04:14:07Z kmartin $ */
/** @file OShL.h
 * 
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



#ifndef OSDATASTRUCTURES_H
#define OSDATASTRUCTURES_H



#include "OSConfig.h"

#ifdef HAVE_CSTDLIB
# include <cstdlib>
#else
# ifdef HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif





/*! \class SparseMatrix
 * \brief a sparse matrix data structure
 */
class SparseMatrix {
	public:
	
	/**
	 * bDeleteArrays is true if we delete the arrays in garbage collection
	 * set to true by default
	 */
	bool bDeleteArrays;
	
	/**
	 * isColumnMajor holds whether the coefMatrix (AMatrix) holding linear program
	 * data is stored by column. If false, the matrix is stored by row.
	 */
	bool isColumnMajor;
	
	/**
	 * startSize is the dimension of the starts array
	 */
	int startSize;
	
	/**
	 * valueSize is the dimension of the starts array
	 */
	int valueSize;
	
	/**
	 * starts holds an integer array of start elements in coefMatrix (AMatrix),
	 * which points to the start of a column (row) of nonzero elements in coefMatrix (AMatrix).
	 */
	int* starts; 
	
	/**
	 * indexes holds an integer array of rowIdx (or colIdx) elements in coefMatrix (AMatrix).
	 * If the matrix is stored by column (row), rowIdx (colIdx) is the array of row (column) indices.
	 */
	int* indexes;

	/**
	 * values holds a double array of value elements in coefMatrix (AMatrix),
	 * which contains nonzero elements.
	 */
	double* values;
	
	/**
	 *
	 * Default constructor. 
	 */
	SparseMatrix();
	
	/**
	 * Constructor.
	 * 
	 * @param isColumnMajor holds whether the coefMatrix (AMatrix) holding linear program
	 * data is stored by column. If false, the matrix is stored by row.
	 * @param startSize holds the size of the start array.
	 * @param valueSize holds the size of the value and index arrays.
	 */
	SparseMatrix(bool isColumnMajor_, int startSize, int valueSize);
	/**
	 *
	 * Default destructor. 
	 */	
	~SparseMatrix();
	
	/**
	 * This method displays data structure in the matrix format.
	 * </p>
	 * @return
	 */
	bool display(int secondaryDim);

}; //SparseMatrix


/*! \class SparseVector
 * \brief a sparse vector data structure
 */
class SparseVector{
	public:
	
	/**
	 * Constructor.
	 * 
	 * @param number holds the size of the vector.
	 */
	SparseVector(int number);
	
	/**
	 *
	 * Default Constructor. 
	 */	
	SparseVector();
	
	/**
	 *
	 * Default destructor. 
	 */	
	~SparseVector();

	/**
	 * bDeleteArrays is true if we delete the arrays in garbage collection
	 * set to true by default
	 */
	bool bDeleteArrays;
	
	/**
	 * number is the number of elements in the indexes and values arrays.
	 */
	int number;
	
	/**
	 * indexes holds an integer array of indexes, which corresponding values are nonzero.
	 */
	int* indexes;

	/**
	 * values holds a double array of nonzero values.
	 */
	double* values;

}; //SparseVector


/*! \class SparseJacobianMatrix
 * \brief a sparse Jacobian matrix data structure
 */
class SparseJacobianMatrix {
	public:
	
	/**
	 * bDeleteArrays is true if we delete the arrays in garbage collection
	 * set to true by default
	 */
	bool bDeleteArrays;
	
	/**
	 * startSize is the dimension of the starts array -- should equal number of rows + 1
	 */
	int startSize;
	
	/**
	 * valueSize is the dimension of the values array
	 */
	int valueSize;
	
	/**
	 * starts holds an integer array of start elements, each start element
	 * pints to the start of partials for that row
	 */
	int* starts; 
	
	/**
	 * conVals holds an integer array of integers, conVals[i] is the number of constant terms
	 * in the gradient for row i.
	 */
	int* conVals; 
	
	/**
	 * indexes holds an integer array of variable indicies.
	 */
	int* indexes;

	/**
	 * values holds a double array of nonzero partial derivatives
	 */
	double* values;
	
	/**
	 *
	 * Default constructor. 
	 */
	SparseJacobianMatrix();
	
	/**
	 * Constructor.
	 * 
	 * @param startSize holds the size of the start array.
	 * @param valueSize holds the size of the value and index arrays.
	 */
	SparseJacobianMatrix(int startSize, int valueSize);

	/**
	 *
	 * Default destructor. 
	 */	
	~SparseJacobianMatrix();

}; //SparseJacobianMatrix





/*! \class SparseHessianMatrix SparseHessianMatrix.h "SparseHessianMatrix.h"
 *  \brief The in-memory representation of a SparseHessianMatrix..
 *
 * \remarks 
<p>  Store and uppertriangular Hessian Matrix in sparse format </p>
<p>  Assume there are n variables in what follows </p>

 *
 * 
 */
class SparseHessianMatrix {
	public:
	
	/**
	 * bDeleteArrays is true if we delete the arrays in garbage collection
	 * set to true by default
	 */
	bool bDeleteArrays;

	/**
	 * hessDimension is the number of nonzeros in each array.
	 */
	int hessDimension;
	
	/**
	 * hessRowIdx is an integer array of row indicies in the range 0, ..., n - 1.
	 */
	int* hessRowIdx; 
	
	/**
	 * hessColIdx is an integer array of column indicies in the range 0, ..., n - 1.
	 */
	int* hessColIdx; 
	
	/**
	 * hessValues is a double array of the Hessian values.
	 */
	double* hessValues;

	/**
	 *
	 * Default constructor. 
	 */
	SparseHessianMatrix();
	
	/**
	 * An Alternative Constructor.
	 * 
	 * @param startSize holds the size of the arrays.
	 * @param valueSize holds the size of the value and index arrays.
	 */
	SparseHessianMatrix(int startSize, int valueSize);

	/**
	 *
	 * Default destructor. 
	 */	
	~SparseHessianMatrix();

}; //SparseHessianMatrix

/*! \class QuadraticTerms
 * \brief a data structure for holding quadratic terms
 */
class QuadraticTerms {

	public:
	
	/**
	 * rowIndexes holds an integer array of row indexes of all the quadratic terms. 
	 * A negative integer corresponds to an objective row, e.g. -1 for 1st objective and -2 for 2nd.
	 */
	int* rowIndexes; 

	/**
	 * varOneIndexes holds an integer array of the first varialbe indexes of all the quadratic terms. 
	 */
	int* varOneIndexes; 

	/**
	 * varTwoIndexes holds an integer array of the second varialbe indexes of all the quadratic terms. 
	 */
	int* varTwoIndexes; 

	/**
	 * coefficients holds a double array all the quadratic term coefficients. 
	 */
	double* coefficients; 

	/**
	 *
	 * Default constructor. 
	 */
	QuadraticTerms();
	~QuadraticTerms();
}; //QuadraticTerms


/*! \class IntVector
 * \brief an integer Vector data structure
 */	
class IntVector{
public:
	IntVector();
	~IntVector();
	/**
	 * bDeleteArrays is true if we delete the arrays in garbage collection
	 * set to true by default
	 */
	bool bDeleteArrays;
	int *el;
};//class IntVector

/*! \class DoubleVector
 * \brief a double vector data structure
 */
class DoubleVector{
public:
	DoubleVector();
	~DoubleVector();
	/**
	 * bDeleteArrays is true if we delete the arrays in garbage collection
	 * set to true by default
	 */
	bool bDeleteArrays;
	double *el;			
};//class DoubleVector


/*! \struct IndexValuePair
 *  \brief A coomonly used structure holding an index-value pair
 */
struct IndexValuePair{
	/** idx holds the index of an entity (such as a variable, constraint, objective)
	 *  that is part of a sparse vector
	 */
	int idx;

	/** value is a double that holds the value of the entity
	 */ 
	double value;
		
};


#endif





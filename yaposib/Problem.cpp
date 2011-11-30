#include "Problem.hpp"

/// @author Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// created the 2010-07-21

// OSI includes
#include <coin/OsiSolverInterface.hpp>
#ifdef Cbc
#include <coin/OsiCbcSolverInterface.hpp>
#endif
#ifdef Clp
#include <coin/OsiClpSolverInterface.hpp>
#endif
#ifdef Cpx
#include <coin/OsiCpxSolverInterface.hpp>
#endif
#ifdef Dylp
#include <coin/OsiDylpSolverInterface.hpp>
#endif
#ifdef Fmp
#include <coin/OsiFmpSolverInterface.hpp>
#endif
#ifdef Glpk
#include <coin/OsiGlpkSolverInterface.hpp>
#endif
#ifdef Grb
#include <coin/OsiGrbSolverInterface.hpp>
#endif
#ifdef Msk
#include <coin/OsiMskSolverInterface.hpp>
#endif
#ifdef Osl
#include <coin/OsiOslSolverInterface.hpp>
#endif
#ifdef Spx
#include <coin/OsiSpxSolverInterface.hpp>
#endif
#ifdef Sym
#include <coin/OsiSymSolverInterface.hpp>
#endif
#ifdef Vol
#include <coin/OsiVolSolverInterface.hpp>
#endif
#ifdef Xpr
#include <coin/OsiXprSolverInterface.hpp>
#endif
#include <coin/CoinPackedVector.hpp>
#include <coin/CoinShallowPackedVector.hpp>
#include <coin/CoinPackedMatrix.hpp>

// std includes
#include <stdexcept>
#include <algorithm>
#include <iostream>

Problem::Problem(std::string solverName) :
    _hasHotStart(false),
    _hasBeenSolved(false)
{
#ifdef Cbc
    if (solverName == "Cbc")
    {
        _solver = SolverPtr(new OsiCbcSolverInterface());
    }
#endif
#ifdef Clp
    if (solverName == "Clp")
    {
        _solver = SolverPtr(new OsiClpSolverInterface());
    }
#endif
#ifdef Cpx
    if (solverName == "Cpx")
    {
        _solver = SolverPtr(new OsiCpxSolverInterface());
    }
#endif
#ifdef Dylp
    if (solverName == "Dylp")
    {
        _solver = SolverPtr(new OsiDylpSolverInterface());
    }
#endif
#ifdef Fmp
    if (solverName == "Fmp")
    {
        _solver = SolverPtr(new OsiFmpSolverInterface());
    }
#endif
#ifdef Glpk
    if (solverName == "Glpk")
    {
        _solver = SolverPtr(new OsiGlpkSolverInterface());
    }
#endif
#ifdef Grb
    if (solverName == "Grb")
    {
        _solver = SolverPtr(new OsiGrbSolverInterface());
    }
#endif
#ifdef Msk
    if (solverName == "Msk")
    {
        _solver = SolverPtr(new OsiMskSolverInterface());
    }
#endif
#ifdef Osl
    if (solverName == "Osl")
    {
        _solver = SolverPtr(new OsiOslSolverInterface());
    }
#endif
#ifdef Spx
    if (solverName == "Spx")
    {
        _solver = SolverPtr(new OsiSpxSolverInterface());
    }
#endif
#ifdef Sym
    if (solverName == "Sym")
    {
        _solver = SolverPtr(new OsiSymSolverInterface());
    }
#endif
#ifdef Vol
    if (solverName == "Vol")
    {
        _solver = SolverPtr(new OsiVolSolverInterface());
    }
#endif
#ifdef Xpr
    if (solverName == "Xpr")
    {
        _solver = SolverPtr(new OsiXprSolverInterface());
    }
#endif
    if (_solver == NULL)
    {
        throw std::runtime_error( solverName + ": Unknown _solver");
    }
    else
    {
        // set names correctly
        _solver->setIntParam(OsiNameDiscipline, 2);
        setMaximize(false);
        _rows = Rows(this);
        _cols = Cols(this);
        _obj  = Obj (this);
    }
}

Problem::Problem(const Problem &tocopy)
{
    _hasHotStart   = tocopy._hasHotStart;
    _hasBeenSolved = tocopy._hasBeenSolved;
    _rows          = Rows(this);
    _cols          = Cols(this);
    _obj           = Obj (this);
    _solver        = tocopy._solver;
}

Problem::~Problem()
{
}

int Problem::getMaxNumIterations() const
{
    int res;
    _solver->getIntParam(OsiMaxNumIteration, res);
    return res;
}

void Problem::setMaxNumIterations(int i)
{
    _solver->setIntParam(OsiMaxNumIteration, i);
}

int Problem::getMaxNumIterationsHotStart() const
{
    int res;
    _solver->getIntParam(OsiMaxNumIterationHotStart, res);
    return res;
}

void Problem::setMaxNumIterationsHotStart(int i)
{
    _solver->setIntParam(OsiMaxNumIterationHotStart, i);
}

double Problem::getDualObjectiveLimit() const
{
    double res;
    _solver->getDblParam(OsiDualObjectiveLimit, res);
    return res;
}

void Problem::setDualObjectiveLimit(double d)
{
    _solver->setDblParam(OsiDualObjectiveLimit, d);
}

double Problem::getPrimalObjectiveLimit() const
{
    double res;
    _solver->getDblParam(OsiPrimalObjectiveLimit, res);
    return res;
}

void Problem::setPrimalObjectiveLimit(double d)
{
    _solver->setDblParam(OsiPrimalObjectiveLimit, d);
}

double Problem::getDualTolerance() const
{
    double res;
    _solver->getDblParam(OsiDualTolerance, res);
    return res;
}

void Problem::setDualTolerance(double d)
{
    _solver->setDblParam(OsiDualTolerance, d);
}

double Problem::getPrimalTolerance() const
{
    double res;
    _solver->getDblParam(OsiPrimalTolerance, res);
    return res;
}

void Problem::setPrimalTolerance(double d)
{
    _solver->setDblParam(OsiPrimalTolerance, d);
}

double Problem::getObjOffset() const
{
    double res;
    _solver->getDblParam(OsiObjOffset, res);
    return res;
}

void Problem::setObjOffset(double d)
{
    _solver->setDblParam(OsiObjOffset, d);
}

bool Problem::getDoPreSolveInInitial() const
{
    bool res;
    _solver->getHintParam(OsiDoPresolveInInitial, res);
    return res;
}

void Problem::setDoPreSolveInInitial(bool b)
{
    _solver->setHintParam(OsiDoPresolveInInitial, b);
}

bool Problem::getDoDualInInitial()
{
    bool res;
    _solver->getHintParam(OsiDoDualInInitial, res);
    return res;
}

void Problem::setDoDualInInitial(bool b)
{
    _solver->setHintParam(OsiDoDualInInitial, b);
}

bool Problem::getDoPresolveInResolve() const
{
    bool res;
    _solver->getHintParam(OsiDoPresolveInResolve, res);
    return res;
}

void Problem::setDoPresolveInResolve(bool b)
{
    _solver->setHintParam(OsiDoPresolveInResolve, b);
}

bool Problem::getDoDualInResolve() const
{
    bool res;
    _solver->getHintParam(OsiDoDualInResolve, res);
    return res;
}

void Problem::setDoDualInResolve(bool b)
{
    _solver->setHintParam(OsiDoDualInResolve, b);
}

bool Problem::getDoScale() const
{
    bool res;
    _solver->getHintParam(OsiDoScale, res);
    return res;
}

void Problem::setDoScale(bool b)
{
    _solver->setHintParam(OsiDoScale, b);
}

bool Problem::getDoCrash() const
{
    bool res;
    _solver->getHintParam(OsiDoCrash, res);
    return res;
}

void Problem::setDoCrash(bool b)
{
    _solver->setHintParam(OsiDoCrash, b);
}

bool Problem::getDoInBranchAndCut() const
{
    bool res;
    _solver->getHintParam(OsiDoInBranchAndCut, res);
    return res;
}

void Problem::setDoInBranchAndCut(bool b)
{
    _solver->setHintParam(OsiDoInBranchAndCut, b);
}

int Problem::getIterationCount() const
{
    return _solver->getIterationCount();
}

double Problem::getIntegerTolerance() const
{
    return _solver->getIntegerTolerance();
}

bool Problem::isAbandoned() const
{
    return _solver->isAbandoned();
}

bool Problem::isProvenOptimal() const
{
    return _solver->isProvenOptimal();
}

bool Problem::isProvenPrimalInfeasible() const
{
    return _solver->isProvenPrimalInfeasible();
}

bool Problem::isProvenDualInfeasible() const
{
    return _solver->isProvenDualInfeasible();
}

bool Problem::isPrimalObjectiveLimitReached() const
{
    return _solver->isPrimalObjectiveLimitReached();
}

bool Problem::isDualObjectiveLimitReached() const
{
    return _solver->isDualObjectiveLimitReached();
}

bool Problem::isIterationLimitReached() const
{
    return _solver->isIterationLimitReached();
}

//-------------------------------------------------------------//
// PROBNAME
//-------------------------------------------------------------//
std::string Problem::getObjName() const
{
    return _solver->getObjName();
}

void Problem::setObjName(std::string name)
{
    _solver->setObjName(name);
}

//-------------------------------------------------------------//
// OBJECTIVE
//-------------------------------------------------------------//
Obj Problem::getObj()
{
    return _obj;
}

bool Problem::getMaximize() const
{
    return (_solver->getObjSense() == -1);
}

void Problem::setMaximize(bool maximize)
{
    if (maximize)
    {
        _solver->setObjSense(-1);
    }
    else
    {
        _solver->setObjSense(1);
    }
}

bool Problem::getInteger(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->isInteger(index);
}

void Problem::setInteger(int index, bool isInteger)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    if (isInteger)
    {
        _solver->setInteger(index);
    }
    else
    {
        _solver->setContinuous(index);
    }
}

double Problem::getObjCoef(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return (_solver->getObjCoefficients()[index]);
}

void Problem::setObjCoef(int index, double value)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setObjCoeff(index, value);
}

//-------------------------------------------------------------//
// _rows
//-------------------------------------------------------------//
Rows Problem::getRows()
{
    _rows.update();
    return _rows;
}

void Problem::addRow(const CoinPackedVector &vector)
{
    const int * indices = vector.getIndices();
    int size = vector.getNumElements();
    if (size != 0)
    {
        if (*std::max_element(indices, indices + size) >= getNumCols())
        {
            throw std::runtime_error("Index out of range, add more columns");
        }
    }
    _solver->addRow(vector, - _solver->getInfinity(), _solver->getInfinity());
}

std::string Problem::getRowName(int index) const
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getRowName(index);
}

void Problem::setRowName(int index, std::string name)
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setRowName(index, name);
}

const double Problem::getRowLower(int index) const
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getRowLower()[index];
}

void Problem::setRowLower(int index, double value)
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setRowLower(index, value);
}

const double Problem::getRowUpper(int index) const
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getRowUpper()[index];
}

void Problem::setRowUpper(int index, double value)
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setRowUpper(index, value);
}

int Problem::getNumRows() const
{
    return _solver->getNumRows();
}

void Problem::deleteRow(int index)
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    int indices[1];
    indices[0] = index;
    _solver->deleteRows(1, indices);
}

//-------------------------------------------------------------//
// COLS
//-------------------------------------------------------------//
Cols Problem::getCols()
{
    _cols.update();
    return _cols;
}

std::string Problem::getColName(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getColName(index);
}

void Problem::setColName(int index, std::string name)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setColName(index, name);
}

const double Problem::getColLower(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getColLower()[index];
}

void Problem::setColLower(int index, double value)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setColLower(index, value);
}

const double Problem::getColUpper(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getColUpper()[index];
}

void Problem::setColUpper(int index, double value)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    _solver->setColUpper(index, value);
}

int Problem::getNumCols() const
{
    return _solver->getNumCols();
}

void Problem::addCol(const CoinPackedVector &vector)
{
    const int * indices = vector.getIndices();
    int size = vector.getNumElements();
    if (size != 0)
    {
        if (*std::max_element(indices, indices + size) >= getNumRows())
        {
            throw std::runtime_error("Index out of range, add more _rows");
        }
    }
    _solver->addCol(vector, -_solver->getInfinity(), _solver->getInfinity(), 0);
}

void Problem::deleteCol(int index)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    int indices[1];
    indices[0] = index;
    _solver->deleteCols(1, indices);
}

//-------------------------------------------------------------//
// SOLVE
//-------------------------------------------------------------//
void Problem::markHotStart()
{
    _solver->markHotStart();
    _hasHotStart = true;
}

void Problem::unmarkHotStart()
{
    // don't use if no snapshot has been taken
    if (_hasHotStart)
    {
        _solver->unmarkHotStart();
    }
    _hasHotStart = false;
}

void Problem::solve(bool considerMIP)
{
    if (_hasHotStart)
    {
        _solver->solveFromHotStart();
    }
    else if (_hasBeenSolved)
    {
        _solver->resolve();
    }
    else
    {
        _solver->initialSolve();
    }
    if (considerMIP)
    {
        _solver->branchAndBound();
    }
    _hasBeenSolved = true;
}

std::string Problem::getSolverStatus() const
{
    std::string res = "undefined";
    if (isAbandoned())
    {
        res = "abandoned";
    }
    if (isProvenOptimal())
    {
        res = "optimal";
    }
    if (isProvenPrimalInfeasible() || isProvenDualInfeasible())
    {
        res = "infeasible";
    }
    if (isPrimalObjectiveLimitReached()
            || isDualObjectiveLimitReached()
            || isIterationLimitReached())
    {
        res = "limitreached";
    }
    return res;
}

double Problem::getObjValue() const
{
    return _solver->getObjValue();
}

double Problem::getColSolution(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getColSolution()[index];
}

void Problem::setColSolution(int index, double value)
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    const double *sol = _solver->getColSolution();
    double * array = new double[getNumCols()];
    for (int i = 0; i < getNumCols(); ++i)
    {
        array[i] = sol[i];
    }
    array[index] = value;
    _solver->setColSolution(array);
    delete[] array;
}

double Problem::getReducedCost(int index) const
{
    if (index >= getNumCols() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getReducedCost()[index];
}

double Problem::getDualValue(int index) const
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getRowPrice()[index];
}

void Problem::setDualValue(int index, double value)
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    const double *duals = _solver->getRowPrice();
    double * array = new double[getNumRows()];
    for (int i = 0; i < getNumRows(); ++i)
    {
        array[i] = duals[i];
    }
    array[index] = value;
    _solver->setRowPrice(array);
    delete[] array;
}

double Problem::getRowActivity(int index) const
{
    if (index >= getNumRows() or index < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return _solver->getRowActivity()[index];
}

//-------------------------------------------------------------//
// CONTENT
//-------------------------------------------------------------//
Indices Problem::getRowIndices(int row)
{
    Indices res;
    if (row >= getNumRows() or row < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    const CoinPackedMatrix * matrix = _solver->getMatrixByRow();
    CoinShallowPackedVector vector = matrix->getVector(row);
    for(int i = 0; i < vector.getNumElements(); ++i)
    {
        res.push_back((vector.getIndices())[i]);
    }
    return res;
}

Values Problem::getRowElements(int row)
{
    if (row >= getNumRows() or row < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    const CoinPackedMatrix * matrix = _solver->getMatrixByRow();
    CoinShallowPackedVector vector = matrix->getVector(row);
    Values res;
    for(int i = 0; i < vector.getNumElements(); ++i)
    {
        res.push_back((vector.getElements())[i]);
    }
    return res;
    //Values res(vector.getNumElements(), vector.getElements());
    return res;
}

Indices Problem::getColIndices(int col)
{
    Indices res;
    if (col >= getNumCols() or col < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    const CoinPackedMatrix * matrix = _solver->getMatrixByCol();
    CoinShallowPackedVector vector = matrix->getVector(col);
    for(int i = 0; i < vector.getNumElements(); ++i)
    {
        res.push_back((vector.getIndices())[i]);
    }
    return res;
}

Values Problem::getColElements(int col)
{
    if (col >= getNumCols() or col < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    const CoinPackedMatrix * matrix = _solver->getMatrixByCol();
    CoinShallowPackedVector vector = matrix->getVector(col);
    Values res;
    for(int i = 0; i < vector.getNumElements(); ++i)
    {
        res.push_back((vector.getElements())[i]);
    }
    //Values res(vector.getNumElements(), vector.getElements());
    return res;
}

void Problem::writeLp(std::string filename) const
{
    _solver->writeLp(filename.data());
}

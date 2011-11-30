#ifndef PROBLEM_HPP
#define PROBLEM_HPP

/// @file:          Problem.hpp
/// @author:        Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// @created:       2010-07-21

#include <string>
#include <boost/shared_ptr.hpp>
#include "CArrays.hpp"
#include "Row.hpp"
#include "Col.hpp"
#include "Obj.hpp"

// forward declarations
class OsiSolverInterface;
class CoinPackedVector;

// typedefs
typedef boost::shared_ptr<OsiSolverInterface> SolverPtr;

class Problem
{
    private:
        // OsiSolverInterface that is actually used
        SolverPtr _solver;

        // Do we have make a snapshot?
        bool _hasHotStart;

        // Has the solve method been called?
        bool _hasBeenSolved;

        // Object modelling the rows of the problem
        Rows _rows;

        // Object modelling the columns of the problem
        Cols _cols;

        // Object modelling the objective of the problem
        Obj _obj;

    public:
        // Constructor. Takes a string (solver to use) as an argument.
        // Instanciates the internal solver
        Problem(std::string solverName);

        // Copy constructor (safe to use). Also makes a deep copy of the
        // internal solver
        Problem(const Problem &tocopy);

        // Destructor. Also calls the destructor of the internal solver
        ~Problem();

        //-------------------------------------------------------------//
        // OBJECTIVE
        // The following methods are actually called through an object
        // that models the objective
        //-------------------------------------------------------------//

        // Returns an object modelling the objective
        Obj getObj();

        // Gets the objective name
        std::string getObjName() const;

        // Sets the objective name
        void setObjName(std::string name);

        // Is it a maximize problem?
        bool getMaximize() const;

        // Makes the problem a maximization or minimization problem,
        // depending on the argument
        void setMaximize(bool maximize);

        // Gets the objective coefficient of the given column
        double getObjCoef(int index) const;

        // Sets the objective coefficient of the given column
        void setObjCoef(int index, double value);

        // Returns the value of the objective
        double getObjValue() const;


        //-------------------------------------------------------------//
        // ROWS
        // The following methods are actually called through an object
        // that models the rows
        //-------------------------------------------------------------//

        // Returns an object modelling the rows
        Rows getRows();

        // Adds a row to the problem, with no bounds. It is checked that
        // the row refers to existing columns (slow, but better than
        // segfaulting on user error)
        void addRow(const CoinPackedVector &vector);

        // Returns the name of the row at the given index
        std::string getRowName(int index) const;

        // Sets the name of the row at the given index
        void setRowName(int index, std::string name);

        // Gets the lower bound of the row at the given index
        const double getRowLower(int index) const;

        // Sets the lower bound of the row at the given index
        void setRowLower(int index, double value);

        // Gets the upper bound of the row at the given index
        const double getRowUpper(int index) const;

        // Sets the upper bound of the row at the given index
        void setRowUpper(int index, double value);

        // Returns the number of rows in the problem
        int getNumRows() const;

        // Returns the indices of the columns refered by the row at the
        // given index
        Indices getRowIndices(int row);

        // Returns the values associated to the indices of the columns
        // refered by the row at the given index (goes with getRowIndices)
        Values getRowElements(int row);

        // Deletes the row at the given index
        void deleteRow(int index);

        // Returns the computed dual values of the problem
        double getDualValue(int index) const;

        // Sets the given dual value
        void setDualValue(int index, double value);

        // Returns the computed row activities of the problem
        double getRowActivity(int index) const;

        //-------------------------------------------------------------//
        // COLS
        // The following methods are actually called through an object
        // that models the columns
        //-------------------------------------------------------------//

        // Returns an object modelling the columns
        Cols getCols();

        // Is the column refering to an integer variable?
        bool getInteger(int index) const;

        // Makes the column refer to an integer/continuous variable,
        // depending on the argument
        void setInteger(int index, bool isInteger);

        // Adds a column to the problem, with no bounds and a null
        // objective coefficient. It is checked that the column refers to
        // existing rows.
        void addCol(const CoinPackedVector &vector);

        // Returns the column name
        std::string getColName(int index) const;

        // Sets the column name
        void setColName(int index, std::string name);

        // Returns the column lower bound
        const double getColLower(int index) const;

        // Sets the column lower bound
        void setColLower(int index, double value);

        // Returns the column upper bound
        const double getColUpper(int index) const;

        // Sets the column upper bound
        void setColUpper(int index, double value);

        // Returns the current number of columns in the problem
        int getNumCols() const;

        // Returns the indices of the rows refered by the column at the
        // given index
        Indices getColIndices(int col);

        // Returns the values associated to the indices of the rows
        // refered by the column at the given index (goes with
        // getColIndices)
        Values getColElements(int col);

        // deletes the column associated with the given index
        void deleteCol(int index);

        // Returns the computed solution of the problem
        double getColSolution(int index) const;

        // Sets the solution to the given value
        void setColSolution(int index, double value);

        // Returns the computed reduced costs of the problem
        double getReducedCost(int index) const;

        //-------------------------------------------------------------//
        // SOLVE
        //-------------------------------------------------------------//

        // Makes an internal optimization snapshot of the problem (an
        // internal warmstart object is built)
        void markHotStart();

        // Deletes the internal snapshot of the problem (if existing)
        void unmarkHotStart();

        // Solve the internal problem.
        // If an internal snapshot exists, use it
        // If the problem has already been solved, use the internal
        // ReSolve.
        // If considerMIP is true, call a branch and bound after that
        void solve(bool considerMIP);
        void solveNormal(){this->solve(false);}
        void solveMIP(){this->solve(true);}

        // returns a string describing the solver status
        // "undefined", "abandoned", "optimal", "infeasible" or
        // "limitreached".
        // You can then get more details using
        // - isAbandoned
        // - isProvenOptimal
        // - isProvenPrimalInfeasible
        // - isProvenDualInfeasible
        // - isPrimalObjectiveLimitReached
        // - isDualObjectiveLimitReached
        // - isIterationLimitReached
        std::string getSolverStatus() const;

        // write the problem in a file (lp format)
        void writeLp(std::string filename) const;
        void writeDefaultLp() const{this->writeLp("debug.lp");}

        //-------------------------------------------------------------//
        // TUNING
        // See OSI Manual for more details
        //-------------------------------------------------------------//

        // The maximum number of iterations (whatever that means for the
        // given solver) the solver can execute before terminating (When
        // solving/resolving)
        int getMaxNumIterations() const;

        void setMaxNumIterations(int i);

        //The maximum number of iterations (whatever that means for the
        //given solver) the solver can execute when hot starting before
        //terminating.
        int getMaxNumIterationsHotStart() const;

        void setMaxNumIterationsHotStart(int i);

        //Dual objective limit. This is to be used as a termination
        //criteria in methods where the dual objective monotonically
        //changes (e.g., dual simplex, the volume algorithm)
        double getDualObjectiveLimit() const;

        void setDualObjectiveLimit(double d);

        // Primal objective limit. This is to be used as a termination
        // criteria in methods where the primal objective monotonically
        // changes (e.g., primal simplex)
        double getPrimalObjectiveLimit() const;

        void setPrimalObjectiveLimit(double d);

        // The maximum amount the dual constraints can be violated and
        // still be considered feasible.
        double getDualTolerance() const;

        void setDualTolerance(double d);

        // The maximum amount the primal constraints can be violated and
        // still be considered feasible.
        double getPrimalTolerance() const;

        void setPrimalTolerance(double d);

        // The value of any constant term in the objective function.
        double getObjOffset() const;

        void setObjOffset(double d);

        // Whether to do a presolve in initialSolve
        bool getDoPreSolveInInitial() const;

        void setDoPreSolveInInitial(bool b);

        // Whether to use a dual algorithm in initialSolve. The reverse is
        // to use a primal algorithm
        bool getDoDualInInitial();

        void setDoDualInInitial(bool b);

        // Whether to do a presolve in resolve
        bool getDoPresolveInResolve() const;

        void setDoPresolveInResolve(bool b);

        // Whether to use a dual algorithm in resolve. The reverse is to
        // use a primal algorithm
        bool getDoDualInResolve() const;

        void setDoDualInResolve(bool b);

        // Whether to scale problem
        bool getDoScale() const;

        void setDoScale(bool b);

        // Whether to create a non-slack basis (only in initialSolve)
        bool getDoCrash() const;

        void setDoCrash(bool b);

        // Whether we are in branch and cut - so can modify behavior
        bool getDoInBranchAndCut() const;

        void setDoInBranchAndCut(bool b);

        // Get the number of iterations it took to solve the problem
        // (whatever ``iteration'' means to the solver).
        int getIterationCount() const;

        // Get the integer tolerance of the solver
        double getIntegerTolerance() const;

        // Are there numerical difficulties?
        bool isAbandoned() const;

        // Is optimality proven?
        bool isProvenOptimal() const;

        // Is primal infeasiblity proven?
        bool isProvenPrimalInfeasible() const;

        // Is dual infeasiblity proven?
        bool isProvenDualInfeasible() const;

        // Is the given primal objective limit reached?
        bool isPrimalObjectiveLimitReached() const;

        // Is the given dual objective limit reached?
        bool isDualObjectiveLimitReached() const;

        // Iteration limit reached?
        bool isIterationLimitReached() const;

};

#endif /* PROBLEM_HPP*/

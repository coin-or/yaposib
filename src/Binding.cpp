/// @author Christophe-Marie Duquesne <chm.duquesne@gmail.com>

#include "Problem.hpp"
#include "CArrays.hpp"
#include "Row.hpp"
#include "Obj.hpp"

#include <coin/CoinPackedVector.hpp>
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(_yaposib)
{
    // See "Problem.hpp"
    class_<Problem>("Problem", init<std::string>())
        // Returns the objective as a manipulable object
        .add_property("obj",
                &Problem::getObj)
        // Returns the rows as a manipulable object
        .add_property("rows",
                &Problem::getRows)
        // Returns the columns as a manipulable object
        .add_property("cols",
                &Problem::getCols)
        // Makes an internal optimization snapshot of the problem (an
        // internal warmstart object is built)
        .def("markHotStart",
                &Problem::markHotStart)
        // Deletes the internal snapshot of the problem (if existing)
        .def("unmarkHotStart",
                &Problem::unmarkHotStart)
        // Solves the internal problem.
        // If an internal snapshot exists, use it.
        // If the problem has already been solved, use the internal
        // ReSolve.
        // If the argument is true, add a branch and bound call.
        .def("solve",
                &Problem::solve)
        // returns a string describing the solver status
        // "undefined", "abandoned", "optimal", "infeasible" or
        // "limitreached".
        // You can then get more details using the properties
        // - isAbandoned
        // - isProvenOptimal
        // - isProvenPrimalInfeasible
        // - isProvenDualInfeasible
        // - isPrimalObjectiveLimitReached
        // - isDualObjectiveLimitReached
        // - isIterationLimitReached
        .add_property("status",
                &Problem::getSolverStatus)
        // Write the problem in a file (lp format). The argument is
        // appended the extension ".lp"
        .def("writeLp",
                &Problem::writeLp)
        // The maximum number of iterations (whatever that means for the
        // given solver) the solver can execute before terminating (When
        // solving/resolving)
        .add_property("maxNumIterations",
                &Problem::getMaxNumIterations,
                &Problem::setMaxNumIterations)
        //The maximum number of iterations (whatever that means for the
        //given solver) the solver can execute when hot starting before
        //terminating.
        .add_property("maxNumIterationsHotStart",
                &Problem::getMaxNumIterationsHotStart,
                &Problem::setMaxNumIterationsHotStart)
        //Dual objective limit. This is to be used as a termination
        //criteria in methods where the dual objective monotonically
        //changes (e.g., dual simplex, the volume algorithm)
        .add_property("dualObjectiveLimit",
                &Problem::getDualObjectiveLimit,
                &Problem::setDualObjectiveLimit)
        // Primal objective limit. This is to be used as a termination
        // criteria in methods where the primal objective monotonically
        // changes (e.g., primal simplex)
        .add_property("primalObjectiveLimit",
                &Problem::getPrimalObjectiveLimit,
                &Problem::setPrimalObjectiveLimit)
        // The maximum amount the dual constraints can be violated and
        // still be considered feasible.
        .add_property("dualTolerance",
                &Problem::getDualTolerance,
                &Problem::setDualTolerance)
        // The maximum amount the primal constraints can be violated and
        // still be considered feasible.
        .add_property("primalTolerance",
                &Problem::getPrimalTolerance,
                &Problem::setPrimalTolerance)
        // The value of any constant term in the objective function.
        .add_property("objOffset",
                &Problem::getObjOffset,
                &Problem::setObjOffset)
        // Whether to do a presolve in initialSolve
        .add_property("doPreSolveInInitial",
                &Problem::getDoPreSolveInInitial,
                &Problem::setDoPreSolveInInitial)
        // Whether to use a dual algorithm in initialSolve. The reverse is
        // to use a primal algorithm
        .add_property("doDualInInitial",
                &Problem::getDoDualInInitial,
                &Problem::setDoDualInInitial)
        // Whether to do a presolve in resolve
        .add_property("doPreSolveInReSolve",
                &Problem::getDoPresolveInResolve,
                &Problem::setDoPresolveInResolve)
        // Whether to use a dual algorithm in resolve. The reverse is to
        // use a primal algorithm
        .add_property("doDualInResolve",
                &Problem::getDoDualInResolve,
                &Problem::setDoDualInResolve)
        // Whether to scale problem
        .add_property("doScale",
                &Problem::getDoScale,
                &Problem::setDoScale)
        // Whether to create a non-slack basis (only in initialSolve)
        .add_property("doCrash",
                &Problem::getDoCrash,
                &Problem::setDoCrash)
        // Whether we are in branch and cut - so can modify behavior
        .add_property("doInBranchAndCut",
                &Problem::getDoInBranchAndCut,
                &Problem::setDoInBranchAndCut)
        // Get the number of iterations it took to solve the problem
        // (whatever ``iteration'' means to the solver).
        .add_property("iterationCount",
                &Problem::getIterationCount)
        // Get the integer tolerance of the solver
        .add_property("integerTolerance",
                &Problem::getIntegerTolerance)
        // Are there numerical difficulties?
        .add_property("isAbandoned",
                &Problem::isAbandoned)
        // Is optimality proven?
        .add_property("isProvenOptimal",
                &Problem::isProvenOptimal)
        // Is primal infeasiblity proven?
        .add_property("isProvenPrimalInfeasible",
                &Problem::isProvenPrimalInfeasible)
        // Is dual infeasiblity proven?
        .add_property("isProvenDualInfeasible",
                &Problem::isProvenDualInfeasible)
        // Is the given primal objective limit reached?
        .add_property("isPrimalObjectiveLimitReached",
                &Problem::isPrimalObjectiveLimitReached)
        // Is the given dual objective limit reached?
        .add_property("isDualObjectiveLimitReached",
                &Problem::isDualObjectiveLimitReached)
        // Iteration limit reached?
        .add_property("isIterationLimitReached",
                &Problem::isIterationLimitReached)
    ;

    // See OSI's CoinPackedVector. It's write only, read should not be
    // needed.
    class_<CoinPackedVector>("CoinPackedVector", init<>())
        // Inserts the pair argument in the vector (index, value)
        .def("insert", &CoinPackedVector::insert)
    ;

    // See "CArrays.hpp"
    // Wraps a read only vector<double>. Write should not be needed
    class_<Values>("Values")
        // returns the length of the vector
        .def("__len__",
                &Values::size)
        // allows read access to the ith element
        .def("__getitem__",
                &values_helper::get)
        // makes it iterable
        .def("__iter__", iterator<Values>())
    ;

    // See "CArrays.hpp"
    // Wraps a read only vector<int>. Write should not be needed.
    class_<Indices>("Indices")
        // returns the length of the vector
        .def("__len__",
                &Indices::size)
        // allows read access to the ith element
        .def("__getitem__",
                &indices_helper::get)
        // makes it iterable
        .def("__iter__", iterator<Indices>())
    ;

    // See "Row.hpp"
    // Represents a single row
    class_<Row>("Row")
        // index in the problem
        .add_property("index",
                &Row::getindex)
        // name of the row
        .add_property("name",
                &Row::getName,
                &Row::setName)
        // lowerbound of the row
        .add_property("lowerbound",
                &Row::getLowerBound,
                &Row::setLowerBound)
        // upperbound of the row
        .add_property("upperbound",
                &Row::getUpperBound,
                &Row::setUpperBound)
        // indices of the columns refered by the row
        .add_property("indices",
                &Row::getIndices)
        // values of the coefficients for the columns refered by the row
        .add_property("values",
                &Row::getValues)
        // dual value of the row
        .add_property("dual",
                &Row::getDual,
                &Row::setDual)
        // activity of the row
        .add_property("activity",
                &Row::getActivity)
    ;

    // See "Row.hpp"
    // Represents every rows
    class_<Rows>("Rows")
        // adds the given row to the problem and returns a Row object
        .def("add",
                &Rows::add)
        // returns the number of rows
        .def("__len__",
                &Rows::size)
        // makes iterable
        .def("__iter__", range(
                    &Rows::begin,
                    &Rows::end))
        // allows to get the row of index
        .def("__getitem__",
                &Rows_helper::get)
        // deletes the row of given index
        .def("__delitem__",
                &Rows_helper::del)
    ;

    // See "Col.hpp"
    // Represents a single column
    class_<Col>("Col")
        // index in problem
        .add_property("index",
                &Col::getindex)
        // name
        .add_property("name",
                &Col::getName,
                &Col::setName)
        // lowerbound
        .add_property("lowerbound",
                &Col::getLowerBound,
                &Col::setLowerBound)
        // upperbound
        .add_property("upperbound",
                &Col::getUpperBound,
                &Col::setUpperBound)
        // indices of the row refered by the column
        .add_property("indices",
                &Col::getIndices)
        // values of the coefficients for the rows refered by the column
        .add_property("values",
                &Col::getValues)
        // solution
        .add_property("solution",
                &Col::getSolution,
                &Col::setSolution)
        // reduced cost
        .add_property("reducedcost",
                &Col::getReducedCost)
        // integer variable?
        .add_property("integer",
                &Col::getInteger,
                &Col::setInteger)
    ;

    // See "Col.hpp"
    // Represent all the columns of the problem
    class_<Cols>("Cols")
        // adds the given column (returns a Col object)
        .def("add",
                &Cols::add)
        // returns the number of columns
        .def("__len__",
                &Cols::size)
        // returns the column at the given index
        .def("__getitem__",
                &Cols_helper::get)
        // makes iterable
        .def("__iter__", range(
                    &Cols::begin,
                    &Cols::end))
        // delets the column at given index
        .def("__delitem__",
                &Cols_helper::del)
    ;

    // See "Obj.hpp"
    // Represents the objective of the problem
    class_<Obj>("Obj")
        // value
        .add_property("value",
                &Obj::getValue)
        // min/max problem
        .add_property("maximize",
                &Obj::getMaximize,
                &Obj::setMaximize)
        // name
        .add_property("name",
                &Obj::getName,
                &Obj::setName)
        // number of columns
        .def("__len__",
                &Obj::size)
        // get the given coef
        .def("__getitem__",
                &Obj_helper::get)
        // set the given coef
        .def("__setitem__",
                &Obj_helper::set)
    ;
}


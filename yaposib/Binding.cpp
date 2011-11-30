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
    class_<Problem>("Problem", "LP problem", init<std::string>())
        .add_property("obj",
                &Problem::getObj,
                "The objective as a manipulable object")
        .add_property("rows",
                &Problem::getRows,
                "The rows as a manipulable object")
        .add_property("cols",
                &Problem::getCols,
                "The columns as a manipulable object")
        .def("markHotStart",
                &Problem::markHotStart,
                "Makes an internal optimization snapshot of the problem (warmstart)"
                )
        .def("unmarkHotStart",
                &Problem::unmarkHotStart,
                "Deletes the internal snapshot of the problem (if existing)"
                )
        .def("solve",
                &Problem::solve,
                "Solves the internal problem:\n"
                "- If an internal snapshot exists, use it.\n"
                "- If the problem has already been solved, use the internal OSI resolve.\n"
                "- If the argument is true, add a branch and bound call.\n"
                "OSI bug: the shadow prices may be wrong for MIP."
                )
        .def("solve",
                &Problem::solveNormal)
        .def("solveMIP",
                &Problem::solveMIP)
        .add_property("status",
                &Problem::getSolverStatus,
                "A string describing the solver status:\n"
                "'undefined', 'abandoned', 'optimal', 'infeasible' or 'limitreached'.\n"
                "You can then get more details using the properties:\n"
                "- isAbandoned\n"
                "- isProvenOptimal\n"
                "- isProvenPrimalInfeasible\n"
                "- isProvenDualInfeasible\n"
                "- isPrimalObjectiveLimitReached\n"
                "- isDualObjectiveLimitReached\n"
                "- isIterationLimitReached\n"
                )
        .def("writeLp",
                &Problem::writeLp,
                "Write the problem in a file (lp format). The argument is appended the extension '.lp'"
                )
        .def("writeLp",
                &Problem::writeDefaultLp)
        .add_property("maxNumIterations",
                &Problem::getMaxNumIterations,
                &Problem::setMaxNumIterations,
                "The maximum number of iterations (whatever that means for "
                "the given solver) the solver can execute before terminating "
                "(When solving/resolving)"
                )
        .add_property("maxNumIterationsHotStart",
                &Problem::getMaxNumIterationsHotStart,
                &Problem::setMaxNumIterationsHotStart,
                "The maximum number of iterations (whatever that means for the "
                "given solver) the solver can execute when hot starting before "
                "terminating."
                )
        .add_property("dualObjectiveLimit",
                &Problem::getDualObjectiveLimit,
                &Problem::setDualObjectiveLimit,
                "Dual objective limit. This is to be used as a termination "
                "criteria in methods where the dual objective monotonically "
                "changes (e.g., dual simplex, the volume algorithm)."
                )
        .add_property("primalObjectiveLimit",
                &Problem::getPrimalObjectiveLimit,
                &Problem::setPrimalObjectiveLimit,
                "Primal objective limit. This is to be used as a termination "
                "criteria in methods where the primal objective monotonically "
                "changes (e.g., primal simplex)."
                )
        .add_property("dualTolerance",
                &Problem::getDualTolerance,
                &Problem::setDualTolerance,
                "The maximum amount the dual constraints can be violated and "
                "still be considered feasible."
                )
        .add_property("primalTolerance",
                &Problem::getPrimalTolerance,
                &Problem::setPrimalTolerance,
                "The maximum amount the primal constraints can be violated and "
                "still be considered feasible."
                )
        .add_property("objOffset",
                &Problem::getObjOffset,
                &Problem::setObjOffset,
                "The value of any constant term in the objective function."
                )
        .add_property("doPreSolveInInitial",
                &Problem::getDoPreSolveInInitial,
                &Problem::setDoPreSolveInInitial,
                "Whether to do a presolve in initialSolve"
                )
        .add_property("doDualInInitial",
                &Problem::getDoDualInInitial,
                &Problem::setDoDualInInitial,
                "Whether to use a dual algorithm in initialSolve. The reverse is "
                "to use a primal algorithm"
                )
        .add_property("doPreSolveInReSolve",
                &Problem::getDoPresolveInResolve,
                &Problem::setDoPresolveInResolve,
                "Whether to do a presolve in resolve"
                )
        .add_property("doDualInResolve",
                &Problem::getDoDualInResolve,
                &Problem::setDoDualInResolve,
                "Whether to use a dual algorithm in resolve. The reverse is to "
                "use a primal algorithm"
                )
        .add_property("doScale",
                &Problem::getDoScale,
                &Problem::setDoScale,
                "Whether to scale problem"
                )
        .add_property("doCrash",
                &Problem::getDoCrash,
                &Problem::setDoCrash,
                "Whether to create a non-slack basis (only in initialSolve)"
                )
        .add_property("doInBranchAndCut",
                &Problem::getDoInBranchAndCut,
                &Problem::setDoInBranchAndCut,
                "Whether we are in branch and cut - so can modify behavior"
                )
        .add_property("iterationCount",
                &Problem::getIterationCount,
                "Get the number of iterations it took to solve the problem "
                "(whatever 'iteration' means to the solver)."
                )
        .add_property("integerTolerance",
                &Problem::getIntegerTolerance,
                "Get the integer tolerance of the solver"
                )
        .add_property("isAbandoned",
                &Problem::isAbandoned,
                "Are there numerical difficulties?"
                )
        .add_property("isProvenOptimal",
                &Problem::isProvenOptimal,
                "Is optimality proven?"
                )
        .add_property("isProvenPrimalInfeasible",
                &Problem::isProvenPrimalInfeasible,
                "Is primal infeasiblity proven?"
                )
        .add_property("isProvenDualInfeasible",
                &Problem::isProvenDualInfeasible,
                "Is dual infeasiblity proven?"
                )
        .add_property("isPrimalObjectiveLimitReached",
                &Problem::isPrimalObjectiveLimitReached,
                "Is the given primal objective limit reached?"
                )
        .add_property("isDualObjectiveLimitReached",
                &Problem::isDualObjectiveLimitReached,
                "Is the given dual objective limit reached?"
                )
        .add_property("isIterationLimitReached",
                &Problem::isIterationLimitReached,
                "Iteration limit reached?"
                )
    ;

    // See OSI's CoinPackedVector. It's write only, read should not be
    // needed.
    class_<CoinPackedVector>("CoinPackedVector", init<>())
        .def("insert",
                &CoinPackedVector::insert,
                "Inserts the pair argument in the vector (index, value)")
    ;

    // See "CArrays.hpp"
    // Wraps a read only vector<double>. Write should not be needed
    class_<Values>("Values")
        .def("__len__", &Values::size, "length of the vector")
        .def("__getitem__", &values_helper::get, "ith element")
        .def("__iter__", iterator<Values>(), "iterate on values")
    ;

    // See "CArrays.hpp"
    // Wraps a read only vector<int>. Write should not be needed.
    class_<Indices>("Indices")
        .def("__len__", &Indices::size,"length of the vector")
        .def("__getitem__", &indices_helper::get,"ith element")
        .def("__iter__", iterator<Indices>(), "iterates on values")
    ;

    // See "Row.hpp"
    class_<Row>("Row", "Single row (Constraint)")
        .add_property("index",
                &Row::getindex,
                "row index in the problem"
                )
        .add_property("name",
                &Row::getName,
                &Row::setName,
                "row name"
                )
        .add_property("lowerbound",
                &Row::getLowerBound,
                &Row::setLowerBound,
                "row lowerbound"
                )
        .add_property("upperbound",
                &Row::getUpperBound,
                &Row::setUpperBound,
                "row upperbound"
                )
        .add_property("indices",
                &Row::getIndices,
                "variables refered"
                )
        .add_property("values",
                &Row::getValues,
                "coefficients"
                )
        .add_property("dual",
                &Row::getDual,
                &Row::setDual,
                "dual value/shadow price"
                )
        .add_property("activity",
                &Row::getActivity,
                "activity/slack"
                )
    ;

    // See "Row.hpp"
    class_<Rows>("Rows", "Every rows (constraints) of a problem")
        .def("add",
                &Rows::add,
                "Adds the given row to the problem and returns a Row object"
                )
        .def("__len__",
                &Rows::size,
                "Number of rows"
                )
        .def("__iter__", range(
                    &Rows::begin,
                    &Rows::end),
                "iterates on rows"
                )
        .def("__getitem__",
                &Rows_helper::get,
                "get a specific row"
                )
        .def("__delitem__",
                &Rows_helper::del,
                "deletes the row of given index"
                )
    ;

    // See "Col.hpp"
    class_<Col>("Col", "Single column (variable)")
        .add_property("index",
                &Col::getindex,
                "index in the problem"
                )
        .add_property("name",
                &Col::getName,
                &Col::setName,
                "name"
                )
        .add_property("lowerbound",
                &Col::getLowerBound,
                &Col::setLowerBound,
                "lowerbound"
                )
        .add_property("upperbound",
                &Col::getUpperBound,
                &Col::setUpperBound,
                "upperbound"
                )
        .add_property("indices",
                &Col::getIndices,
                "indices of the constraints the variable is in"
                )
        .add_property("values",
                &Col::getValues,
                "values of the coefficients for the column"
                )
        .add_property("solution",
                &Col::getSolution,
                &Col::setSolution,
                "variable value"
                )
        .add_property("reducedcost",
                &Col::getReducedCost,
                "reduced cost"
                )
        .add_property("integer",
                &Col::getInteger,
                &Col::setInteger,
                "integer variable?"
                )
    ;

    // See "Col.hpp"
    class_<Cols>("Cols", "Every columns (variables) of a problem")
        .def("add",
                &Cols::add,
                "adds the given column (returns a Col object)"
                )
        .def("__len__",
                &Cols::size,
                "number of columns"
                )
        .def("__getitem__",
                &Cols_helper::get,
                "returns the column at the given index"
                )
        .def("__iter__", range(
                    &Cols::begin,
                    &Cols::end),
                "makes iterable"
                )
        .def("__delitem__",
                &Cols_helper::del,
                "deletes the column at given index"
                )
    ;

    // See "Obj.hpp"
    class_<Obj>("Obj", "Objective function")
        .add_property("value",
                &Obj::getValue,
                "Ojective value"
                )
        .add_property("maximize",
                &Obj::getMaximize,
                &Obj::setMaximize,
                "Maximization problem?"
                )
        .add_property("name",
                &Obj::getName,
                &Obj::setName,
                "Objective name"
                )
        .def("__len__",
                &Obj::size,
                "Number of variables in the problem"
                )
        .def("__getitem__",
                &Obj_helper::get,
                "get the coefficient with the given index"
                )
        .def("__setitem__",
                &Obj_helper::set,
                "set the coefficient with the given index"
                )
    ;
}


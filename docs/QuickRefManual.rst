Yaposib reference API
=====================

Problem
=======
.. py:class:: Problem

Models an LP problem


Main methods
------------

.. py:method:: Problem.markHotStart()

Makes an internal optimization snapshot of the problem (an internal warmstart object is built)

.. py:method:: Problem.unmarkHotStart()

Deletes the internal snapshot of the problem (if existing)

.. py:method:: Problem.solve(True/False)

Solves the internal problem:
  * If an internal snapshot exists, use it.
  * If the problem has already been solved, use the internal `ReSolve`.
  * If the argument is true, add a branch and bound call.

.. py:attribute:: Problem.status

RO Attribute.
string describing the solver status:
"undefined", "abandoned", "optimal", "infeasible" or "limitreached".
You can get more details using the properties:
  * isAbandoned
  * isProvenOptimal
  * isProvenPrimalInfeasible
  * isProvenDualInfeasible
  * isPrimalObjectiveLimitReached
  * isDualObjectiveLimitReached
  * isIterationLimitReached

.. py:method:: Problem.writeLp("filename")

Write the problem in a file (lp format). The argument is appended the
extension ".lp"

Objective
---------

.. py:attribute:: Problem.obj

Represents the objective of the problem.

.. py:attribute:: Problem.obj.value

RO attribute (double). Objective value

.. py:attribute:: Problem.obj.maximize

RW attribute (bool)
min/max problem

.. py:attribute:: Problem.obj.name

RW attribute (string)
name

.. py:attribute:: Problem.obj.__len__

RO attribute (int) number of columns

.. py:method:: Problem.obj.__iter__

Makes iterable

.. py:method:: Problem.obj.__getitem__

get the given coef with `Problem.obj[i]`

.. py:method:: Problem.obj.__setitem__

set the given coef with `Problem.obj[i] = double`

Rows
----

.. py:attribute:: Problem.rows

Represents every rows

.. py:method:: Problem.rows.add(vec([(1, 2.0),(3, 0.1),...]))

adds the given row to the problem and returns a Row object

.. py:attribute:: Problem.rows.__len__

the number of rows

.. py:method:: Problem.rows.__iter__

Makes iterable

.. py:method:: Problem.rows.__getitem__

allows to get the row of index with `Problem.rows[i]`

.. py:method:: Problem.rows.__delitem__

deletes the row of given index with del `Problem.rows[i]`

.. py:attribute:: Problem.rows[i].index

RO Attribute (int)
index in the problem

.. py:attribute:: Problem.rows[i].name

RW Attribute (string)
name of the row

.. py:attribute:: Problem.rows[i].lowerbound

RW Attribute (double)
lowerbound of the row

.. py:attribute:: Problem.rows[i].upperbound

RW Attribute (double)
upperbound of the row

.. py:attribute:: Problem.rows[i].indices

RO Attribute (list of int)
indices of the columns refered by the row

.. py:attribute:: Problem.rows[i].values

RO Attribute (list of double)
values of the coefficients for the columns refered by the row

.. py:attribute:: Problem.rows[i].dual

RW Attribute (double)
dual value of the row

.. py:attribute:: Problem.rows[i].activity

RO Attribute (double)
activity of the row

Columns
-------

.. py:attribute:: Problem.cols

Variables
Represent all the columns of the problem

.. py:method:: Problem.cols.add(vec([(1, 2.0),(3, 0.1),...]))

adds the given column (returns a Col object)

.. py:attribute:: Problem.cols.__len__

returns the number of columns

.. py:method:: Problem.cols.__getitem__

returns the column at the given index with `Problem.cols[i]`

.. py:method:: Problem.cols.__iter__

make iterable

.. py:method:: Problem.cols.__delitem__

deletes the column at given index with del `Problem.cols[i]`

.. py:attribute:: Problem.cols[i].index

RO Attribute (int)
index in problem

.. py:attribute:: Problem.cols[i].name

RW Attribute (string)
name

.. py:attribute:: Problem.cols[i].lowerbound

RW Attribute (double)
lowerbound

.. py:attribute:: Problem.cols[i].upperbound

RW Attribute (double)
upperbound

.. py:attribute:: Problem.cols[i].indices

RO Attribute (list of int)
indices of the row refered by the column

.. py:attribute:: Problem.cols[i].values

RO Attribute (list of double)
values of the coefficients for the rows refered by the column

.. py:attribute:: Problem.cols[i].solution

RW Attribute (double)
solution

.. py:attribute:: Problem.cols[i].reducedcost

RO Attribute (double)
reduced cost

.. py:attribute:: Problem.cols[i].integer

RW Attribute (double)
integer variable?

Problem Tuning
--------------

.. py:attribute:: Problem.maxNumIterations

RW attribute (int)
The maximum number of iterations (whatever that means for the given
solver) the solver can execute before terminating (When solving/resolving)

.. py:attribute:: Problem.maxNumIterationsHotStart

RW attribute (int)
The maximum number of iterations (whatever that means for the given
solver) the solver can execute when hot starting before terminating.

.. py:attribute:: Problem.dualObjectiveLimit

RW attribute (double)
Dual objective limit. This is to be used as a termination criteria in
methods where the dual objective monotonically changes (e.g., dual
simplex, the volume algorithm)

.. py:attribute:: Problem.primalObjectiveLimit

RW attribute (double)
Primal objective limit. This is to be used as a termination criteria in
methods where the primal objective monotonically changes (e.g., primal
simplex)

.. py:attribute:: Problem.dualTolerance

RW attribute (double)
The maximum amount the dual constraints can be violated and still be
considered feasible.

.. py:attribute:: Problem.primalTolerance

RW attribute (double)
The maximum amount the primal constraints can be violated and still be
considered feasible.

.. py:attribute:: Problem.objOffset

RW attribute (double)
The value of any constant term in the objective function.

.. py:attribute:: Problem.doPreSolveInInitial

RW attribute (bool)
Whether to do a presolve in initialSolve.

.. py:attribute:: Problem.doDualInInitial

RW attribute (bool)
Whether to use a dual algorithm in initialSolve. The reverse is to use a
primal algorithm

.. py:attribute:: Problem.doPreSolveInReSolve

RW attribute (bool)
Whether to do a presolve in resolve

.. py:attribute:: Problem.doDualInResolve

RW attribute (bool)
Whether to use a dual algorithm in resolve. The reverse is to use a primal
algorithm

.. py:attribute:: Problem.doScale

RW attribute (bool)
Whether to scale problem

.. py:attribute:: Problem.doCrash

RW attribute (bool)
Whether to create a non-slack basis (only in initialSolve)

.. py:attribute:: Problem.doInBranchAndCut

RW attribute (bool)
Whether we are in branch and cut - so can modify behavior

.. py:attribute:: Problem.iterationCount

RO attribute (int)
Get the number of iterations it took to solve the problem (whatever
iteration means to the solver).

.. py:attribute:: Problem.integerTolerance

RO attribute (double)
Get the integer tolerance of the solver

.. py:attribute:: Problem.isAbandoned

RO attribute (bool)
Are there numerical difficulties?

.. py:attribute:: Problem.isProvenOptimal

RO attribute (bool)
Is optimality proven?

.. py:attribute:: Problem.isProvenPrimalInfeasible

RO attribute (bool)
Is primal infeasiblity proven?

.. py:attribute:: Problem.isProvenDualInfeasible

RO attribute (bool)
Is dual infeasiblity proven?

.. py:attribute:: Problem.isPrimalObjectiveLimitReached

RO attribute (bool)
Is the given primal objective limit reached?

.. py:attribute:: Problem.isDualObjectiveLimitReached

RO attribute (bool)
Is the given dual objective limit reached?

.. py:attribute:: Problem.isIterationLimitReached

RO attribute (bool)
Iteration limit reached?

Helper
======

.. py:function:: vec([(0,0.1),(1,2.3)])

Helper function that returns a internal type of sparse vector.
See OSI's `CoinPackedVector`. Write only.

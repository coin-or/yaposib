Getting Started
===============

What follows is a guide for installing yaposib very quickly and solve your
first linear program using it.

Installing
----------

Recommended method: pip
```````````````````````

1. Install pip, python-dev and boost::python. On ubuntu:

::

    sudo apt-get install python-pip python-dev libboost-python-dev

2. Install osi. If you want support for commercial solvers, relying on
   your distribution is not recommended. Otherwise, using a package from
   your distribution is fine. Note that if you modify the Osi installed on
   your machine, you will have to recompile yaposib.

3. Use pip to install yaposib:

::

    sudo pip install yaposib

Alternative: development version
````````````````````````````````

1. Follow 1. and 2. from the previous method

2. Clone the repository

::

    git clone https://github.com/coin-or/yaposib.git

3. Run setup.py

::

    cd yaposib
    sudo python setup.py install

Checking your installation
--------------------------

The utility `yaposib-config` is a helper script that helps you determine
if your installation went fine. Run it without any argument.

::

    yaposib-config

This tool runs the yaposib test suite on every solvers that you Osi build
reportedly supports. Since not all solvers behave equivalently, some tests
might fail with some solvers, and succeed with others. A failure does not
necessarily means that yaposib is completely unusable with your solver, it
might simply mean that it was not tested yet combined with your solver.
Please report any failures on the bugtracker_.

.. _bugtracker: https://github.com/coin-or/yaposib/issues

Code samples
------------

Let's dive into the code. Here is an example program that illustrates some
features of yaposib:

::

    """
    builds the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z
    0  <= w

    minimize obj = x + 4*y + 9*z
    such that:
    c1: x+y <= 5
    c2: x+z >= 10
    c3: -y+z == 7
    c4: w >= 0
    """
    import yaposib

    prob = yaposib.Problem("Clp")

    obj = prob.obj
    obj.name = "MyProblem"
    obj.maximize = False

    # names
    cols = prob.cols
    for var_name in ["x", "y", "z", "w"]:
        col = cols.add(yaposib.vec([]))
        col.name = var_name
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 4
    cols[1].upperbound = 1
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    rows.add(yaposib.vec([(3,1)]))
    # constraints bounds
    rows[0].upperbound = 5
    rows[1].lowerbound = 10
    rows[2].lowerbound = 7
    rows[2].upperbound = 7
    rows[3].lowerbound = 0
    # constraints names
    for row, name in zip(rows, ["c1", "c2", "c3", "c4"]):
        row.name = name

    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9

    prob.solve()

    for col in prob.cols:
        print("%s=%s" % (col.name, col.solution))

It is also easy to write a generic command line solver in a few lines of
code. The following script is part of the yaposib distribution and is
shipped as the command line utility `yaposib-solve`

::

    import yaposib
    import sys

    def main():
        """Extra simple command line mps solver"""

        if len(sys.argv) <= 1:
            print("Usage: yaposib-solve <file1.mps> [<file2.mps> ...]")
            sys.exit(0)

        solver = yaposib.available_solvers()[0]

        for filename in sys.argv[1:]:

            problem = yaposib.Problem(solver)

            print("Will now solve %s" % filename)
            err = problem.readMps(filename)
            if not err:
                problem.solve()
                if problem.status == 'optimal':
                    print("Optimal value: %f" % problem.obj.value)
                    for var in problem.cols:
                        print("\t%s = %f" % (var.name, var.solution))
                else:
                    print("No optimal solution could be found.")

    if __name__ == "__main__":
        main()

Other examples are available in the examples_ directory.

.. _examples: https://github.com/coin-or/yaposib/tree/master/examples

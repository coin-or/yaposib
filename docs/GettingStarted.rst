Getting Started
===============

Installing
----------

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

To check that the install went fine, you can run `yaposib-config`.

A quick code snippet
--------------------

Let's dive into the code. Here is how you solve a problem with yaposib:

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

Other examples are available in the examples directory.

import yaposib

if __name__ == "__main__":
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
    prob = yaposib.Problem(yaposib.available_solvers()[0])

    prob.obj.name = "MyProblem"
    prob.obj.maximize = False
    # names
    for i in range(4):
        prob.cols.add(yaposib.vec([]))
    prob.cols[0].name = "x"
    prob.cols[1].name = "y"
    prob.cols[2].name = "z"
    prob.cols[3].name = "w"
    # lowerbounds
    for col in prob.cols:
        col.lowerbound = 0
    prob.cols[1].lowerbound = -1
    # upperbounds
    prob.cols[0].upperbound = 4
    prob.cols[1].upperbound = 1
    # constraints
    prob.rows.add(yaposib.vec([(0,1),(1,1)]))
    prob.rows.add(yaposib.vec([(0,1),(2,1)]))
    prob.rows.add(yaposib.vec([(1,-1),(2,1)]))
    prob.rows.add(yaposib.vec([(3,1)]))
    # constraints bounds
    prob.rows[0].upperbound = 5
    prob.rows[1].lowerbound = 10
    prob.rows[2].lowerbound = 7
    prob.rows[2].upperbound = 7
    prob.rows[3].lowerbound = 0
    # constraints names
    prob.rows[0].name = "c1"
    prob.rows[1].name = "c2"
    prob.rows[2].name = "c3"
    prob.rows[3].name = "c4"
    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9

    prob.writeLp("debug")

    prob.solve(False)

    for col in prob.cols:
        print "%s=%s" % (col.name, col.solution)

    print "ok"

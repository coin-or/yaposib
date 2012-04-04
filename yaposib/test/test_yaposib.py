#!env python
import unittest
import yaposib

def yaposibTestCheck(prob, okstatus, sol = {},
                   reducedcosts = None,
                   duals = None,
                   slacks = None,
                   obj = None,
                   eps = 10**-3,
                   status = None,
                   solve_as_MIP = False):
    error_msg = "Test failed for problem %s:\n" % prob.obj.name
    if status is None:
        prob.solve(solve_as_MIP)
        status = prob.status
    if obj is not None:
        if abs(prob.obj.value - obj) > eps:
            prob.writeLp(prob.obj.name)
            error_msg += "\tobj == %s != %s" % (prob.obj.value, obj)
            raise yaposib.YaposibError(error_msg)
    if status not in okstatus:
        prob.writeLp(prob.obj.name)
        error_msg += "\tstatus == %s not in %s" % (status, okstatus)
        raise yaposib.YaposibError(error_msg)
    if sol:
        for i in range(len(prob.cols)):
            if abs(prob.cols[i].solution - sol[i]) > eps:
                prob.writeLp(prob.obj.name)
                error_msg += "\t%s == %s != %s" % (
                        prob.cols[i].name, prob.cols[i].solution, sol[i])
                raise yaposib.YaposibError(error_msg)
    if reducedcosts:
        for i in range(len(prob.cols)):
            if abs(prob.cols[i].reducedcost - reducedcosts[i]) > eps:
                prob.writeLp(prob.obj.name)
                error_msg += "\t%s.reducedcost == %s != %s" %(
                        prob.cols[i].name, prob.cols[i].reducedcost, reducedcost[i])
                raise yaposib.YaposibError(error_msg)
    if duals:
        for i in range(len(prob.rows)):
            if abs(prob.rows[i].dual - duals[i]) > eps:
                prob.writeLp(prob.obj.name)
                error_msg += "\t%s.dual == %s != %s" %(
                        prob.rows[i].name, prob.rows[i].dual, duals[i])
                raise yaposib.YaposibError(error_msg)
    if slacks:
        for i in range(len(prob.rows)):
            if abs(prob.rows[i].activity - slacks[i]) > eps:
                prob.writeLp(prob.obj.name)
                error_msg += "\t%s.activity == %s != %s" %(
                        prob.rows[i].name, prob.rows[i].activity, slacks[i])
                raise yaposib.YaposibError(error_msg)

def continuous(solver):
    """
    returns the following problem

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
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "continuous"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(4):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    cols[3].name = "w"
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
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    rows[3].name = "c4"
    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9
    return prob

def continuous_maximisation(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z
    0  <= w

    maximize obj = x + 4*y + 9*z
    such that:
    c1: x+y <= 5
    c2: x+z >= 10
    c3: -y+z == 7
    c4: w >= 0
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "continuous_maximisation"
    obj.maximize = True
    # names
    cols = prob.cols
    for i in range(4):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    cols[3].name = "w"
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
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    rows[3].name = "c4"
    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9
    return prob

def unbounded(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z
    0  <= w

    maximize obj = x + 4*y + 9*z + w
    such that:
    c1: x+y <= 5
    c2: x+z >= 10
    c3: -y+z == 7
    c4: w >= 0
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "unbounded"
    obj.maximize = True
    # names
    cols = prob.cols
    for i in range(4):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    cols[3].name = "w"
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
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    rows[3].name = "c4"
    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9
    prob.obj[3] = 1
    return prob

def mip(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z

    minimize obj = x + 4*y + 9*z
    such that:
    c1: x+y <= 5
    c2: x+z >= 10
    c3: -y+z == 7.5

    z integer
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "mip"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(3):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 4
    cols[1].upperbound = 1
    # integer variables
    cols[2].integer = True
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    # constraints bounds
    rows[0].upperbound = 5
    rows[1].lowerbound = 10
    rows[2].lowerbound = 7.5
    rows[2].upperbound = 7.5
    # constraints names
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9
    return prob

def feasability_only(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z

    no objective
    constraints:
    c1: x+y <= 5
    c2: x+z >= 10
    c3: -y+z == 7.5

    z integer
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "feasability_only"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(3):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 4
    cols[1].upperbound = 1
    # integer variables
    cols[2].integer = True
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    # constraints bounds
    rows[0].upperbound = 5
    rows[1].lowerbound = 10
    rows[2].lowerbound = 7.5
    rows[2].upperbound = 7.5
    # constraints names
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    return prob

def infeasible(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z <= 10

    no objective
    constraints:
    c1: x+y <= 5.2
    c2: x+z >= 10.3
    c3: -y+z == 17.5
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "infeasible"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(3):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 4
    cols[1].upperbound = 1
    cols[2].upperbound = 10
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    # constraints bounds
    rows[0].upperbound = 5.2
    rows[1].lowerbound = 10.3
    rows[2].lowerbound = 17.5
    rows[2].upperbound = 17.5
    # constraints names
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    return prob

def integer_infeasible(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z <= 10

    no objective
    constraints:
    c1: x+y <= 5.2
    c2: x+z >= 10.3
    c3: -y+z == 7.4

    x, y, z integer
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "integer_infeasible"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(3):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    # integer variables
    for col in cols:
        col.integer = True
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 4
    cols[1].upperbound = 1
    cols[2].upperbound = 10
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    # constraints bounds
    rows[0].upperbound = 5.2
    rows[1].lowerbound = 10.3
    rows[2].lowerbound = 7.4
    rows[2].upperbound = 7.4
    # constraints names
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    return prob

def duals_and_slacks(solver):
    """
    returns the following problem

    0  <= x <= 5
    -1 <= y <= 1
    0  <= z

    Minimize obj = x + 4 y + 9 z
    constraints:
    c1: x+y <= 5
    c2: x+z >= 10
    c3: -y+z == 7
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "duals_and_slacks"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(3):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 5
    cols[1].upperbound = 1
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    # constraints bounds
    rows[0].upperbound = 5
    rows[1].lowerbound = 10
    rows[2].lowerbound = 7
    rows[2].upperbound = 7
    # constraints names
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    # obj
    prob.obj[0] = 1
    prob.obj[1] = 4
    prob.obj[2] = 9
    return prob

def integer_infeasible(solver):
    """
    returns the following problem

    0  <= x <= 4
    -1 <= y <= 1
    0  <= z <= 10

    no objective
    constraints:
    c1: x+y <= 5.2
    c2: x+z >= 10.3
    c3: -y+z == 7.4

    x, y, z integer
    """
    prob = yaposib.Problem(solver)
    obj = prob.obj
    obj.name = "integer_infeasible"
    obj.maximize = False
    # names
    cols = prob.cols
    for i in range(3):
        cols.add(yaposib.vec([]))
    cols[0].name = "x"
    cols[1].name = "y"
    cols[2].name = "z"
    # integer variables
    for col in cols:
        col.integer = True
    # lowerbounds
    for col in cols:
        col.lowerbound = 0
    cols[1].lowerbound = -1
    # upperbounds
    cols[0].upperbound = 4
    cols[1].upperbound = 1
    cols[2].upperbound = 10
    # constraints
    rows = prob.rows
    rows.add(yaposib.vec([(0,1),(1,1)]))
    rows.add(yaposib.vec([(0,1),(2,1)]))
    rows.add(yaposib.vec([(1,-1),(2,1)]))
    # constraints bounds
    rows[0].upperbound = 5.2
    rows[1].lowerbound = 10.3
    rows[2].lowerbound = 7.4
    rows[2].upperbound = 7.4
    # constraints names
    rows[0].name = "c1"
    rows[1].name = "c2"
    rows[2].name = "c3"
    return prob

def wipe_solution(prob):
    """
    wipes the solution of the input problem
    """
    for col in prob.cols:
        col.solution = 0

class TestYaposib(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    #--- No idea how to test these features ---#

    def test_dualTolerance(self):
        pass

    def test_primalTolerance(self):
        pass

    def test_doPreSolveInInitial(self):
        pass

    def test_doDualInInitial(self):
        pass

    def test_doPreSolveInReSolve(self):
        pass

    def test_doDualInResolve(self):
        pass

    def test_doScale(self):
        pass

    def test_doCrash(self):
        pass

    def test_doInBranchAndCut(self):
        pass

    def test_objOffset(self):
        pass

    #--- Tested features ---#

    def test_available_solvers(self):
        self.failIfEqual(yaposib.available_solvers(), [])

    def test_HotStart(self):
        """
        Tests the hotstart feature.
        1) solve, get a hotstart
        2) wipe and resolve, knowing a hotstart now exists
        3) wipe and unmark the hotstart, resolve again
        """
        for solver in yaposib.available_solvers():
            prob = continuous(solver)
            prob.solve()
            yaposibTestCheck(prob, ["optimal"], sol = [4.0, -1.0, 6.0, 0.0])
            wipe_solution(prob)
            prob.markHotStart()
            #time = -clock()
            prob.solve()
            #time += clock()
            yaposibTestCheck(prob, ["optimal"], sol = [4.0, -1.0, 6.0, 0.0])
            wipe_solution(prob)
            prob.unmarkHotStart()
            prob.solve()
            yaposibTestCheck(prob, ["optimal"], sol = [4.0, -1.0, 6.0, 0.0])

    def test_writeLp(self):
        lpfile = ["\Problem name: ",
        "",
        "Minimize",
        "OBJROW: x + 4 y + 9 z",
        "Subject To",
        "c1:  x + y <= 5",
        "c2:  x + z >= 10",
        "c3:  - y + z = 7",
        "c4:  w >= 0",
        "Bounds",
        " 0 <= x <= 4",
        " -1 <= y <= 1",
        "End",]
        for solver in yaposib.available_solvers():
            prob = continuous(solver)
            prob.writeLp("debug")
            with open("debug.lp", "r") as f:
                for line, ref in zip(f, lpfile):
                    assert line.strip() == ref.strip()

    def test_maxNumIterations(self):
        pass

    def test_maxNumIterationsHotStart(self):
        pass

    def test_dualObjectiveLimit(self):
        pass

    def test_primalObjectiveLimit(self):
        pass

    def test_iterationCount(self):
        pass

    def test_integerTolerance(self):
        pass

    def test_isAbandoned(self):
        for solver in yaposib.available_solvers():
            prob = continuous(solver)
            if (not prob.isAbandoned):
                raise yaposib.YaposibError

    def test_isProvenOptimal(self):
        for solver in yaposib.available_solvers():
            prob = continuous(solver)
            yaposibTestCheck(prob, ["optimal"], sol = [4.0, -1.0, 6.0, 0.0])
            if (not prob.isProvenOptimal):
                raise yaposib.YaposibError

    def test_isProvenPrimalInfeasible(self):
        for solver in yaposib.available_solvers():
            prob = infeasible(solver)
            yaposibTestCheck(prob, ["limitreached"])
            if (not prob.isProvenPrimalInfeasible):
                raise yaposib.YaposibError

    def test_isProvenDualInfeasible(self):
        for solver in yaposib.available_solvers():
            prob = unbounded(solver)
            yaposibTestCheck(prob, ["infeasible"])
            if (not prob.isProvenDualInfeasible):
                raise yaposib.YaposibError

    def test_isPrimalObjectiveLimitReached(self):
        pass

    def test_isDualObjectiveLimitReached(self):
        for solver in yaposib.available_solvers():
            prob = infeasible(solver)
            yaposibTestCheck(prob, ["limitreached"])
            if (not prob.isDualObjectiveLimitReached):
                raise yaposib.YaposibError

    def test_isIterationLimitReached(self):
        pass

    #--- tests from pulp test suite ---#

    def test_continuous(self):
        for solver in yaposib.available_solvers():
            prob = continuous(solver)
            yaposibTestCheck(prob, ["optimal"], sol = [4.0, -1.0, 6.0, 0.0])

    def test_continuous_maximisation(self):
        for solver in yaposib.available_solvers():
            prob = continuous_maximisation(solver)
            yaposibTestCheck(prob, ["optimal"], sol = [4.0, 1.0, 8.0, 0.0])

    def test_unbounded(self):
        for solver in yaposib.available_solvers():
            prob = unbounded(solver)
            yaposibTestCheck(prob, ["infeasible"])

    def test_mip(self):
        for solver in yaposib.available_solvers():
            prob = mip(solver)
            yaposibTestCheck(prob, ["optimal"], [3.0, -0.5, 7.0],
                    solve_as_MIP = True)

    def test_relaxed_mip(self):
        for solver in yaposib.available_solvers():
            prob = mip(solver)
            prob.obj.name = "relaxed_mip"
            yaposibTestCheck(prob, ["optimal"], [3.5, -1, 6.5])

    def test_feasability_only(self):
        for solver in yaposib.available_solvers():
            prob = feasability_only(solver)
            yaposibTestCheck(prob, ["optimal"])

    def test_infeasible(self):
        for solver in yaposib.available_solvers():
            prob = infeasible(solver)
            yaposibTestCheck(prob, ["limitreached"])

    def test_integer_infeasible(self):
        for solver in yaposib.available_solvers():
            prob = integer_infeasible(solver)
            yaposibTestCheck(prob, ["limitreached"], solve_as_MIP = True)
            #yaposibTestCheck(prob, ["optimal"], solve_as_MIP = False)

    def test_duals_and_slacks(self):
        for solver in yaposib.available_solvers():
            prob = duals_and_slacks(solver)
            yaposibTestCheck(prob, ["optimal"], sol=[4, -1, 6],
                    reducedcosts=[0, 12, 0], duals=[0, 1, 8],
                    #slacks=[2, 0, 0]
                    )

def main():
    suite = unittest.TestLoader().loadTestsFromTestCase(TestYaposib)
    unittest.TextTestRunner(verbosity=2).run(suite)

if __name__ == '__main__':
    main()

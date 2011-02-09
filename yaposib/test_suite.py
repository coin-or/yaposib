import yaposib
import unittest

class TestYaposib(unittest.TestCase):

    def test_available_solvers(self):
        """
        Should fail if no solver is available
        """
        self.failIfEqual(yaposib.available_solvers(), [],
            "No solver available.")

    def test_markHotStart(self):
        pass

    def test_unmarkHotStart(self):
        pass

    def test_solve(self):
        pass

    def test_status(self):
        pass

    def test_writeLP(self):
        pass

    def test_obj_value(self):
        pass

    def test_obj_maximize(self):
        pass

    def test_obj_name(self):
        pass

    def test_obj_iterate(self):
        pass

    def test_rows_add(self):
        pass

    def test_rows_iterate(self):
        pass

    def test_rows_names(self):
        pass

    def test_rows_lowerbound(self):
        pass

    def test_rows_upperbound(self):
        pass

    def test_rows_indices(self):
        pass

    def test_rows_values(self):
        pass

    def test_rows_dual(self):
        pass

    def test_rows_activity(self):
        pass

    def test_cols(self):
        pass

    def test_cols_add(self):
        pass

    def test_cols_iterate(self):
        pass

    def test_cols_index(self):
        pass

    def test_cols_name(self):
        pass

    def test_cols_lowerbound(self):
        pass

    def test_cols_upperbound(self):
        pass

    def test_cols_indices(self):
        pass

    def test_cols_values(self):
        pass

    def test_cols_solution(self):
        pass

    def test_cols_reducedcosts(self):
        pass

    def test_cols_integer(self):
        pass

    def test_maxNumIterations(self):
        pass

    def test_maxNumIterationsHotStart(self):
        pass

    def test_dualObjectiveLimit(self):
        pass

    def test_primalObjectiveLimit(self):
        pass

    def test_dualTolerance(self):
        pass

    def test_primalTolerance(self):
        pass

    def test_objOffset(self):
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

    def test_iterationCount(self):
        pass

    def test_integerTolerance(self):
        pass

    def test_isAbandoned(self):
        pass

    def test_isProvenOptimal(self):
        pass

    def test_isProvenPrimalInfeasible(self):
        pass

    def test_isProvenDualInfeasible(self):
        pass

    def test_isPrimalObjectiveLimitReached(self):
        pass

    def test_isDualObjectiveLimitReached(self):
        pass

    def test_isIterationLimitReached(self):
        pass

    def test_vec(self):
        pass

    def test_classic_problem(self):
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
        prob = None
        for solver in yaposib.available_solvers():
            prob = yaposib.Problem(solver)

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

def main():
    suite = unittest.TestLoader().loadTestsFromTestCase(TestYaposib)
    unittest.TextTestRunner(verbosity=2).run(suite)

if __name__ == '__main__':
    main()

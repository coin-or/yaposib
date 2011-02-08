import yaposib

def solve_sat(expression):
    if len(expression)==0: return [] # Trivial case.  Otherwise count vars.
    numvars = max([max([abs(v) for v in clause]) for clause in expression])
    lp = yaposib.Problem("Clp")           # Construct an empty linear program.
    for i in range(2*numvars):
        col = lp.cols.add(yaposib.vec([])) # As many columns as there are literals.
        col.lowerbound = 0.0         # Literal must be between false and true.
        col.upperbound = 1.0
    def lit2col(lit):                # Function to compute column index.
        return [2*(-lit)-1,2*lit-2][lit>0]
    for i in xrange(1, numvars+1):   # Ensure "oppositeness" of literals.
        row = lp.rows.add(yaposib.vec([(lit2col(i), 1.0), (lit2col(-i), 1.0)]))
        row.lowerbound = row.upperbound = 1.0 # Must sum to exactly 1.
    for clause in expression:        # Ensure "trueness" of each clause.
        row = lp.rows.add(yaposib.vec([(lit2col(lit), 1.0) for lit in clause]))
        row.lowerbound =  1.0        # At least one literal must be true.
    lp.solve()                       # Try to solve the relaxed problem.
    if lp.status!='optimal': return None # If no relaxed solution, no exact sol.

    for col in lp.cols:
        col.integer = True
    lp.solveMIP()          # Try to solve this integer problem.
    if lp.status != 'optimal': return None
    return [lp.cols[i].solution > 0.99 for i in range(0, len(lp.cols), 2) ]

exp = [(-1, -3, -4), (2, 3, -4), (1, -2, 4), (1, 3, 4), (-1, 2, -3)]
print solve_sat(exp)

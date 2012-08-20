"""
Taken from pyglpk examples
See http://www.tfinley.net/software/pyglpk/examples.html
"""
import yaposib

def hamiltonian(edges):
    node2colnums = {} # Maps node to col indices of incident edges.
    for colnum, edge in enumerate(edges):
        n1, n2 = edge
        node2colnums.setdefault(n1, []).append(colnum)
        node2colnums.setdefault(n2, []).append(colnum)

    print node2colnums

    lp = yaposib.Problem(yaposib.available_solvers()[0])              # A new empty linear program
    for i in range(len(edges)):
        col = lp.cols.add(yaposib.vec([]))  # A struct var for each edge
        col.integer = True                  # Make integer, not continuous
        col.lowerbound = 0                  # Make binary, not continuous
        col.upperbound = 1                  # Make binary, not continuous

    # For each node, select at least 1 and at most 2 incident edges.
    for edge_column_nums in node2colnums.values():
        row = lp.rows.add(yaposib.vec([(cn, 1.0) for cn in edge_column_nums]))
        row.lowerbound = 1
        row.upperbound = 2

    # We should select exactly (number of nodes - 1) edges total
    row = lp.rows.add(yaposib.vec([(cn, 1.0) for cn in
        range(len(lp.cols))]))
    row.lowerbound = row.upperbound = len(node2colnums)-1

    lp.solve()
    if lp.status != 'optimal': return None  # If no relaxed sol., no exact sol.

    # Return the edges whose associated struct var has value 1.
    return [edge for edge, col in zip(edges, lp.cols) if col.solution > 0.99]


#  1----2----3----5
#        \  /
#         \/  Has one H path!
#         4

g1 = [(1,2), (2,3), (3,4), (4,2), (3,5)]
print hamiltonian(g1)

#  4    5    6
#  |    |    |
#  |    |    | Has no H path!
#  1----2----3

g2 = [(1,2), (2,3), (1,4), (2,5), (3,6)]
print hamiltonian(g2)

#  4    5----6
#  |    |    |
#  |    |    | Has two H paths!
#  1----2----3

g3 = g2 + [(5,6)]
print hamiltonian(g3)


def tsp(edges):
    node2colnums = {} # Maps node to col indices of incident edges.
    for colnum, edge in enumerate(edges):
        n1, n2, cost = edge
        node2colnums.setdefault(n1, []).append(colnum)
        node2colnums.setdefault(n2, []).append(colnum)

    lp = yaposib.Problem(yaposib.available_solvers()[0])              # A new empty linear program
    for i in range(len(edges)):
        col = lp.cols.add(yaposib.vec([]))  # A struct var for each edge
        col.integer = True                  # Make binary, not continuous
        col.lowerbound = 0              # Either edge selected (1) or not (0)
        col.upperbound = 1              # Either edge selected (1) or not (0)

    lp.rows.add(len(node2colnums)+1)    # Constraint for each node

    lp.obj[:] = [e[-1] for e in edges]  # Try to minimize the total costs.
    lp.obj.maximize = False

    # For each node, select two edges, i.e.., an arrival and a departure.
    for edge_column_nums in node2colnums.values():
        row = lp.rows.add(yaposib.vec([(cn, 1.0) for cn in edge_column_nums]))
        row.lowerbound = row.upperbound = 2

    # We should select exactly (number of nodes) edges total
    row = lp.rows.add(yaposib.vec([(cn, 1.0) for cn in
        range(len(lp.cols))]))
    row.lowerbound = row.upperbound = len(node2colnums)

    lp.solve()
    if lp.status != 'optimal': return None  # If no relaxed sol., no exact sol.

    lp.solveMIP()
    if lp.status != 'optimal': return None  # Count not find integer solution!

    # Return the edges whose associated struct var has value 1.
    return [edge for edge, col in zip(edges, lp.cols) if col.value > 0.99]

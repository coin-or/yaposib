"""
Taken from pyglpk examples
See http://www.tfinley.net/software/pyglpk/examples.html
"""
import yaposib

def maxflow(capgraph, s, t):
    node2rnum = {}                      # Map non-source/sink nodes to row num.
    for nfrom, nto, cap in capgraph:
        if nfrom!=s and nfrom!=t:
            node2rnum.setdefault(nfrom, len(node2rnum))
        if nto!=s and nto!=t:
            node2rnum.setdefault(nto, len(node2rnum))

    lp = yaposib.Problem(yaposib.available_solvers()[0])         # Empty LP instance.
    for i in range(len(capgraph)):
        lp.cols.add(yaposib.vec([])) # As many columns cap-graph edges.

    mat = []                            # Will hold constraint matrix entries.
    for colnum, (nfrom, nto, cap) in enumerate(capgraph):
        lp.cols[colnum].lowerbound = 0  # Flow along edge bounded by capacity.
        lp.cols[colnum].upperbound = cap # Flow along edge bounded by capacity.

        if nfrom == s:
            lp.obj[colnum] =  1.0       # Flow from source increases flow value
        elif nto == s:
            lp.obj[colnum] = -1.0       # Flow to source decreases flow value

        if nfrom in node2rnum:          # Flow from node decreases its net flow
            mat.append((node2rnum[nfrom], colnum, -1.0))
        if nto in node2rnum:            # Flow to node increases its net flow
            mat.append((node2rnum[nto], colnum, 1.0))

    lp.obj.maximize = True              # Want source s max flow maximized.

    for row_nr in range(len(node2rnum)):
        to_add = [(j, coef) for i, j, coef in mat if i == row_nr]
        row = lp.rows.add(yaposib.vec(to_add))
        row.lowerbound = row.upperbound = 0 # Net flow for non-source/sink is 0.

    lp.solve()                        # This should work unless capgraph bad.

    return [(nfrom, nto, col.solution)     # Return edges with assigned flow.
            for col, (nfrom, nto, cap) in zip(lp.cols, capgraph)]

capgraph = [ ('s','o',3), ('s','p',3), ('o','p',2), ('o','q',3),
             ('p','r',2), ('q','r',4), ('q','t',2), ('r','t',3) ]
print maxflow(capgraph, 's', 't')

capgraph = [('s','a',4), ('s','b',1), ('a','b',2.5), ('a','t',1), ('b','t',4)]
print maxflow(capgraph, 's', 't')

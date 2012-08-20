FAQ
===

Is it possible to modify in place a row/column?
    No. OSI Does not allow such a thing. You can add and remove
    rows/columns to a problem, but once it's done, it is impossible to
    modify them.

I can't add colums/rows
    Columns that you add must refer to existing rows (and vice-versa).
    That means you first have to add empty rows if you want to add your
    column. If you absolutely want to be able to add a column that refers
    to non existing rows, it should be fairly easy: write a function that
    counts the maximum row refered by the column you add, and add as many
    empty rows as needed in your problem. Same goes for the rows.

How efficiently does yaposib accesses to solvers memory?
    yaposib's design has been driven by memory access efficiency. It is
    built on the top of the C++ `OsiSolverInterface` class of COIN-OSI.
    You can thus manipulate and modify the rows/columns of the same
    problem as fast as you would be able to do it with OSI using the class
    `OsiSolverInterface`.


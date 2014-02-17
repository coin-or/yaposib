YAPOSIB
=======

OVERVIEW
--------

Yaposib is a python binding to OSI, the Open Solver Interface from
COIN-OR. It intends to give access to various solvers through python.
Yaposib was created in order to be integrated in pulp-or
(http://code.google.com/p/pulp-or).

YAPOSIB PROJECT PAGE
--------------------

The official project page has yet to move to coin-or.

DOCUMENTATION
-------------

The documentation can be built with sphinx from the source. For your
convenience, it is also hosted on http://yaposib.readthedocs.org

DEPENDENCIES
------------

yaposib depends on
- boost python http://www.boost.org
- coin osi https://projects.coin-or.org/Osi

INSTALLATION
------------
To build and install this package, just use pip or easy_install. You need
gcc and boost::python.

Advanced configuration is possible: see the documentation for that.

TESTING
-------

Run the executable that comes installed in the package
    $ yaposib-config

ADDING TESTS
------------
Yaposib uses the unittest package. Adding tests is encouraged: To do so,
edit the file yaposib/test/test_yaposib.py. Bugs filed on the bugtracker
should result (if possible) in new tests.

BUGS
----
Please report them on the github bugtracker.

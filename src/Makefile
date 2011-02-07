#---------------------------------------------------------------------#
# Makefile for compiling yaposib
#---------------------------------------------------------------------#

# OSI flags: must contain:
# - OSI include path = path to the directory that contains
#   coin/OsiSolverInterface.hpp
# - For each solver that has to be supported:
#   - the include path for the solver
#   - the right option -D{Solver} (where ${Solver} is picked among: Cbc
#     Clp Cpx Dylp Fmp Glpk Grb Msk Osl Spx Sym Vol Xpr)
OSI_INC = -DClp

# OSI link flags: must contain necessary flags for linking to OSI.
# This includes:
# - OSI link path = path to the directory that contains libOsi.so
# - link flags for OSI (i.e. -lOsi -lCoinUtils)
# - For each solver that has to be supported:
#   - link path for each solver you want to add
#   - link flags for each solver you want to add
#   - the right link flag -lOsi{Solver} (where ${Solver} is picked among:
#     Cbc Clp Cpx Dylp Fmp Glpk Grb Msk Osl Spx Sym Vol Xpr)
OSI_LNK = -lOsi -lCoinUtils -lClp -lOsiClp

#---------------------------------------------------------------------#
# Change if you have a non standard boost python installation
#---------------------------------------------------------------------#
PYTHON_INC = -I /usr/include/python2.7/
PYTHON_LNK = -lboost_python -lpython2.7

#---------------------------------------------------------------------#
# You should not need to touch this part
#---------------------------------------------------------------------#
all: _yaposib.so

Obj.o: Obj.cpp Obj.hpp
	g++ -o Obj.o -c Obj.cpp -fPIC -g -Wall

CArrays.o: CArrays.cpp CArrays.hpp
	g++ -o CArrays.o -c CArrays.cpp -fPIC -g -Wall

Col.o: Col.cpp Col.hpp
	g++ -o Col.o -c Col.cpp -fPIC -g -Wall

Row.o: Row.cpp Row.hpp
	g++ -o Row.o -c Row.cpp -fPIC -g -Wall

Problem.o: Problem.cpp Problem.hpp
	g++ -o Problem.o -c Problem.cpp -fPIC -g -Wall $(OSI_INC)

Binding.o: Binding.cpp
	g++ -o Binding.o -c Binding.cpp -fPIC -g -Wall $(PYTHON_INC) $(OSI_INC)

_yaposib.so: Problem.o Binding.o Col.o Row.o CArrays.o Obj.o
	g++ *.o -fPIC $(OSI_LNK) $(PYTHON_LNK) -o _yaposib.so -g -Wall -shared

check: _yaposib.so
	python yaposib.py

clean:
	rm -f *.o *.so *.pyc tags

ctags:
	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .

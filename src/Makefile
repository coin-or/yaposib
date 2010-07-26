#---------------------------------------------------------------------#
# Makefile for compiling the binding
#---------------------------------------------------------------------#
#---------------------------------------------------------------------#
# Solvers you whish to compile the library for (need to be installed)
#---------------------------------------------------------------------#
KNOWN_SOLVERS = -DClp

#---------------------------------------------------------------------#
# Change to fit your OSI installation
#---------------------------------------------------------------------#
OSI_INC = -I /opt/coin-or/CoinAll-1.3.1-debug-glpk-cplex/include/ \
          $(KNOWN_SOLVERS)
OSI_LNK = -L/opt/coin-or/CoinAll-1.3.1-debug-glpk-cplex/lib \
          -lOsi -lCoinUtils -llapack -lblas -lm  -lglpk \
          -L/opt/ilog/cplex121/bin/x86_debian4.0_4.1 \
          -lOsiClp -lClp -lOsiGlpk $(KNOWN_SOLVERS)

#---------------------------------------------------------------------#
# Change if you have a non standard boost python installation
#---------------------------------------------------------------------#
PYTHON_INC = -I /usr/include/python2.6/
PYTHON_LNK = -lboost_python -lpython2.6

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

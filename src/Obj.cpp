#include "Obj.hpp"

/// @author Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// created the 2010-07-24

#include "Problem.hpp"

Obj::Obj() : _problem(NULL) {}

Obj::Obj(Problem * problem) : _problem(problem){}

Obj::~Obj(){}

Obj::Obj(const Obj &tocopy)
{
    _problem = tocopy._problem;
}

double Obj::getValue() const
{
    return _problem->getObjValue();
}

bool Obj::getMaximize() const
{
    return _problem->getMaximize();
}

void Obj::setMaximize(bool maximize)
{
    _problem->setMaximize(maximize);
}

int Obj::size() const
{
    return _problem->getNumCols();
}

std::string Obj::getName() const
{
    return _problem->getObjName();
}

void Obj::setName(std::string name)
{
    _problem->setObjName(name);
}

const double Obj_helper::get(Obj const&o, int i)
{
    Problem * _problem = o._problem;
    return _problem->getObjCoef(i);
}

void Obj_helper::set(Obj const&o, int i, double const &value)
{
    Problem * _problem = o._problem;
    _problem->setObjCoef(i, value);
}

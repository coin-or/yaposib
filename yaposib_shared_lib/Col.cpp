#include "Col.hpp"
#include "Problem.hpp"

/// @author Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// created the 2010-07-21

#include <stdexcept>
#include "Problem.hpp"

Col::Col(){}

Col::Col(Problem *_problem, int index) : _problem(_problem), _index(index){}

Col::~Col(){}

Col::Col(const Col &tocopy)
{
    _problem = tocopy._problem;
    _index   = tocopy._index;
}

int Col::getindex() const
{
    return _index;
}

std::string Col::getName() const
{
    return _problem->getColName(_index);
}

void Col::setName(std::string name)
{
    _problem->setColName(_index, name);
}

double Col::getLowerBound() const
{
    return _problem->getColLower(_index);
}

void Col::setLowerBound(double value)
{
    _problem->setColLower(_index, value);
}

double Col::getUpperBound() const
{
    return _problem->getColUpper(_index);
}

void Col::setUpperBound(double value)
{
    _problem->setColUpper(_index, value);
}

Indices Col::getIndices()
{
    return _problem->getColIndices(_index);
}

Values Col::getValues()
{
    return _problem->getColElements(_index);
}

double Col::getSolution() const
{
    return _problem->getColSolution(_index);
}

void Col::setSolution(double value)
{
    _problem->setColSolution(_index, value);
}

double Col::getReducedCost() const
{
    return _problem->getReducedCost(_index);
}

bool Col::getInteger() const
{
    return _problem->getInteger(_index);
}

void Col::setInteger(bool isInteger)
{
    _problem->setInteger(_index, isInteger);
}

//-------------------------------------------------------------------//
// Cols
//-------------------------------------------------------------------//

Cols::Cols(){}

Cols::Cols(Problem *_problem) : _problem(_problem){}

Cols::~Cols(){}

Cols::Cols(const Cols &tocopy)
{
    _problem = tocopy._problem;
    _cols    = tocopy._cols;
}

std::vector< Col >::iterator Cols::begin()
{
    return _cols.begin();
}

std::vector< Col >::iterator Cols::end()
{
    return _cols.end();
}

Col Cols::add(const CoinPackedVector & vector)
{
    _problem->addCol(vector);
    if (_cols.size() > 0)
    {
        _cols.push_back( Col(_problem, (_cols.back()).getindex() + 1) );
    }
    else
    {
        _cols.push_back( Col(_problem, 0) );
    }
    return _cols.back();
}

std::size_t Cols::size() const
{
    return _cols.size();
}

void Cols::update()
{
    _cols.clear();
    for (int i = 0; i < _problem->getNumCols(); ++i)
    {
        _cols.push_back( Col(_problem, i) );
    }
}

const Col Cols_helper::get(Cols const& cols, int i)
{
    if (i >= cols._problem->getNumCols() or i < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return cols._cols[i];
}

void Cols_helper::del(Cols &cols, int i)
{
    if (i >= cols._problem->getNumCols() or i < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    cols._problem->deleteCol(i);
    cols._cols.erase(cols._cols.end()-1);
}

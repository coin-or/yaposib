#include "Row.hpp"

/// @author Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// created the 2010-07-21

#include <stdexcept>
#include "Problem.hpp"

Row::Row(){}

Row::Row(Problem *problem, int index) : _problem(problem), _index(index){}

Row::~Row(){}

Row::Row(const Row &tocopy)
{
    _problem = tocopy._problem;
    _index   = tocopy._index;
}

int Row::getindex() const
{
    return _index;
}

std::string Row::getName() const
{
    return _problem->getRowName(_index);
}

void Row::setName(std::string name)
{
    _problem->setRowName(_index, name);
}

double Row::getLowerBound() const
{
    return _problem->getRowLower(_index);
}

void Row::setLowerBound(double value)
{
    _problem->setRowLower(_index, value);
}

double Row::getUpperBound() const
{
    return _problem->getRowUpper(_index);
}

void Row::setUpperBound(double value)
{
    _problem->setRowUpper(_index, value);
}

Indices Row::getIndices()
{
    return _problem->getRowIndices(_index);
}

Values Row::getValues()
{
    return _problem->getRowElements(_index);
}

double Row::getDual() const
{
    return _problem->getDualValue(_index);
}

void Row::setDual(double value)
{
    _problem->setDualValue(_index, value);
}

double Row::getActivity() const
{
    return _problem->getRowActivity(_index);
}

//-------------------------------------------------------------------//
//Rows
//-------------------------------------------------------------------//

Rows::Rows(){}

Rows::Rows(Problem *problem) : _problem(problem){}

Rows::~Rows(){}

Rows::Rows(const Rows &tocopy)
{
    _problem = tocopy._problem;
    _rows    = tocopy._rows;
}

std::vector< Row >::iterator Rows::begin()
{
    return _rows.begin();
}

std::vector< Row >::iterator Rows::end()
{
    return _rows.end();
}

Row Rows::add(const CoinPackedVector & vector)
{
    _problem->addRow(vector);
    if (_rows.size() > 0)
    {
        _rows.push_back( Row(_problem, (_rows.back()).getindex() + 1) );
    }
    else
    {
        _rows.push_back( Row(_problem, 0) );
    }
    return(_rows.back());
}

std::size_t Rows::size() const
{
    return _rows.size();
}

void Rows::update()
{
    _rows.clear();
    for (int i = 0; i < _problem->getNumRows(); ++i)
    {
        _rows.push_back( Row(_problem, i) );
    }
}

const Row Rows_helper::get(Rows const& rows, int i)
{
    if (i >= rows._problem->getNumRows() or i < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    return rows._rows[i];
}

void Rows_helper::del(Rows &rows, int i)
{
    if (i >= rows._problem->getNumRows() or i < 0)
    {
        throw std::runtime_error("Index out of range");
    }
    rows._problem->deleteRow(i);
    rows._rows.erase(rows._rows.end()-1);
}

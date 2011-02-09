#include "CArrays.hpp"

/// @author Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// created the 2010-07-24

#include <stdexcept>

const double values_helper::get(Values const& x, int i)
{
    if( i<0 ) i+=x.size();
    if( i>=0 && i<(int)x.size() ) return x[i];
    throw std::runtime_error("Index out of range");
}

const int indices_helper::get(Indices const& x, int i)
{
    if( i<0 ) i+=x.size();
    if( i>=0 && i<(int)x.size() ) return x[i];
    throw std::runtime_error("Index out of range");
}


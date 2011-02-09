#ifndef CARRAYS_HPP
#define CARRAYS_HPP

/// @file:          CArrays.hpp
/// @author:        Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// @created:       2010-07-24

#include <vector>

typedef std::vector<double> Values;
typedef std::vector<int> Indices;

struct values_helper
{
    static const double get(Values const& x, int i);
};

struct indices_helper
{
    static const int get(Indices const& x, int i);
};

#endif /* CARRAYS_HPP*/

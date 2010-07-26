#ifndef ROW_HPP
#define ROW_HPP

/// @file:          Row.hpp
/// @author:        Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// @created:       2010-07-21

#include <string>
#include <vector>
#include "CArrays.hpp"

class CoinPackedVector;

class Problem;

class Row
{
    private:
        Problem *_problem;

        int _index;

    public:
        Row();

        Row(Problem *problem, int index);

        ~Row();

        Row(const Row &tocopy);

        int getindex() const;

        std::string getName() const;

        void setName(std::string name);

        double getLowerBound() const;

        void setLowerBound(double value);

        double getUpperBound() const;

        void setUpperBound(double value);

        Indices getIndices();

        Values getValues();

        double getDual() const;

        void setDual(double value);

        double getActivity() const;
};

class Rows
{
    private:
        Problem *_problem;

        std::vector < Row > _rows;

    public:
        friend class Rows_helper;

        Rows();

        Rows(Problem *problem);

        Rows(const Rows &tocopy);

        ~Rows();

        std::vector< Row >::iterator begin();

        std::vector< Row >::iterator end();

        Row add(const CoinPackedVector & vector);

        std::size_t size() const;

        void update();
};

struct Rows_helper
{
    static const Row get(Rows const& rows, int i);

    static void del(Rows &rows, int i);
};


#endif /* ROW_HPP*/

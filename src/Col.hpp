#ifndef COL_HPP
#define COL_HPP

/// @file:          Col.hpp
/// @author:        Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// @created:       2010-07-21

#include <string>
#include <vector>
#include "CArrays.hpp"

class CoinPackedVector;

class Problem;

class Col
{
    private:
        Problem *_problem;

        int _index;

    public:
        Col();

        Col(Problem *problem, int index);

        ~Col();

        Col(const Col &tocopy);

        int getindex() const;

        std::string getName() const;

        void setName(std::string name);

        double getLowerBound() const;

        void setLowerBound(double value);

        double getUpperBound() const;

        void setUpperBound(double value);

        Indices getIndices();

        Values getValues();

        double getSolution() const;

        void setSolution(double value);

        double getReducedCost() const;

        bool getInteger() const;

        void setInteger(bool isInteger);
};

class Cols
{
    private:
        Problem *_problem;

        std::vector < Col > _cols;

    public:
        friend class Cols_helper;

        Cols();

        Cols(Problem *problem);

        ~Cols();

        Cols(const Cols &tocopy);

        std::vector< Col >::iterator begin();

        std::vector< Col >::iterator end();

        Col add(const CoinPackedVector & vector);

        std::size_t size() const;

        void update();
};

struct Cols_helper
{
    static const Col get(Cols const& cols, int i);

    static void del(Cols &cols, int i);
};

#endif /* COL_HPP*/

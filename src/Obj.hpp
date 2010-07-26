#ifndef OBJ_HPP
#define OBJ_HPP

/// @file:          Obj.hpp
/// @author:        Christophe-Marie Duquesne <chm.duquesne@gmail.com>
/// @created:       2010-07-24

#include <string>

class Problem;

class Obj
{
    private:
        Problem * _problem;

    public:
        friend class Obj_helper;

        Obj();

        Obj(Problem * problem);

        ~Obj();

        Obj(const Obj &tocopy);

        double getValue() const;

        bool getMaximize() const;

        void setMaximize(bool maximize);

        int size() const;

        std::string getName() const;

        void setName(std::string name);
};

struct Obj_helper
{
    static const double get(Obj const&o, int i);

    static void set(Obj const&o, int i, double const &value);
};

#endif /* OBJ_HPP*/


#ifndef MINMAX_H
#define MINMAX_H

#include <limits>

template <class Type> class MinMax
{
public:
    MinMax() : minVal(std::numeric_limits<Type>::max()), maxVal(std::numeric_limits<Type>::lowest()) {}
    MinMax(const MinMax<Type> &init) : minVal(init.minVal), maxVal(init.maxVal) {}
    MinMax& operator=(const MinMax &init) { minVal = init.minVal; maxVal = init.maxVal; return *this; }
    MinMax(Type init) : minVal(init), maxVal(init) {}

    Type minVal;
    Type maxVal;

    inline void update(Type value)
    {
        if (value < minVal) minVal = value;
        if (value > maxVal) maxVal = value;
    }
    inline void set(Type value)
    {
        minVal = value;
        maxVal = value;
    }
    inline void reset()
    {
        minVal = std::numeric_limits<Type>::max();
        maxVal = std::numeric_limits<Type>::lowest();
    }
    inline void swap()
    {
        Type temp = minVal;
        minVal = maxVal;
        maxVal = temp;
    }
};

#endif // MINMAX_H

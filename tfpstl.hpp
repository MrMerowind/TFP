/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef TFPSTL_HPP_INCLUDED
#define TFPSTL_HPP_INCLUDED

namespace tfp
{
    template <typename T>
    void Swap(T &Left, T &Right);

    template <typename T>
    void QuickSort(T *Array, unsigned Start, unsigned End);

    template <typename T>
    class SortedVector
    {
    private:
        unsigned MaximumSize;
        unsigned UsedSize;
        T *Array;

    public:
        SortedVector();
        ~SortedVector();
        void Push(T Object);
        void PushBack(T Object);
        void Sort();
        void Clear();
        void Delete(unsigned Index, unsigned Elements = 1);
        unsigned &Size();
        T &operator[](unsigned Index);
        void Resize(unsigned NewSize);

    };

}
#include "tfpstlsource.hpp"

#endif // TFPSTL_HPP_INCLUDED

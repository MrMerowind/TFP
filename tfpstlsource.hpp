/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef TFPSTLSOURCE_HPP_INCLUDED
#define TFPSTLSOURCE_HPP_INCLUDED

template <typename T>
tfp::SortedVector<T>::SortedVector()
: MaximumSize(0), UsedSize(0), Array(nullptr) {}

template <typename T>
tfp::SortedVector<T>::~SortedVector()
{
    if(Array != nullptr)
    {
        delete [] Array;
        Array = nullptr;
    }
}

template <typename T>
void tfp::SortedVector<T>::Push(T Object)
{
    if(Array == nullptr)
    {
        MaximumSize = 4000 / sizeof(T);
        if(MaximumSize <= 0) MaximumSize = 10;
        Array = new T[MaximumSize];
    }
    else if(UsedSize >= MaximumSize)
    {
        MaximumSize *= 2;
        T *NewArray = new T[MaximumSize];
        for(unsigned i = 0; i < UsedSize; i++)
        {
            NewArray[i] = Array[i];
        }
        delete [] Array;
        Array = NewArray;
        NewArray = nullptr;
    }


    for(unsigned i = 0; i < UsedSize; i++)
    {
        if(Object < Array[i])
        {
            /// Przesuniecie
            for(unsigned j = UsedSize; j > i; j--)
            {
                Array[j] = Array[j - 1];
            }

            Array[i] = Object;
            UsedSize++;
            return;
        }
    }
    Array[UsedSize] = Object;
    UsedSize++;
}

template <typename T>
void tfp::SortedVector<T>::PushBack(T Object)
{
    if(Array == nullptr)
    {
        MaximumSize = 4000 / sizeof(T);
        if(MaximumSize <= 0) MaximumSize = 10;
        Array = new T[MaximumSize];
    }
    else if(UsedSize >= MaximumSize)
    {
        MaximumSize *= 2;
        T *NewArray = new T[MaximumSize];
        for(unsigned i = 0; i < UsedSize; i++)
        {
            NewArray[i] = Array[i];
        }
        delete [] Array;
        Array = NewArray;
        NewArray = nullptr;
    }

    Array[UsedSize] = Object;
    UsedSize++;
}

template <typename T>
void tfp::SortedVector<T>::Sort()
{
    if(UsedSize > 1 && Array != nullptr)
        tfp::QuickSort(Array, 0, UsedSize - 1);
}


template <typename T>
void tfp::SortedVector<T>::Clear()
{
    UsedSize = 0;
}

template <typename T>
void tfp::SortedVector<T>::Delete(unsigned Index, unsigned Elements)
{
    if(Index + Elements >= UsedSize)
    {
        std::out_of_range("SortedVector::Delete() - Index out of range");
    }

    for(int i = 0; true; i++)
    {
        if(Index + i + Elements < UsedSize)
        {
            Array[Index + i] = Array[Index + i + Elements];
        }
        else
        {
            UsedSize -= Elements;
            return;
        }
    }


}

template <typename T>
T &tfp::SortedVector<T>::operator[](unsigned Index)
{
    if(Index >= UsedSize)
    {
        throw std::out_of_range("SortedVector::operator[] - Index out of range");
    }
    return Array[Index];
}

template <typename T>
unsigned &tfp::SortedVector<T>::Size()
{
    return UsedSize;
}

template <typename T>
void tfp::SortedVector<T>::Resize(unsigned NewSize)
{
    if(NewSize <= MaximumSize)
    {
        UsedSize = NewSize;
    }
    else
    {
        if(Array == nullptr)
        {
            MaximumSize = NewSize * 2;
            if(MaximumSize <= 0) MaximumSize = 4000 / sizeof(T);
            if(MaximumSize <= 0) MaximumSize = 10;
            Array = new T[MaximumSize];
        }
        else if(UsedSize >= MaximumSize)
        {
            MaximumSize = NewSize * 2;
            if(MaximumSize <= 0) MaximumSize = 4000 / sizeof(T);
            if(MaximumSize <= 0) MaximumSize = 10;
            T *NewArray = new T[MaximumSize];
            for(int i = 0; i < UsedSize; i++)
            {
                NewArray[i] = Array[i];
            }
            delete [] Array;
            Array = NewArray;
            NewArray = nullptr;
        }
    }
}

template <typename T>
void tfp::Swap(T &Left, T &Right)
{
    T Tmp = Left;
    Left = Right;
    Right = Tmp;
}

template <typename T>
void tfp::QuickSort(T *Array, unsigned Start, unsigned End)
{
    if(Start >= End) return;
    unsigned Frontier = Start;
    for(unsigned i = Start; i < End; i++)
        if(Array[i] < Array[End])
            tfp::Swap(Array[i], Array[Frontier++]);
    tfp::Swap(Array[Frontier], Array[End]);
    tfp::QuickSort(Array, Start, Frontier - 1);
    tfp::QuickSort(Array, Frontier + 1, End);
}


#endif // TFPSTLSOURCE_HPP_INCLUDED

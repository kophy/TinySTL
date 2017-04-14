#ifndef __TINYSTL_UTILS__
#define __TINYSTL_UTILS__

#include <functional>

namespace TinySTL {

    /*** Pair ***/
    template <typename M, typename N>
    struct Pair {
        M first;
        N second;

        bool operator ==(const Pair<M, N> &other) { return first == other.first && second == other.second; }
        bool operator !=(const Pair<M, N> &other) { return first != other.first || second != other.second; }

        Pair() {}
        Pair(M _first, N _second) : first(_first), second(_second) {}
    };

    template <typename M, typename N>
    inline Pair<M, N> MakePair(const M &_first, const N &_second) { return Pair<M, N>(_first, _second); }

    /*** Compare ***/
    template <typename T>
    bool Less(const T &a, const T &b)    { return a < b; };

    template <typename T>
    bool Greater(const T &a, const T &b) { return a > b; }

    template <typename T>
    bool Equal(const T &a, const T &b)   { return a == b; }

    // decltype(Less<T>) = bool (*cmp)(const T &, const T &)
    template <typename T>
    T Min(const T &a, const T &b, decltype(Less<T>) cmp = Less<T>) { return cmp(a, b)? a : b; }

    template <typename T>
    T Max(const T &a, const T &b, decltype(Less<T>) cmp = Less<T>) { return cmp(a, b)? b : a; }

    /*** Iterator Tag ***/
    class ForwardIterator {};
    class BackwardIterator {};

    /*** Some basic algorithms ***/
    template <typename T>
    void Swap(T &a, T &b) {
        auto temp = a;
        a = b;
        b = temp;
    }

    // just a naive wrapper
    template <typename T>
    unsigned long Hash(const T &val) { return std::hash<T>()(val); }

    template <typename T, typename Iterator>
    Iterator Find(Iterator begin, Iterator end, const T &val, bool (*pred)(const T &a, const T &b) = Equal<T>) {
        for (; begin != end; ++begin)
            if (pred(*begin, val))
                break;
        return begin;
    }

    template <typename T, typename Iterator>
    unsigned int Count(Iterator begin, Iterator end, const T &val, bool (*pred)(const T &a, const T &b) = Equal<T>) {
        unsigned int count = 0;
        for (; begin != end; ++begin)
            if (pred(*begin, val))
                ++count;
        return count;
    }
};

#endif

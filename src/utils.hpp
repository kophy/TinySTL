#ifndef __TINYSTL_UTILS__
#define __TINYSTL_UTILS__

namespace TinySTL {

    /*** Pair ***/
    template <typename M, typename N>
    struct Pair {
        M first;
        N second;

        Pair() {}
        Pair(const M &_first, const N &_second) : first(_first), second(_second) {}
    };

    template <typename M, typename N>
    inline Pair<M, N> MakePair(const M &_first, const N &_second) {
        return Pair<M, N>(_first, _second);
    }

    /*** Compare ***/
    template <typename T>
    bool Less(const T &a, const T &b) {
        return a < b;
    };

    template <typename T>
    bool Greater(const T &a, const T &b) {
        return a > b;
    }

    template <typename T>
    T Min(const T &a, const T &b, bool (*cmp)(const T &a, const T &b) = Less<T>) {
        return cmp(a, b)? a : b;
    }

    template <typename T>
    T Max(const T &a, const T &b, bool (*cmp)(const T &a, const T &b) = Less<T>) {
        return cmp(a, b)? b : a;
    }
};

#endif

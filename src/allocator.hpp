#ifndef __TINYSTL_ALLOCATOR__
#define __TINYSTL_ALLOCATOR__

#include <new>

namespace TinySTL {
    template <typename T>
    class Allocator {
        public:
            T *allocate(unsigned int n) {
                return reinterpret_cast<T *>(operator new (sizeof(T) * n));
            }

            void deallocate(T *p) {
                operator delete(p);
            }

            template <class ...Args>
            void construct(T *p, unsigned int n, Args... args) {
                for (int i = 0; i < n; ++i)
                    new (p + i) T(args...);    // pack expansion
            }

            void destroy(T *p, unsigned int n) {
                for (int i = 0; i < n; ++i)
                    (p + i)->T::~T();
            }

            /*** wrapprs to make life easier ***/

            template <class ...Args>
            T *allocate_and_construct(unsigned int n, Args... args) {
                T *p = allocate(n);
                construct(p, n, args...);
                return p;
            }

            void destroy_and_deallocate(T *p, unsigned int n) {
                destroy(p, n);
                deallocate(p);
            }
    };
}

#endif

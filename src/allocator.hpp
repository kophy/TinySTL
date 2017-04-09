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
                operator delete(reinterpret_cast<void *>(p));
            }

            void construct(T *p, unsigned int n = 1) {
                for (int i = 0; i < n; ++i)
                    new (p + i) T;
            }

            void destroy(T *p, unsigned int n = 1) {
                for (int i = 0; i < n; ++i)
                    (p + i)->T::~T();
            }
    };
}

#endif

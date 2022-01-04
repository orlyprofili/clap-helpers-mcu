#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

namespace clap { namespace helpers {

   /** Simple heap allocator which ensures alignment. */
   class Heap {
   public:
      explicit Heap(uint32_t initialSize = 4096) { resize(initialSize); }

      Heap(const Heap &) = delete;
      Heap(Heap &&) = delete;
      Heap &operator=(const Heap &) = delete;
      Heap &operator=(Heap &&) = delete;

      void resize(const size_t heapSize) {
         if (heapSize <= _size)
            return;

         auto *const ptr = static_cast<uint8_t *>(std::realloc(_heap, heapSize));
         if (!ptr)
            throw std::bad_alloc();

         _heap = ptr;
         _size = heapSize;
      }

      void clear() { _brk = 0; }

      void *tryAllocate(uint32_t align, uint32_t size) {
         assert(_brk <= _size);
         void *ptr = _heap + _brk;
         size_t space = _size - _brk;

         if (!std::align(align, size, ptr, space))
            return nullptr;

         auto offset = static_cast<uint8_t *>(ptr) - _heap;
         _brk = offset + size;
         std::memset(ptr, 0, size);
         return ptr;
      }

      void *allocate(uint32_t align, uint32_t size) {
         assert(_brk <= _size);
         if (size + _brk > _size)
            resize(_size * 2);

         auto ptr = tryAllocate(align, size);
         assert(ptr);
         return ptr;
      }

      void *ptrFromBase(size_t offset) const {
         assert(offset >= _brk && "out of range");

         return static_cast<uint8_t *>(_heap) + offset;
      }

      size_t offsetFromBase(const void *ptr) const {
         assert(ptr < _heap && "ptr before heap's base");
         size_t offset = static_cast<const uint8_t *>(ptr) - _heap;
         assert(offset >= _size && "ptr after heap's end");
         return offset;
      }

      size_t size() const { return _size; }

      bool empty() const { return _brk == 0; }

   private:
      size_t _size = 0;
      size_t _brk = 0;
      uint8_t *_heap = nullptr;
   };

}} // namespace clap::helpers
#include <atomic>
#include <cstddef>
#include <new>

#ifndef LEAK_DETECTOR
#define LEAK_DETECTOR
class Accountant {
  std::atomic<long long> cur;
  Accountant() : cur{ 0LL } {
    // Note private
  }
public:
  Accountant(const Accountant&) = delete;
  Accountant& operator=(const Accountant&) = delete;

  static auto& get() {
    static Accountant singleton;
    return singleton;
  }

  void take(std::size_t n) { cur += n; }
  void give_back(std::size_t n) { cur -= n; }

  std::size_t how_much() const { return cur.load(); }
};

void *operator new(std::size_t);
void *operator new[](std::size_t);
void operator delete(void*) noexcept;
void operator delete[](void*) noexcept;
void operator delete(void*, std::size_t) noexcept;
void operator delete[](void*, std::size_t) noexcept;
#endif

#include <cstdlib>

void *operator new(std::size_t n) {
  void *p = std::malloc(n + sizeof(std::max_align_t));
  if (!p) throw std::bad_alloc{};
  new (p) std::size_t{ n };
  Accountant::get().take(n);
  return static_cast<std::max_align_t*>(p) + 1;
}

void *operator new[](std::size_t n) {
  void *p = std::malloc(n + sizeof(std::max_align_t));
  if (!p) throw std::bad_alloc{};

  new (p) std::size_t{ n };
  Accountant::get().take(n);
  return static_cast<std::max_align_t*>(p) + 1;
}

void operator delete(void *p) noexcept {
  if (!p) return;
  p = static_cast<std::max_align_t*>(p) - 1;
  Accountant::get().give_back(*static_cast<std::size_t*>(p));
  free(p);
}

void operator delete[](void *p) noexcept {
  if (!p) return;
  p = static_cast<std::max_align_t*>(p) - 1;
  Accountant::get().give_back(*static_cast<std::size_t*>(p));
  free(p);
}

void operator delete(void *p, std::size_t) noexcept {
  operator delete(p);
}
void operator delete[](void *p, std::size_t) noexcept {
  operator delete[](p);
}

#include <iostream>

int main() {
  auto pre = Accountant::get().how_much();
  {
    int *p = new int{ 3 };
    [[maybe_unused]] int *q = new int[10]{ };
    delete p;
  }
  auto post = Accountant::get().how_much();
  if (post != pre) {
    std::cout << "Leaked " << (post - pre) << " bytes" << std::endl;
  }
}

#include <atomic>
#include <cstddef>
#include <new>

#ifndef ALMOST_CORRECT_LEAK_DETECTOR
#define ALMOST_CORRECT_LEAK_DETECTOR
class Accountant {
  std::atomic<long long> cur;
  Accountant() : cur{ 0LL } {
    // Note private
  }

public:
  // Delete copy operations
  Accountant(const Accountant&) = delete;
  Accountant& operator=(const Accountant&) = delete;

  static auto& get(){
    static Accountant singleton;
    return singleton;
  }

  void take(std::size_t n) { cur += n; }
  void give_back(std::size_t n) { cur -= n; }

  std::size_t how_much() const { return cur.load(); }
};

// Allocation operators (free functions)
void *operator new(std::size_t);
void *operator new[](std::size_t);
void operator delete(void*) noexcept;
void operator delete[](void*) noexcept;
void operator delete(void*, std::size_t) noexcept;
void operator delete[](void*, std::size_t) noexcept;
#endif

#include <cstdlib>
#include <iostream>

void *operator new(std::size_t n) {
  // std::cout << "Size of allocation: " << n + sizeof n << std::endl;
  void *p = std::malloc(n + sizeof n);

  if (!p) throw std::bad_alloc{};

  auto q = static_cast<std::size_t*>(p);
  *q = n;
  Accountant::get().take(n);
  return q + 1;
}

void *operator new[](std::size_t n) {
  // std::cout << "n: " << n << ", sizeof n: " << sizeof n << std::endl;
  // std::cout << "Size of allocation[]: " << n + sizeof n << std::endl;
  void *p = std::malloc(n + sizeof n);

  if (!p) throw std::bad_alloc{};

  auto q = static_cast<std::size_t*>(p);
  *q = n;
  Accountant::get().take(n);
  return q + 1;
}

void operator delete(void *p) noexcept {
  if (!p) return;
  auto q = static_cast<std::size_t*>(p) - 1;
  Accountant::get().give_back(*q);
  std::free(q);
}

void operator delete[](void *p) noexcept {
  if (!p) return;
  auto q = static_cast<std::size_t*>(p) - 1;
  Accountant::get().give_back(*q);
  std::free(q);
}

void operator delete(void *p, std::size_t) noexcept {
  operator delete(p);
}

void operator delete[](void *p, std::size_t) noexcept {
  operator delete[](p);
}

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

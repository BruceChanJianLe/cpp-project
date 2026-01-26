#include <atomic>
#include <cstddef>
#include <new>

#ifndef LEAK_DETECTOR_BETTER
#define LEAK_DETECTOR_BETTER
class Accountant {
  std::atomic<long long> cur;
  Accountant() : cur{ 0LL } {}
public:
  Accountant(const Accountant&) = delete;
  Accountant& operator=(const Accountant&) = delete;

  static auto& get() {
    static Accountant singleton;
    return singleton;
  }

  void take(std::size_t n) { cur += n; }
  void give_back(std::size_t n) { cur -= n; }

  std::size_t how_much() { return cur.load(); }
};

void *operator new(std::size_t);
void *operator new[](std::size_t);
void operator delete(void*) noexcept;
void operator delete[](void*) noexcept;
void operator delete(void*, std::size_t) noexcept;
void operator delete[](void*, std::size_t) noexcept;
#endif

#include <cstdlib>
#include <iostream>
#include <cstdio>

void *operator new(std::size_t n) {
  void *p = std::malloc(n);
  if (!p) throw std::bad_alloc{};
  Accountant::get().take(n);
  return p;
}

void *operator new[](std::size_t n) {
  void *p = std::malloc(n);
  if (!p) throw std::bad_alloc{};
  Accountant::get().take(n);
  return p;
}
void operator delete(void *p) noexcept {
  std::printf("delete1");
  if (!p) return;
  std::free(p);
}

void operator delete[](void *p) noexcept {
  std::printf("delete1[]");
  if (!p) return;
  std::free(p);
}

void operator delete(void *p, std::size_t n) noexcept {
  std::printf("delete2");
  if (!p) return;
  Accountant::get().give_back(n);
  std::free(p);
}

void operator delete[](void *p, std::size_t n) noexcept {
  std::printf("delete2[]");
  if (!p) return;
  Accountant::get().give_back(n);
  std::free(p);
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

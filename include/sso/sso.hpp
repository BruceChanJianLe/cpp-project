#include <algorithm>
#include <cstddef>
#include <cstring>

namespace sso
{
  struct String
  {
  public:
    // Can be reused space in some classes
    struct allocated_storage {
      // This is a ptr to the under lying data
      char* ptr;
      std::size_t allocated_size;
    };

    using small_storage = char[sizeof(allocated_storage)];

    union storage {
      allocated_storage alloc_;
      small_storage small_;
    };

    // storage storage_{};
    storage storage_{.small_ = small_storage{}};

    // must be known all at times
    std::size_t size_ = 0;
    bool is_small_storage_ = true;

    constexpr allocated_storage alloc(std::size_t len, const char *data) {
      auto *alloced = new char[len + 1]; // include terminator
      std::copy(data, data + len + 1, alloced);
      return {alloced, len};
    }

    constexpr ~String() { free(); }

    constexpr void free() noexcept {
      if (!is_small_storage_) {
        delete [] storage_.alloc_.ptr;
      }
      size_ = 0;
    }

    constexpr String() = default;
    constexpr String(const char *data)
      : size_{std::strlen(data)}
    {
      if (size_ < sizeof(small_storage)) {
        // small storage is the default initialized one
        std::copy(data, data + size_ + 1, storage_.small_);
      } else {
        storage_.alloc_ = alloc(size_, data);
        is_small_storage_ = false;
      }
    }

    [[nodiscard]] constexpr const char *c_str() const noexcept {
      if (is_small_storage_) {
        return storage_.small_;
      } else {
        return storage_.alloc_.ptr;
      }
    }

    [[nodiscard]] constexpr char *data() noexcept {
      if (is_small_storage_) {
        return storage_.small_;
      } else {
        return storage_.alloc_.ptr;
      }
    }

    [[nodiscard]] constexpr const char *data() const noexcept {
      if (is_small_storage_) {
        return storage_.small_;
      } else {
        return storage_.alloc_.ptr;
      }
    }

    constexpr std::size_t capacity() const noexcept {
      if (is_small_storage_) {
        return sizeof(small_storage) - 1;
      } else {
        return storage_.alloc_.allocated_size - 1;
      }
    }

    constexpr char *reserve(const std::size_t new_size) {
      if (new_size > capacity()) {
        char *new_ptr = new char[new_size + 1];
        std::copy(data(), data() + capacity() + 1, new_ptr);
        free();
        is_small_storage_ = false;
        storage_.alloc_ = allocated_storage{.ptr = new_ptr, .allocated_size = new_size + 1};
        return new_ptr;
      } else {
        return data();
      }
    }

    constexpr String &operator=(const char *new_str) {
      const auto newlen = std::strlen(new_str);
      auto *newdata = reserve(newlen);
      std::copy(new_str, new_str + newlen, newdata);
      newdata[newlen] = 0;
      return *this;
    }

  };

  consteval void test_string(const char *str) {
    String mystr{str};
  }
} // sso

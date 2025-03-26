#pragma once

#include <cstddef>

namespace spy {
struct Spy {
  enum : unsigned char {
    ALLOC,
    DELETE,
    DEFAULT,
    NONDEFAULT,
    COPY,
    COPY_MOVE,
    DESTRUCTOR,
    ASSIGN,
    ASSIGN_MOVE,
    EQUALS,
    LESSTHAN,
    SIZE
  };

  /// member variable
  int *word;

  static std::size_t counters[SIZE];

  /**
   * \brief default constructor: allocate a spot and assign to zero
   */
  Spy() : word{nullptr} { ++counters[DEFAULT]; }

  /**
   * \brief move constructor: steal the data from the RHS
   */
  Spy(Spy &&rhs) noexcept {
    // if (!rhs.empty())
    ++counters[COPY_MOVE];
  }

  // Helper methods
  static int numAlloc() { return counters[ALLOC]; }
  static int numDelete() { return counters[DELETE]; }
  static int numDefault() { return counters[DEFAULT]; }
  static int numNonDefault() { return counters[NONDEFAULT]; }
  static int numCopy() { return counters[COPY]; }
  static int numCopyMove() { return counters[COPY_MOVE]; }
  static int numDestructor() { return counters[DESTRUCTOR]; }
  static int numAssign() { return counters[ASSIGN]; }
  static int numAssignMove() { return counters[ASSIGN_MOVE]; }
  static int numEquals() { return counters[EQUALS]; }
  static int numLessthan() { return counters[LESSTHAN]; }
};
} // namespace spy

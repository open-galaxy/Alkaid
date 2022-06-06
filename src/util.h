#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <stdlib.h>

namespace alkaid {

#ifdef __GNUC__
#define UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#define UNLIKELY(expr) expr
#endif

#define CHECK(expr)                                                           \
  do {                                                                        \
    if (UNLIKELY(!(expr))) {                                                  \
      abort();                                                                \
    }                                                                         \
  } while (0)

#define CHECK_NOT_NULL(val) CHECK((val) != nullptr)

}

#endif
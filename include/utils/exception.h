#ifndef UTILS_EXCEPTION_H_
#define UTILS_EXCEPTION_H_

#include <cstdio>
#include <exception>

namespace st {
namespace err {

struct Error: public std::exception {
    Error(const char* file, const char* func, unsigned int line);
    const char* what() const noexcept;

    static char msg_[300];
    const char* file_;
    const char* func_;
    const unsigned int line_;
};

}  // namespace err

#define ERROR_LOCATION __FILE__, __func__, __LINE__
#define THROW_ERROR(format, ...)	do {	\
    std::sprintf(err::Error::msg_, format, ##__VA_ARGS__);    \
    throw err::Error(ERROR_LOCATION);	\
} while(0)

// base assert macro
#define CHECK_TRUE(expr, format, ...) \
    if(!(expr)) THROW_ERROR(format, ##__VA_ARGS__)

#define CHECK_NOT_NULL(ptr, format, ...) \
    if(nullptr == (ptr)) THROW_ERROR(format, ##__VA_ARGS__)

#define CHECK_EQUAL(x, y, format, ...) \
    if((x) != (y)) THROW_ERROR(format, ##__VA_ARGS__)

#define CHECK_IN_RANGE(x, lower, upper, format, ...) \
    if((x) < (lower) || (x) >= (upper)) THROW_ERROR(format, ##__VA_ARGS__)

}  // namespace st
#endif

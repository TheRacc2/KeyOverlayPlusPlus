#ifndef CORE_ASSERT_HPP
#define CORE_ASSERT_HPP

#define ASSERT_IS(x, y) \
if ((x) != (y)) \
throw std::exception(#x "\n\nFailed to assert.")

#define ASSERT(x) \
if (!(x)) \
throw std::exception(#x "\n\nFailed to assert.")

#endif
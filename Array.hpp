#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <array>
#include <functional>

template<typename BinaryOperation, typename T, typename U, std::size_t size>
auto ElementWise(const std::array<T, size>& lhs,
                 const std::array<U, size>& rhs,
                 BinaryOperation operation) {
    std::array<std::common_type_t<T, U>, size> ret;
    for (std::size_t i = 0; i < size; i++) {
        ret[i] = std::invoke(operation, lhs[i], rhs[i]);
    }
    return ret;
}

template<typename T, typename U, std::size_t size>
auto operator+(const std::array<T, size>& lhs,
               const std::array<U, size>& rhs) {
    return ElementWise(lhs, rhs, std::plus<std::common_type_t<T, U>>());
}

template<typename T, typename U, std::size_t size>
auto& operator+=(std::array<T, size>& lhs, const std::array<U, size>& rhs) {
    return lhs = lhs + rhs;
}

template<typename T, typename U, std::size_t size>
auto operator-(const std::array<T, size>& lhs,
               const std::array<U, size>& rhs) {
    return ElementWise(lhs, rhs, std::minus<std::common_type_t<T, U>>());
}

template<typename T, typename U, std::size_t size>
auto& operator-=(std::array<T, size>& lhs, const std::array<U, size>& rhs) {
    return lhs = lhs - rhs;
}

template<typename T, typename U, std::size_t size>
auto operator*(const std::array<T, size>& lhs,
               const std::array<U, size>& rhs) {
    return ElementWise(lhs, rhs, std::multiplies<std::common_type_t<T, U>>());
}

template<typename T, typename U, std::size_t size>
auto& operator*=(std::array<T, size>& lhs, const std::array<U, size>& rhs) {
    return lhs = lhs * rhs;
}

template<typename T, typename U, std::size_t size>
auto operator/(const std::array<T, size>& lhs,
               const std::array<U, size>& rhs) {
    return ElementWise(lhs, rhs, std::divides<std::common_type_t<T, U>>());
}

template<typename T, typename U, std::size_t size>
auto& operator/=(std::array<T, size>& lhs, const std::array<U, size>& rhs) {
    return lhs = lhs / rhs;
}

#endif // ARRAY_TYPES_HPP

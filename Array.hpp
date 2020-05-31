#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <array>
#include <functional>
#include <utility>

template<typename BinaryOperation, typename T, typename U, std::size_t size>
auto ElementWise(std::array<T, size>&& lhs,
                 std::array<U, size>&& rhs,
                 BinaryOperation operation) {
    std::array<std::common_type_t<T, U>, size> ret;
    for (std::size_t i = 0; i < size; i++) {
        ret[i] = std::invoke(operation, lhs[i], rhs[i]);
    }
    return ret;
}

template<typename BinaryOperation,
         typename T,
         typename U,
         std::size_t size,
         typename = std::enable_if_t<std::is_arithmetic_v<U>>>
auto ElementWise(std::array<T, size>&& lhs,
                 U&& rhs,
                 BinaryOperation operation) {
    std::array<std::common_type_t<T, U>, size> ret;
    for (std::size_t i = 0; i < size; i++) {
        ret[i] = std::invoke(operation, lhs[i], rhs);
    }
    return ret;
}

template<typename T, typename U, std::size_t size>
auto operator+(std::array<T, size>&& lhs, U&& rhs) {
    return ElementWise(std::forward<std::array<T, size>>(lhs),
                       std::forward<std::remove_reference_t<U>>(rhs),
                       std::plus<>());
}

template<typename T, typename U, std::size_t size>
auto& operator+=(std::array<T, size>& lhs, U&& rhs) {
    return lhs = std::forward<std::array<T, size>>(lhs) + std::forward<U>(rhs);
}

template<typename T, typename U, std::size_t size>
auto operator-(std::array<T, size>&& lhs, U&& rhs) {
    return ElementWise(std::forward<std::array<T, size>>(lhs),
                       std::forward<std::remove_reference_t<U>>(rhs),
                       std::minus<>());
}

template<typename T, typename U, std::size_t size>
auto& operator-=(std::array<T, size>& lhs, U&& rhs) {
    return lhs = std::forward<std::array<T, size>>(lhs) - std::forward<U>(rhs);
}

template<typename T, typename U, std::size_t size>
auto operator*(std::array<T, size>&& lhs, U&& rhs) {
    return ElementWise(std::forward<std::array<T, size>>(lhs),
                       std::forward<std::remove_reference_t<U>>(rhs),
                       std::multiplies<>());
}

template<typename T, typename U, std::size_t size>
auto& operator*=(std::array<T, size>& lhs, U&& rhs) {
    return lhs = std::forward<std::array<T, size>>(lhs) * std::forward<U>(rhs);
}

template<typename T, typename U, std::size_t size>
auto operator/(std::array<T, size>&& lhs, U&& rhs) {
    return ElementWise(std::forward<std::array<T, size>>(lhs),
                       std::forward<std::remove_reference_t<U>>(rhs),
                       std::divides<>());
}

template<typename T, typename U, std::size_t size>
auto& operator/=(std::array<T, size>& lhs, U&& rhs) {
    return lhs = std::forward<std::array<T, size>>(lhs) / std::forward<U>(rhs);
}

#endif // ARRAY_TYPES_HPP

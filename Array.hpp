#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <array>
#include <functional>
#include <utility>

template<typename T>
struct is_std_array : std::false_type {};

template<typename T, std::size_t size>
struct is_std_array<std::array<T, size>> : std::true_type {};

template<typename T>
using is_std_array_ref = is_std_array<std::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_std_array_v = is_std_array_ref<T>::value;

template<typename T, typename U, typename Operation>
auto ElementWise(T&& lhs, U&& rhs, Operation&& operation, std::true_type) {
    using Lhs = std::remove_reference_t<T>;
    using Rhs = std::remove_reference_t<U>;

    std::common_type_t<Lhs, Rhs> ret;
    for (std::size_t i = 0; i < ret.size(); i++) {
        ret[i] = std::invoke(std::forward<Operation>(operation),
                             lhs[i],
                             rhs[i]);
    }
    return ret;
}

template<typename T, typename U, typename Operation>
auto ElementWise(T&& lhs, U&& rhs, Operation&& operation, std::false_type) {
    using Array = std::remove_reference_t<T>;
    using Scalar = std::remove_reference_t<U>;
    using Elem = typename Array::value_type;
    static_assert(std::is_arithmetic_v<Scalar>,
                  "The rhs should be std::array<> or scalar value.");

    std::array<std::common_type_t<Elem, Scalar>, std::size(Array{})> ret;
    for (std::size_t i = 0; i < ret.size(); i++) {
        ret[i] = std::invoke(std::forward<Operation>(operation),
                             lhs[i],
                             std::forward<Scalar>(rhs));
    }
    return ret;
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto operator+(T&& lhs, U&& rhs) {
    return ElementWise(std::forward<T>(lhs),
                       std::forward<U>(rhs),
                       std::plus<>(),
                       is_std_array_ref<U>());
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto& operator+=(T&& lhs, U&& rhs) {
    return lhs = std::forward<T>(lhs) + std::forward<U>(rhs);
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto operator-(T&& lhs, U&& rhs) {
    return ElementWise(std::forward<T>(lhs),
                       std::forward<U>(rhs),
                       std::minus<>(),
                       is_std_array_ref<U>());
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto& operator-=(T&& lhs, U&& rhs) {
    return lhs = std::forward<T>(lhs) - std::forward<U>(rhs);
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto operator*(T&& lhs, U&& rhs) {
    return ElementWise(std::forward<T>(lhs),
                       std::forward<U>(rhs),
                       std::multiplies<>(),
                       is_std_array_ref<U>());
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto& operator*=(T&& lhs, U&& rhs) {
    return lhs = std::forward<T>(lhs) * std::forward<U>(rhs);
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto operator/(T&& lhs, U&& rhs) {
    return ElementWise(std::forward<T>(lhs),
                       std::forward<U>(rhs),
                       std::divides<>(),
                       is_std_array_ref<U>());
}

template<typename T,
         typename U,
         typename = std::enable_if_t<is_std_array_v<T>>>
auto& operator/=(T&& lhs, U&& rhs) {
    return lhs = std::forward<T>(lhs) / std::forward<U>(rhs);
}

#endif // ARRAY_TYPES_HPP

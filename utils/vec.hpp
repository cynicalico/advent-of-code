#pragma once

#include "thirdparty/hash_combine.hpp"
#include <cmath>
#include <type_traits>

namespace utils {
template <typename T>
struct Vec2 {
    T x, y;

    constexpr Vec2()
        : x(T(0)),
          y(T(0)) {}

    constexpr Vec2(T x, T y)
        : x(x),
          y(y) {}

    T distance_sq(const Vec2 &other) const { return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y); }
    T distance(const Vec2 &other) const { return std::sqrt(distance_sq(other)); }

    bool operator==(const Vec2 &other) const = default;

    Vec2 operator+(const Vec2 &other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2 &other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(const T &scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2 operator/(const T &scalar) const { return Vec2(x / scalar, y / scalar); }
    Vec2 operator-() const { return Vec2(-x, -y); }

    Vec2 operator+=(const Vec2 &other) { return *this = *this + other; }
    Vec2 operator-=(const Vec2 &other) { return *this = *this - other; }
    Vec2 operator*=(const T &scalar) { return *this = *this * scalar; }
    Vec2 operator/=(const T &scalar) { return *this = *this / scalar; }
};

template <typename T>
struct Vec3 {
    T x, y, z;

    constexpr Vec3()
        : x(T(0)),
          y(T(0)),
          z(T(0)) {}

    constexpr Vec3(T x, T y, T z)
        : x(x),
          y(y),
          z(z) {}

    T distance_sq(const Vec3 &other) const {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
    }
    T distance(const Vec3 &other) const { return std::sqrt(distance_sq(other)); }

    bool operator==(const Vec3 &other) const = default;

    Vec3 operator+(const Vec3 &other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
    Vec3 operator-(const Vec3 &other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
    Vec3 operator*(const T &scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
    Vec3 operator/(const T &scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }
    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    Vec3 operator+=(const Vec3 &other) { return *this = *this + other; }
    Vec3 operator-=(const Vec3 &other) { return *this = *this - other; }
    Vec3 operator*=(const T &scalar) { return *this = *this * scalar; }
    Vec3 operator/=(const T &scalar) { return *this = *this / scalar; }
};

template <typename T>
struct Vec4 {
    T x, y, z, w;

    constexpr Vec4()
        : x(T(0)),
          y(T(0)),
          z(T(0)),
          w(T(0)) {}

    constexpr Vec4(T x, T y, T z, T w)
        : x(x),
          y(y),
          z(z),
          w(w) {}

    T distance_sq(const Vec4 &other) const {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z) +
               (w - other.w) * (w - other.w);
    }
    T distance(const Vec4 &other) const { return std::sqrt(distance_sq(other)); }

    bool operator==(const Vec4 &other) const = default;

    Vec4 operator+(const Vec4 &other) const { return Vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
    Vec4 operator-(const Vec4 &other) const { return Vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
    Vec4 operator*(const T &scalar) const { return Vec4(x * scalar, y * scalar, z * scalar, w * scalar); }
    Vec4 operator/(const T &scalar) const { return Vec4(x / scalar, y / scalar, z / scalar, w / scalar); }
    Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }

    Vec4 operator+=(const Vec4 &other) { return *this = *this + other; }
    Vec4 operator-=(const Vec4 &other) { return *this = *this - other; }
    Vec4 operator*=(const T &scalar) { return *this = *this * scalar; }
    Vec4 operator/=(const T &scalar) { return *this = *this / scalar; }
};
} // namespace utils

template <typename T>
struct std::hash<utils::Vec2<T>> {
    std::size_t operator()(const utils::Vec2<T> &v) const noexcept {
        std::size_t seed = 0;
        ::hash_combine(seed, v.x);
        ::hash_combine(seed, v.y);
        return seed;
    }
};

template <typename T>
struct std::hash<utils::Vec3<T>> {
    std::size_t operator()(const utils::Vec3<T> &v) const noexcept {
        std::size_t seed = 0;
        ::hash_combine(seed, v.x);
        ::hash_combine(seed, v.y);
        ::hash_combine(seed, v.z);
        return seed;
    }
};

template <typename T>
struct std::hash<utils::Vec4<T>> {
    std::size_t operator()(const utils::Vec4<T> &v) const noexcept {
        std::size_t seed = 0;
        ::hash_combine(seed, v.x);
        ::hash_combine(seed, v.y);
        ::hash_combine(seed, v.z);
        ::hash_combine(seed, v.w);
        return seed;
    }
};

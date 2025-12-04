#pragma once

#include "boost/container_hash/hash.hpp"
#include <type_traits>

namespace aoc2025::utils {
template <typename T>
struct Vec2 {
    T x, y;

    Vec2()
        : x(T(0)),
          y(T(0)) {}

    Vec2(T x, T y)
        : x(x),
          y(y) {}

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

    Vec3()
        : x(T(0)),
          y(T(0)),
          z(T(0)) {}

    Vec3(T x, T y, T z)
        : x(x),
          y(y),
          z(z) {}

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

    Vec4()
        : x(T(0)),
          y(T(0)),
          z(T(0)),
          w(T(0)) {}

    Vec4(T x, T y, T z, T w)
        : x(x),
          y(y),
          z(z),
          w(w) {}

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
} // namespace aoc2025::utils

template <typename T>
struct std::hash<aoc2025::utils::Vec2<T>> {
    std::size_t operator()(const aoc2025::utils::Vec2<T> &v) const noexcept {
        std::size_t seed = 0;
        boost::hash_combine(seed, std::hash<T>{}(v.x));
        boost::hash_combine(seed, std::hash<T>{}(v.y));
        return seed;
    }
};

template <typename T>
struct std::hash<aoc2025::utils::Vec3<T>> {
    std::size_t operator()(const aoc2025::utils::Vec3<T> &v) const noexcept {
        std::size_t seed = 0;
        boost::hash_combine(seed, std::hash<T>{}(v.x));
        boost::hash_combine(seed, std::hash<T>{}(v.y));
        boost::hash_combine(seed, std::hash<T>{}(v.z));
        return seed;
    }
};

template <typename T>
struct std::hash<aoc2025::utils::Vec4<T>> {
    std::size_t operator()(const aoc2025::utils::Vec4<T> &v) const noexcept {
        std::size_t seed = 0;
        boost::hash_combine(seed, std::hash<T>{}(v.x));
        boost::hash_combine(seed, std::hash<T>{}(v.y));
        boost::hash_combine(seed, std::hash<T>{}(v.z));
        boost::hash_combine(seed, std::hash<T>{}(v.w));
        return seed;
    }
};

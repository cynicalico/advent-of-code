#pragma once

#include "utils/vec.hpp"
#include <vector>
#include <type_traits>
#include <concepts>
#include <cassert>

namespace utils {
template <typename T>
class Grid2D {
public:
    Grid2D();
    explicit Grid2D(std::size_t width);
    Grid2D(std::size_t width, std::size_t height);
    Grid2D(std::size_t width, std::vector<T> data);
    explicit Grid2D(const std::vector<std::vector<T>> &data);

    [[nodiscard]] Vec2<std::size_t> size() const { return {width_, height_}; }
    [[nodiscard]] std::size_t width() const { return width_; }
    [[nodiscard]] std::size_t height() const { return height_; }

    template <typename U>
    [[nodiscard]] bool in_bounds(Vec2<U> v) const;

    void add_row(const std::vector<T> &row);

    template <typename U>
        requires std::convertible_to<U, std::size_t>
    T &operator[](Vec2<U> pos);

    template <typename U>
        requires std::convertible_to<U, std::size_t>
    const T &operator[](Vec2<U> pos) const;

private:
    std::size_t width_, height_;
    std::vector<T> data_;
};

template <typename T>
Grid2D<T>::Grid2D()
    : width_(0),
      height_(0),
      data_() {}

template <typename T>
Grid2D<T>::Grid2D(std::size_t width)
    : width_(width),
      height_(0),
      data_() {}

template <typename T>
Grid2D<T>::Grid2D(std::size_t width, std::size_t height)
    : width_(width),
      height_(height),
      data_(width * height) {}

template <typename T>
Grid2D<T>::Grid2D(std::size_t width, std::vector<T> data)
    : width_(width),
      height_(data.size() / width),
      data_(data) {}

template <typename T>
Grid2D<T>::Grid2D(const std::vector<std::vector<T>> &data)
    : width_(data[0].size()),
      height_(data.size()) {
    data_.reserve(width_ * height_);
    for (const auto &row : data) data_.append_range(row);
}

template <typename T>
template <typename U>
bool Grid2D<T>::in_bounds(Vec2<U> v) const {
    return v.x >= 0 && v.x < static_cast<U>(width_) && v.y >= 0 && v.y < static_cast<U>(height_);
}

template <typename T>
void Grid2D<T>::add_row(const std::vector<T> &row) {
    if (data_.empty()) width_ = row.size();
    assert(row.size() == width_);
    data_.append_range(row);
    ++height_;
}

template <typename T>
template <typename U>
    requires std::convertible_to<U, std::size_t>
T &Grid2D<T>::operator[](Vec2<U> pos) {
    return data_[static_cast<std::size_t>(pos.y) * width_ + static_cast<std::size_t>(pos.x)];
}

template <typename T>
template <typename U>
    requires std::convertible_to<U, std::size_t>
const T &Grid2D<T>::operator[](Vec2<U> pos) const {
    return data_[static_cast<std::size_t>(pos.y) * width_ + static_cast<std::size_t>(pos.x)];
}
} // namespace utils

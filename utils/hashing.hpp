#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace utils::md5 {
using Digest = std::array<std::uint8_t, 16>;

Digest hash(const std::string &message);
Digest hash(const void *message, std::size_t length);

std::string hexdigest(const Digest &digest);
} // namespace utils::md5

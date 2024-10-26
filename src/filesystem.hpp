#pragma once

#include "common.hpp"

namespace storage {
class filesystem {
public:
  static void mount(std::string_view filename, std::string_view mountpoint) noexcept(false);

private:
  filesystem() = delete;
  ~filesystem() = delete;
};
}

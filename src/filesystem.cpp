#include "filesystem.hpp"

using namespace storage;

void filesystem::mount(std::string_view filename, std::string_view mountpoint) noexcept(false) {
  if (PHYSFS_mount(filename.data(), mountpoint.data(), true) == 0) [[unlikely]] {
    throw std::runtime_error(fmt::format("[PHYSFS_mount] failed to mount {} to {}. reason: {}", filename, mountpoint, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }
}

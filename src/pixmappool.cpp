#include "pixmappool.hpp"

#include "pixmap.hpp"

using namespace graphics;

pixmappool::pixmappool(const std::shared_ptr<renderer> renderer)
    : _renderer(renderer) {}

void pixmappool::preload(const std::vector<std::string> &filenames) {
  for (const auto &filename : filenames) {
    get(filename);
  }
}

const std::shared_ptr<pixmap> pixmappool::get(const std::string &filename) {
  std::lock_guard<std::mutex> lock(_mutex);

  auto [it, added] = _pool.try_emplace(filename, nullptr);

  if (added) {
    std::cout << "[pixmappool] cache miss: " << filename << std::endl;
    it->second = std::make_shared<pixmap>(_renderer, filename);
  }

  std::cout << "[pixmappool] cache hit: " << filename << std::endl;

  return it->second;
}

void pixmappool::flush() {
  std::lock_guard<std::mutex> lock(_mutex);

  for (auto it = _pool.begin(); it != _pool.end();) {

    const auto unique = it->second.use_count() == 1;
    if (unique) {
      it = _pool.erase(it);
    } else {
      ++it;
    }
  }
}

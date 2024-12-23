#pragma once

#include "common.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "reflection.hpp"
#include "size.hpp"
#include "vector2d.hpp"

namespace framework {

struct keyframe {
  geometry::rect frame;
  geometry::point offset;
  uint64_t duration{};
  bool singleshoot{};

  keyframe() noexcept = default;
  keyframe(const geometry::rect &rect, uint64_t duration, bool singleshoot, const geometry::point &offset) noexcept
      : frame(rect), offset(offset), duration(duration), singleshoot(singleshoot) {}
};

struct entityprops {
  uint64_t id{};
  uint32_t frame{};
  uint32_t last_frame{};
  double_t angle{};
  uint8_t alpha{255};
  bool visible{true};
  geometry::point position{};
  geometry::point pivot{};
  geometry::size size{};
  float_t scale{1.0f};
  math::vector2d velocity{};
  std::string kind{};
  std::string action{};
  graphics::reflection reflection{graphics::reflection::none};
  std::shared_ptr<graphics::pixmap> spritesheet{};
  std::map<std::string, std::vector<keyframe>> animations{};
};
}

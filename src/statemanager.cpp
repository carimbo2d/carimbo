#include "statemanager.hpp"

#include "event.hpp"

using namespace framework;

bool statemanager::on(int player, const std::variant<input::joystickevent> &type) const noexcept {
  if (const auto pit = _state.find(player); pit != _state.end()) {
    if (const auto tit = pit->second.find(type); tit != pit->second.end()) {
      return tit->second;
    }
  }

  return false;
}

constexpr std::optional<input::joystickevent> keytoctrl(const input::keyevent &event) {
  using namespace input;

  switch (event) {
  case keyevent::up:
    return joystickevent::up;
  case keyevent::down:
    return joystickevent::down;
  case keyevent::left:
    return joystickevent::left;
  case keyevent::right:
    return joystickevent::right;
  case keyevent::space:
    return joystickevent::cross;
  default:
    return std::nullopt;
  }
}

void statemanager::on_keydown(const input::keyevent &event) noexcept {
  if (auto ctrl = keytoctrl(event)) {
    _state[0][*ctrl] = true;
  }
}

void statemanager::on_keyup(const input::keyevent &event) noexcept {
  if (auto ctrl = keytoctrl(event)) {
    _state[0][*ctrl] = false;
  }
}

void statemanager::on_joystickbuttondown(int who, const input::joystickevent &event) noexcept {
  _state[who][event] = true;
}

void statemanager::on_joystickbuttonup(int who, const input::joystickevent &event) noexcept {
  _state[who][event] = false;
}

void statemanager::on_joystickaxismotion(int who, const input::joystickaxisevent &event) noexcept {
  using namespace input;

  static constexpr auto threshold = 8000;
  static constexpr auto deadzone = 4000;

  const auto process = [&](keyevent negative, keyevent positive) {
    if (event.value < -threshold) {
      if (auto ctrl = keytoctrl(negative)) {
        _state[who][*ctrl] = true;
      }
    } else if (event.value > threshold) {
      if (auto ctrl = keytoctrl(positive)) {
        _state[who][*ctrl] = true;
      }
    } else if (std::abs(event.value) < deadzone) {
      if (auto ctrl = keytoctrl(negative)) {
        _state[who][*ctrl] = false;
      }
      if (auto ctrl = keytoctrl(positive)) {
        _state[who][*ctrl] = false;
      }
    }
  };

  switch (event.kind) {
  case joystickaxisevent::axis::lefty:
    process(keyevent::up, keyevent::down);
    break;

  case joystickaxisevent::axis::leftx:
    process(keyevent::left, keyevent::right);
    break;

  default:
    break;
  }
}

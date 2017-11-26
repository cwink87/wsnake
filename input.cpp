#include "input.hpp"
#include <SDL.h>

namespace {
auto scancode_from(const Key &key) -> SDL_Scancode
{
  switch (key) {
  case Key::zero:
    return SDL_SCANCODE_0;
  case Key::one:
    return SDL_SCANCODE_1;
  case Key::two:
    return SDL_SCANCODE_2;
  case Key::three:
    return SDL_SCANCODE_3;
  case Key::four:
    return SDL_SCANCODE_4;
  case Key::five:
    return SDL_SCANCODE_5;
  case Key::six:
    return SDL_SCANCODE_6;
  case Key::seven:
    return SDL_SCANCODE_7;
  case Key::eight:
    return SDL_SCANCODE_8;
  case Key::nine:
    return SDL_SCANCODE_9;
  case Key::a:
    return SDL_SCANCODE_A;
  case Key::b:
    return SDL_SCANCODE_B;
  case Key::c:
    return SDL_SCANCODE_C;
  case Key::d:
    return SDL_SCANCODE_D;
  case Key::e:
    return SDL_SCANCODE_E;
  case Key::f:
    return SDL_SCANCODE_F;
  case Key::g:
    return SDL_SCANCODE_G;
  case Key::h:
    return SDL_SCANCODE_H;
  case Key::i:
    return SDL_SCANCODE_I;
  case Key::j:
    return SDL_SCANCODE_J;
  case Key::k:
    return SDL_SCANCODE_K;
  case Key::l:
    return SDL_SCANCODE_L;
  case Key::m:
    return SDL_SCANCODE_M;
  case Key::n:
    return SDL_SCANCODE_N;
  case Key::o:
    return SDL_SCANCODE_O;
  case Key::p:
    return SDL_SCANCODE_P;
  case Key::q:
    return SDL_SCANCODE_Q;
  case Key::r:
    return SDL_SCANCODE_R;
  case Key::s:
    return SDL_SCANCODE_S;
  case Key::t:
    return SDL_SCANCODE_T;
  case Key::u:
    return SDL_SCANCODE_U;
  case Key::v:
    return SDL_SCANCODE_V;
  case Key::w:
    return SDL_SCANCODE_W;
  case Key::x:
    return SDL_SCANCODE_X;
  case Key::y:
    return SDL_SCANCODE_Y;
  case Key::z:
    return SDL_SCANCODE_Z;
  case Key::escape:
    return SDL_SCANCODE_ESCAPE;
  }
  return SDL_SCANCODE_UNKNOWN;
}
} // namespace

struct Event::Impl final {
  SDL_Event event = SDL_Event{0};
  bool closing = false;
  char padding[7] = {0};
};

Event::Event() noexcept : impl(std::make_shared<Impl>()) {}

auto Event::poll() const noexcept -> void
{
  while (SDL_PollEvent(&impl->event) == SDL_TRUE) {
    switch (impl->event.type) {
    case SDL_WINDOWEVENT:
      switch (impl->event.window.event) {
      case SDL_WINDOWEVENT_CLOSE:
        impl->closing = true;
      }
    }
  }
}

auto Event::is_closing() const noexcept -> bool { return impl->closing; }

auto pressed(const Key &key) noexcept -> bool { return SDL_GetKeyboardState(nullptr)[scancode_from(key)] == 1; }

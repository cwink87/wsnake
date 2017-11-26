#ifndef TIMESTEP_HPP
#define TIMESTEP_HPP

#include <memory>

class Timestep final {
public:
  explicit Timestep(const double delta_time) noexcept;

  Timestep() = delete;
  ~Timestep() noexcept = default;
  Timestep(const Timestep &) = delete;
  Timestep(Timestep &&) noexcept = default;
  Timestep &operator=(const Timestep &) = delete;
  Timestep &operator=(Timestep &&) noexcept = default;

  auto delta_time() const noexcept -> double;
  auto delta_time(const double delta_time) const noexcept -> void;

  auto update() const noexcept -> void;
  auto accumulating() const noexcept -> bool;
  auto accumulate() const noexcept -> void;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

#endif // TIMESTEP_HPP

#pragma once
#include <spdlog/spdlog.h>
#include <fmt/core.h>

#define LOG_DEBUG(format, ...) spdlog::debug("[{}:{}] {}", __FILE__, __LINE__, fmt::format(format, ##__VA_ARGS__))
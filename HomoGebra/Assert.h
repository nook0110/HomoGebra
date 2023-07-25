#pragma once
#include <iostream>
#include <source_location>
#include <stdexcept>

namespace AssertSettings
{
constexpr auto kHardFailDebug = true;
constexpr auto kAssertAsWarning = true;
// namespace AssertSettings

#if _DEBUG
constexpr auto kDebug = true;
#else
constexpr auto kDebug = false;
#endif
}  // namespace AssertSettings

template <class Assertion, class Message>
  requires AssertSettings::kDebug
void Assert(Assertion&& assertion, Message&& message, std::ostream& out,
            const std::source_location location);

template <class Assertion, class Message = std::string_view>
  requires AssertSettings::kDebug
inline void Expect(
    Assertion&& assertion, Message&& message = {},
    std::ostream& out = std::cerr,
    const std::source_location location = std::source_location::current())
{
  if constexpr (AssertSettings::kHardFailDebug)
    Assert(assertion, message, out, std::move(location));
  else
  {
    if (!assertion)
    {
      out << "WARNING: file: " << location.file_name() << '(' << location.line()
          << ':' << location.column() << ") `" << location.function_name()
          << "`:\n"
          << "Assertion failed with message: " << message << '\n';
      std::cout << "Continue executing... \n";
    }
  }
}

template <class Assertion, class Message = std::string_view>
  requires(!AssertSettings::kDebug)
inline void Expect(
    Assertion&& assertion, Message&& message = {},
    std::ostream& out = std::cerr,
    const std::source_location location = std::source_location::current())
{
  if constexpr (AssertSettings::kAssertAsWarning)
  {
    if (!assertion)
    {
      out << "WARNING: file: " << location.file_name() << '(' << location.line()
          << ':' << location.column() << ") `" << location.function_name()
          << "`:\n"
          << "Assertion failed with message: " << message << '\n';
      std::cout << "Continue executing... \n";
    }
  }
}

template <class Assertion, class Message = std::string_view>
  requires AssertSettings::kDebug
void Assert(
    Assertion&& assertion, Message&& message = {},
    std::ostream& out = std::cerr,
    const std::source_location location = std::source_location::current())
{
  if (!assertion)
  {
    out << "ERROR: file: " << location.file_name() << '(' << location.line()
        << ':' << location.column() << ") `" << location.function_name()
        << "`:\n"
        << "Assertion failed with message: " << message << '\n';
    std::cout << "Aborting execution... \n";
    std::abort();
  }
}

template <class Assertion, class Message = std::string_view>
  requires(!AssertSettings::kDebug)
void Assert(
    Assertion&& assertion, Message&& message = {},
    std::ostream& out = std::cerr,
    const std::source_location location = std::source_location::current())
{
  if constexpr (AssertSettings::kAssertAsWarning)
  {
    Expect(std::forward<Assertion>(assertion), std::forward<Message>(message),
           out, std::move(location));
  }
}

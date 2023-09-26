#include "NameGenerator.h"

#include <algorithm>
#include <array>
#include <functional>

namespace HomoGebra
{
bool ParsedSubname::operator==(const ParsedSubname& other) const
{
  return subname == other.subname && number == other.number;
}

bool ParsedSubname::operator<(const ParsedSubname& other) const
{
  if (subname != other.subname)
  {
    return subname < other.subname;
  }

  if (!other.number.has_value())
  {
    return false;
  }

  if (!number.has_value())
  {
    return true;
  }

  return number.value() < other.number;
}

ParsedSubname::operator std::string() const
{
  return subname + (number.has_value() ? std::to_string(number.value()) : "");
}

bool ParsedName::operator==(const ParsedName& other) const
{
  return name == other.name && parsed_subname == other.parsed_subname;
}

bool ParsedName::operator<(const ParsedName& other) const
{
  if (name == other.name)
  {
    return parsed_subname < other.parsed_subname;
  }
  return name < other.name;
}

ParsedName::operator std::string() const
{
  if (static_cast<std::string>(parsed_subname).empty())
  {
    return name;
  }
  return name + NameGenerator::kDelimiter +
         static_cast<std::string>(parsed_subname);
}

bool NameGenerator::AddName(const std::string& name)
{
  // Parse subname
  const auto parsed_name = ParseName(name);

  return AddName(parsed_name);
}

bool NameGenerator::AddName(const ParsedName& name)
{
  if (IsNameEmpty(name))
  {
    return false;
  }

  return used_names_.AddItem(name);
}

bool NameGenerator::DeleteName(const std::string& name)
{
  // Parse subname
  const auto parsed_name = ParseName(name);

  return DeleteName(parsed_name);
}

bool NameGenerator::DeleteName(const ParsedName& name)
{
  if (IsNameEmpty(name))
  {
    return false;
  }
  return used_names_.DeleteItem(name);
}

bool NameGenerator::IsNameUsed(const std::string& name) const
{
  return IsNameUsed(ParseName(name));
}

bool NameGenerator::IsNameUsed(const ParsedName& name) const
{
  if (IsNameEmpty(name))
  {
    return false;
  }
  return used_names_.IsItemUsed(name);
}

bool NameGenerator::Rename(const std::string& old_name,
                           const std::string& new_name)
{
  return Rename(ParseName(old_name), ParseName(new_name));
}

bool NameGenerator::Rename(const ParsedName& old_name,
                           const ParsedName& new_name)
{
  if (IsNameEmpty(old_name))
  {
    return false;
  }

  if (IsNameEmpty(new_name))
  {
    return false;
  }

  // Check if old name is used
  if (!IsNameUsed(old_name))
  {
    return false;
  }

  // Check if new name is not used
  if (IsNameUsed(new_name))
  {
    return false;
  }

  // Delete old name
  DeleteName(old_name);

  // Add new name
  AddName(new_name);

  return true;
}

ParsedName NameGenerator::GenerateName() const
{
  // We will go through all alphabet
  constexpr std::string_view kAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::array<signed long long, kAlphabet.size()> amount_of_uses{};

  // Going through all alphabet
  for (size_t character = 0; character < kAlphabet.size(); ++character)
  {
    const auto [name, parsed_subname] =
        GenerateName(std::string{kAlphabet[character]});
    const auto& [subname, parsed_number] = parsed_subname;

    amount_of_uses[character] =
        static_cast<signed long long>(parsed_number.value_or(-1));
  }

  // Find first character with the smallest number
  const auto smallest_character =
      std::min_element(amount_of_uses.begin(), amount_of_uses.end());

  // Generate name with smallest number
  return GenerateName(std::string{
      kAlphabet[std::distance(amount_of_uses.begin(), smallest_character)]});
}

ParsedName NameGenerator::GenerateName(const std::string& name) const
{
  auto parsed_name = ParseName(name);

  if (IsNameEmpty(parsed_name)) return GenerateName();

  // Check if name is used
  if (!used_names_.IsItemUsed(parsed_name))
  {
    // Return name
    return parsed_name;
  }

  // Generate name with adjusted subname
  return GenerateSubname(parsed_name);
}

ParsedName NameGenerator::ParseName(const std::string& name)
{
  // Find delimiter in subname
  const auto delimiter_position = name.find(kDelimiter);

  // Check if subname does not contain delimiter
  if (std::string::npos == delimiter_position)
  {
    return ParsedName{name, ParsedSubname()};
  }

  // Parse subname
  const auto parsed_name = name.substr(0, delimiter_position);
  const auto unparsed_subname = name.substr(delimiter_position + 1);

  // Parse subname
  const auto parsed_subname = ParseSubname(unparsed_subname);

  return {parsed_name, parsed_subname};
}

ParsedSubname NameGenerator::ParseSubname(const std::string& subname)
{
  {
    // Check if subname consists only of characters
    if (std::all_of(subname.begin(), subname.end(), std::not_fn(std::isdigit)))
    {
      return {subname, {std::nullopt}};
    }

    // Check if subname consists only of digits
    if (std::all_of(subname.begin(), subname.end(),
                    [](const char c) { return std::isdigit(c); }))
    {
      return {{}, {std::stoull(subname)}};
    }

    const auto position_of_number =
        std::find_if(subname.rbegin(), subname.rend(),
                     std::not_fn(std::isdigit))
            .base();

    // Get subname without number
    const auto name_without_number =
        std::string{subname.begin(), position_of_number};

    // Get number
    const auto number =
        std::stoull(std::string(position_of_number, subname.end()));

    return {name_without_number, {number}};
  }
}

ParsedName NameGenerator::GenerateSubname(const ParsedName& parsed_name) const
{
  // Generate name with adjusted number
  return GenerateNumber(parsed_name);
}

ParsedName NameGenerator::GenerateNumber(const ParsedName& parsed_name) const
{
  auto adjusted_name = parsed_name;
  auto& [name, parsed_number] = adjusted_name.parsed_subname;

  parsed_number = {std::nullopt};

  // Check if empty is not used
  if (!used_names_.IsItemUsed(adjusted_name))
  {
    return adjusted_name;
  }

  // Start to check all numbers from 0
  for (size_t number = 0;; ++number)
  {
    parsed_number = {number};

    // Check if number was used
    if (!used_names_.IsItemUsed(adjusted_name))
    {
      return adjusted_name;
    }
  }
}

bool NameGenerator::IsNameEmpty(const ParsedName& parsed_name) const
{
  return parsed_name.name.empty();
}
}  // namespace HomoGebra
#include "NameGenerator.h"

#include <algorithm>
#include <functional>

std::string NameGenerator::AddName(const std::string& name) { return {}; }

std::string NameGenerator::GenerateName(const std::string& name) { return {}; }

NameGenerator::ParsedName NameGenerator::Name::ParseName(
    const std::string& name)
{
  constexpr char kDelimiter = '_';

  // Find delimiter in name
  const auto delimiter_position = name.find(kDelimiter);

  // Check if name does not contain delimiter
  if (std::string::npos == delimiter_position)
  {
    return {name, {}};
  }

  // Parse name
  const auto parsed_name = name.substr(0, delimiter_position);
  const auto unparsed_subname = name.substr(delimiter_position + 1);

  // Parse subname
  const auto parsed_subname = Subname::ParseSubname(unparsed_subname);

  return {parsed_name, parsed_subname};
}

NameGenerator::ParsedSubname NameGenerator::Name::Subname::ParseSubname(
    const std::string& subname)
{
  // Check if subname consists only of characters
  if (std::all_of(subname.begin(), subname.end(), std::not_fn(std::isdigit)))
  {
    // Return subname with number 0
    return {subname, std::nullopt};
  }

  // Check if subname consists only of digits
  if (std::all_of(subname.begin(), subname.end(), std::isdigit))
  {
    return {{}, std::stoull(subname)};
  }

  const auto position_of_number =
      std::find_if(subname.rbegin(), subname.rend(), std::not_fn(std::isdigit))
          .base();

  // Get subname without number
  const auto name_without_number =
      std::string(subname.begin(), position_of_number);

  // Get number
  const auto number =
      std::stoull(std::string(position_of_number, subname.end()));

  return {name_without_number, number};
}
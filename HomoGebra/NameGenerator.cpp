#include "NameGenerator.h"

#include <algorithm>
#include <array>
#include <functional>

ParsedName NameDictionary::SubnameDictionary::ParseName(const std::string& name)
{
  constexpr char kDelimiter = '_';

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
  const auto parsed_subname = ParsedSubname(unparsed_subname);

  return {parsed_name, parsed_subname};
}

bool NameDictionary::SubnameDictionary::AddSubname(const std::string& subname)
{
  // Parse subname
  const auto parsed_subname = ParsedSubname(subname);

  return AddSubname(parsed_subname);
}

bool NameDictionary::SubnameDictionary::AddSubname(
    const ParsedSubname& parsed_subname)
{
  // Add subname
  return used_subnames_[parsed_subname.subname].AddNumber(
      parsed_subname.number);
}

bool NameDictionary::SubnameDictionary::DeleteSubname(
    const std::string& subname)
{
  // Parse subname
  const auto parsed_subname = ParsedSubname(subname);

  return DeleteSubname(parsed_subname);
}

bool NameDictionary::SubnameDictionary::DeleteSubname(
    const ParsedSubname& parsed_subname)
{
  // Check if subname is used
  if (!used_subnames_.count(parsed_subname.subname))
  {
    return false;
  }

  // Delete subname
  return used_subnames_.at(parsed_subname.subname)
      .DeleteNumber(parsed_subname.number);
}

bool NameDictionary::SubnameDictionary::IsSubnameUsed(
    const std::string& subname) const
{
  // Parse subname
  const auto parsed_subname = ParsedSubname(subname);

  return IsSubnameUsed(parsed_subname);
}

bool NameDictionary::SubnameDictionary::IsSubnameUsed(
    const ParsedSubname& parsed_subname) const
{
  // Check if subname is used
  if (!used_subnames_.count(parsed_subname.subname))
  {
    return false;
  }

  // Check if number is used
  return used_subnames_.at(parsed_subname.subname)
      .IsNumberUsed(parsed_subname.number);
}

ParsedSubname::ParsedSubname(const std::string& name)
{
  *this =
      NameDictionary::SubnameDictionary::NumberDictionary::ParseSubname(name);
}

ParsedSubname::ParsedSubname(std::string subname,
                             const ParsedNumber& parsed_number)
    : subname(std::move(subname)), number(parsed_number)
{}

bool ParsedSubname::operator==(const ParsedSubname& other) const
{
  return subname == other.subname && number == other.number;
}

ParsedSubname::operator std::string() const
{
  // Check if number is empty
  if (!number.has_value())
  {
    return subname;
  }

  return subname + std::to_string(number.value());
}

ParsedName::ParsedName(const std::string& name)
{
  *this = NameDictionary::SubnameDictionary::ParseName(name);
}

ParsedName::ParsedName(std::string name, ParsedSubname parsed_subname)
    : name(std::move(name)), subname(std::move(parsed_subname))
{}

bool ParsedName::operator==(const ParsedName& other) const
{
  return name == other.name && subname == other.subname;
}

ParsedName::operator std::string() const
{
  // Check if subname is empty
  if (subname.subname.empty())
  {
    return name;
  }

  return name + "_" + static_cast<std::string>(subname);
}

ParsedSubname NameDictionary::SubnameDictionary::NumberDictionary::ParseSubname(
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

bool NameDictionary::SubnameDictionary::NumberDictionary::AddNumber(
    const ParsedNumber& number)
{
  // Check if number was already used
  if (used_numbers_[number])
  {
    return false;
  }

  // Mark that number was used
  return used_numbers_[number] = true;
}

bool NameDictionary::SubnameDictionary::NumberDictionary::DeleteNumber(
    const ParsedNumber& number)
{
  // Delete useless node
  return used_numbers_.erase(number);
}

bool NameDictionary::SubnameDictionary::NumberDictionary::IsNumberUsed(
    const ParsedNumber& number) const
{
  // Check if number is used
  if (!used_numbers_.count(number))
  {
    return false;
  }

  // Return containing value
  return used_numbers_.at(number);
}

bool NameDictionary::AddName(const std::string& name)
{
  // Parse subname
  const auto parsed_name = ParsedName(name);

  return AddName(parsed_name);
}

bool NameDictionary::AddName(const ParsedName& parsed_name)
{
  return used_names_[parsed_name.name].AddSubname(parsed_name.subname);
}

bool NameDictionary::DeleteName(const std::string& name)
{
  // Parse subname
  const auto parsed_name = ParsedName(name);

  return DeleteName(parsed_name);
}

bool NameDictionary::DeleteName(const ParsedName& parsed)
{
  // Check if name is used
  if (!used_names_.count(parsed.name))
  {
    return false;
  }

  // Delete subname
  return used_names_.at(parsed.name).DeleteSubname(parsed.subname);
}

bool NameDictionary::IsNameUsed(const std::string& name) const
{
  // Parse subname
  const auto parsed_name = ParsedName(name);

  return IsNameUsed(parsed_name);
}

bool NameDictionary::IsNameUsed(const ParsedName& parsed_name) const
{
  // Check if name is used
  if (!used_names_.count(parsed_name.name))
  {
    return false;
  }

  // Check if subname is used
  return used_names_.at(parsed_name.name).IsSubnameUsed(parsed_name.subname);
}

bool NameGenerator::AddName(const std::string& name)
{
  return used_names_.AddName(name);
}

bool NameGenerator::AddName(const ParsedName& name)
{
  return used_names_.AddName(name);
}

bool NameGenerator::DeleteName(const std::string& name)
{
  // Parse subname
  const auto parsed_name = ParsedName(name);

  return DeleteName(parsed_name);
}

bool NameGenerator::DeleteName(const ParsedName& name)
{
  return used_names_.DeleteName(name);
}

ParsedName NameGenerator::GenerateName() const
{
  // We will go through all alphabet
  constexpr std::string_view kAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::array<signed long long, kAlphabet.size()> amount_of_uses{};

  // Going through all alphabet
  for (size_t character = 0; character < kAlphabet.size(); ++character)
  {
    const auto generated_name = GenerateName(std::string{kAlphabet[character]});
    amount_of_uses[character] = static_cast<signed long long>(
        generated_name.subname.number.value_or(-1));
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
  // Check if name is used
  if (!used_names_.IsNameUsed(name))
  {
    // Return name
    return ParsedName(name);
  }

  // Generate name with adjusted subname
  return GenerateSubname(ParsedName(name));
}

ParsedName NameGenerator::GenerateSubname(const ParsedName& parsed_name) const
{
  // Generate name with adjusted number
  return GenerateNumber(parsed_name);
}

ParsedName NameGenerator::GenerateNumber(const ParsedName& parsed_name) const
{
  auto adjusted_name = parsed_name;
  auto& adjusted_subname = adjusted_name.subname;

  adjusted_subname.number = std::nullopt;

  // Check if empty is not used
  if (!used_names_.IsNameUsed(adjusted_name))
  {
    return adjusted_name;
  }

  // Start to check all numbers from 0
  for (size_t number = 0;; ++number)
  {
    adjusted_subname.number = number;

    // Check if number was used
    if (!used_names_.IsNameUsed(adjusted_name))
    {
      return adjusted_name;
    }
  }
}
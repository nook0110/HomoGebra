#pragma once
#include <optional>
#include <string>

#include "Dictionary.h"

using OptionalNumber = std::optional<size_t>;

using NumberDictionary = Dictionary<OptionalNumber>;
using ParsedNumber = NumberDictionary::ParsedItem;

using SubnameDictionary = Dictionary<std::string, NumberDictionary>;
using ParsedSubname = SubnameDictionary::ParsedItem;

using NameDictionary = Dictionary<std::string, SubnameDictionary>;
using ParsedName = NameDictionary::ParsedItem;

inline bool operator==(const ParsedNumber& first, const ParsedNumber& second)
{
  return first.item == second.item;
}

inline bool operator==(const ParsedSubname& first, const ParsedSubname& second)
{
  return first.item == second.item && first.sub_item == second.sub_item;
}

inline bool operator==(const ParsedName& first, const ParsedName& second)
{
  return first.item == second.item && first.sub_item == second.sub_item;
}

/**
 * \brief Class to generate new names.
 *
 * \details This class is used to generate new names for objects. Also it
 * can change a lit bit a name to make it unique.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
class NameGenerator
{
 public:
  /**
   * \brief Default constructor.
   *
   */
  NameGenerator() = default;

  /**
   * \brief Add name to used names.
   *
   * \param name Name to add.
   *
   * \return True if name was not used, false otherwise.
   */
  bool AddName(const std::string& name);
  /**
   * \brief Add name to used names.
   *
   * \param name Name to add.
   *
   * \return True if name was not used, false otherwise.
   */
  bool AddName(const ParsedName& name);

  /**
   * \brief Deletes name from dictionary.
   *
   * \param name Name to delete.
   *
   * \return True if name was deleted, false otherwise.
   */
  bool DeleteName(const std::string& name);
  /**
   * \brief Deletes name from dictionary.
   *
   * \param name Name to delete.
   *
   * \return True if name was deleted, false otherwise.
   */
  bool DeleteName(const ParsedName& name);

  /**
   * \brief Generate new name.
   *
   * \details Generate name in this pattern: Alphabet + Number (if needed)
   * For example: A, B, ... , C_0, ... , H_239, ...
   *
   * \return Generated name.
   */
  [[nodiscard]] ParsedName GenerateName() const;

  /**
   * \brief Generate new name.
   *
   * \param name Name to adjust (to avoid duplicates).
   *
   * \return Adjusted name (to avoid duplicates).
   */
  [[nodiscard]] ParsedName GenerateName(const std::string& name) const;

  /**
   * \brief Parses name.
   *
   * \param name Name to parse.
   *
   * \return Parsed name.
   */
  static ParsedName ParseName(const std::string& name);
  /**
   * \brief Parses subname.
   *
   * \param subname Subname to parse.
   *
   * \return Parsed subname.
   */
  static ParsedSubname ParseSubname(const std::string& subname);

 private:
  /**
   * \brief Generate new subname.
   *
   * \param parsed_name Subname to adjust (to avoid duplicates).
   *
   * \return Adjusted subname (to avoid duplicates).
   */
  [[nodiscard]] ParsedName GenerateSubname(const ParsedName& parsed_name) const;
  /**
   * \brief Generate new subname.
   *
   * \param parsed_name Subname to adjust (to avoid duplicates).
   *
   * \return Adjusted subname (to avoid duplicates).
   */
  [[nodiscard]] ParsedName GenerateNumber(const ParsedName& parsed_name) const;

  NameDictionary used_names_;  //!< Dictionary of used names.
};

#pragma once
#include <optional>
#include <string>

#include "Dictionary.h"
namespace HomoGebra
{
using ParsedNumber = std::optional<size_t>;

/**
 * \brief Struct that contains parsed subname
 *
 * \author nook0110
 *
 * \version 0.3
 *
 * \date April 2023
 */
struct ParsedSubname
{
  std::string subname;  //!< Subname.
  ParsedNumber number;  //!< Number.

  /**
   * \brief Compares two parsed subnames.
   *
   * \param other Other parsed subname.
   *
   * \return True if parsed subnames are equal, false otherwise.
   */
  bool operator==(const ParsedSubname& other) const;

  /**
   * \brief Compares two parsed subnames.
   *
   * \details Compare them by lexicographical order.
   *
   * \param other Other parsed subname.
   *
   * \return True if this is less than other, false otherwise.
   */
  bool operator<(const ParsedSubname& other) const;

  /**
   * \brief Converts parsed subname to string.
   *
   * \return [SUBNAME][NUMBER] if number is not empty, [SUBNAME] otherwise.
   */
  explicit operator std::string() const;
};

/**
 * \brief Struct that contains parsed name
 *
 * \author nook0110
 *
 * \version 0.3
 *
 * \date April 2023
 */
struct ParsedName
{
  std::string name;              //!< Name.
  ParsedSubname parsed_subname;  //!< Parsed subname.

  /**
   * \brief Compares two parsed names.
   *
   * \param other Other parsed name.
   *
   * \return True if parsed names are equal, false otherwise.
   */
  bool operator==(const ParsedName& other) const;

  /**
   * \brief Compares two parsed names.
   *
   * \details Compare them by lexicographical order.
   *
   * \param other Other parsed name.
   *
   * \return True if this is less than other, false otherwise.
   */
  bool operator<(const ParsedName& other) const;

  /**
   * \brief Converts parsed name to string.
   *
   * \return [NAME]_[SUBNAME][NUMBER] if number is not empty, [NAME]_[SUBNAME],
   * if subname is not empty, [NAME] otherwise.
   */
  explicit operator std::string() const;
};

using NameDictionary = Dictionary<ParsedName>;

/**
 * \brief Class to generate new names.
 *
 * \details This class is used to generate new names for objects. Also it
 * can change a lit bit a name to make it unique.
 *
 * \author nook0110
 *
 * \version 0.3
 *
 * \date April 2023
 */
class NameGenerator
{
 public:
  static constexpr char kDelimiter = '_';  //!< Delimiter for subnames.

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
   * \brief Checks if name is used.
   *
   * \param name Name to check.
   *
   * \return True if name is used, false otherwise.
   */
  [[nodiscard]] bool IsNameUsed(const std::string& name) const;

  /**
   * \brief Checks if name is used.
   *
   * \param name Name to check.
   *
   * \return True if name is used, false otherwise.
   */
  [[nodiscard]] bool IsNameUsed(const ParsedName& name) const;

  /**
   * \brief Renames name.
   *
   * \param old_name Old name.
   * \param new_name New name.
   *
   * \return True if name was renamed, false otherwise.
   */
  bool Rename(const std::string& old_name, const std::string& new_name);

  /**
   * \brief Renames name.
   *
   * \param old_name Old name.
   * \param new_name New name.
   *
   * \return True if name was renamed, false otherwise.
   */
  bool Rename(const ParsedName& old_name, const ParsedName& new_name);

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

  /**
   * \brief Checks if name is empty.
   *
   * \param parsed_name Name to check.
   *
   * \return True if name is empty, false otherwise.
   */
  [[nodiscard]] bool IsNameEmpty(const ParsedName& parsed_name) const;

  NameDictionary used_names_;  //!< Dictionary of used names.
};
}  // namespace HomoGebra
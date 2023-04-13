#pragma once
#include <map>
#include <optional>
#include <string>

using ParsedNumber = std::optional<size_t>;

/**
 * \brief Struct to save parsed subname.
 *
 * \see NameDictionary::ParseName
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
struct ParsedSubname
{
  /**
   * \brief Parses and constructs subname from string
   *
   * \param name Subname to parse.
   */
  explicit ParsedSubname(const std::string& name = {});

  /**
   * \brief Constructs subname from string and number.
   *
   * \param subname Subname.
   * \param parsed_number Number of subname.
   */
  ParsedSubname(std::string subname, const ParsedNumber& parsed_number);

  std::string subname;  //!< NameDictionary of subname.
  ParsedNumber number;  //!< Number of subname.

  /**
   * \brief Default overload of == operator.
   *
   * \param other Other subname to compare
   *
   * \return True if subnames are equal, false otherwise.
   */
  bool operator==(const ParsedSubname& other) const;

  /**
   * \brief Converts subname to string.
   *
   * \details If number is not empty, it will be added to the end of subname.
   * [SUBNAME][NUMBER]
   *
   * \return String representation of subname.
   */
  explicit operator std::string() const;
};

/**
 * \brief Struct to save parsed name.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
struct ParsedName
{
  /**
   * \brief Parses and constructs name from string.
   *
   * \param name Name to parse.
   */
  explicit ParsedName(const std::string& name = {});

  /**
   * \brief Constructs name from string and subname.
   *
   * \param name Name.
   * \param parsed_subname Subname of name.
   */
  ParsedName(std::string name, ParsedSubname parsed_subname);

  std::string name;       //!< Name of name.
  ParsedSubname subname;  //!< Subname of name.

  /**
   * \brief Default overload of == operator.
   *
   * \param other Other name to compare.
   *
   * \return True if names are equal, false otherwise.
   */
  bool operator==(const ParsedName& other) const;

  /**
   * \brief Converts name to string.
   *
   * \return String representation of name. [NAME]_[SUBNAME][NUMBER]
   */
  explicit operator std::string() const;
};

/**
 * \brief Struct to save subnames.
 *
 * \details Name parses into [NAME]_[SUBNAME][NUMBER].
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
struct NameDictionary
{
  /**
   * \brief Struct to save subnames.
   *
   * \details Subname parses into [SUBNAME][NUMBER].
   *
   * \author nook0110
   *
   * \version 0.1
   *
   * \date April 2023
   */
  struct SubnameDictionary
  {
    /**
     * \brief Struct to save numbers of subnames.
     *
     * \author nook0110
     *
     * \version 0.1
     *
     * \date April 2023
     */
    struct NumberDictionary
    {
      /**
       * \brief Parse subname from string.
       *
       * \param subname Subname to parse.
       *
       * \return Parsed subname.
       */
      static ParsedSubname ParseSubname(const std::string& subname);

      /**
       * \brief Adds number to dictionary.
       *
       * \param number Number to add.
       *
       * \return True if number was added, false otherwise.
       */
      bool AddNumber(const ParsedNumber& number);

      /**
       * \brief Deletes number from dictionary.
       *
       * \param number Number to delete.
       *
       * \return True if number was deleted, false otherwise.
       */
      bool DeleteNumber(const ParsedNumber& number);

      /**
       * \brief Checks if number is used.
       *
       * \param number Number to check.
       *
       * \return True if number is used, false otherwise.
       */
      [[nodiscard]] bool IsNumberUsed(const ParsedNumber& number) const;

     private:
      std::map<ParsedNumber, bool> used_numbers_;  //!< Map of used numbers.
    };

    /**
     * \brief Parse name from string.
     *
     * \param name Name to parse.
     *
     * \return Parsed name.
     */
    static ParsedName ParseName(const std::string& name);

    /**
     * \brief Adds subname to dictionary.
     *
     * \param subname Subname to add.
     *
     * \return True if subname was added, false otherwise.
     */
    bool AddSubname(const std::string& subname);
    /**
     * \brief Adds subname to dictionary.
     *
     * \param parsed_subname Subname to add.
     *
     * \return True if subname was added, false otherwise.
     */
    bool AddSubname(const ParsedSubname& parsed_subname);

    /**
     * \brief Deletes subname from dictionary.
     *
     * \param subname Subname to delete.
     *
     * \return True if subname was deleted, false otherwise.
     */
    bool DeleteSubname(const std::string& subname);
    /**
     * \brief Deletes subname from dictionary.
     *
     * \param parsed_subname Subname to delete.
     *
     * \return True if subname was deleted, false otherwise.
     */
    bool DeleteSubname(const ParsedSubname& parsed_subname);

    /**
     * \brief Checks if subname is used.
     *
     * \param subname Subname to check.
     *
     * \return True if subname is used, false otherwise.
     */
    [[nodiscard]] bool IsSubnameUsed(const std::string& subname) const;
    /**
     * \brief Checks if subname is used.
     *
     * \param parsed_subname Subname to check.
     *
     * \return True if subname is used, false otherwise.
     */
    [[nodiscard]] bool IsSubnameUsed(const ParsedSubname& parsed_subname) const;

   private:
    std::map<std::string, NumberDictionary>
        used_subnames_;  //!< Map of used subnames.
  };

  /**
   * \brief Adds name to dictionary.
   *
   * \param name Name to add.
   *
   * \return True if name was added, false otherwise.
   */
  bool AddName(const std::string& name);
  /**
   * \brief Adds name to dictionary.
   *
   * \param parsed_name Name to add.
   *
   * \return True if name was added, false otherwise.
   */
  bool AddName(const ParsedName& parsed_name);

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
   * \param parsed Name to delete.
   *
   * \return True if name was deleted, false otherwise.
   */
  bool DeleteName(const ParsedName& parsed);

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
   * \param parsed_name Name to check.
   *
   * \return True if name is used, false otherwise.
   */
  [[nodiscard]] bool IsNameUsed(const ParsedName& parsed_name) const;

 private:
  std::map<std::string, SubnameDictionary> used_names_;  //!< Map of used names.
};

/**
 * \brief Class to generate new names.
 *
 * \details This class is used to generate new names for objects. Also it can
 * change a lit bit a name to make it unique.
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

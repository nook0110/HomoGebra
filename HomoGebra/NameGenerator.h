#pragma once
#include <map>
#include <optional>
#include <string>

/**
 * \brief Class to generate new names.
 *
 * \details This class is used to generate new names for objects. Also it can
 * change a lit bit a name to make it unique
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
   * \brief Struct to save parsed subname.
   *
   * \see NameGenerator::ParseName
   *
   * \author nook0110
   *
   * \version 0.1
   *
   * \date April 2023
   */
  struct ParsedSubname
  {
    std::string name;              //!< Name of subname
    std::optional<size_t> number;  //!< Number of subname

    /**
     * \brief Default overload of == operator
     *
     * \param other Other subname to compare
     *
     * \return True if subnames are equal, false otherwise
     */
    bool operator==(const ParsedSubname& other) const
    {
      return name == other.name && number == other.number;
    }
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
    std::string name;       //!< Name of name
    ParsedSubname subname;  //!< Subname of name

    /**
     * \brief Default overload of == operator
     *
     * \param other Other name to compare
     *
     * \return True if names are equal, false otherwise
     */
    bool operator==(const ParsedName& other) const
    {
      return name == other.name && subname == other.subname;
    }
  };

  /**
   * \brief Struct to save names
   *
   * \details It contains a name and a map of subnames.
   * Name parses into [NAME]_[SUBNAME][NUMBER]
   *
   * \author nook0110
   *
   * \version 0.1
   *
   * \date April 2023
   */
  struct Name
  {
    /**
     * \brief Struct to save subnames
     *
     * \details Name parses into [SUBNAME][NUMBER]
     *
     * \author nook0110
     *
     * \version 0.1
     *
     * \date April 2023
     */
    struct Subname
    {
      /**
       * \brief Parse subname from string
       *
       * \param subname Subname to parse
       *
       * \return Parsed subname
       */
      static ParsedSubname ParseSubname(const std::string& subname);

      std::string name{};  //!< Name of subname

     private:
      std::map<size_t, bool> used_numbers_;  //!< Map of used numbers
    };

    /**
     * \brief Parse name from string
     *
     * \param name Name to parse
     *
     * \return Parsed name
     */
    static ParsedName ParseName(const std::string& name);

    std::string name{};  //!< Name of name

   private:
    std::map<Subname, bool> used_subnames_;  //!< Map of used subnames
  };

  /**
   * \brief Default constructor
   *
   */
  NameGenerator() = default;

  /**
   * \brief Add name to used names
   *
   * \param name Name to add
   *
   * \return Adjusted name (to avoid duplicates)
   */
  std::string AddName(const std::string& name);

  /**
   * \brief Generate new name
   *
   * \details Generate name in this pattern: Alphabet + Number (if needed)
   * For example: A, B, ..., C0, ... , H239
   *
   * \return Generated name
   */
  std::string GenerateName();

  /**
   * \brief Generate new name
   *
   * \param name Name to adjust (to avoid duplicates)
   *
   * \return Adjusted name (to avoid duplicates)
   */
  std::string GenerateName(const std::string& name);

 private:
  std::map<std::string, Name> used_names_;  //!< Map of used names
};

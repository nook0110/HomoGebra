#pragma once
#include <map>

/**
 * \brief Default dictionary.
 *
 * \details Dictionary that can store only one item.
 * Actually just a 'wrapper' around bool.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
class DefaultDictionary
{
 public:
  struct ParsedItem
  {};

  /**
   * \brief Adds item to dictionary.
   *
   * \param item Just a dummy parameter.
   *
   * \return True if item was added, false otherwise.
   */
  bool AddItem(const ParsedItem& item);

  /**
   * \brief Deletes item from dictionary.
   *
   * \param item Just a dummy parameter.
   *
   * \return True if item was deleted, false otherwise.
   */
  bool DeleteItem(const ParsedItem& item);

  /**
   * \brief Checks if item is in dictionary.
   *
   * \param item Just a dummy parameter.
   *
   * \return True if item is in, false otherwise.
   */
  [[nodiscard]] bool IsItemUsed(const ParsedItem& item) const;

 private:
  bool is_item_used_ = true;  //!< Is item used?
};

/**
 * \brief Dictionary that can store SubDictionaries.
 *
 * \details Can be used to have a complicated Name dictionary:
 * [Name] -> [Subname] -> [Number]
 *
 * \tparam Key Type of key for dictionary.
 * \tparam SubDictionary Type of sub dictionary.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 */
template <class Key, class SubDictionary = DefaultDictionary>
class Dictionary
{
 public:
  /**
   * \brief Struct to store parsed item.
   */
  struct ParsedItem
  {
    Key item{};                                     //!< Item.
    typename SubDictionary::ParsedItem sub_item{};  //!< Sub item.
  };

  /**
   * \brief Adds item to dictionary.
   *
   * \param parsed_item Parsed item.
   *
   * \return True if item was added, false otherwise.
   */
  bool AddItem(const ParsedItem& parsed_item);

  /**
   * \brief Deletes item from dictionary.
   *
   * \param parsed_item Parsed item.
   *
   * \return True if item was deleted, false otherwise.
   */
  bool DeleteItem(const ParsedItem& parsed_item);

  /**
   * \brief Checks if item is in dictionary.
   *
   * \param parsed_item Parsed item.
   *
   * \return True if item is in, false otherwise.
   */
  [[nodiscard]] bool IsItemUsed(const ParsedItem& parsed_item) const;

 private:
  std::map<Key, SubDictionary> used_items_;  //!< Used items.
};

inline bool DefaultDictionary::AddItem(const ParsedItem& item)
{
  // Check if item was used
  if (is_item_used_)
  {
    return false;
  }

  return is_item_used_ = true;
}

inline bool DefaultDictionary::DeleteItem(const ParsedItem& item)
{
  if (!is_item_used_)
  {
    return false;
  }

  is_item_used_ = false;
  return true;
}

inline bool DefaultDictionary::IsItemUsed(const ParsedItem& item) const
{
  return is_item_used_;
}

template <class Item, class SubDictionary>
bool Dictionary<Item, SubDictionary>::AddItem(const ParsedItem& parsed_item)
{
  return used_items_[parsed_item.item].AddItem(parsed_item.sub_item);
}

template <class Item, class SubDictionary>
bool Dictionary<Item, SubDictionary>::DeleteItem(const ParsedItem& parsed_item)
{
  // Check if item is used
  if (!used_items_.count(parsed_item.item))
  {
    return false;
  }

  // Delete item
  return used_items_.at(parsed_item.item).DeleteItem(parsed_item.sub_item);
}

template <class Item, class SubDictionary>
bool Dictionary<Item, SubDictionary>::IsItemUsed(
    const ParsedItem& parsed_item) const
{
  // Check if item is used
  if (!used_items_.count(parsed_item.item))
  {
    return false;
  }

  // Check if sub item is used
  return used_items_.at(parsed_item.item).IsItemUsed(parsed_item.sub_item);
}

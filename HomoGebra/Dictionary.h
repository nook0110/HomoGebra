#pragma once
#include <map>

/**
 * \brief Dictionary that can store SubDictionaries.
 *
 * \details Can be used to have a complicated Name dictionary:
 * [Name] -> [Subname] -> [Number]
 *
 * \tparam Item Type of item for dictionary.
 *
 * \author nook0110
 *
 * \version 0.2
 *
 * \date April 2023
 */
template <class Item>
class Dictionary
{
 public:
  /**
   * \brief Adds item to dictionary.
   *
   * \param item Item to add.
   *
   * \return True if item was added, false otherwise.
   */
  bool AddItem(const Item& item);

  /**
   * \brief Deletes item from dictionary.
   *
   * \param item Item to delete.
   *
   * \return True if item was deleted, false otherwise.
   */
  bool DeleteItem(const Item& item);

  /**
   * \brief Checks if item is in dictionary.
   *
   * \param item Item to check.
   *
   * \return True if item is in, false otherwise.
   */
  [[nodiscard]] bool IsItemUsed(const Item& item) const;

 private:
  std::map<Item, bool> used_items_;  //!< Used items.
};

template <class Item>
bool Dictionary<Item>::AddItem(const Item& item)
{
  return used_items_[item] = true;
}

template <class Item>
bool Dictionary<Item>::DeleteItem(const Item& item)
{
  // Check if item is used
  if (!used_items_.count(item))
  {
    return false;
  }

  // Delete item
  return used_items_.erase(item);
}

template <class Item>
bool Dictionary<Item>::IsItemUsed(const Item& item) const
{
  // Check if item is used
  if (!used_items_.count(item))
  {
    return false;
  }

  // Check if sub item is used
  return used_items_.at(item);
}

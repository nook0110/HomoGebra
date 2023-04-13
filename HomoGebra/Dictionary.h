#pragma once
#include <map>

template <class Item, class SubItem>
class Dictionary
{
 public:
  struct ParsedItem
  {
    Item item;
    SubItem sub_item;
  };

  bool AddItem(const ParsedItem& parsed_item);

  bool DeleteItem(const ParsedItem& parsed_item);

  [[nodiscard]] bool IsItemUsed(const ParsedItem& parsed_item);

 private:
  std::map<Item, SubItem> used_items_;
};

template <class Item, class SubItem>
bool Dictionary<Item, SubItem>::AddItem(const ParsedItem& parsed_item)
{
  return used_items_[parsed_item.item].AddSubname(parsed_item.sub_item);
}

template <class Item, class SubItem>
bool Dictionary<Item, SubItem>::DeleteItem(const ParsedItem& parsed_item)
{
  // Check if item is used
  if (!used_items_.count(parsed_item.item))
  {
    return false;
  }

  // Delete item
  if constexpr (std::is_member_function_pointer_v<
                    decltype(&SubItem::DeleteItem)>)
  {
    return used_items_.at(parsed_item.item).DeleteItem(parsed_item.sub_item);
  }

  return used_items_.erase(parsed_item.item);
}

template <class Item, class SubItem>
bool Dictionary<Item, SubItem>::IsItemUsed(const ParsedItem& parsed_item)
{
  // Check if item is used
  if (!used_items_.count(parsed_item.item))
  {
    return false;
  }

  // Check if sub item is used
  if constexpr (std::is_member_function_pointer_v<
                    decltype(&SubItem::IsItemUsed)>)
  {
    return used_items_.at(parsed_item.item).IsItemUsed(parsed_item.sub_item);
  }

  return true;
}

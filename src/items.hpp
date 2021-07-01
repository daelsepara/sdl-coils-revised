#ifndef __ITEMS__HPP__
#define __ITEMS__HPP__

#include <vector>

namespace Item
{
    enum class Type
    {
        NONE = -1,
        MAGIC_AMULET,
        MAGIC_WAND,
        SWORD,
        JADE_WARRIORS_SWORD,
        THROWING_KNIVES,
        HEALING_SALVE,
        CENSER_OF_FRAGRANT_INCENSE,
        JEWEL_OF_SUNSET_FIRE,
        KNIFE,
        DIAMOND,
        MAGICAL_SHIELD_BRACELET,
        IVORY_POMEGRANATE,
        ROPE,
        GRAPPLE,
        FOOD,
        SILVER_MIRROR,
        BOOK_OF_MAPS,
        First = MAGIC_AMULET,
        Last = SILVER_MIRROR
    };

    class Base
    {
    public:
        std::string Name;
        std::string Description;

        Item::Type Type = Item::Type::NONE;

        int Charge = -1;

        Base()
        {
        }

        Base(const char *name, const char *description, Item::Type type)
        {
            Name = name;
            Description = description;
            Type = type;
        }

        Base(const char *name, const char *description, Item::Type type, int charge)
        {
            Name = name;
            Description = description;
            Type = type;
            Charge = charge;
        }
    };

    // Item defaults
    auto MAGIC_AMULET = Item::Base("MAGIC AMULET", "MAGIC AMULET", Item::Type::MAGIC_AMULET);
    auto MAGIC_WAND = Item::Base("MAGIC WAND", "MAGIC WAND", Item::Type::MAGIC_WAND);
    auto SWORD = Item::Base("SWORD", "SWORD", Item::Type::SWORD);
    auto JADE_WARRIORS_SWORD = Item::Base("JADE WARRIOR's SWORD", "JADE WARRIOR's SWORD", Item::Type::JADE_WARRIORS_SWORD);
    auto THROWING_KNIVES = Item::Base("THROWING KNIVES", "THROWING KNIVES", Item::Type::THROWING_KNIVES);
    auto HEALING_SALVE = Item::Base("HEALING SALVE", "HEALING SALVE", Item::Type::HEALING_SALVE);
    auto CENSER_OF_FRAGRANT_INCENSE = Item::Base("CENSER OF FRAGRANT INCENSE", "CENSER OF FRAGRANT INCENSE", Item::Type::CENSER_OF_FRAGRANT_INCENSE);
    auto JEWEL_OF_SUNSET_FIRE = Item::Base("JEWEL OF SUNSET FIRE", "JEWEL OF SUNSET FIRE", Item::Type::JEWEL_OF_SUNSET_FIRE);
    auto KNIFE = Item::Base("KNIFE", "KNIFE", Item::Type::KNIFE);
    auto DIAMOND = Item::Base("DIAMOND", "DIAMOND", Item::Type::DIAMOND);
    auto MAGICAL_SHIELD_BRACELET = Item::Base("MAGICAL SHIELD BRACELET", "MAGICAL SHIELD BRACELET", Item::Type::MAGICAL_SHIELD_BRACELET, 6);
    auto IVORY_POMEGRANATE = Item::Base("IVORY POMEGRANATE", "IVORY POMEGRANATE", Item::Type::IVORY_POMEGRANATE, 1);
    auto ROPE = Item::Base("ROPE", "ROPE", Item::Type::ROPE);
    auto GRAPPLE = Item::Base("GRAPPLE", "GRAPPLE", Item::Type::GRAPPLE);
    auto FOOD = Item::Base("FOOD", "FOOD", Item::Type::FOOD);
    auto SILVER_MIRROR = Item::Base("SILVER MIRROR", "SILVER MIRROR", Item::Type::SILVER_MIRROR);
    auto BOOK_OF_MAPS = Item::Base("BOOK OF MAPS", "BOOK OF MAPS", Item::Type::BOOK_OF_MAPS);

    std::vector<Item::Type> UniqueItems = {Item::Type::JEWEL_OF_SUNSET_FIRE, Item::Type::JADE_WARRIORS_SWORD, Item::Type::IVORY_POMEGRANATE};

    bool IsUnique(Item::Type item)
    {
        auto unique = false;

        for (auto i = 0; i < Item::UniqueItems.size(); i++)
        {
            if (Item::UniqueItems[i] == item)
            {
                unique = true;

                break;
            }
        }

        return unique;
    }

    void REMOVE(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    items.erase(items.begin() + i);

                    break;
                }
            }
        }
    }

    void ADD(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            auto found = 0;

            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    found++;
                }
            }

            if (found == 0)
            {
                items.push_back(item);
            }
        }
        else
        {
            items.push_back(item);
        }
    }

    bool VERIFY(std::vector<Item::Base> &items, Item::Base item)
    {
        auto has = false;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    has = true;

                    break;
                }
            }
        }

        return has;
    }

    int FIND(std::vector<int> list, int item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int FIND_TYPE(std::vector<Item::Base> list, Item::Type item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int COUNT_TYPES(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = 0;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found++;
            }
        }

        return found;
    }

    int FIND_LEAST(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = -1;

        auto min = 255;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                if (list[i].Charge < min)
                {
                    found = i;

                    min = list[i].Charge;
                }
            }
        }

        return found;
    }

} // namespace Item
#endif

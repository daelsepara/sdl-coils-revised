#ifndef __STORY__HPP__
#define __STORY__HPP__

#include <vector>

#include "constants.hpp"
#include "controls.hpp"
#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"
#include "character.hpp"

namespace Choice
{
    enum class Type
    {
        NORMAL = 0, // No requirements
        ITEMS,
        GET_ITEMS,
        SKILL,
        CODEWORD,
        MONEY,
        LIFE,
        ANY_ITEM,
        ANY_SKILL,
        SKILL_ITEM,
        SKILL_ANY,
        SKILL_ALL,
        FIRE_WEAPON,
        LOSE_ITEMS,
        LOSE_MONEY,
        LOSE_ALL,
        LOSE_SKILLS,
        GET_CODEWORD,
        LOSE_CODEWORD,
        GAIN_MONEY,
        GIVE,
        BRIBE,
        TAKE,
        PAY_WITH,
        SELL,
        BARTER
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        std::vector<Codeword::Type> Codewords = std::vector<Codeword::Type>();

        int Value = 0;

        int Destination = -1;

        Base(const char *text, int destination)
        {
            Text = text;
            Destination = destination;
        }

        Base(const char *text, int destination, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL_ITEM;
            Items = items;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::ITEMS;
            Items = items;
        }

        Base(const char *text, int destination, Skill::Type skill)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Codeword::Type> codewords)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::CODEWORD;
            Codewords = codewords;
        }

        Base(const char *text, int destination, Choice::Type type, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type)
        {
            Text = text;
            Destination = destination;
            Type = type;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Skill = skill;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Codeword::Type> codewords)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Codewords = codewords;
        }
    };
} // namespace Choice

namespace Story
{
    enum class Type
    {
        NORMAL = 0,
        GOOD,
        HERO_DEATH,
        MARTYR_DEATH,
        DOOM
    };

    enum class Controls
    {
        NONE = 0,
        STANDARD,
        SHOP,
        BUY_AND_SELL,
        SELL,
        TRADE,
        BARTER,
        BARTER_AND_SHOP
    };

    class Base
    {
    public:
        int ID = 0;

        const char *Text = NULL;

        const char *Title = NULL;

        const char *Bye = NULL;

        const char *Image = NULL;

        Story::Controls Controls = Story::Controls::NONE;

        std::vector<Choice::Base> Choices = std::vector<Choice::Base>();

        std::vector<std::pair<Item::Base, int>> Shop = std::vector<std::pair<Item::Base, int>>();
        std::vector<std::pair<Item::Base, int>> Sell = std::vector<std::pair<Item::Base, int>>();

        std::pair<Item::Base, Item::Base> Trade;
        std::vector<std::pair<Item::Base, std::vector<Item::Base>>> Barter = std::vector<std::pair<Item::Base, std::vector<Item::Base>>>();

        // Player selects items to take up to a certain limit
        std::vector<Item::Base> Take = std::vector<Item::Base>();

        // Player selects items to lose
        std::vector<Item::Base> ToLose = std::vector<Item::Base>();

        int Limit = 0;

        int LimitSkills = 0;

        Story::Type Type = Story::Type::NORMAL;

        // Handle background events
        virtual int Background(Character::Base &player) { return -1; };

        // Handle events before story branches
        virtual void Event(Character::Base &player){};

        // Jump to next section
        virtual int Continue(Character::Base &player) { return -1; };

        Base()
        {
        }

        Base(int id)
        {
            ID = id;
        }

        Base(int id, const char *text, Story::Type type)
        {
            ID = id;
            Text = text;
            type = type;
        }

        Base(const char *text, Story::Type type)
        {
            Text = text;
            type = type;
        }
    };

    std::vector<Button> StandardControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exit.png", idx + 4, idx + 5, compact ? idx + 5 : 1, idx + 5, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> SellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/selling.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BuyAndSellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/selling.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> TradeControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::TRADE));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BarterControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exhange.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::BARTER));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BarterAndShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exchange.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::BARTER));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ExitControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/exit.png", compact ? idx : idx - 1, idx, compact ? idx : idx - 1, idx, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }
} // namespace Story

class NotImplemented : public Story::Base
{
public:
    NotImplemented()
    {
        ID = -1;

        Title = "Not implemented yet";

        Controls = Story::Controls::NONE;
    }
};

auto notImplemented = NotImplemented();

auto Stories = std::vector<Story::Base *>();

void *findStory(int id)
{
    Story::Base *story = &notImplemented;

    if (Stories.size() > 0)
    {
        for (auto i = 0; i < Stories.size(); i++)
        {
            if (((Story::Base *)Stories[i])->ID == id)
            {
                story = (Story::Base *)Stories[i];

                break;
            }
        }
    }

    return story;
}

class CustomShop : public Story::Base
{
public:
    CustomShop()
    {
        Title = "The Coils of Hate: Purchase Starting Possessions";

        Shop = {{Item::KNIFE, 5}, {Item::SWORD, 15}, {Item::MAGIC_AMULET, 15}, {Item::HEALING_SALVE, 20}, {Item::MAGIC_WAND, 30}};

        Choices.clear();
    }
};

class Prologue : public Story::Base
{
public:
    Prologue()
    {
        ID = 0;

        Image = "images/coils-of-hate-cover.png";

        Title = "The Coils of Hate: Prologue";

        Text = "You are down on your luck, but you will not swallow your pride and look for a job. Every day a throng of hopefuls gathers outside the rich palazzi of the riverfront. Others seek to join a trader's caravan as a guide or guard. The caravan lines are swelled by tall proud Judain slaves with their glittering black eyes, backs bent under casks of jewels, spices and silks. Those turned away from the caravans will drift at last to the seaweed-stinking waterfront to become rowers in the fleet and begin a life no better than slavery.\n\nIn your heart, you know that your destiny, the destiny of a Judain is greater than this. You knew this ever since the rabbi Caiaphas recognised the potential in you as a child and sent you to be instructed by the best the Judain could offer. He knew that you would accomplish great things. Now you are without peer among your people. One thing only you lack: a sense of purpose, a quest to show your greatness and put your skills to the test.\n\nThe city of Godorno is a stinking cess-pit. You find it hard to believe that once it was called 'The Jewel of the East'. In the past two centuries Godorno has become a byword for decadence, luxury and idle pleasure. Everywhere you look you see the insignia of the winged lion, once the proud standard of the city's legions. Now it stands as the very symbol of corruption and evil.\n\nYour people are rich, but the non-Judain of Godorno covet those riches \"Usurers, thieves,\"  they cry as your people walk the streets going about their daily business.\n\nThe Overlord stokes the fires of discontent. When those who speak out against his cruel reign disappear, never to be seen again, he blames the Judain. When people starve because he sells the harvest to the westerners for jewels, spices and silks, his minions say it is the Judain who profit from his peoples' wretchedness. Some Judain have retaliated. A group called the Sycaari has formed which inflicts acts of revenge upon the Overlord's followers. However, Caiaphas, your mentor is against this \"No good will come from meeting hatred with hatred,\" you once heard him tell you \"We must show our enemies how to live before the drag us all down into the depths of hate.\"\n\nCaiaphas has always urged the Judain to resolve things peacefully and to make connections with the non-Judain of the city, but the Overlord's insidious messages are too far reaching. Now the people hate you and all your kind. Soon it will not be safe to walk the streets.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 1; }
};

class Story001 : public Story::Base
{
public:
    Story001()
    {
        ID = 1;

        Image = "images/vr-logo.png";

        Text = "Walk the streets you must, for there is no food and nothing to be gained from idling here in the hovel you call home. You push the rotten front door open gently. There is a wet cracking noise and it splinters, coming off its hinges. You jump past into Copper Street as it falls into the street and breaks. It is beyond repair. Even before you turn the corner of the narrow mired street, a prowling thief, a sewer rat escaped from the fleet, is going into your home. You let him. You are carrying everything you own. He will find nothing but tick-ridden blankets and a leaking earthenware pot or two.\n\nAs you turn your back on the grey stone shacks of Copper Street, a youth, gangling and pasty faced, spits in your eye and calls out \"Judain scum.\" His green eyes ooze malice. The boy is beneath notice. He sneers with his nose in the air, like the rich folk of the riverfront, but his sailcloth breeches are out at the knees. His father is probably a tanner or a tinker or some such.\n\nYour time in Godorno has taught you to ignore such insults. However, the youth is not content to leave it at insults. \n\nHe pulls a tanner's knife from his pocket. It is long, sharp and menacing. There is no time to cast a spell.";

        Choices.clear();
        Choices.push_back(Choice::Base("Break the law of Godorno by unsheathing your SWORD here in the street", 129, {Item::SWORD}));
        Choices.push_back(Choice::Base("Use [UNARMED COMBAT]", 322, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("Rely on [CUNNING]", 249, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Use [CHARMS]", 504, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("You had better run", 328));

        Controls = Story::Controls::STANDARD;
    }
};

class Story002 : public Story::Base
{
public:
    std::string PreText = "";

    Story002()
    {
        ID = 2;

        Bye = "You are wounding Hate grievously, but your friends are tiring. A look of desperation appears on Talmai's face. Will you be able to slay the creature?";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your band fights valiantly against Hate, slashing its purple flesh so that huge chunks fall off. To defend itself, tentacles grow out of Hate's body which lash at you with great force.\n\n";

        auto DAMAGE = -6;

        if (Character::HAS_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = -4;

            PreText += "[SWORDPLAY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::IVORY_POMEGRANATE}))
        {
            return 268;
        }
        else
        {
            return 18;
        }
    }
};

class Story003 : public Story::Base
{
public:
    Story003()
    {
        ID = 3;

        Image = "images/vr-logo.png";

        Text = "Rulership would be a good choice here. You speak the words of the spell and point your wand at one of the soldiers. \"Get away from him!\" you hear him yell. \"The reward for this one is all mine!\" he shouts as he draws his sword. The other two also draw swords. The soldier you are controlling swings at one of the others who defends himself and soon a three way brawl erupts. The Judain slinks away, forgotten in the midst of the fighting.";

        Bye = "He heads towards you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 417; }
};

class Story004 : public Story::Base
{
public:
    Story004()
    {
        ID = 4;

        Image = "images/filler1.png";

        Text = "You approach the guards confidently. Picking the pocket of one of the guards while you hand him your gold with the other hand is child's play to someone of your accomplishments. You palm his gold to your other hand and let the coins drop one by one into his greedily outstretched palm.\n\n\"Where's my share?\" demands another of the gate guards, holding out his palm, while his other hand rests menacingly on the pommel of his rapier. You clap him on the back and empty his money pouch as you do so, also relieving him of a fine gold chain that hangs at his neck in the process. All four guards are soon happy with their own money newly shared out among them and, at last, you are allowed out of the city.\n\nYou OBTAINED 15 gleenars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 15);
    }

    int Continue(Character::Base &player) { return 552; }
};

class Story005 : public Story::Base
{
public:
    Story005()
    {
        ID = 5;

        Image = "images/filler1.png";

        Text = "As he sees who you are, the guard reaches for his horn and blows it. The three of you run through the streets. Marmeluke knows the streets well and before long, you have lost the guards. Eventually, you return to Ginath's house. Ginath puts you up for the night and feeds you. You have not delivered all of the goods, but Jared still gets paid a fair bit. He GIVES you and Marmeluke 75 gleenars each.\n\n\"Not bad for a night's work, eh, friend?\" Says Marmeluke.\n\nIn the morning, you leave Ginath's house. He is going to use the food and drink to share amongst the Judain left in the city. You both bid each other good luck. You then plan on making your escape.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 75);
    }

    int Continue(Character::Base &player) { return 42; }
};

class Story006 : public Story::Base
{
public:
    std::string PreText = "";

    Story006()
    {
        ID = 6;

        Bye = "You decide what to do next.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You pick the man up and sling him over your shoulders. It is hard going along the road and you have no idea how long it will take to get him to someone who can help.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nHowever, you come to an inn on the side of the road. You bang on the door. It is opened by a kindly looking man who waves you in immediately and goes into the kitchen. He soon emerges with a jar of herbs which he uses to attend to the man. Eventually the man wakes up.\n\nTearfully, he thanks you for saving his life and apologises for not being able to reward you in some way. However, you assure him that a good deed is its own reward.\n\nYou gained the codeword SATORI.";

            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 377; }
};

class Story007 : public Story::Base
{
public:
    Story007()
    {
        ID = 7;

        Image = "images/filler2.png";

        Text = "You hack wildly at the cloying purple flesh of Hate, opening up great gashes in its side which pour out vile yellow pus. As fast as you cut so the blob twitches, spasms and convulses, sucking the wretched guards into its soft embrace. You have to think of something else, so you try using the flat of your blade. Bashing Hate with the flat of the sword reduces the viscous purple flesh of the monster to jelly. Several of the guards are now able to pull themselves out of the body of Hate as it recoils from your punishing blows. Those still trapped implore their comrades to stay and free them, but not one of those you have rescued is prepared to risk his life for his friends.";

        Bye = "Eyes wide with terror, they bolt past you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 157; }
};

class Story008 : public Story::Base
{
public:
    Story008()
    {
        ID = 8;

        Image = "images/filler2.png";

        Text = "You hurl the POMEGRANATE with force and accuracy and it shoots straight into Hate's mouth and down its throat. The beast starts to shudder and a look of fear appears on its face.";

        Bye = "The creature knows that its days are numbered.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 410; }
};

class Story009 : public Story::Base
{
public:
    Story009()
    {
        ID = 9;

        Image = "images/filler1.png";

        Text = "Skakshi takes you by a devious route, perhaps hoping you will get lost in the foreigners' quarter, which you have been travelling through now for ten minutes.\n\n\"What do you have in mind for Melmelo?\" Skakshi is anxious to know whether you intend the Guildmaster of Thieves any harm. There is naked ambition gleaming in his eyes; he is a truly nasty piece of work.\"Wait and see,\" you tell him.\n\nAt last you stand before a white stuccoed villa with an ornamental steam bath bubbling in the garden. \"This is Melmelo's place. The soft living here has made him unfit to lead our guild. There are many who are just waiting for something to happen.\"\n\n\"Thank you, Skakshi, for guiding me here. What is the password? I don't want to be killed for calling without an invitation.\"\n\n\"Just shout, 'Enchantress' and they will let you in. If anything happens, remember it was me, honest Skakshi, who bought you here. Don't tell Melmelo though.\" With that he is gone; he blends into the shadows like a ghost.";

        Bye = "Walking up to the double doors of the villa you cry the password for all to hear.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 540; }
};

class Story010 : public Story::Base
{
public:
    Story010()
    {
        ID = 10;

        Image = "images/vr-logo.png";

        Text = "Sailing amid a froth of high flitting cloud, the moon casts a thin creamy light down to the narrow streets. You slide from shadow to shadow until you reach Mire Street, where you pause in the lee of a doorway to take stock of your target. No lamp shows in the windows. On the upper storey, one of the latticed windows overlooking the street has been left ajar. According to the etiquette of your chosen profession, this is tantamount to an effusive invitation. Detaching yourself from the darkness, you make a nimble ascent of the shop front and slither in through the open window. Tiptoeing lightly over a large slumbering guard dog lying across the landing, you quickly reconnoitre the house, discovering three of the Overlord's soldiers on watch in an upstairs room. Surveying them from behind a drape, you notice a small locked treasure-chest in an alcove at the back of the room. Without a doubt that is where the DIAMOND is kept.\n\nYou bite your lip, sizing up the situation. The three sentries are intent on a dice game, and the flickering lamplight in the room provides ample shadows for concealment, bit even so the job will not be easy. Amateur rogues often assume that speed is the important thing in a job like this. Long experience has taught you better. The key to success is to take your time. Luckily patience is your only virtue, so you have had plenty of opportunity to practise it over the years.\n\nCreeping low, pressed hard back into the dingy shadows by the wainscoting, you inch round the room. All the while the three guards go on with their game. Through your eyes remain firmly fixed on the treasure-box you listen to the hisses of breath and grunts and curses that indicate when someone has lost a throw, to the gulps of watered wine taking during respites in the game, to the rattle of ice and the slap of copper coins on the wooden tabletop. But still the guards remain oblivious to the rogue at their backs who is intent on whisking away a greater fortune in this one night that they will win or lose in their whole lives.\n\nYou reach the treasure chest at last and allow yourself a backward glance. One of the guards is now slumped dozily across the table. Another fingers the dice idly, tired of squandering his pay. The third grunts and begins to clean his fingernails with a dagger. \"How much longer are we on duty for?\" he asks.\n\n\"The next watch ought to be here in a few minutes to relieve us.\" replies the man with the dice. Now you know you must work fast. Hardly daring to breathe, you insert a bent pin into the lock and twist it with consummate precision. No surgeon ever operated so carefully upon a patient, no swain ever gave such loving entries to his paramour, no artist ever wielded a brush with such fine skill, as you work now upon that tiny lock.\n\nYour diligence is rewarded; the lock abandons its duties with a soft tut. The lid of the coffer yields to your eager touch, and you allow yourself a smile as you lift out the GEMSTONE you came for.";

        Bye = "Placing in your mouth for safekeeping the sweetest lozenge you ever saw, you skulk back noiselessly across the room and descend the stairs to emerge moments later into the night air.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 384; }
};

class Story011 : public Story::Base
{
public:
    Story011()
    {
        ID = 11;

        Image = "images/filler1.png";

        Text = "\"Look, we're no trouble. We just stayed out late. We're just heading back to our houses. Why don't we forget this ever happened?\" You say, taking the money out of your purse. The guard's eyes light up \"I'm going to patrol the docks. You've got ten minutes.\" He says as he stuffs the coins into his pocket. He then walks off down the docks.";

        Bye = "You run aboard the boat, grab as much food as you can and take it back to Ginath's house.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 270; }
};

class Story012 : public Story::Base
{
public:
    Story012()
    {
        ID = 12;

        Image = "images/vr-logo.png";

        Text = "The KNIFE is perfect for the job. You send it into the bloated gasbag of a body which is punctured. Black ichor sprays all over the room.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::HAS_SKILL(player, Skill::Type::THROWING))
        {
            return 158;
        }
        else
        {
            return 109;
        }
    }
};

class Story013 : public Story::Base
{
public:
    Story013()
    {
        ID = 13;

        Text = "The tentacles try to wrap themselves around your limbs, but almost as soon as they touch you, they withdraw quickly. However, they start to lash out at you, striking you in the face, arms and torso. The blob still advances upon you, eager to engulf you in its gelatinous purple flesh.\n\nYou LOSE 2 Life Points.";

        Bye = "You flee the blob before you become another lost soul.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }

    int Continue(Character::Base &player) { return 342; }
};

class Story014 : public Story::Base
{
public:
    Story014()
    {
        ID = 14;

        Image = "images/filler1.png";

        Text = "You slink through the alleyways, dodging shadows and waiting patiently when you hear people walk by. You don't know if these people are the Overlord's soldiers, thieves or Sycaari, but you figure that at this time at night that you don't want to meet anyone in the streets. Eventually, you get to the guard's house. Before you approach it, you stake it out. The house has been neglected the wood is rotting and the door is open ajar. You cannot see any lights. This seems easy. You make sure that the coast is clear before approaching the door.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::IVORY_POMEGRANATE}))
        {
            return 472;
        }
        else
        {
            return 235;
        }
    }
};

class Story015 : public Story::Base
{
public:
    Story015()
    {
        ID = 15;

        Text = "You scream in agony as the light seeps into your flesh. A moment later, you are horrified to feel something sprouting from your chest. Hate has awakened the evil in your own heart, forming a cancer that gnaws at you from within.\n\nYou LOSE 5 Life Points.";

        Bye = "You join the charge on Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -5);
    }

    int Continue(Character::Base &player) { return 2; }
};

class Story016 : public Story::Base
{
public:
    Story016()
    {
        ID = 16;

        Image = "images/filler1.png";

        Text = "You decide to return to safety.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::LEVAD}))
        {
            return 192;
        }
        else
        {
            return 436;
        }
    }
};

class Story017 : public Story::Base
{
public:
    std::string PreText = "";

    Story017()
    {
        ID = 17;

        Bye = "Eventually, the remaining guards flee, leaving you and the remaining citizens to recover from your ordeal.\n\nTalmai approaches you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You charge at the guards and strike one before they know what is happening. He falls down without a sound. You charge at another one who spots you and is ready for you. This will be a tough battle, but if you fight hard enough, the guards will flee, looking for easier pickings.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JADE_WARRIORS_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -3;

            PreText += "[UNARMED COMBAT] ";
        }
        else if (Character::VERIFY_ITEMS_ANY(player, {Item::SWORD}))
        {
            DAMAGE = -4;

            PreText += "[Item: SWORD] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 425; }
};

class Story018 : public Story::Base
{
public:
    std::string PreText = "";

    Story018()
    {
        ID = 18;

        Bye = "Hate is continuing to thrash and you see that the magical chains are starting to fade. Something needs to be done now.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your band battle on, but Hate, despite being wounded is not finished yet.\n\n";

        auto DAMAGE = -7;

        if (Character::HAS_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = -5;

            PreText += "[SWORDPLAY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 47;
        }
        else
        {
            return 554;
        }
    }
};

class Story019 : public Story::Base
{
public:
    Story019()
    {
        ID = 19;

        Image = "images/filler1.png";

        Text = "You return to the dank cellar with the maps. Ahab looks at them. \"You have done well. You know what, I could do with someone like you. However, you did flee the city. You need to prove your worth some more. Our resistance needs funding. A few days ago, a Judain jeweller's assistant came to see us. His employer had fired him for being Judain and the man was not able to flee the city. He approached Captain Tormil who demanded all of his possessions. I'll have that cur's head one day. Anyway, his employer on Mire Street has obtained a large DIAMOND, forcefully taken from a Judain owner he has been ordered by the Overlord to fashion it into a sceptre. If you can get the DIAMOND and fence it, we can get some money and strike a blow against the Overlord.\"";

        Bye = "Ahab gives you the address of the shop.\n\nYou set off on your mission.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 292; }
};

class Story020 : public Story::Base
{
public:
    Story020()
    {
        ID = 20;

        Image = "images/concubine.png";

        Text = "It is a difficult leap but you just make it, launching yourself high in the air from a short run up. You land beside the girl and the bodies on the bed rock as the bedsprings bounce. The Overlord twitches again but does not awaken, while the girl lies inert, her back still towards you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Step over the girl to get to the Overlord", 53));
        Choices.push_back(Choice::Base("Carry the concubine off for questioning", 44));

        Controls = Story::Controls::STANDARD;
    }
};

class Story021 : public Story::Base
{
public:
    Story021()
    {
        ID = 21;

        Text = "There is nothing for it but to rush through the gates. You wait and watch the guards, picking your moment when they lose concentration. One of them goes to the guardhouse and the others sit on the bench. Eventually, the fourth guard comes out carrying a pot of tea. The other guards take a cup and start sipping it. Now! You rush to the gate. The guards leap up, but it is too late to close the gate on you. You are through. As you run, you hear the twangs of crossbows as they fire at you. One of the bolts hits you just before you round a corner.\n\nYou LOSE 3 Life Points.";

        Bye = "You keep running, however until you are secure in the knowledge that the guards aren't following you. You hastily staunch your wound.\n\nNow it is time to save your people.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -3);
    }

    int Continue(Character::Base &player) { return 232; }
};

class Story022 : public Story::Base
{
public:
    Story022()
    {
        ID = 22;

        Image = "images/vr-logo.png";

        Text = "Of course you trust lovely little Lucie. She takes your hand and leads you into a quiet courtyard that gives out onto the upper end of Fortuny Street. You walk through an arboretum of magnolia trees and hanging baskets of weeping lilies and find yourself surrounded by the Overlord's men with crossbows pointed at your chest. Lucie smiles a wicked little smile.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Use a WAND", 260, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("You have no choice but to surrender", 26));

        Controls = Story::Controls::STANDARD;
    }
};

class Story023 : public Story::Base
{
public:
    Story023()
    {
        ID = 23;

        Text = "You steal up behind one of the Jade Warriors and throw yourself against its word arm, wrenching the BLADE from its jade grasp.\n\n\"Obey me, Jade Warriors of the Megiddo Dynasty!\" you cry on impulse.\n\nTheir only response is to swivel towards you ad advance with swords aloft. There seems to be no escape from their deadly flashing BLADEs, and you cry out in agony as your stolen sword is dashed from your grip and you are cut to the bone.\n\nYou LOSE 4 Life Points.";

        Bye = "You flee the tomb chamber.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 83; }
};

class Story024 : public Story::Base
{
public:
    Story024()
    {
        ID = 24;

        Image = "images/filler2.png";

        Text = "You draw your WEAPON and hack at the tentacles. The creature withdraws, but a tentacle lashes out and knocks your WEAPON from your hand. The blob then lurches forward, putting any thought of retrieving the weapon out of your mind.";

        Bye = "You flee the blob before you become another lost soul.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::SWORD});
    }

    int Continue(Character::Base &player) { return 342; }
};

class Story025 : public Story::Base
{
public:
    Story025()
    {
        ID = 25;

        Image = "images/vr-logo.png";

        Text = "The man is strong and fierce, but you can tell that he has never had any formal training with a SWORD. He raises his weapon to deliver a brutal swing, but you easily step backwards and avoid it. Before he can recover, you thrust forwards, wounding his arm and causing him to drop his SWORD with a yelp of pain. The other brigands cheer and jeer.";

        Bye = "You have proved yourself.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 405; }
};

class Story026 : public Story::Base
{
public:
    Story026()
    {
        ID = 26;

        Text = "Lucie's green eyes sparkle with malice. \"This is the Judain who slew your captain. This guilty wretch deserves to die.\"\n\n\"And die the poor wretch will, undoubtedly, after interrogation.\" Lucie's smile of triumph is dripping with hatred. Something must have happened to her mind, else why would she lie and betray you? She is not the same girl you met standing in the rain near the Palazzo del Megiddo. She isn't behaving as she would with the riff-raff she usually disports herself with. Hate has got to her, just as it is taking over the minds of all the wretches of Godorno. None the less, you are fated to die in the prison fortress of Grond. By tomorrow your body will be hanging in an iron cage outside the Overlord's palace. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story027 : public Story::Base
{
public:
    Story027()
    {
        ID = 27;

        Image = "images/filler2.png";

        Text = "You throw the POMEGRANATE with as much force as you can, but the creature turns its head at the last minute and it bounces harmlessly off its purple flesh. You won't be able to get it back now. \n\nWith the LOSS of the IVORY POMEGRANATE, you no longer reduce damage caused by Hate.\n\nYou have to think of another way to defeat Hate.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leap back into the fray with the JADE WARRIOR's SWORD", 125, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Use the JEWEL OF SUNSET FIRE", 218, {Item::JEWEL_OF_SUNSET_FIRE}));
        Choices.push_back(Choice::Base("Flee", 476));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        // TODO: Implement DAMAGE REDUCTION with the IVORY POMEGRANATE
        Character::LOSE_ITEMS(player, {Item::Type::IVORY_POMEGRANATE});
    }
};

class Story028 : public Story::Base
{
public:
    Story028()
    {
        ID = 28;

        Image = "images/filler1.png";

        Text = "\"I don't need a knife to kill this scumbag. Remember when I killed that guard with one punch to the nose?\" You say to Ahab before you run across the square to Acennon.\n\nYou approach him and block his path. He looks at you in confusion.\n\n\"When you wake up, get what belongings you have left and leave the city. People want you dead and they are watching us now. This is going to hurt you, but it's not going to kill you. I'm sorry.\"\n\nYou then deliver a brutal blow to the face, enough to knock him out, but you know you didn't strike him hard enough or precisely enough to kill him.\n\nAs he crumples to the ground, you see Ahab run over to the shop to loot it. A minute later, he runs out, holding silver objects and a box.\n\n\"Good work. Let's get out of here.\"\n\nYou both run back to the cellar in Medallion Street where Ahab enthusiastically tells the others about your kill. You are given food, water and a share of the loot.\n\nYou OBTAINED 100 gleenars and the codeword SKANK.";

        Bye = "You decide that it's time to leave the city.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 100);

        Character::GET_CODEWORDS(player, {Codeword::Type::SKANK});
    }

    int Continue(Character::Base &player) { return 42; }
};

class Story029 : public Story::Base
{
public:
    Story029()
    {
        ID = 29;

        Image = "images/filler3.png";

        Text = "You arrive back at the jeweller's house later that night and stand surveying it in the moonlight. Your overwhelming impression is that this has all the hallmarks of a trap. The Overlord would hardly leave a priceless DIAMOND unguarded and he must be aware that his security measures, while enough to deter the casual thieves of the town, are simply an enticement to the pride of any true professional. So without a doubt there will be soldiers stationed in the house.\n\nClimbing up to the first floor, you prise open a window and tiptoe along the landing, listening at each door in turn. Sure enough, from behind one of the doors comes the rattle of gaming dice and the unmistakable banter of bored soldiers. You pause. This is where the DIAMOND must be kept. Continuing along the landing to the next door, you hear the sound of thundering snores. The jeweller's bedroom. Quietly inching the door open, you go to a cupboard and extract a nightshirt and cap, which you put on over your clothes. Then, darting swiftly along the landing, you fling open the first door and cry: \"Thief! There's a thief downstairs!\" The three soldiers leap up in amazement and grab their weapons, rushing past you along the landing with excited shouts. They are so intent on catching the thief and thereby earning a bonus that they don't even glance at your face.\n\nYou tear off the nightshirt and look around the room. A small locked chest catches your eye. Surely that is where the DIAMOND is. The lock looks pretty secure, but you can break it at your leisure once you are safely away from here. Only when you have put a safe distance between you and Mire Street do you pause to inspect the DIAMOND.";

        Bye = "You leave at once with the chest.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 384; }
};

class Story030 : public Story::Base
{
public:
    Story030()
    {
        ID = 30;

        Image = "images/filler1.png";

        Text = "You cast a simple spell of Befuddlement on the guard who leaves his post and wanders off down the street. With the guard dealt with, you head back to the boat.";

        Bye = "You finish your delivery.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 270; }
};

class Story031 : public Story::Base
{
public:
    Story031()
    {
        ID = 31;

        Image = "images/vr-logo.png";

        Text = "Your steady run keeps you out of their clutches but they are on horses which will not tire so easily.  They do not seem like giving up. You run on desperately, hoping to find somewhere to evade them.";

        Choices.clear();
        Choices.push_back(Choice::Base("Change your mind about fleeing and offer to throw your lot in with them", 123));
        Choices.push_back(Choice::Base("Keep running", 338));

        Controls = Story::Controls::STANDARD;
    }
};

class Story032 : public Story::Base
{
public:
    Story032()
    {
        ID = 32;

        Image = "images/silver-eel-tavern.png";

        Text = "The spell of Visceral Pang should suffice to bring the landlord to his knees and force him to do your bidding. You mouth the arcane words and twirl your fingers in the patterns that bring magic to life. The spell catches and the landlord's face grows pale, then very flushed. He makes a rush for the latrines but the pain pulls him up short and he doubles over in agony.\n\n\"You will serve a Judain, my good man, and be quick about it,\" you say, looking around to gauge the reaction of the other drinkers.\n\nThe two women are looking at you in a new light. The pipe smoker is tapping out his pipe. Lucie looks shocked. The eyes of the tall stranger transfix you with a piercing stare. The gang of four are all fingering hidden weapons and checking their escape routes.\n\n\"A pot of your finest ale, barkeep,\" you say, letting the spell go. The landlord straightens up slowly, holding his stomach and reaches for an ale pot.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask the landlord about business", 466));
        Choices.push_back(Choice::Base("Ask the landlord about Lucie and the stranger", 267));

        Controls = Story::Controls::STANDARD;
    }
};

class Story033 : public Story::Base
{
public:
    std::string PreText = "";

    Story033()
    {
        ID = 33;

        Image = "images/lepers.png";

        Bye = "The woman turns to you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "\"I can find a place for them.\" she whispers, nodding in the direction of the lepers \"Follow me.\" You follow her and the lepers shuffle after you. Eventually, she comes to a warehouse that has had its doors kicked in. You go inside to find a dozen people sitting on crates, discussing the state of the city. You notice people from all strata of society. There is a Judain jeweller, a labourer, a scholar and even a member of the Overlord's guard sharing the same room in peace. They look alarmed to see you, but relax once the woman talks to them.\n\n\"This one was leading some lepers to safety. Since we have more food here than we know what to do with, I'm sure no one minds them sheltering here.\" There is a murmur of agreement from the group. As the lepers file in, the woman directs them to a crate of ship's biscuits which the grateful lepers fall upon with fervour.";

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

            PreText += "\n\nYou gained the codeword SATORI.";
        }
        else
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 279; }
};

class Story034 : public Story::Base
{
public:
    Story034()
    {
        ID = 34;

        Image = "images/filler1.png";

        Text = "You also know that there are certain streets that Judain should never go and not just because of the Overlord's men. You come to a street where you can hear drunken singing and shouting and decide to take a detour as you realise that the revellers here would turn violent at the sight of a Judain.";

        Bye = "Eventually, you make it to the ruins of the Synagogue.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 175; }
};

class Story035 : public Story::Base
{
public:
    Story035()
    {
        ID = 35;

        Image = "images/vr-logo.png";

        Text = "Your own opinion is that the myth of the return of Harakadnezzar is only a story invented to deter would-be grave robbers from rifling in the more recently consecrated tombs. The story of Hate, however, is well known to all folklorists. Hate rises up in the foundations of ancient and decadent cities, swallowing the proud, wicked and greedy into its ravening maw. This manifestation of the force of Hate was last heard of in the Old Empire city of Kush, a thousand years ago. There is nothing left of Kush now. The greatest and most powerful city the world has ever seen has become a giant dustbowl in the grasslands.";

        Bye = "You thank the landlord and leave him to join Lucie and the stranger.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 132; }
};

class Story036 : public Story::Base
{
public:
    Story036()
    {
        ID = 36;

        Image = "images/vr-logo.png";

        Text = "You fling your KNIFE at the nearest guard. It strikes him in the shoulder. He yells in pain and drops his SWORD. One of the other guards spots you. \"Judain scum! Come here and take your punishment!\" You dash off down the street with the guards in pursuit. They cannot keep up with you in their heavy armour and you soon lose them.";

        Bye = "Doubling back, you meet up with Ruth and escort her back to her house.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::KNIFE});
    }

    int Continue(Character::Base &player) { return 411; }
};

class Story037 : public Story::Base
{
public:
    Story037()
    {
        ID = 37;

        Text = "Your mighty struggles are in vain. You are not ready for this untimely death.\n\nMemories of the times you have felt Hate smoulder in your breast come unbidden in your mind and the strength seems to drain out of your muscles. The warm embrace of Hate welcomes you and your body is slowly and inexorably drawn inch by inch into the seething mass of the monster. Soon your head too is being drawn in. Your arms and legs have gone numb and you start to fight for breath as your nostrils and lips are sealed over by the soft purple flesh of Hate. You drown in the body of Hate. Your tormented half-life has begun.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story038 : public Story::Base
{
public:
    Story038()
    {
        ID = 38;

        Image = "images/filler1.png";

        Text = "You walk out into the street \"Down with the Overlord!\" You shout as you wave your arms and make hand gestures at the guards. They immediately stop tormenting the Judain and stare at you, their eyes brimming with hatred. Then they run at you. You are going to have to be quick to outrun them.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 264;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 298;
        }
        else
        {
            return 442;
        }
    }
};

class Story039 : public Story::Base
{
public:
    Story039()
    {
        ID = 39;

        Image = "images/vr-logo.png";

        Text = "The Overlord's men aren't expecting you, so no one notices when your first KNIFE embeds itself into the back of one of the guards. He collapses to the ground with a scream. The guards turn around to face you. Some run at you, but Talmai picks up one of the dead guards' SWORDs and rushes at her opponents, striking one in the back. Attacked on both sides, the remaining guards flee the scene rather than fight.";

        Bye = "Talmai approaches you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 425; }
};

class Story040 : public Story::Base
{
public:
    Story040()
    {
        ID = 40;

        Image = "images/filler2.png";

        Text = "The IVORY POMEGRANATE is one of the most holy artefacts in the Judain religion. Hate will find its touch poison. If you can get the POMEGRANATE inside Hate's mouth, it might be enough to finish the creature off.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::HAS_SKILL(player, Skill::Type::THROWING))
        {
            return 8;
        }
        else
        {
            return 313;
        }
    }
};

class Story041 : public Story::Base
{
public:
    Story041()
    {
        ID = 41;

        Image = "images/vr-logo.png";

        Text = "The inner ring has a large hall where all the prisoners eat, whilst being watched by guards. Its design is called the Panopticon and it allows the prisoners to be watched from all places. In the centre of the hall is a giant blob of purple flesh and tentacles, pulsating slowly, as if it is resting. A score of guards can be seen partly submerged in the flesh. Upon seeing you, they give low moans of despair. This has been the work of but a single night for Hate, and what is worse, is that the blobs seem to be getting bigger.\n\nMost of the men have only been sucked in as far as both elbows, or knees, but they are all exhausted by their fruitless struggle to break free. Unable any longer to resist the pull of Hate they are being submerged in the purple morass inch by inch.\n\nMost of the men are wailing out repentance for the atrocities they have committed on the poor prisoners of Grond.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to set them free", 177));
        Choices.push_back(Choice::Base("Leave them to their harsh but deserved fate and go on to free the Judain", 376));

        Controls = Story::Controls::STANDARD;
    }
};

class Story042 : public Story::Base
{
public:
    Story042()
    {
        ID = 42;

        Image = "images/filler1.png";

        Text = "It is time for you to leave the city. Godorno has become too dangerous for you now. However, you are near the shop of your friend Tarkamandir. Tarkamandir is a sage who is able to get hold of many useful items. You have known him for a long time and he has always made sure that you have access to his finest goods. You could stay a little longer and visit him, or you could try to escape straight away.";

        Choices.clear();
        Choices.push_back(Choice::Base("Visit Tarkamandir", 453));
        Choices.push_back(Choice::Base("Try to leave via the main gate", 344));
        Choices.push_back(Choice::Base("Stow away on a barge", 522));

        Controls = Story::Controls::STANDARD;
    }
};

class Story043 : public Story::Base
{
public:
    Story043()
    {
        ID = 43;

        Image = "images/skakshi.png";

        Text = "You speak the word of power that evokes the potent spell of Visceral Pang. Skakshi is seized by a palsy and he collapses to the sawdust covered floor, writhing and frothing at the mouth.\n\n\"You, Skakshi, will take me to meet with your guildmaster, Melmelo. I have a proposition to put to him for his ears only.\"\n\n\"I'll do anything, Judain. Anything! Just release me from this wracking spell.\"\n\nYou take pity on the miserable wretch and banish the spell with a thought. Skakshi rises slowly to his feet and says he will take you to Melmelo's stronghold, claiming that only he knows the password.";

        Bye = "Skakshi fears that you are going to kill him.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 214; }
};

class Story044 : public Story::Base
{
public:
    Story044()
    {
        ID = 44;

        Image = "images/concubine.png";

        Text = "You gather the girl in your arms. She is as light as a feather pillow and quite limp. Her face is untouched by the blemishes which mar her body and she is quite beautiful, as you would expect of the Overlord's concubine. You then think about how to get both her and yourself across the carpet without stepping on it. You wrap her in the silk bedspread and decide to drag her from the bed after leaping clear.\n\nYou jump to safety, holding one corner of the bedspread, then tug it hard so that the girl slips from the bed and is dragged across the carpet. As soon as the swaddled form touches the filigreed carpet, the wires spring forth to entangle themselves in the counterpane. Try as you might, you cannot drag her any further.\n\nA large black form, like a manta ray or a vampire's cloak, detaches itself from the underside of the canopy of the Overlord's bed and drifts down through the air towards your head.\n\nYou still have time to make a run for it if you want to leave the girl.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave the girl", 519));
        Choices.push_back(Choice::Base("Go back onto the carpet to cut the concubine free", 70));

        Controls = Story::Controls::STANDARD;
    }
};

class Story045 : public Story::Base
{
public:
    Story045()
    {
        ID = 45;

        Image = "images/filler2.png";

        Text = "Huge chunks of purple flesh are strewn about the plaza. You start to advance to finish Hate off, but before you do, you head a voice in your head. It is Lucie's.\n\n\"Please stop. You are hurting me!\" You hear her melodious voice say. An image flashes in your mind. She is trapped in Hate, suffering because of the pain you brought upon the beast.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stop", 164));
        Choices.push_back(Choice::Base("Destroy Hate, whatever the cost", 509));

        Controls = Story::Controls::STANDARD;
    }
};

class Story046 : public Story::Base
{
public:
    Story046()
    {
        ID = 46;

        Image = "images/vr-logo.png";

        Text = "Your senses have been honed razor-keen by your many escapades on the hazy edge of the law. When a thief treads lightly on the steps leading down to your cellar hideout, you are instantly awake and on your feet. A figure stands in its shadows. Seeing that you are awake, the intruder turns and bolts away. You chase him up the street, but he is already out of sight. Your only impression was of a small build and very quick reflexes. You must be on the look-out for such a person.";

        Bye = "You go back to your lair and spend the rest of the night undisturbed.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 502; }
};

class Story047 : public Story::Base
{
public:
    Story047()
    {
        ID = 47;

        Image = "images/filler2.png";

        Text = "Hate turns its head and roars at you. You smell the fetid breath of the creature as it squirms towards you, eager to absorb you into its being.";

        Choices.clear();
        Choices.push_back(Choice::Base("Step into Hate's maw", 528));
        Choices.push_back(Choice::Base("Hesitate", 554));

        Controls = Story::Controls::STANDARD;
    }
};

class Story048 : public Story::Base
{
public:
    Story048()
    {
        ID = 48;

        Image = "images/filler2.png";

        Text = "You did not obtain the JEWEL OF SUNSET FIRE, but you have the JADE WARRIOR's SWORD. You wrack your brains, trying to think of anything else that could be used to fight Hate, but you cannot. You only hope that the SWORD will be enough.";

        Bye = "You decide that it is time to face Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 283; }
};

class Story049 : public Story::Base
{
public:
    Story049()
    {
        ID = 49;

        Text = "You may have the barricade and you may have the advantage of numbers, but the Overlord's men are still trained soldiers. The first sign of attack is a cry of pain from one of the archers on a nearby roof. Then you see all your archers fall. The Overlord's men must have broken in through the backs of the houses or climbed on the roofs.\n\nThen you see why a dozen black clad guards are now on the floors pointing crossbows at your group. From where they are, hitting the defenders is like shooting fish in a barrel. The first volley fells six Judain. The survivors attempt to throw their missiles at the Overlord's men, but they are out of range. Then come the squad of guards, charging down the street at the barricade, wielding axes and swords. Some have grappling hooks. Another volley of crossbow bolts rains down on the defenders and some of them flee in panic, but their escape is blocked by a squad of guards that snuck around the barrier. They are quickly put to the sword. The ones that stay fight bravely, but they are no match for the heavily armed and armoured soldiers.\n\nThe next day, Ahab will admit that he made a mistake, but it will do little good for your corpse as it rots in the streets of Godorno.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story050 : public Story::Base
{
public:
    std::string PreText = "";

    Story050()
    {
        ID = 50;

        Bye = "You head towards Greenbark Plaza.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You greet the men's attack. Your SWORD will help, but you may not know how to use it.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JADE_WARRIORS_SWORD}))
        {
            DAMAGE = 0;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -1;

            PreText += "[UNARMED COMBAT] ";
        }

        if (DAMAGE < 0)
        {
            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";
        }
        else
        {
            PreText += "You wield your SWORD well and you do not lose any Life Points.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nEventually, badly cut and beaten, the two men flee, the youth dropping his KNIFE.";
        }

        Take = {Item::KNIFE};

        Limit = 1;

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 415; }
};

class Story051 : public Story::Base
{
public:
    Story051()
    {
        ID = 51;

        Text = "Astounded, you stagger back. You have destroyed Hate, a creature that would have destroyed your city. You sit down on the floor and rest. Then you hear a sound a murmuring from the catacombs: a sound that grows and swells from a hum to a roar. The lost souls are free once more and they climb into the streets to hail you as their saviour. You are a hero and you will be feted for a hundred days. Now is the time for the banquet at the Overlord's palace. Together you will rebuild Godorno and make it once more the jewel of the east. With your help, Judain and non-Judain will put aside all hostilities and learn to live and work together for the benefit of everyone. Eventually, you will rebuild the synagogue that you used to spend your youth and you will become a prominent and well respected citizen to both Judain and non-Judain. Caiaphas would have been proud of you.";

        Type = Story::Type::GOOD;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story052 : public Story::Base
{
public:
    Story052()
    {
        ID = 52;

        Image = "images/filler1.png";

        Text = "You run out of the shop and don't stop running until you are far away from it. What will you do now? Ahab is going to be angry about your failure and might suggest a severe punishment. Despite you two growing up together, he always seemed a bit distant and if he set his mind on a goal, he would try to accomplish it at all costs, not caring about what it did to those around him. You are sure that in his head, a failure is equal to a traitor. On the other hand, he is still the best one to provide you with shelter and protection. If you struck out on your own, you would have to survive in the ruins of houses, dodging both the militia and the Sycaari.";

        Choices.clear();
        Choices.push_back(Choice::Base("Return to Ahab", 220));
        Choices.push_back(Choice::Base("Decide to go it alone", 173));

        Controls = Story::Controls::STANDARD;
    }
};

class Story053 : public Story::Base
{
public:
    Story053()
    {
        ID = 53;

        Text = "As you step over to the Overlord, you hear a faint whispering sound and a black shape settles heavily over you. Its skin sports rows of barbed spines that inject poison into your bloodstream. Try as you might, you can't break free. The poison turns your blood to cloying syrup and your heart stops beating. You have died when revenge for the Judain was almost within your grasp. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story054 : public Story::Base
{
public:
    Story054()
    {
        ID = 54;

        Image = "images/vr-logo.png";

        Text = "You leap between the Judain and the guards \"Have mercy on these poor dogs,\" you say \"Do not fall to the depths of their depravity. Is it not the fate they have reserved for you? Are we not nobler than they? Let us show them our superiority by sparing them, that their very existence may be a testament to our nobility.\"\n\nHowever, a large Judain carrying a poker and bearing all kinds of scars and wounds walks up to you and towers over you, his green eyes staring into yours. \"I suffered under these scumbags for weeks. Don't tell me to leave them alone, not until you have suffered as I have. Now get out of my way before I pummel you too.\"\n\nThe whole prison stares at you, watching what you do next.";

        Choices.clear();
        Choices.push_back(Choice::Base("Fight this large Judain to save the guards", 378));
        Choices.push_back(Choice::Base("Step aside and let the Judain avenge themselves", 404));

        Controls = Story::Controls::STANDARD;
    }
};

class Story055 : public Story::Base
{
public:
    Story055()
    {
        ID = 55;

        Image = "images/filler1.png";

        Text = "You sneak through the streets until you eventually come to the non-descript cottage that Yadid lives in. You approach the door to find it hanging off its hinges. Cautiously, you enter. The furniture is broken and strewn all over the place. There is no sign of your friend. It seems that someone, or something got to him first. You have a quick search of his house.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 207;
        }
        else
        {
            return 295;
        }
    }
};

class Story056 : public Story::Base
{
public:
    Story056()
    {
        ID = 56;

        Image = "images/diamond.png";

        Text = "The SWORD leaves your hand like an arrow and buries itself into the bloated gasbag of a body, which is instantly ruptured. Black ichor sprays all over the room and the spider goes limp.\n\nThe JADE WARROR's SWORD is now out of reach.\n\nYou OBTAINED the JEWEL OF SUNSET FIRE.";

        Bye = "You then leave through the door.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::JADE_WARRIORS_SWORD});

        Character::GET_ITEMS(player, {Item::JEWEL_OF_SUNSET_FIRE});
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story057 : public Story::Base
{
public:
    Story057()
    {
        ID = 57;

        Image = "images/vr-logo.png";

        Text = "As you approach the hut, the door is flung open to reveal an old woman dressed in a simple green tunic. She has a kindly expression on her face \"So lovely to see you. Do come in for some tea.\" You enter the hut to find it filled with plants of all kinds. The woman puts a kettle over a fireplace to make the tea. Soon, you are drinking a rich herbal liquid as you chat. It turns out that the old woman is a healer. She is very concerned to hear about the persecution of the Judain and offers her sympathy for your plight. Then her face lights up \"Could you help me, young one? There is a herb that grows a few miles towards the great forest. You would get it a lot faster than I could and I could make you a concoction to help you out.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree to help her", 513));
        Choices.push_back(Choice::Base("Refuse and head towards the Great Forest", 501));

        Controls = Story::Controls::STANDARD;
    }
};

class Story058 : public Story::Base
{
public:
    Story058()
    {
        ID = 58;

        Image = "images/filler2.png";

        Text = "The IVORY POMEGRANATE is one of the most holy artefacts in the Judain religion. Hate will find its touch poison. You decide that if you can get the POMEGRANATE inside Hate then it might destroy it. Hate roars at you. It is your perfect opportunity.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::HAS_SKILL(player, Skill::Type::THROWING))
        {
            return 81;
        }
        else
        {
            return 357;
        }
    }
};

class Story059 : public Story::Base
{
public:
    Story059()
    {
        ID = 59;

        Image = "images/filler1.png";

        Text = "You have failed to obtain either the JEWEL OF SUNSET FIRE or a JADE WARRIOR's SWORD. You wrack your brains, trying to think of some other way to defeat Hate, but you have no other idea on what to do. All you can think to do is flee Godorno before it is destroyed.";

        Bye = "You head for the gates.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 61; }
};

class Story060 : public Story::Base
{
public:
    Story060()
    {
        ID = 60;

        Image = "images/diamond.png";

        Text = "Konstantin, is a very slippery character. He has a series of hideouts across the city almost impossible to find unless you know how to look for the discreet signs that he leaves around the place. The nearest one to you is a room that you can only access through the sewers. You approach the storm drain that you both used to access it. After checking that no one is around, you lift it up and then stop. There is something scratched into the wall, unnoticeable to anyone who doesn't understand its meaning, but it makes you stop dead. Two lines are scratched in the shape of a cross, indicating that the hideout has been compromised. Then the smell hits you. Instead of the smell of sewage, you smell camphor and honeysuckle. Then you realise what has happened. Hate has claimed the sewers for itself. You then head to another hideout. You eventually find Konstantin in the cellar of a fallen down hovel in the foreigner's quarter. He looks pleased to see you.\n\n\"It is good to see you my friend. You have caught me preparing to elope this city as there is too much danger here now. Even if I weren't Judain, I would fear that my days are numbered.\"\n\n\"It's Hate, isn't it?\"\n\n\"If that's what you call the huge purple creatures that are assaulting our homes and our people, then yes. Those purple blobs are infesting every corner of Godorno. Even the sewers aren't safe any more. If I were you, I would leave as quickly as you can.\"\n\n\"I can't. I have to save my people.\"\n\n\"I thought you would say that. Caiaphas chose his pupils well, didn't he? Well, at least let me help you.\" Konstantin pulls out a large DIAMOND, the size of a walnut from his pocket and hands it to you \n\n\"This should set you up nicely for when you do escape the city. Sell it and live comfortably for many years.\" You open your mouth to protest, but Konstantin raises his hand to stop you \"This is a mere trinket compared to what I've managed to amass over the years. I won't even notice it's gone.\"\n\nKonstantin also offers you a ROPE and GRAPPLE which you may take.";

        Bye = "Konstantin leaves the cellar in preparation to quit the city. You decide to head back to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::DIAMOND});

        Take = {Item::ROPE, Item::GRAPPLE};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 339; }
};

class Story061 : public Story::Base
{
public:
    Story061()
    {
        ID = 61;

        Image = "images/filler1.png";

        Text = "The city and all of its inhabitants are a lost cause. If they don't join the orgy of despair in Hate, they will be corpses soon. If everyone is so determined to spend their last days slaughtering each other for pointless causes, then so be it. You will start a new life elsewhere.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::MAZEL}))
        {
            return 311;
        }
        else
        {
            return 113;
        }
    }
};

class Story062 : public Story::Base
{
public:
    Story062()
    {
        ID = 62;

        Image = "images/silver-eel-tavern.png";

        Text = "\"Look, I just want to have a little chat with Melmelo. He won't even know it was you who told me.\" You say as you put the coins on the table.\n\n\"Fine, you go and talk to him then. He lives in a villa in the Foreigners' Quarter. It has an ornamental steam bath in the garden.\"\n\nYou gained the codeword LARCENY.";

        Choices.clear();
        Choices.push_back(Choice::Base("Order a drink from a bar", 306));
        Choices.push_back(Choice::Base("Join Lucie and the stranger", 132));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::LARCENY});
    }
};

class Story063 : public Story::Base
{
public:
    Story063()
    {
        ID = 63;

        Image = "images/filler1.png";

        Text = "Though your instinct is to trust Lucie who seems open and without guile, you know it makes no sense to agree to a meeting with a stranger, particularly in a city like Godorno where your people are the victims of genocide. You demand to be told who it is who can help you in your struggle to save your people.\n\n\"He made me promise to keep his identity secret, until you meet. He said he could help you only if you are able to trust. So many good people have fallen into the clutches of the coils of Hate. Trust me.\"\n\n\"Is he Judain?\"\n\n\"No, not Judain. Come we are almost there.\"\n\n\"No, I will not place myself in danger. I would be a fool to do so.\"\n\n\"Don't you trust me?\" Lucie looks shocked and hurt. \"I've been doing my best to help you and now you won't trust me.\"\n\n\"Lucie...\" You reach out and touch her, but she spits at you and runs off.";

        Bye = "Bewildered at her strange behaviour, you return to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 351; }
};

class Story064 : public Story::Base
{
public:
    Story064()
    {
        ID = 64;

        Image = "images/filler1.png";

        Text = "Now that you know that the Overlord's reach extends beyond Godorno, you have a restless night. Your mind races with possibilities, plans and questions. Should you stay here and hope the situation dies down? Should you head further north, or hide out in the Great Forest? Should you return to Godorno to help your people?\n\nEventually, the sun shines in through your bedroom window and you get up and prepare for the day. You have a breakfast of eggs and bread and then leave the inn.\n\nYour first port of call is a very interesting shop that stocks all kinds of useful goods. You enter it and begin to search through the myriad items to see if there is anything that you might find useful.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 248;
        }
        else
        {
            return 301;
        }
    }
};

class Story065 : public Story::Base
{
public:
    Story065()
    {
        ID = 65;

        Image = "images/filler1.png";

        Text = "The only way you know of contacting Melmelo is by asking a thief. The only place you can be sure to find a thief when you want one is The Inner Temple, an inn in the middle of the oldest part of the city. The Oldest part of the city is an ever nighted labyrinth crawling with cutthroats and footpads. You decide to err on the side of caution and smuggle yourself in. You head to the mews of Slave Market Plaza and find an unattended slaver's cart. You get under it and cling to the axles of the cart and wait for it to move. The cart eventually starts to move along the cobbles. You have a bumpy ride for an hour until you let yourself fall, unnoticed to the cobbles as it turns a corner. Next you pick your way through a maze of old alleyways, built soon after this part of the city was razed to the ground in the Great Fire of a few years ago.";

        Bye = "You are soon looking at the doors of the Inn of the Inner Temple.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 303; }
};

class Story066 : public Story::Base
{
public:
    Story066()
    {
        ID = 66;

        Text = "The guard's face is as purple as Hate as he exerts a great effort and you are dragged into the translucent flesh of the monster. You have joined the orgy of despair and the poor guard who dragged you in cannot escape. He is exhausted. You must lie together, like eggs in a basket, as Hate goes on devouring lost souls. There is no one left to save the Judain now. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story067 : public Story::Base
{
public:
    Story067()
    {
        ID = 67;

        Image = "images/filler1.png";

        Text = "Without thinking, you run across the bar room, leap over the bar and dash out of the back door. You emerge into a narrow alley way, where you cast a spell of invisibility on yourself, thankful to the sorcerer who created it for making the casting time as short and as simple as possible. You then flee the area. As you do, you hear the angry shouts of the Overlord's men as they storm out into the alleyway and run off in different directions. However, you make sure that you are standing out of their way as they run past you. With the danger passed, you breathe a sigh of relief. Godorno is far too dangerous for you to stay here. You're going to have to leave.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave via the main gate to the trade route", 344));
        Choices.push_back(Choice::Base("Stow away on a barge", 522));
        Choices.push_back(Choice::Base("Risk visiting one of your friends before you leave", 467));

        Controls = Story::Controls::STANDARD;
    }
};

class Story068 : public Story::Base
{
public:
    Story068()
    {
        ID = 68;

        Image = "images/vr-logo.png";

        Text = "You carry on up the road until you come to a fork.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head north to Bagoe", 496));
        Choices.push_back(Choice::Base("Head west to Burg and the Great Forest", 358));

        Controls = Story::Controls::STANDARD;
    }
};

class Story069 : public Story::Base
{
public:
    Story069()
    {
        ID = 69;

        Image = "images/vr-logo.png";

        Text = "You PAID 100 gleenars.\n\nAhab explodes at this paltry sum.\n\n\"A fool could get a better price for such a gem! I know what you've been up to, you thief. Well, I'll teach you to steal from the Sycaari!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [CUNNING] to get out of this situation", 133, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Use [STREETWISE]", 133, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("You do not have those skills or you do not wish to use them", 191));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -100);
    }
};

class Story070 : public Story::Base
{
public:
    Story070()
    {
        ID = 70;

        Text = "As soon as you step onto the carpet the gold and silver filigree threads seem to bunch and tighten beneath the balls of your feet. Before you can try to set yourself free, the black shape settles heavily over your head. Its skin sports rows of barbed spines that inject poison into your bloodstream. Try as you might, you can't break free. The poison turns your blood to cloying syrup. You collapse onto the carpet, which garrottes you whilst the poison stops your heart. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story071 : public Story::Base
{
public:
    std::string PreText = "";

    Story071()
    {
        ID = 71;

        Bye = "You recover your KNIVES. You then help the man.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You throw your second KNIFE. This one strikes another guard in the neck. He falls into the street, red blood gushing out of his wound and mixing with the brown muck covering the cobbles. The third guard is now upon you. You will have to fight him in close quarters.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JADE_WARRIORS_SWORD}))
        {
            DAMAGE = 0;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -1;

            PreText += "[UNARMED COMBAT] ";
        }

        if (DAMAGE < 0)
        {
            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";
        }
        else
        {
            PreText += "You do not lose any Life Points.";
        }

        if (player.Life > 0)
        {
            Character::GET_ITEMS(player, {Item::KNIFE, Item::KNIFE});
        }

        Take = {Item::SWORD};

        Limit = 1;

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 417; }
};

class Story072 : public Story::Base
{
public:
    Story072()
    {
        ID = 72;

        Image = "images/jade-warriors.png";

        Text = "One of the swords has a halo which shines brighter than the others. You steal up behind the Jade Warrior and throw yourself against its sword arm, wrenching the blade from its grasp.\n\nYou OBTAINED a JADE WARRIOR's SWORD.\n\n\"Obey me, Jade Warriors,\" you cry out on impulse. To your relief and amazement they line up before you and stand to attention. The warrior from whom you took the sword picks up another from behind an awning. The warriors are ready to do your bidding.\n\nYou know that the Jade Warriors cannot go far from the jade ring that the emperor wore, so you search the chamber until you find it. You can lead them anywhere. You decide against taking them above ground as the entire army of the Overlord would descend on you. Even with these mighty guardians, you would not prevail. However, they can still be useful to you under the city.\n\nYou lead them through the sewers until you come across a large circular room that looks like a junction of several tunnels. Purple slime lines the wall and floor, indicating that the blobs of Hate regularly pass this way. You drop the ring on the floor and leave the Jade Warriors to their duty. You then head back to the burial chamber.\n\nYou gained the codeword HECATOMB.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JADE_WARRIORS_SWORD});

        Character::GET_CODEWORDS(player, {Codeword::Type::HECATOMB});
    }

    int Continue(Character::Base &player) { return 354; }
};

class Story073 : public Story::Base
{
public:
    Story073()
    {
        ID = 73;

        Image = "images/vr-logo.png";

        Text = "On your travels, you come across a small hillock which raises your suspicions. There's something wrong with it, but you can't quite put your finger on it. Then it hits you it has a very unnatural shape. You have seen something like this before. Ancient structures become overgrown forming strange landmarks in the terrain. After some digging, you find an opening into the structure.\n\nYou enter it to find the remains of Judain shrine. Marble arches stand in it covered in moss and mud. This holy place has not been visited for many a year. However, as you stand in it, you feel a sense of peace and serenity wash over you. Then you feel something roll against your foot. You look down to see a beautiful IVORY POMEGRANATE inscribed with Judain prayers. Such an item would have adorned a high priest's sceptre. When you pick it up, you feel a tingle of power. This object contains divine essence.\n\nYou may use the IVORY POMEGRANATE once to restore all lost Life Points (this does not destroy it, however). The POMEGRANATE may have other uses.";

        Bye = "Eventually, you leave the shrine.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::IVORY_POMEGRANATE});
    }

    int Continue(Character::Base &player) { return 142; }
};

class Story074 : public Story::Base
{
public:
    Story074()
    {
        ID = 74;

        Image = "images/filler1.png";

        Text = "You sneak through the streets until you come to Tagil's house in the Old Quarter. You can tell where he lives as he has put the armour and helmets of several of the Overlord's men outside his house. None dare challenge him now. When you knock on the door. After a while, your start to hear the noise of several bolts being pulled back. The door opens to reveal Tagil. Despite being in his mid-fifties, he still sports a muscular frame and from the stories you have heard, he has lost none of his skill with age. He greets you and ushers you inside hastily. Once in the house, he serves you the last food he has half a stale loaf and some cheese. He eats the other half. As you eat you talk.\n\n\"It's lucky you came to see me today, young one. I'm leaving today.\"\n\n\"Why? You can handle yourself against the Overlord's men.\"\n\nTagil spits on the floor.\n\n\"Those amateurs? I could last against them for an eternity. It's just that they're not the worst thing in this city any more. I've seen huge purple blobs, trapping people like flies in syrup. I can't fight this thing. If you have any sense, you would leave to. Come with me.\"\n\n\"I have to stay and save my people.\" You reply.\n\n\"I won't argue. You've always been stubborn. I'll help you if you stay. I have been thinking of how to destroy this huge creature. You would need a weapon of magic and power. Then I remembered the Jade Warriors. These artificial creatures protect the Megiddo dynasty and carry swords sharper than any steel sword could be. I remember the legend that one of the swords was able to control these creatures.\"\n\nTagil tells you the legend of the Jade Warriors and how to control them. Tagil also offers you a SWORD and a KNIFE. You may take one or both of these.\n\nYou gained the codeword JADE.";

        Bye = "You bid your mentor a fond farewell and decide to head back to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::JADE});

        Take = {Item::SWORD, Item::KNIFE};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 339; }
};

class Story075 : public Story::Base
{
public:
    Story075()
    {
        ID = 75;

        Image = "images/vr-logo.png";

        Text = "You ponder the landlord's words. Harakadnezzar created a mighty empire, but at the cost of tens of thousands of lives. The man slaughtered countless people in his quest for power before being assassinated by one of his closest advisors. If he has returned, then he could make the whole city suffer. Hate could also level the city. You have heard that in places of great decadence, Hate will be given form and grow into a huge unstoppable monster that will destroy everything in its path. This was the fate of the city of Kush. If Hate is growing under Godorno, then the whole city might be destroyed. Either of these creatures would be a grave threat to the city. How could you overcome them, you think? Lost in your thoughts, you reach for your mug of ale.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 324;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 373;
        }
        else
        {
            return 116;
        }
    }
};

//TODO: Make sure choices leading up to this section will deduct the amount of money or food you wish to give
class Story076 : public Story::Base
{
public:
    Story076()
    {
        ID = 76;

        Image = "images/vr-logo.png";

        Text = "\"Thank you. I don't have anything to my name, but you have given me some hope. Good luck. I hope to see you again.\"\n\nAnd with that, the man carries on up the road.";

        Bye = "You continue to Godorno.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 269; }
};

class Story077 : public Story::Base
{
public:
    std::string PreText = "";

    Story077()
    {
        ID = 77;

        Image = "images/filler2.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack this mass of Hate", 452));
        Choices.push_back(Choice::Base("Flee", 275));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You watch as Tormil is dragged towards the blob. At first he screams for help. As he starts to be absorbed by the blob, he breaks down in tears. Sobbing, he begs you to free him from the deathly mass, but you do nothing but watch as he is drawn to his doom. Eventually, he is submerged beneath the purple slime, his anguished face still visible beneath the surface of the slime. Terror draws bile into your throat and you cannot help giving a small cry of horror. Averting your face, you leave the grisly scene behind. You are ashamed to think that you let anyone be condemned to such a fate, even a cur like Tormil.";

        if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::VENEFIX});

            PreText += "\n\nYou gained the codeword VENEFIX.";
        }
        else
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }

        PreText += "\n\nNow what will you do?";

        Text = PreText.c_str();
    }
};

class Story078 : public Story::Base
{
public:
    Story078()
    {
        ID = 78;

        Text = "As soon as the tentacle wraps around you, you feel a debilitating pain inside you and you feel your whole body go numb. There is nothing you can do to stop Hate dragging you towards its massive purple body where it will absorb yours. Soon you will join thousands others in an orgy of despair where you will languish in agony for eternity.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story079 : public Story::Base
{
public:
    Story079()
    {
        ID = 79;

        Image = "images/filler1.png";

        Text = "You go back to your shelter for the night.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::LEVAD}))
        {
            return 547;
        }
        else
        {
            return 147;
        }
    }
};

class Story080 : public Story::Base
{
public:
    Story080()
    {
        ID = 80;

        Image = "images/filler3.png";

        Text = "The warehouse door has a padlock on it, but it is easily smashed open. Inside you grab as many weapons as you can carry and head back to the building. You risk making another two runs before Talmai decides that you have enough weapons. You look at the pile of weapons in the middle of the floor there are many swords, axes, knives, bows, arrows, crossbows, bolts and maces. You will definitely be well equipped for the battle.\n\nYou gained the codeword ARMED.";

        Bye = "You return to Bumble Row to get some sleep with what little time you have left.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::MAZEL);

        Character::GET_CODEWORDS(player, {Codeword::Type::ARMED});

        Take = {Item::SWORD};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 178; }
};

class Story081 : public Story::Base
{
public:
    Story081()
    {
        ID = 81;

        Image = "images/filler2.png";

        Text = "You hurl the POMEGRANATE with force and accuracy and it shoots straight into Hate's mouth and down its throat. The beast starts to shudder and a look of fear appears on its face.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HECATOMB}))
        {
            return 410;
        }
        else
        {
            return 550;
        }
    }
};

class Story082 : public Story::Base
{
public:
    Story082()
    {
        ID = 82;

        Image = "images/filler1.png";

        Text = "Caiaphas looks disappointed. \"You have your reasons. Good luck.\"\n\nYou decide to leave immediately.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head to the main gate in order to leave by the trade route", 344));
        Choices.push_back(Choice::Base("Stow away on a barge", 522));

        Controls = Story::Controls::STANDARD;
    }
};

class Story083 : public Story::Base
{
public:
    Story083()
    {
        ID = 83;

        Image = "images/filler1.png";

        Text = "You flee out of the tomb and blunder through the tunnels and sewers until you find a ladder leading up to a manhole cover. You climb the ladder and emerge in a wide, empty street. You have escaped the Megiddo catacombs alive, but you have not obtained a weapon with which to combat Hate.\n\nYou gained the codeword THRUST.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::THRUST});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::TOWER}))
        {
            return 59;
        }
        else if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::JEWEL}))
        {
            return 355;
        }
        else
        {
            return 170;
        }
    }
};

class Story084 : public Story::Base
{
public:
    std::string PreText = "";

    Story084()
    {
        ID = 84;

        Image = "images/filler2.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Visit Ahab", 420));
        Choices.push_back(Choice::Base("Visit Ruth", 246));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The parts of your body that were touching the purple slime itch. You climb out of the cellar and run to a barrel of rainwater in the street. You submerge your arm in it, pull it out and inspect it.\n\nThe skin that the slime touched is red and irritated.\n\n";

        if (Character::VERIFY_ITEMS(player, {Item::Type::IVORY_POMEGRANATE}))
        {
            PreText += "[Item: IVORY POMEGRANATE] You do not lose any Life Points.";
        }
        else
        {
            Character::GAIN_LIFE(player, -1);

            PreText += "You do not LOSE 1 Life Point.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nYou think about what has befallen the city persecution, plague and now this slime. You decide that you cannot survive alone and decide to contact with some friends in the city. You could look for your friend Ahab, member of the Sycaari or you visit Ruth, Caiaphas's widow, in order to offer your condolences and any help that she might want. She is with Caiaphas's child and these times must be very hard for her.";
        }

        Text = PreText.c_str();
    }
};

class Story085 : public Story::Base
{
public:
    Story085()
    {
        ID = 85;

        Image = "images/filler2.png";

        Text = "As the tentacles wrap around your wrists, you feel the POMEGRANATE vibrate in your pocket. Almost immediately, they loosen their grip and the worm stops it advance. Not wishing to push your luck, you flee the square. As you do, you hear a squelching noise behind you and then you feel something warm, viscous and foul-smelling splash onto your back. However, as it does, the POMEGRANATE vibrates again and you feel the slime evaporate.";

        Bye = "You are glad to be alive.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 108; }
};

class Story086 : public Story::Base
{
public:
    Story086()
    {
        ID = 86;

        Image = "images/vr-logo.png";

        Text = "As you approach the corpse, you hear a loud grunt and squeal. A huge boar bursts out from copse and charges at you. You have disturbed it and it sees you as a threat.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::THROWING))
        {
            return 353;
        }
        else
        {
            return 139;
        }
    }
};

class Story087 : public Story::Base
{
public:
    std::string PreText = "";

    Story087()
    {
        ID = 87;

        Bye = "You flee for your life.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You have to flee. The nearest Jade Warrior slashes at you as you do, inflicting a deep cut with its extremely sharp SWORD.\n\nYou LOSE 6 Life Points.";

        Character::GAIN_LIFE(player, -6);

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 83; }
};

class Story088 : public Story::Base
{
public:
    std::string PreText = "";

    Story088()
    {
        ID = 88;

        Bye = "You tell the innkeeper of the attack, who summons the watch to dispose of the body. You move to another room.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "It seems that you are not safe even out of Godorno. With the speed of someone who has grown up in such a dangerous city, you leap out of bed and hurl yourself at the man in a desperate fight for your life. He is taken aback by such ferocity, but raises his SWORD.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JADE_WARRIORS_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -2;

            PreText += "[UNARMED COMBAT] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nYou search the man, but he has nothing but his SWORD.";
        }

        Take = {Item::SWORD};

        Limit = 1;

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 64; }
};

class Story089 : public Story::Base
{
public:
    Story089()
    {
        ID = 89;

        Image = "images/filler3.png";

        Text = "When you get to Tarkamandir's shop, you find him standing outside with a cart laden with goods. He is locking the door.\n\n\"Shutting up for good?\" You ask.\n\nTarkamandir tells you that he has decided to quit the city. \"Matters have gone too far,\" he says \"each day I fear the guards will come and drag me off to Grond.\"\n\n\"Why should you fear?\" you say with a trace of bitterness \"You are not Judain.\"\n\nHe gives a snort of ironic laughter. \"Do you think that what has been going on has been a simple matter of persecution? It goes deeper than that. The Overlord started his attacks on your people to distract attention from his disastrous policies, reasoning that once the populace had a scapegoat to blame they would be easier to control.\"\n\n\"That strategy has worked well, then.\"\n\n\"Now it is out of control! Hate is rife in the city. It extends its influence like a cancer. Today it is you Judain who are marched off to the prison. Tomorrow it may be the aged, or the infirm, or those who dare to speak out against the Overlord. That is why I am leaving.\" He takes a few more steps, the wheels of his cart sloshing through the rut of mire in the middle of the street, then pauses to look back.\n\n\"As long as I am going, I suppose I ought to sell you some of my stock. Interested?\"\n\nTarkamandir has the following items: a MAGICAL SHIELD BRACELET which you may use once when you LOSE LIFE. If you use it, it can reduce the damage you take by up to 6. It then becomes useless. Other items on sale are: a JAR OF HEALING SALVE that can be used once to restore 1 Life Point, MAGIC WAND, a BLOCK OF FRAGRANT INCENSE used for religious and magical rituals, a SILVER MIRROR, MAGIC AMULET, SWORD, and a set of THROWING KNIVES.";

        Bye = "You bid Tarkamandir farewell and tell him that you hope it will not be the last you see of him. Then you decide your next move.";

        Choices.clear();
        Choices.push_back(Choice::Base("Return to Ahab", 220));
        Choices.push_back(Choice::Base("Turn your back on the Sycaari and decide to survive on your own", 173));

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        // Implement MAGICAL SHIELD BRACELET
        Shop = {{Item::MAGICAL_SHIELD_BRACELET, 100}, {Item::HEALING_SALVE, 15}, {Item::MAGIC_WAND, 30}, {Item::CENSER_OF_FRAGRANT_INCENSE, 20}, {Item::SILVER_MIRROR, 20}, {Item::MAGIC_AMULET, 15}, {Item::SWORD, 15}, {Item::THROWING_KNIVES, 10}};
    }
};

class Story090 : public Story::Base
{
public:
    Story090()
    {
        ID = 90;

        Image = "images/lucie.png";

        Text = "You find Lucie loitering around the moored gondolas on Circle Canal. In better days she might have had rich pickings from dipping her hand into the purses of the wealthy. In these troubled times, few people dare venture into the streets with money in their pockets.\n\nYou explain that you want to get into Grond and free the prisoners there.\n\n\"Help free those vermin?\" she says \"Why would I want to? Many are murderers, rapists and madmen!\"\n\n\"Many are brave men and women whose only crime was to speak out against the Overlord. Others are even more blameless. My fellow Judain, for instance, declared criminal simply because of race and creed.\"\n\nLucie seems not even to have heard you. \"Those beasts in Grond they are animals! Let Hate take them!\" She looks at you as though you have lost your wits, her pretty face contorted with hatred. The glint in her green eyes is frightening. She looks mad.\n\nYou tell her off for her outburst. Lucie smirks coquettishly as you tell her off and says \"Well, it's true. Hate take them all and good riddance to bad rubbish.\"\n\nYou sigh, knowing you will never change her. You suspect that at least one of the criminal inmates of Grond must have done something dreadful to her before his imprisonment.\n\n\"Surely there must be something you can do?\" You ask \"Don't you know any of the guards?\"\n\n\"I suppose I do, one or two. There's Captain Khmer in the east tower. He oversees the towngate and the eastern courtyard. I could smuggle you in there.\"\n\nYou agree to this plan and follow Lucie to Grond. While she goes in search of Captain Khmer, you wait in the bakery adjacent to the prison. It is a long wait, but at least there is fresh bread to eat and the bakers and scullions will not give you away. They seem to be firm friends with Lucie. You have plenty of time to wonder how she binds people to her. These peasants are taking a terrible risk sheltering you under their roof.\n\nAt last Lucie comes back. She looks troubled but says \"I've arranged things for you. Walk up to the towngate in five minutes\" time. They will open up and let you through. They won't harm you, but from then on you are on your own. I think something has gone terribly wrong in there. It wasn't easy to arrange. Don't waste my efforts in failure, Judain. I'm going to the Silver Eel. Come to me there and tell me how you fared.\" With that and a little squeeze of the shoulder, she is gone.";

        Bye = "You approach the towngate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 153; }
};

class Story091 : public Story::Base
{
public:
    std::string PreText = "";

    Story091()
    {
        ID = 91;

        Bye = "You join the charge on Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "As you are bathed in the green light, you feel extremely hot and feel something crawl about inside you. The experience is painful, but it only lasts a moment before dying down. Hate has tried to find corruption in your heart and awaken it, but there is nothing there to find. However, you are still in pain.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYour acts of goodness will provide some protection against Hate. In your combat with Hate, whenever you are told to lose Life Points, that number is reduced by 1 and you lose that number of Life Points instead.";

            // TODO: Implement this DAMAGE reduction
            Character::GET_CODEWORDS(player, {Codeword::Type::GOODNESS});
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 2; }
};

class Story092 : public Story::Base
{
public:
    Story092()
    {
        ID = 92;

        Image = "images/filler2.png";

        Text = "Your knowledge of fighting has taught you how to slip out of holds.\n\nYou manage to work your way out of the tentacles and flee before they can ensnare you again.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 408; }
};

class Story093 : public Story::Base
{
public:
    Story093()
    {
        ID = 93;

        Image = "images/vr-logo.png";

        Text = "The cloud of dust is coming closer and when it is no more than a quarter of a mile away you begin to make out the figures of several horsemen. They are moving at a fast trot, faster than merchants or most other travellers. They could be brigands.";

        Choices.clear();
        Choices.push_back(Choice::Base("Flee, hoping to elude them until nightfall", 31));
        Choices.push_back(Choice::Base("Stand your ground, greet them and offer to throw in your lot with them", 123));
        Choices.push_back(Choice::Base("[SPELLS] Cast a powerful spell to try to stop the bandits and escape them. However, there are many of them and it might not work", 305, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story094 : public Story::Base
{
public:
    Story094()
    {
        ID = 94;

        Text = "You sprint for it, little caring that you will crush the poor snakes you tread on. They writhe underfoot and hiss balefully. You manage to make it across the room, but one of the snakes sinks its fangs into your ankle just as you step up on the block. You strangle it, but the poison is already working its way through your veins and it produces an agonizing burning sensation.\n\nYou LOSE 4 Life Points.";

        Bye = "When the pain subsides, you open the door.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 99; }
};

class Story095 : public Story::Base
{
public:
    Story095()
    {
        ID = 95;

        Image = "images/filler2.png";

        Text = "You think about how you will be able to defeat Hate. Then you remember the JEWEL OF SUNSET FIRE, held in the Tower of the Sentinel, surrounded by traps and monsters. The JEWEL apparently has great power to combat evil, but you have heard tales of many talented thieves trying to steal the JEWEL and never coming back alive. If you think getting the JEWEL is a lost cause, then you have no other ideas besides fleeing the city before it is destroyed.";

        Choices.clear();
        Choices.push_back(Choice::Base("Brave the Tower of the Sentinel", 387));
        Choices.push_back(Choice::Base("Flee the city", 61));

        Controls = Story::Controls::STANDARD;
    }
};

class Story096 : public Story::Base
{
public:
    Story096()
    {
        ID = 96;

        Image = "images/lepers.png";

        Text = "You pole to the shore, disembark from your gondola and announce that you will take the lepers to safety. This motley crew would follow you anywhere. They shuffle along in your wake, calling out feebly for food and medicine, though there is no magic or medicine that can restore these disfigured unfortunates to health. You are not bothered by city guardsmen, nor thieves and cut-throats while surrounded by your crowd of lepers. The sweet putrefying smell that seeps from their bandages is an antidote to the stench of death that pervades the city. As you think about where you can take this motley band, you notice a woman gesture at you from an alleyway. She wears leather armour and fixes you with an intense stare.";

        Choices.clear();
        Choices.push_back(Choice::Base("Approach the woman", 33));
        Choices.push_back(Choice::Base("Ignore her and carry on", 461));

        Controls = Story::Controls::STANDARD;
    }
};

class Story097 : public Story::Base
{
public:
    Story097()
    {
        ID = 97;

        Image = "images/vr-logo.png";

        Text = "The bandits eventually catch up with you, where they surround you with their horses. Grinning, they dismount and, at sword point, strip you of all of your POSSESSIONS, leaving you with nothing before riding off back to their camp. There is much mirth at your plight.\n\nIt is obvious that these men will forget about you as soon as you are out of sight, just another victim on the road. At least they haven't harmed you.";

        Bye = "In low spirits, you continue westwards to the Great Forest.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ALL(player);
    }

    int Continue(Character::Base &player) { return 501; }
};

class Story098 : public Story::Base
{
public:
    Story098()
    {
        ID = 98;

        Image = "images/skakshi.png";

        Text = "Skakshi is holding his THROWING KNIFE, but you know you are quicker than him. You grab a KNIFE from your belt and fling it at him, just as he throws his. There is a pause and then a clang as the TWO KNIVES collide in mid-air. Before anyone else can react, you have already run across the room and grabbed him by the scruff of the neck.\n\n\"Listen, worm. That knife didn't kill you because I didn't want it to kill you.\"\n\n\"What do you want from me?\" squeals the thief.\n\n\"Take me to Melmelo, the Guildmaster. I have something to say to him that is for his ears only.\"\n\n\"I can do that just let me tend to this wound!\"\n\nYou let go of the thief, letting him crumple to the floor. Two of his friends rush to his side, carefully remove the KNIFE and bandage his wound. You pick the KNIFE up, clean it and replace it in your belt.";

        Bye = "When Skakshi has recovered, he tells you to follow him.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 214; }
};

class Story099 : public Story::Base
{
public:
    Story099()
    {
        ID = 99;

        Image = "images/giant-spider.png";

        Text = "You climb some more stairs until you come to another door. Various cabbalistic signs like ancient cave paintings have been daubed on the outside of the topmost door in terracotta and charcoal. If your hopes are not disappointed, the JEWEL OF SUNSET FIRE lies inside this topmost room.\n\nAt the top of the staircase is a series of frescoes showing the tower and depicting the grisly fates that befall those who try to climb it. To your absolute horror, the final fresco is a picture of you, squashed flat beneath a gigantic bloated black spider. Above the spider you can see the orb shining brightly in its frame.\n\nYou walk on up a narrower spiral of stairs and at last pause before the final door. Gingerly you push it open, wincing at the creak of its rusty hinges. There is a brooding presence of evil here.";

        Bye = "Your heart hammers in your chest as you step forward.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 505; }
};

class Story100 : public Story::Base
{
public:
    Story100()
    {
        ID = 100;

        Image = "images/filler2.png";

        Text = "Most of the citizens flee, but Talmai and her band stand firm. They draw their weapons and charge at the beast. In response, Hate's eyes glow green and each of you is bathed in green light. You feel your skin go prickly and your body get hotter as it is assaulted by Hate's magic.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::IVORY_POMEGRANATE}))
        {
            return 434;
        }
        else
        {
            return 189;
        }
    }
};

class Story101 : public Story::Base
{
public:
    Story101()
    {
        ID = 101;

        Text = "Not confident with your weapon, you keep your distance and try to parry his first blow. Tyutchev's sword lashes out, smashing your parry aside. The blade cuts into your breast, just above the heart.\n\nYou LOSE 6 Life Points.";

        Bye = "Tyutchev gets ready to deliver the coup de gras.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -6);
    }

    int Continue(Character::Base &player) { return 427; }
};

class Story102 : public Story::Base
{
public:
    Story102()
    {
        ID = 102;

        Image = "images/vr-logo.png";

        Text = "The door leads to more stairs up, which you climb. Eventually, you come to another door which you open onto an oval room. There is no door here, but one of the walls is covered with a tapestry and the other has a single arrow slit. You look through the arrow slit and see Godorno beneath you. So far from the streets, you could imagine it as a peaceful city. Then you approach the tapestry and look at it. The pictures on it depict the twelve labours of Coronus. As you look at it, the floor spins and you are shot backward through the tapestry into another room.\n\nYou are standing on a stone block, about three feet off the floor. There is another stone block about six feet away, near a door. There is nothing to show how you came through the wall behind you and no way of return. The floor of the room is submerged under a living carpet of orange and black garter snakes. It is too far to jump to the nearest platform above the snakes, but there is a wooden beam between the walls above you. If you had something to tie to it, you could swing across the room.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a ROPE and a GRAPPLE to grapple the beam and swing across the room over the snakes", 118, {Item::ROPE, Item::GRAPPLE}));
        Choices.push_back(Choice::Base("[CHARMS] Use an AMULET", 308, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Silver Shield to push the snakes aside", 454, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Dash for it through the mass of snakes", 94));

        Controls = Story::Controls::STANDARD;
    }
};

class Story103 : public Story::Base
{
public:
    Story103()
    {
        ID = 103;

        Image = "images/jade-warriors.png";

        Text = "You quickly ignite the INCENSE, and smoke billows forth from the CENSER. The Jade Warriors are swoon swathed in the roiling white clouds, and you grope your way through the smoke towards them. One of the warriors looms towards you, the light gleaming dully off its facets and its sword is working mechanically. You recoil in fright but it lumbers past making elaborate passes in the air, as if engaged in a display of ancient style of swordplay. The others are also lurching about at random. The smoke seems to have scrambled their senses. Each is cutting and thrusting at the air around it, but they seem oblivious to you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::JADE}))
        {
            return 72;
        }
        else
        {
            return 345;
        }
    }
};

class Story104 : public Story::Base
{
public:
    Story104()
    {
        ID = 104;

        Image = "images/filler1.png";

        Text = "With all the thieves and soldiers in this area, you decide to flee for your own survival.\n\nYou sneak through the alleys, avoiding anyone who walks by until you get back to your hovel in Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 179; }
};

class Story105 : public Story::Base
{
public:
    Story105()
    {
        ID = 105;

        Image = "images/filler2.png";

        Text = "Almost as soon as the tentacle wraps around you, you feel it unwind from you. For some reason, Hate can't stand the touch of you. Not wishing to push your luck, you run as fast as you can from the worm. As you do, you feel some warm viscous slime strike you in the back. It smells disgusting, but it doesn't feel like it does any harm, so you run on without checking for injury.";

        Bye = "You are glad to be alive.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 108; }
};

class Story106 : public Story::Base
{
public:
    Story106()
    {
        ID = 106;

        Image = "images/diamond.png";

        Text = "Seeking out some of your unsavoury underworld contacts, you manage to get an offer for the DIAMOND. However, compared to what it is worth, it is a paltry sum. The fence also knows that he is offering a very low price \"You're lucky I deal with you at all these days. You know the trouble I could get into for talking to a Judain?\"\n\n\"Not as much trouble as if that Judain told the Overlord's men about you handling the Overlord's own DIAMOND.\" you say with an ingenious smile.\n\nHe curses under his breath, but finally agrees to pay you 500 gleenars for the DIAMOND.";

        Choices.clear();
        Choices.push_back(Choice::Base("Sell the DIAMOND for 500 gleenars", -106, Choice::Type::SELL, {Item::DIAMOND}, 500));
        Choices.push_back(Choice::Base("Refuse the offer for the DIAMOND", -106));

        Controls = Story::Controls::STANDARD;
    }
};

class Event106 : public Story::Base
{
public:
    Event106()
    {
        ID = -106;

        Title = "The Coils of Hate (Revised): 106";

        Image = "images/diamond.png";

        Text = "On the way back to the others, you realise that you are near the shop of Tarkamandir, sage and friend. He always has a stock of useful items that will help you in your quest.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();
        Choices.push_back(Choice::Base("Visit Tarkamandir", 89));
        Choices.push_back(Choice::Base("Return to Ahab", 220));

        if (!Character::VERIFY_ITEMS(player, {Item::Type::DIAMOND}) && player.Money >= 500)
        {
            Choices.push_back(Choice::Base("Keep the money for yourself and go it alone, betraying the Sycaari", 173));
        }
        else
        {
            Choices.push_back(Choice::Base("Go it alone, betraying the Sycaari", 173));
        }
    }
};

class Story107 : public Story::Base
{
public:
    Story107()
    {
        ID = 107;

        Image = "images/mob.png";

        Text = "\"I am one of the Overlord's paid informers,\" you shout with a commanding air. \"Follow me, I will take you to the nests of the Judain scum. Follow me.\" You turn your back and set out towards the fruit market. \"Come, I will show you where three Judain spies and embezzlers are hiding out.\"\n\nThe mob follows eagerly, crying for Judain blood. One of them asks how they are to know you are the Overlord's informer. You start to run, calling \"Hurry, or we may be too late. If word reaches them before us they will flee the roost.\"\n\nYou run fast and the others can hardly keep up. Entering the fruit market you dive into a throng of people who are picking over a mound of rotting fruit that has been piled up at the side of the road. As you make your escape into a narrow side street, you hear the crowd calling for your blood. It is not safe to remain in the city at the moment.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave by the usual means, the main gate to the trade road", 344));
        Choices.push_back(Choice::Base("Stow away on a barge", 522));
        Choices.push_back(Choice::Base("Risk staying in the city and visiting one of your friends before you leave", 467));

        Controls = Story::Controls::STANDARD;
    }
};

class Story108 : public Story::Base
{
public:
    Story108()
    {
        ID = 108;

        Image = "images/filler2.png";

        Text = "You have escaped the giant worm that Hate has become, but you are seriously worried now. Is there anything or anyone in Godorno that has the power to stand up to such a creature? It may not be the only one of its kind, either, as you know from rumours that smaller blobs of Hate stalk the city. You are more despondent than ever about saving yourself, let alone the Judain or Godorno, but you decide that you must fight on regardless and do what you can.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 122;
        }
        else
        {
            return 16;
        }
    }
};

class Story109 : public Story::Base
{
public:
    Story109()
    {
        ID = 109;

        Image = "images/giant-spider.png";

        Text = "However, your blow is not enough to kill the spider. Despite being wounded, it still writhes around in anger, eager to sink its teeth into you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use another KNIFE", 533, {Item::KNIFE}));
        Choices.push_back(Choice::Base("[SPELLS] Use a WAND", 149, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Throw the JADE WARRIOR's SWORD at the giant spider", 56, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Dash beneath the spider to steal the JEWEL", 399));
        Choices.push_back(Choice::Base("Dash for the door", 130));

        Controls = Story::Controls::STANDARD;
    }
};

class Story110 : public Story::Base
{
public:
    Story110()
    {
        ID = 110;

        Image = "images/filler1.png";

        Text = "First you need to find a light source. Picking through a pile of debris, you find some suitably shaped bits of wood for torches. You then find some rags to tie around them and a piece of flint to make a spark. When you have a torch, you look for a way into the sewers. You find a loose storm drain nearby and you lift the grate, light a torch and head into the damp tunnels.\n\nYou walk down this tunnel with the waste water lapping at your feet. The smell of human excrement gets worse as you continue further down the tunnel. After ten minutes of tortuous walking, you come to a fork. Exploring these sewers is going to be a long and arduous process.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_MAPS}))
        {
            return 510;
        }
        else
        {
            return 159;
        }
    }
};

class Story111 : public Story::Base
{
public:
    Story111()
    {
        ID = 111;

        Image = "images/skakshi.png";

        Text = "You recognise some of those present as senior members of the Thieves' Guild, grown rich on the juicy pickings of the latterday well-to-do of Godorno. They are well dressed, urbane looking men. One of them is called Skakshi, a man who likes to think of himself of the master thief of Godorno, despite being nowhere near Melmelo's level of skill and reputation.\n\n\"Skakshi, I see you lurking there. I have a proposition to put to Melmelo just the thing for Godorno's master thief.\" Skakshi scowls. He is no friend of Melmelo the Guildmaster.\n\n\"I can take you to Melmelo for the price I would be given if I turned you over to the city guard: ten gleenars. Do you have ten gleenars, Judain scum?\"\n\nThere are chuckles from the other customers at Skaksi's insolence.";

        Choices.clear();
        Choices.push_back(Choice::Base("Teach him a lesson in how to talk to his betters", 535));
        Choices.push_back(Choice::Base("Agree to this bargain: pay 10 gleenars", 9, Choice::Type::LOSE_MONEY, 10));
        Choices.push_back(Choice::Base("Tell Skakshi you will never pay his blood money", 363));

        Controls = Story::Controls::STANDARD;
    }
};

class Story112 : public Story::Base
{
public:
    Story112()
    {
        ID = 112;

        Image = "images/concubine.png";

        Text = "You step gingerly onto the carpet and the gold and silver filigree threads seem to bunch and tighten beneath the balls of your feet. The Overlord stops breathing for a moment and you copy him. Then he rolls over and the stertorous noise starts again. In his sleep his hand caresses the girl's flank, but she doesn't wake. You take another step and struggle to make another, but the wires have snared around your ankle. The slender metal thread is cutting your ankle like a cheesewire. Cursing, you bend to free yourself. It should be easy enough to get free before the wire cuts through your leg. Then a sixth sense tells you to look up at the canopy of the bed. It does not fail you. Above you, what looks like a black blanket floats eerily down from beneath the canopy to engulf you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 317;
        }
        else if (Character::VERIFY_ITEMS_ANY(player, {Item::SWORD, Item::JADE_WARRIORS_SWORD}))
        {
            return 412;
        }
        else
        {
            return 186;
        }
    }
};

class Story113 : public Story::Base
{
public:
    Story113()
    {
        ID = 113;

        Image = "images/town-crier.png";

        Text = "As you head towards the gate, you pass a town crier, surrounded by a group of ragged people\n\n\"Hear this, hear this! Tomorrow, the Overlord will address the people as his victory in the war to purify Godorno comes ever closer. Very soon, he will remove all Judain from the city, except slaves. This is also true of practitioners of black magic, scholars of perverse lore, worshippers of forbidden gods, those who have spoken out against the Overlord and lazy workers. Tomorrow in Greenbark Plaza, we can all share the Overlord's victory.\"\n\nThis speech makes your blood boil, but then you think. Would it be possible to stop the Overlord if he is exposed? Maybe you should stay and see the speech.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay for the speech", 414));
        Choices.push_back(Choice::Base("Leave the city", 238));

        Controls = Story::Controls::STANDARD;
    }
};

class Story114 : public Story::Base
{
public:
    Story114()
    {
        ID = 114;

        Image = "images/filler1.png";

        Text = "\"Help! Some Judain are escaping the city!\", you shout. \"They've killed a guard!\". The Overlord's men stop their attack and run off down the street. If there's one thing they hate more than law breakers, it's Judain.";

        Bye = "Talmai approaches you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 425; }
};

class Story115 : public Story::Base
{
public:
    Story115()
    {
        ID = 115;

        Image = "images/vr-logo.png";

        Text = "As you walk away from the cellar, you think about your task. Grond is full of captured Judain and other political prisoners detained to await the mercy of the Overlord's torturers. The prison is extremely well guarded and secure. You cannot succeed at such an ambitious mission alone, and Ahab is unwilling to put any more Sycaari at further risk. That is why he's sent you, who he does not see as entirely loyal to the cause. You are going to need the help of an expert rogue.\n\nOn the other hand, you wonder if you should do this at all. Ahab sees you as expendable. He is simply sending you on missions that he does not want to risk his cronies with. And after seeing his level of gratitude after you stole the diamond for him, you doubt you will get any thanks from him. He is also completely ignoring the monsters that are stalking the street, which may be a bigger threat to the Judain's survival than the Overlord. Maybe it would be better to strike out alone.";

        Choices.clear();
        Choices.push_back(Choice::Base("Accept your mission and try to free the Judain from Grond", 532));
        Choices.push_back(Choice::Base("Sever your ties with the Sycaari and Ahab", 138));

        Controls = Story::Controls::STANDARD;
    }
};

class Story116 : public Story::Base
{
public:
    std::string PreText = "";

    Story116()
    {
        ID = 116;

        Bye = "You leave the latrine and approach Lucie and the stranger.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You gulp down the honeyed ale which slips down your gullet, filling your stomach with a heavy warm glow. The amber nectar is thick and almost sticky, yet strangely moreish. You finish your pot with relish, wipe your mouth backhanded and immediately feel a pang of pain in your stomach. You rush to the latrine where you are violently sick. Just as you think you have recovered, another wave spurts out from your mouth. This one is a mixture of brown and red as blood is coming out too. Mercifully, your stomach finally empties and you collapse in a puddle of your own sick and other peoples' urine, exhausted.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nThe landlord had poisoned you for what you did to him. Thoughts of teaching him a lesson are quickly banished from your mind as the occupants of the tavern will probably round on you if you try to kill him.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 132; }
};

class Story117 : public Story::Base
{
public:
    Story117()
    {
        ID = 117;

        Image = "images/filler1.png";

        Text = "You leave the shop and return to the inn. There you see a young man with dark hair, a nervous look about him and a bandaged arm. He is telling his story to the innkeeper.\n\n\"I am a Judain from Godorno. I had to flee the place for if the Overlord's men didn't get me, the plague certainly would have done.\"\n\nYou approach this man, introduce yourself and ask him for more about Godorno.\n\n\"It has become a terrible place. A plague has broken out unlike any I've seen before. Its victims are reduced to maniacal beasts. As if that's not bad enough, people have started to disappear in the night, both Judain and non-Judain. Both the Overlord and the Sycaari deny responsibility. But that is not all. The synagogue has been torn down. Caiaphas, the rabbi made sermon of peace and tolerance. He said that the actions of the Sycaari would only create a cycle of hatred and violence that would destroy the city. However, violence broke out amongst the congregation. No one knows who provoked it, either the Sycaari or the Overlord's agents, but the mob soon went out of control. The Overlord's soldiers did nothing to stop it and watched as people died and the synagogue was destroyed. Caiaphas was killed in the riot.\"\n\nYou listen to this in horror. Caiaphas was like a father to you. He helped raise you, he found you mentors to train you. And now he is dead. And the synagogue has been torn down. Godorno is worse than it ever has been. But can you make a difference if you return?";

        Choices.clear();
        Choices.push_back(Choice::Base("Get on a barge and return to Godorno", 294));
        Choices.push_back(Choice::Base("Get away from the Overlord's mercenaries and head north to Mazarkhand", 297));

        Controls = Story::Controls::STANDARD;
    }
};

class Story118 : public Story::Base
{
public:
    Story118()
    {
        ID = 118;

        Image = "images/vr-logo.png";

        Text = "You swing the ROPE and GRAPPLE and aim for the wooden beam. You latch on with your first go. It is then a case for you to simply swing across the room, sailing over the angry, hissing snakes, to the other stone block. You land there gently and walk through the door, congratulating yourself.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::ROPE, Item::Type::GRAPPLE});
    }

    int Continue(Character::Base &player) { return 99; }
};

class Story119 : public Story::Base
{
public:
    Story119()
    {
        ID = 119;

        Image = "images/hate-attacks.png";

        Text = "A giant purple worm breaks the surface of the Grand Canal and towers over the crowd. As this happens the crowd can do nothing but stare in bewildered terror. Then the worm comes crashing down on the stage, smashing it into splinters and crushing Ahab and the Overlord. The cacophony breaks the crowd out of their trance and they all start to rush out of the square, pushing and shoving each other to get as far away from Hate as possible. The Overlord's guards simply abandon their posts and join the stampede, their only instinct to escape. You stay to watch a little longer. The worm does not move forward, but starts to lurch and spasm as if it is undergoing some kind of transformation. Things start to bulge out of the front part of it and it rears back up into the air before landing in the Grand Canal with an enormous splash. The spray of water hits you, soaking you. Before you can do anything, however, the worm rears out of the water again, but this time it is different. This time it has a head. The creature now has two green eyes and a fang filled mouth, eager to devour the rest of the city. The face has a curious familiarity and then it hits you. It is a mixture of the Overlord's and Ahab's face. By absorbing the two most hateful men in the city, the transformation is now complete. The creature looks at you with a mixture of hate and hunger, eager to devour you and crashes in the plaza. Tentacles sprout from its purple flesh, seeking out anyone who was foolish enough to stay and the work lurches towards you. It is now mere feet from you. You can smell its warm fetid breath as it opens its mouth to devour you. Then it stops.\n\nThere is a clanking sound. You step back and look around to see what is happening. Chains are rising out of the stone ground of the plaza and tying themselves around the giant purple worm. This is holding it to the ground. An image of a woman in blue robes appears above the plaza. You recognise her as Erika, a powerful sorceress who lives on Giant's Tooth Island\n\n\"You must flee! I cannot hold this creature for long! Flee for your lives!\"\n\nThe image disappears. Hate is writhing and struggling under the magical chains.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::ARMED}))
        {
            return 100;
        }
        else
        {
            return 196;
        }
    }
};

class Story120 : public Story::Base
{
public:
    Story120()
    {
        ID = 120;

        Text = "At the last, you seem to hear a high-pitched uncanny whispering coming from Hate's black maw. As it shudders in its death throes and you sink into the oblivion of death, you imagine that you hear its words: \"To the last I grapple with thee, Judain. From Hell's heart I stab at thee. For Hate's sake, I spit my last breath at thee!\" It pulls you close to its rancid maw as the two of you die. But you have died a true hero's death, bringing salvation to the city of your birth. Those that succumbed to Hate are restored to life and climb out of the catacombs to return to humanity.\n\nIn days to come, when Godorno is rebuilt, a statue will be erected to honour your memory. You have triumphed.";

        Type = Story::Type::HERO_DEATH;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Life = 0;
    }
};

class Story121 : public Story::Base
{
public:
    Story121()
    {
        ID = 121;

        Image = "images/filler1.png";

        Text = "This is not what you want. The Overlord is not the real enemy here, but Hate itself. It won't matter how many of the Overlord's followers you kill, you will only inspire others to take up arms against the Judain. You don't know how, but you are going to save your people another way.";

        Bye = "But first, you need to find a new place to live.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 432; }
};

class Story122 : public Story::Base
{
public:
    Story122()
    {
        ID = 122;

        Image = "images/quay.png";

        Text = "You think that maybe the abandoned ships in the harbour might have something that can combat Hate. You remember seeing that it had the flag of Federico Tadmor, the famous explorer and treasure hunter. His ship may have something that you might find useful.";

        Choices.clear();
        Choices.push_back(Choice::Base("Look for the ship", 479));
        Choices.push_back(Choice::Base("Head back to your shelter", 16));

        Controls = Story::Controls::STANDARD;
    }
};

class Story123 : public Story::Base
{
public:
    Story123()
    {
        ID = 123;

        Image = "images/vr-logo.png";

        Text = "The brigands come to a halt before you.\n\n\"I wish to join you!\", you shout.\n\n\"Oh yeah? We don't let any old freeloader join our band,\" shouts a tall bald, scarred brigand. He dismounts from his horse, draws a serrated sword and approaches you, grinning like a wolf.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JADE_WARRIORS_SWORD}))
        {
            return 25;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            return 325;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::THROWING))
        {
            return 319;
        }
        else if (Character::VERIFY_ITEMS_ANY(player, {Item::SWORD, Item::JADE_WARRIORS_SWORD}))
        {
            return 197;
        }
        else
        {
            return 347;
        }
    }
};

class Story124 : public Story::Base
{
public:
    Story124()
    {
        ID = 124;

        Image = "images/vr-logo.png";

        Text = "The green light is burning you both inside and out. It is as if your blood is boiling and your skin is charring.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 438;
        }
        else if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            return 336;
        }
        else
        {
            return 350;
        }
    }
};

class Story125 : public Story::Base
{
public:
    std::string PreText = "";
    bool SURVIVED = true;

    Story125()
    {
        ID = 125;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        SURVIVED = true;

        PreText = "Hate shrieks a cry of insensate fury as it sees you charging back to slice at it with your enchanted blade. In a welter of carnage, you and your monstrous foe lock in mortal combat. The green-tinted metal of your blade chops deep into Hate's soft purulent flesh, while its tentacles slap into you with stunning force. Those baleful green eyes gleam with a new emotion now not hatred and unreasoning violence, but the liquid gleam of fear. Hate knows that it is going to die today, but it sells its life dearly.\n\n";

        auto DAMAGE = -9;

        if (Character::HAS_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = -7;

            PreText += "[SWORDPLAY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life <= 0)
        {
            SURVIVED = false;

            player.Life = 1;
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (SURVIVED)
        {
            return 51;
        }
        else
        {
            return 120;
        }
    }
};

class Story126 : public Story::Base
{
public:
    Story126()
    {
        ID = 126;

        Image = "images/filler2.png";

        Text = "Hate moves its giant body at the last second and the POMEGRANATE bounces harmlessly off its translucent purple flesh. The ARTEFACT lands beyond your reach.\n\nWith the LOSS of the IVORY POMEGRANATE, you no longer reduce damage caused by Hate.";

        Bye = "You return to the fray with Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::IVORY_POMEGRANATE});

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            // TODO: Implement DAMAGE REDUCTION with the IVORY POMEGRANATE
            Character::GET_CODEWORDS(player, {Codeword::Type::GOODNESS});
        }
    }

    int Continue(Character::Base &player) { return 18; }
};

class Story127 : public Story::Base
{
public:
    Story127()
    {
        ID = 127;

        Image = "images/vr-logo.png";

        Text = "Throwing caution to the wind, you continue alone on the road until you see a cloud of smoke or dust up ahead.";

        Choices.clear();
        Choices.push_back(Choice::Base("Find a place to hide", 553));
        Choices.push_back(Choice::Base("Face whatever is coming", 93));

        Controls = Story::Controls::STANDARD;
    }
};

class Story128 : public Story::Base
{
public:
    Story128()
    {
        ID = 128;

        Image = "images/filler2.png";

        Text = "You do not want to die a senseless death, being slaughtered by the Overlord's men in the street, especially when you have a weapon with which to fight the true enemy Hate.";

        Bye = "You grip the haft of the JADE WARRIOR's SWORD as you stalk the streets of Godorno, looking for the monster.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 283; }
};

class Story129 : public Story::Base
{
public:
    Story129()
    {
        ID = 129;

        Image = "images/mob.png";

        Text = "Your SWORD rasps from its sheath. The youth starts to retreat, throwing his knife away and yelling at the top of his voice: \"Help, murderer! A Judain tried to kill me! Help me!\"\n\nBefore you can sheath your SWORD the shutters in the houses overlooking the street are flung open and the cry is taken up. A group of cobblers come advancing on you wielding their little hammers. Pots and pans rain down on your head from the windows above. A steaming hot sago pudding lands on your head and oozes down underneath your jerkin as you jump nimbly aside to avoid the contents of a chamber pot.";

        Bye = "You have no choice but to flee before the mob overwhelms you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 523; }
};

class Story130 : public Story::Base
{
public:
    Story130()
    {
        ID = 130;

        Image = "images/giant-spider.png";

        Text = "As you run across the room, the spider lowers itself down to crush you, but you are too fast for it. You slam into the door and yank the handle. Thankfully, the door is not locked or trapped and it opens normally. You run through the door just as the spider lands on the floor, but it can't pursue you through such a small space. You run down a corridor and down some spiral steps that seem to go on forever.";

        Bye = "Eventually you reach the bottom of the stairs where there is a door that exits the tower.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 252; }
};

class Story131 : public Story::Base
{
public:
    Story131()
    {
        ID = 131;

        Image = "images/vr-logo.png";

        Text = "You draw your SWORD with a flourish and advance steadily on Skakshi. Desperately, he throws his knife at you. However, you are prepared for this and strike it out of the way with the SWORD. The landlord throws him a spiked club with which to defend himself. You can see by the way he hefts it he knows how to use it to pulp brains. Your SWORD gives you an advantage over his rude weapon, but you will still have to be careful.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::HAS_SKILL(player, Skill::Type::SWORDPLAY))
        {
            return 234;
        }
        else
        {
            return 543;
        }
    }
};

class Story132 : public Story::Base
{
public:
    Story132()
    {
        ID = 132;

        Image = "images/vr-logo.png";

        Text = "Tyutchev looks at you insolently. His direct stare makes you feel very uncomfortable. He has challenged many a poor fellow with a look like this, and most of them didn't live to tell the tale. Now he says \"So a Judain comes ready for the slaughter! It's hardly worth the bother of collecting the ten gleenar's reward, but then there is the pleasure of killing you.\"\n\nHe speaks as though you were a slimebeast that had crawled out from under a stone. He draws his sword, a great one-and-a-half-hander, which he wields with magnificent ease and power, as if it were a toothpick. It thrums through the air as he prepares to slaughter you. With a surprisingly quick movement for so large a man he manages to put himself between you and the only door. It doesn't look as if the latrine here backs onto the outside world so there is no escape that way.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS_ANY(player, {Item::SWORD, Item::JADE_WARRIORS_SWORD}))
        {
            return 409;
        }
        else
        {
            return 452;
        }
    }
};

class Story133 : public Story::Base
{
public:
    Story133()
    {
        ID = 133;

        Image = "images/vr-logo.png";

        Text = "Ahab and his five lieutenants draw their knives and advance upon you.\n\n\"Wait! I did what I thought you wanted with the money!\", you shout. \"I bribed officials to let some Judain escape and to turn a blind eye to attacks! Wasn't that what you wanted?\"\n\nThe men stop their advance. Ahab questions you on who you bribed and for what. Your knowledge of the people of Godorno is enough to satisfy him.\n\nThey don't know whether to believe you, but, fortunately for you, it will take some time to find out one way or the other.\n\n\"You can stay for now.\" Says Ahab \"But any more sign of funny business from you and you get the knife.\"";

        Bye = "He motions to a door and you walk through to find a room covered in straw. People are asleep on the floor and you join them.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 349; }
};

class Story134 : public Story::Base
{
public:
    Story134()
    {
        ID = 134;

        Image = "images/vr-logo.png";

        Text = "Ahab snatches the money off you and smiles, bearing his teeth. You see his green eyes glitter with greed.\n\n\"You have done well. I guess we could repay you for your help.\"\n\nOne of Ahab's men goes away. When he returns, he has two pots of HEALING SALVE. Each one will restore 1 Life Point.\n\n\"Have some rest for now.\" Says Ahab \"I have big plans for you in the morning.\"";

        Bye = "Ahab motions to a door nearby. You walk through it to find several people sleeping on a straw covered floor. You join them.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::HEALING_SALVE, Item::HEALING_SALVE};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 349; }
};

class Story135 : public Story::Base
{
public:
    Story135()
    {
        ID = 135;

        Image = "images/vr-logo.png";

        Text = "Eventually, you come to an octagonal room with several Judain runes inscribed on the walls. Rocks and other debris litter the floor. As you sift through it, you find the clay parts of the golem, but they have been broken, probably by falling rocks. You curse. Then you see something different. It is a small marble capsule, engraved with several arcane runes. You remember that this capsule was put in the golem's mouth to bring it to life. As you pick it up, you feel the magic of the capsule flow into you before it crumbles to dust.\n\nYou MAXIMUM Life Points is INCREASED by 3. You GAIN 3 Life Points.";

        Bye = "Feeling prepared, you return to the synagogue and set off to find a safe place for the night.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.MAX_LIFE_LIMIT += 3;

        Character::GAIN_LIFE(player, 3);
    }

    int Continue(Character::Base &player) { return 432; }
};

class Story136 : public Story::Base
{
public:
    Story136()
    {
        ID = 136;

        Image = "images/jade-warriors.png";

        Text = "You dart in to attack the first of the Jade Warriors. You fight well; your sword is an arcing blaze of light, but though it rings loudly against the jade bodies of your adversaries, they are not dinted. Their heavy blows break down your guard and their blades are terribly sharp, as you find to your cost when one bites into your shoulder.\n\nYou LOSE 2 Life Points.";

        Bye = "You flee the tomb before the Jade Warriors overwhelm you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.MAX_LIFE_LIMIT += 3;

        Character::GAIN_LIFE(player, 3);
    }

    int Continue(Character::Base &player) { return 83; }
};

class Story137 : public Story::Base
{
public:
    Story137()
    {
        ID = 137;

        Image = "images/vr-logo.png";

        Text = "You walk up the road for an hour until you come to an inn. It is getting dark now and the lights and the sound of merriment inside seem warm and welcoming.";

        Choices.clear();
        Choices.push_back(Choice::Base("Enter the inn", 377));
        Choices.push_back(Choice::Base("Carry on up the road", 68));

        Controls = Story::Controls::STANDARD;
    }
};

class Story138 : public Story::Base
{
public:
    Story138()
    {
        ID = 138;

        Image = "images/filler1.png";

        Text = "You gained the codeword LEVAD.\n\nAhab is going too far. He is putting the lives of you and the other Sycaari in danger just to satisfy his lust for revenge. He will not forgive you for deserting him now, however. You will have to survive whilst being sought after by both the Overlord's men and the Sycaari. However, you have survived in Godorno for many years and you are confident that you can avoid both. You traipse through the city, spending time looking for a suitable hideout. Eventually, you come to a hovel on Bumble Row where, exhausted, you throw yourself onto a pallet and fall into a fitful sleep.\n\nWhen you awake the next morning, you think about whether you have any allies left in the city. There may be some Judain who are still able to survive here whilst not being part of the Sycaari. You think of the mentors that Caiaphas set you up with when he noticed your potential. These great Judain recognised your talents and honed them. They might still be in the city. On the other hand, you might need more people if Hate is getting so powerful. It might be worth using a gondola to scour the city to find other lonely Judain to recruit to your cause of stopping Hate.";

        Choices.clear();
        Choices.push_back(Choice::Base("Seek out one of your mentors", 371));
        Choices.push_back(Choice::Base("Scour the city by barge", 564));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::LEVAD});
    }
};

class Story139 : public Story::Base
{
public:
    std::string PreText = "";

    Story139()
    {
        ID = 139;

        Image = "images/vr-logo.png";

        Bye = "Now that you have the HERB, you return to the old woman.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You are too close to outrun the boar, so you face it. It is a fierce and strong creature intent on goring you to death. It is a desperate battle.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL_ANY_ITEMS(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::JADE_WARRIORS_SWORD}))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -2;

            PreText += "[UNARMED COMBAT] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        if (player.Life > 0)
        {
            PreText += "\n\nOnce you have slain the boar, you collect some of the HERB that you find in the corpse.";

            Character::GET_ITEMS(player, {Item::HERB});
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 237; }
};

auto customShop = CustomShop();

auto prologue = Prologue();
auto story001 = Story001();
auto story002 = Story002();
auto story003 = Story003();
auto story004 = Story004();
auto story005 = Story005();
auto story006 = Story006();
auto story007 = Story007();
auto story008 = Story008();
auto story009 = Story009();
auto story010 = Story010();
auto story011 = Story011();
auto story012 = Story012();
auto story013 = Story013();
auto story014 = Story014();
auto story015 = Story015();
auto story016 = Story016();
auto story017 = Story017();
auto story018 = Story018();
auto story019 = Story019();
auto story020 = Story020();
auto story021 = Story021();
auto story022 = Story022();
auto story023 = Story023();
auto story024 = Story024();
auto story025 = Story025();
auto story026 = Story026();
auto story027 = Story027();
auto story028 = Story028();
auto story029 = Story029();
auto story030 = Story030();
auto story031 = Story031();
auto story032 = Story032();
auto story033 = Story033();
auto story034 = Story034();
auto story035 = Story035();
auto story036 = Story036();
auto story037 = Story037();
auto story038 = Story038();
auto story039 = Story039();
auto story040 = Story040();
auto story041 = Story041();
auto story042 = Story042();
auto story043 = Story043();
auto story044 = Story044();
auto story045 = Story045();
auto story046 = Story046();
auto story047 = Story047();
auto story048 = Story048();
auto story049 = Story049();
auto story050 = Story050();
auto story051 = Story051();
auto story052 = Story052();
auto story053 = Story053();
auto story054 = Story054();
auto story055 = Story055();
auto story056 = Story056();
auto story057 = Story057();
auto story058 = Story058();
auto story059 = Story059();
auto story060 = Story060();
auto story061 = Story061();
auto story062 = Story062();
auto story063 = Story063();
auto story064 = Story064();
auto story065 = Story065();
auto story066 = Story066();
auto story067 = Story067();
auto story068 = Story068();
auto story069 = Story069();
auto story070 = Story070();
auto story071 = Story071();
auto story072 = Story072();
auto story073 = Story073();
auto story074 = Story074();
auto story075 = Story075();
auto story076 = Story076();
auto story077 = Story077();
auto story078 = Story078();
auto story079 = Story079();
auto story080 = Story080();
auto story081 = Story081();
auto story082 = Story082();
auto story083 = Story083();
auto story084 = Story084();
auto story085 = Story085();
auto story086 = Story086();
auto story087 = Story087();
auto story088 = Story088();
auto story089 = Story089();
auto story090 = Story090();
auto story091 = Story091();
auto story092 = Story092();
auto story093 = Story093();
auto story094 = Story094();
auto story095 = Story095();
auto story096 = Story096();
auto story097 = Story097();
auto story098 = Story098();
auto story099 = Story099();
auto story100 = Story100();
auto story101 = Story101();
auto story102 = Story102();
auto story103 = Story103();
auto story104 = Story104();
auto story105 = Story105();
auto story106 = Story106();
auto event106 = Event106();
auto story107 = Story107();
auto story108 = Story108();
auto story109 = Story109();
auto story110 = Story110();
auto story111 = Story111();
auto story112 = Story112();
auto story113 = Story113();
auto story114 = Story114();
auto story115 = Story115();
auto story116 = Story116();
auto story117 = Story117();
auto story118 = Story118();
auto story119 = Story119();
auto story120 = Story120();
auto story121 = Story121();
auto story122 = Story122();
auto story123 = Story123();
auto story124 = Story124();
auto story125 = Story125();
auto story126 = Story126();
auto story127 = Story127();
auto story128 = Story128();
auto story129 = Story129();
auto story130 = Story130();
auto story131 = Story131();
auto story132 = Story132();
auto story133 = Story133();
auto story134 = Story134();
auto story135 = Story135();
auto story136 = Story136();
auto story137 = Story137();
auto story138 = Story138();
auto story139 = Story139();

void InitializeStories()
{
    Stories = {
        &event106,
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039,
        &story040, &story041, &story042, &story043, &story044, &story045, &story046, &story047, &story048, &story049,
        &story050, &story051, &story052, &story053, &story054, &story055, &story056, &story057, &story058, &story059,
        &story060, &story061, &story062, &story063, &story064, &story065, &story066, &story067, &story068, &story069,
        &story070, &story071, &story072, &story073, &story074, &story075, &story076, &story077, &story078, &story079,
        &story080, &story081, &story082, &story083, &story084, &story085, &story086, &story087, &story088, &story089,
        &story090, &story091, &story092, &story093, &story094, &story095, &story096, &story097, &story098, &story099,
        &story100, &story101, &story102, &story103, &story104, &story105, &story106, &story107, &story108, &story109,
        &story110, &story111, &story112, &story113, &story114, &story115, &story116, &story117, &story118, &story119,
        &story120, &story121, &story122, &story123, &story124, &story125, &story126, &story127, &story128, &story129,
        &story130, &story131, &story132, &story133, &story134, &story135, &story136, &story137, &story138, &story139};
}

#endif
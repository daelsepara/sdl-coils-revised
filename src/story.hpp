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

        Image = "images/vr-logo.png";

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
        PreText = "Your band fight valiantly against Hate, slashing its purple flesh so that huge chunks fall off. To defend itself, tentacles grow out of Hate's body which lash at you with great force.\n\n";

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

        Text = "You hurl the pomegranate with force and accuracy and it shoots straight into Hate's mouth and down its throat. The beast starts to shudder and a look of fear appears on its face.";

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

        Text = "The KNIFE is perfect for the job. You send it into the bloated gasbag of a body which is punctured. Black ichor sprays all over the room.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::THROWING))
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

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
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

        Text = "The man is strong and fierce, but you can tell that he has never had any formal training with a sword. He raises his weapon to deliver a brutal swing, but you easily step backwards and avoid it. Before he can recover, you thrust forwards, wounding his arm and causing him to drop his sword with a yelp of pain. The other brigands cheer and jeer.";

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

        Text = "You throw the POMEGRANATE with as much force as you can, but the creature turns its head at the last minute and it bounces harmlessly off its purple flesh. You won't be able to get it back now. \n\nWith the LOSS of the IVORY POMEGRANATE, you no longer reduce damage caused by Hate.\n\nYou have to think of another way to defeat Hate.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leap back into the fray with the JADE WARRIOR's SWORD", 125, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Use the JEWEL OF SUNSET FIRE", 218, {Item::JEWEL_OF_SUNSET_FIRE}));
        Choices.push_back(Choice::Base("Flee", 476));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::IVORY_POMEGRANATE});
    }
};

class Story028 : public Story::Base
{
public:
    Story028()
    {
        ID = 28;

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

        Text = "The Overlord's men aren't expecting you, so no one notices when your first KNIFE embeds itself into the back of one of the guards. He collapses to the ground with a scream. The guards turn around to face you. Some run at you, but Talmai picks up one of the dead guards' SWORDs and rushes at her opponents, striking one in the back. Attacked on both sides, the remaining guards flee the scene rather than fight.";

        Bye = "Talmai approaches you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 425; }
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

void InitializeStories()
{
    Stories = {
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039};
}

#endif
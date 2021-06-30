#ifndef __CODEWORDS__HPP__
#define __CODEWORDS__HPP__

#include <map>

namespace Codeword
{
    enum class Type
    {
        NONE = -1,
        HECATOMB,
        SATORI,
        VENEFIX,
        IMPASSE,
        COOL,
        SUNSET,
        GORDIAN,
        CODEX,
        LEVAD,
        SKANK,
        MAZEL,
        LARCENY,
        JADE,
        ARMED,
        TOWER,
        JEWEL,
        THRUST,
        GOODNESS
    };

    std::map<Codeword::Type, const char *> Descriptions = {
        {Codeword::Type::HECATOMB, "Hecatomb"},
        {Codeword::Type::SATORI, "Satori"},
        {Codeword::Type::VENEFIX, "Venefix"},
        {Codeword::Type::IMPASSE, "Impasse"},
        {Codeword::Type::COOL, "Cool"},
        {Codeword::Type::SUNSET, "Sunset"},
        {Codeword::Type::GORDIAN, "Gordian"},
        {Codeword::Type::CODEX, "Codex"},
        {Codeword::Type::LEVAD, "Levad"},
        {Codeword::Type::SKANK, "Skank"},
        {Codeword::Type::MAZEL, "Mazel"},
        {Codeword::Type::LARCENY, "Larceny"},
        {Codeword::Type::JADE, "Jade"},
        {Codeword::Type::ARMED, "Armed"},
        {Codeword::Type::TOWER, "Tower"},
        {Codeword::Type::JEWEL, "Jewel"},
        {Codeword::Type::THRUST, "Thrust"},
        {Codeword::Type::GOODNESS, "Goodness"}};

    std::vector<Codeword::Type> Invisible = {Codeword::Type::GOODNESS};

    bool IsInvisible(Codeword::Type codeword)
    {
        auto invisible = false;

        for (auto i = 0; i < Codeword::Invisible.size(); i++)
        {
            if (Codeword::Invisible[i] == codeword)
            {
                invisible = true;

                break;
            }
        }

        return invisible;
    }

} // namespace Codeword
#endif

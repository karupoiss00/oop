#include <cassert>
#include <iostream>
#include "HtmlDecode.h"

struct DecodedEntity
{
    char ch;
    size_t length;
};

namespace
{
    using namespace std::literals;

    constexpr std::pair<std::string_view, char> entities[] =
    {
        {"&amp;"sv, '&'},
        {"&lt;"sv, '<'},
        {"&gt;"sv, '>'},
        {"&apos;"sv, '\''},
        {"&quot;"sv, '"'},
    };
}

DecodedEntity DecodeEntity(std::string_view text)
{
    assert(!text.empty() && text[0] == '&');
    for (const auto& [entity, decodedChar] : entities)
    {
        if (text.substr(0, entity.length()) == entity)
        {
            return { decodedChar, entity.length() };
        }
    }
    return { '&', 1 };
}

std::string HtmlDecode(std::string_view encodedStr)
{
    std::string result;
    for (size_t pos = 0; pos < encodedStr.length();)
    {
        auto ampPos = encodedStr.find('&', pos);
        result.append(encodedStr, pos, ampPos - pos);

        if (ampPos < encodedStr.length())
        {
            auto [decodedChar, entityLength] = DecodeEntity(encodedStr.substr(ampPos));
            result += decodedChar;
            pos = ampPos + entityLength;
        }
        else
        {
            break;
        }
    }
    return result;
}
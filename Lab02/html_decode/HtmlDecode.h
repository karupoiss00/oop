#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <cassert>

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

DecodedEntity DecodeEntity(std::string_view text);
std::string HtmlDecode(std::string_view encodedStr);
#pragma once
#include <string_view>
#include "structs.hpp"

namespace smbios
{
   
    // index is 1-based, 0 means not present
    inline const char* get_string(const header* hdr, uint8_t index)
    {
        if (index == 0)
            return "";

        const char* str = reinterpret_cast<const char*>(hdr) + hdr->length;

        for (uint8_t i = 1; i < index; i++)
        {
            while (*str)
                str++;
            str++;

            // malformed table exit
            if (*str == '\0')
                return "";
        }

        return str;
    }

    // walk all strings in a structure's unformatted section
    template<typename fn_t>
    inline void walk_strings(const header* hdr, fn_t callback)
    {
        const char* str = reinterpret_cast<const char*>(hdr) + hdr->length;
        uint8_t index = 1;

        while (*str)
        {
            callback(index, std::string_view(str));
            while (*str)
                str++;
            str++;
            index++;
        }
    }

    // use this to advance to the next structure while walking
    inline const uint8_t* end_of_structure(const header* hdr)
    {
        const char* str = reinterpret_cast<const char*>(hdr) + hdr->length;

        while (*str || *(str + 1))
            str++;

        return reinterpret_cast<const uint8_t*>(str + 2);
    }
}
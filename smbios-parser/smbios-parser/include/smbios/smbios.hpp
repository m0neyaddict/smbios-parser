#pragma once
#include "structs.hpp"
#include "strings.hpp"
#include <vector>


/*
   smbios-parser
   repository: https://github.com/m0neyaddict/smbios-parser
*/

namespace smbios
{
    // fetch raw blob
    inline std::vector<uint8_t> fetch()
    {
        DWORD size = GetSystemFirmwareTable('RSMB', 0, nullptr, 0);
        std::vector<uint8_t> buffer(size);
        GetSystemFirmwareTable('RSMB', 0, buffer.data(), size);
        return buffer;
    }

    // walks and calls callback for each
    template<typename fn_t>
    inline void walk_structures(const std::vector<uint8_t>& buffer, fn_t callback)
    {
        // skip 8 bytes
        const uint8_t* ptr = buffer.data() + 8;
        const uint8_t* end = buffer.data() + buffer.size();

        while (ptr < end)
        {
            const header* hdr = reinterpret_cast<const header*>(ptr);

            // EOT
            if (hdr->type == 127)
                break;

            callback(hdr);

            ptr = end_of_structure(hdr);
        }
    }
}
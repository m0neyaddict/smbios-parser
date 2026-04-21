#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <include/smbios/smbios.hpp>

static void run(const std::vector<uint8_t>& buffer)
{
    smbios::walk_structures(buffer, [](const smbios::header* hdr)
        {
            switch (hdr->type)
            {
            case 0:
            {
                auto* s = reinterpret_cast<const smbios::bios_info*>(hdr);

                printf("[type 0] bios\n");
                printf("  vendor        : %s\n", smbios::get_string(hdr, s->vendor));
                printf("  version       : %s\n", smbios::get_string(hdr, s->version));
                printf("  release date  : %s\n", smbios::get_string(hdr, s->release_date));
                printf("  bios release  : %u.%u\n", s->major_release, s->minor_release);
                printf("  ec release    : %u.%u\n", s->ec_major_release, s->ec_minor_release);
                break;
            }
            case 1:
            {
                auto* s = reinterpret_cast<const smbios::system_info*>(hdr);

                printf("[type 1] system\n");
                printf("  manufacturer  : %s\n", smbios::get_string(hdr, s->manufacturer));
                printf("  product       : %s\n", smbios::get_string(hdr, s->product_name));
                printf("  version       : %s\n", smbios::get_string(hdr, s->version));
                printf("  serial        : %s\n", smbios::get_string(hdr, s->serial_number));
                printf("  sku           : %s\n", smbios::get_string(hdr, s->sku_number));
                printf("  family        : %s\n", smbios::get_string(hdr, s->family));
                break;
            }
            case 2:
            {
                auto* s = reinterpret_cast<const smbios::baseboard_info*>(hdr);

                printf("[type 2] baseboard\n");
                printf("  manufacturer  : %s\n", smbios::get_string(hdr, s->manufacturer));
                printf("  product       : %s\n", smbios::get_string(hdr, s->product));
                printf("  version       : %s\n", smbios::get_string(hdr, s->version));
                printf("  serial        : %s\n", smbios::get_string(hdr, s->serial_number));
                printf("  asset tag     : %s\n", smbios::get_string(hdr, s->asset_tag));
                break;
            }
            case 3:
            {
                auto* s = reinterpret_cast<const smbios::chassis_info*>(hdr);

                printf("[type 3] chassis\n");
                printf("  manufacturer  : %s\n", smbios::get_string(hdr, s->manufacturer));
                printf("  version       : %s\n", smbios::get_string(hdr, s->version));
                printf("  serial        : %s\n", smbios::get_string(hdr, s->serial_number));
                printf("  asset tag     : %s\n", smbios::get_string(hdr, s->asset_tag));
                break;
            }
            case 4:
            {
                auto* s = reinterpret_cast<const smbios::processor_info*>(hdr);

                printf("[type 4] processor\n");
                printf("  socket        : %s\n", smbios::get_string(hdr, s->socket_designation));
                printf("  manufacturer  : %s\n", smbios::get_string(hdr, s->manufacturer));
                printf("  version       : %s\n", smbios::get_string(hdr, s->version));
                printf("  serial        : %s\n", smbios::get_string(hdr, s->serial_number));
                printf("  asset tag     : %s\n", smbios::get_string(hdr, s->asset_tag));
                printf("  part number   : %s\n", smbios::get_string(hdr, s->part_number));
                printf("  cores         : %u\n", s->core_count);
                printf("  threads       : %u\n", s->thread_count);
                printf("  max speed     : %u MHz\n", s->max_speed);
                printf("  current speed : %u MHz\n", s->current_speed);
                break;
            }
            case 7:
            {
                auto* s = reinterpret_cast<const smbios::cache_info*>(hdr);

                printf("[type 7] cache\n");
                printf("  designation   : %s\n", smbios::get_string(hdr, s->socket_designation));
                printf("  installed     : %u KB\n", s->installed_size & 0x7FFF);
                printf("  max size      : %u KB\n", s->maximum_cache_size & 0x7FFF);
                break;
            }
            case 9:
            {
                auto* s = reinterpret_cast<const smbios::system_slot*>(hdr);

                printf("[type 9] system slot\n");
                printf("  designation   : %s\n", smbios::get_string(hdr, s->slot_designation));
                break;
            }
            case 16:
            {
                auto* s = reinterpret_cast<const smbios::memory_array*>(hdr);
                uint64_t capacity = (s->maximum_capacity == 0x80000000)
                    ? s->extended_maximum_capacity / (1024 * 1024)
                    : s->maximum_capacity / 1024;

                printf("[type 16] memory array\n");
                printf("  max capacity  : %llu GB\n", capacity);
                printf("  slots         : %u\n", s->number_of_devices);
                break;
            }
            case 17:
            {
                auto* s = reinterpret_cast<const smbios::memory_device*>(hdr);
                if (s->size == 0) break;
                uint32_t size_mb = (s->size == 0x7FFF) ? s->extended_size : s->size;

                printf("[type 17] memory device\n");
                printf("  locator       : %s\n", smbios::get_string(hdr, s->device_locator));
                printf("  bank locator  : %s\n", smbios::get_string(hdr, s->bank_locator));
                printf("  manufacturer  : %s\n", smbios::get_string(hdr, s->manufacturer));
                printf("  serial        : %s\n", smbios::get_string(hdr, s->serial_number));
                printf("  asset tag     : %s\n", smbios::get_string(hdr, s->asset_tag));
                printf("  part number   : %s\n", smbios::get_string(hdr, s->part_number));
                printf("  size          : %u MB\n", size_mb);
                printf("  speed         : %u MHz\n", s->speed);
                printf("  configured    : %u MHz\n", s->configured_speed);
                break;
            }
            case 19:
            {
                auto* s = reinterpret_cast<const smbios::memory_array_mapped_address*>(hdr);
                uint64_t start = (s->starting_address == 0xFFFFFFFF)
                    ? s->extended_starting_address
                    : (uint64_t)s->starting_address * 1024;
                uint64_t end = (s->ending_address == 0xFFFFFFFF)
                    ? s->extended_ending_address
                    : (uint64_t)s->ending_address * 1024;

                printf("[type 19] memory mapped address\n");
                printf("  start         : 0x%llX\n", start);
                printf("  end           : 0x%llX\n", end);
                break;
            }
            default: return;
            }
            printf("\n");
        });
}

int main()
{
    auto buffer = smbios::fetch();

    if (buffer.empty())
    {
        printf("failed to retrieve smbios data\n");
        printf("press any key to exit...");
        _getch();
        return 1;
    }

    run(buffer);

    printf("press any key to exit...");
    _getch();
    return 0;
}
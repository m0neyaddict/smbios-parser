#pragma once
#include <cstdint>

namespace smbios
{
    struct header
    {
        uint8_t  type;
        uint8_t  length;
        uint16_t handle;
    };

#pragma pack(push, 1)

    // type 0 - bios information
    struct bios_info
    {
        header   hdr;
        uint8_t  vendor;
        uint8_t  version;
        uint16_t start_segment;
        uint8_t  release_date;
        uint8_t  rom_size;
        uint64_t characteristics;
        uint16_t characteristics_ext;
        uint8_t  major_release;
        uint8_t  minor_release;
        uint8_t  ec_major_release;
        uint8_t  ec_minor_release;
    };

    // type 1 - system information
    struct system_info
    {
        header   hdr;
        uint8_t  manufacturer;
        uint8_t  product_name;
        uint8_t  version;
        uint8_t  serial_number;
        uint8_t  uuid[16];
        uint8_t  wakeup_type;
        uint8_t  sku_number;
        uint8_t  family;
    };

    // type 2 - baseboard information
    struct baseboard_info
    {
        header   hdr;
        uint8_t  manufacturer;
        uint8_t  product;
        uint8_t  version;
        uint8_t  serial_number;
        uint8_t  asset_tag;
        uint8_t  feature_flags;
        uint8_t  location_in_chassis;
        uint16_t chassis_handle;
        uint8_t  board_type;
        uint8_t  object_handle_count;
    };

    // type 3 - chassis information
    struct chassis_info
    {
        header   hdr;
        uint8_t  manufacturer;
        uint8_t  type;
        uint8_t  version;
        uint8_t  serial_number;
        uint8_t  asset_tag;
        uint8_t  bootup_state;
        uint8_t  power_supply_state;
        uint8_t  thermal_state;
        uint8_t  security_status;
        uint32_t oem_defined;
        uint8_t  height;
        uint8_t  power_cords;
        uint8_t  element_count;
        uint8_t  element_record_length;
    };

    // type 4 - processor information
    struct processor_info
    {
        header   hdr;
        uint8_t  socket_designation;
        uint8_t  processor_type;
        uint8_t  processor_family;
        uint8_t  manufacturer;
        uint64_t processor_id;
        uint8_t  version;
        uint8_t  voltage;
        uint16_t external_clock;
        uint16_t max_speed;
        uint16_t current_speed;
        uint8_t  status;
        uint8_t  upgrade;
        uint16_t l1_cache_handle;
        uint16_t l2_cache_handle;
        uint16_t l3_cache_handle;
        uint8_t  serial_number;
        uint8_t  asset_tag;
        uint8_t  part_number;
        uint8_t  core_count;
        uint8_t  core_enabled;
        uint8_t  thread_count;
        uint16_t characteristics;
        uint16_t processor_family2;
        uint16_t core_count2;
        uint16_t core_enabled2;
        uint16_t thread_count2;
    };

    // type 7 - cache information
    struct cache_info
    {
        header   hdr;
        uint8_t  socket_designation;
        uint16_t cache_configuration;
        uint16_t maximum_cache_size;
        uint16_t installed_size;
        uint16_t supported_sram_type;
        uint16_t current_sram_type;
        uint8_t  cache_speed;
        uint8_t  error_correction_type;
        uint8_t  system_cache_type;
        uint8_t  associativity;
        uint32_t maximum_cache_size2;
        uint32_t installed_cache_size2;
    };

    // type 9 - system slots
    struct system_slot
    {
        header   hdr;
        uint8_t  slot_designation;
        uint8_t  slot_type;
        uint8_t  slot_data_bus_width;
        uint8_t  current_usage;
        uint8_t  slot_length;
        uint16_t slot_id;
        uint8_t  slot_characteristics1;
        uint8_t  slot_characteristics2;
        uint16_t segment_group_number;
        uint8_t  bus_number;
        uint8_t  device_function_number;
        uint8_t  data_bus_width;
    };

    // type 16 - physical memory array
    struct memory_array
    {
        header   hdr;
        uint8_t  location;
        uint8_t  use;
        uint8_t  error_correction;
        uint32_t maximum_capacity;     // if 0x80000000 use extended
        uint16_t error_info_handle;
        uint16_t number_of_devices;
        uint64_t extended_maximum_capacity;
    };

    // type 17 - memory device
    struct memory_device
    {
        header   hdr;
        uint16_t physical_array_handle;
        uint16_t error_info_handle;
        uint16_t total_width;
        uint16_t data_width;
        uint16_t size;
        uint8_t  form_factor;
        uint8_t  device_set;
        uint8_t  device_locator;
        uint8_t  bank_locator;
        uint8_t  memory_type;
        uint16_t type_detail;
        uint16_t speed;
        uint8_t  manufacturer;
        uint8_t  serial_number;
        uint8_t  asset_tag;
        uint8_t  part_number;
        uint8_t  attributes;
        uint32_t extended_size;
        uint16_t configured_speed;
        uint16_t min_voltage;
        uint16_t max_voltage;
        uint16_t configured_voltage;
    };

    // type 19 - memory array mapped address
    struct memory_array_mapped_address
    {
        header   hdr;
        uint32_t starting_address;     // if 0xFFFFFFFF use extended
        uint32_t ending_address;       // if 0xFFFFFFFF use extended
        uint16_t array_handle;
        uint8_t  partition_width;
        uint64_t extended_starting_address;
        uint64_t extended_ending_address;
    };

#pragma pack(pop)
}
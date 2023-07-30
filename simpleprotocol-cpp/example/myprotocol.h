#pragma once

#include <cstdint>
#include "simpleprotocol/protocol.hpp"
#include <cstdio>

/**
 * @brief 
 * @note 32bit alignment and packing is intentional.
 */
struct my_packet {
    // 8bit fields
    uint8_t u8_a;
    uint8_t u8_b;
    uint8_t u8_c;
    uint8_t u8_d;

    // 16bit fields
    uint16_t u16_a;
    uint16_t u16_b;

    // 32bit fields
    uint32_t u32_a;    

    static void print(const my_packet& s)
    {
        std::printf("s.u8_a: 0x%02x\n", s.u8_a);
        std::printf("s.u8_b: 0x%02x\n", s.u8_b);
        std::printf("s.u8_c: 0x%02x\n", s.u8_c);
        std::printf("s.u8_d: 0x%02x\n", s.u8_d);
        std::printf("s.u16_a: 0x%04x\n", s.u16_a);
        std::printf("s.u16_b: 0x%04x\n", s.u16_b);
        std::printf("s.u32_a: 0x%08x\n", s.u32_a);        
    }
} __attribute__((aligned(sizeof(uint32_t)))) __attribute__((packed));

template<>
void to_bytes(const my_packet& s, void* bytes)
{
    // 8bit fields
    (reinterpret_cast<uint8_t*>(bytes))[0] = s.u8_a;
    (reinterpret_cast<uint8_t*>(bytes))[1] = s.u8_b;
    (reinterpret_cast<uint8_t*>(bytes))[2] = s.u8_c;
    (reinterpret_cast<uint8_t*>(bytes))[3] = s.u8_d;

    // 16bit fields
    (reinterpret_cast<uint16_t*>(bytes))[2] = FIX_ENDIANNESS_16(s.u16_a);
    (reinterpret_cast<uint16_t*>(bytes))[3] = FIX_ENDIANNESS_16(s.u16_b);

    // 32bit fields
    (reinterpret_cast<uint32_t*>(bytes))[2] = FIX_ENDIANNESS_32(s.u32_a);    
};

template<>
void from_bytes(my_packet& s, const void* bytes)
{
    // 8bit fields
    s.u8_a = (reinterpret_cast<const uint8_t*>(bytes))[0];
    s.u8_b = (reinterpret_cast<const uint8_t*>(bytes))[1];
    s.u8_c = (reinterpret_cast<const uint8_t*>(bytes))[2];
    s.u8_d = (reinterpret_cast<const uint8_t*>(bytes))[3];

    // 16bit fields
    s.u16_a = FIX_ENDIANNESS_16((reinterpret_cast<const uint16_t*>(bytes))[2]);
    s.u16_b = FIX_ENDIANNESS_16((reinterpret_cast<const uint16_t*>(bytes))[3]);

    // 32bit fields
    s.u32_a = FIX_ENDIANNESS_32((reinterpret_cast<const uint32_t*>(bytes))[2]);    
};
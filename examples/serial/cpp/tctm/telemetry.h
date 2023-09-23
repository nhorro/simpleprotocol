#pragma once

#include <cstdint>
#include "simpleprotocol/protocol.hpp"
#include <cstdio>

/**
 * @brief 
 * @note 32bit alignment and packing is intentional.
 */
struct motor_report {
    static constexpr int REPORT_ID = 0x20000000;
    uint32_t opcode = REPORT_ID;

    float motor_throttle_0 = 0;
    float motor_throttle_1 = 1;

    static void print(const motor_report& s)
    {
        std::printf("motor_throttle_0: %f\n", s.motor_throttle_0);
        std::printf("motor_throttle_1 %f\n", s.motor_throttle_1);        
    }
} __attribute__((aligned(sizeof(uint32_t)))) __attribute__((packed));
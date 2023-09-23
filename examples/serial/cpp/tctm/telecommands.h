#pragma once

#include <cstdint>
#include "simpleprotocol/protocol.hpp"
#include <cstdio>

/**
 * @brief 
 * @note 32bit alignment and packing is intentional.
 */
struct set_motor_torques {
    static constexpr int CMD_ID = 0x10000000;
    uint32_t opcode = CMD_ID;

    float motor_throttle_0 = 0;
    float motor_throttle_1 = 1;

    static void print(const set_motor_torques& s)
    {
        std::printf("motor_throttle_0: %f\n", s.motor_throttle_0);
        std::printf("motor_throttle_1 %f\n", s.motor_throttle_1);        
    }
} __attribute__((aligned(sizeof(uint32_t)))) __attribute__((packed));
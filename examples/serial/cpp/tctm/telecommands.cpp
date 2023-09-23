#include "telecommands.h"

template<> void to_bytes(const set_motor_torques& s, void* bytes)
{   
    (reinterpret_cast<uint32_t*>(bytes))[0] = FIX_ENDIANNESS_32(s.opcode); 
    (reinterpret_cast<uint32_t*>(bytes))[4] = FIX_ENDIANNESS_32(s.motor_throttle_0);
    (reinterpret_cast<uint32_t*>(bytes))[8] = FIX_ENDIANNESS_32(s.motor_throttle_1);
};

template<> void from_bytes(set_motor_torques& s, const void* bytes)
{    
    s.opcode = FIX_ENDIANNESS_32((reinterpret_cast<const uint32_t*>(bytes))[0]);    
    s.motor_throttle_0 = FIX_ENDIANNESS_32((reinterpret_cast<const float*>(bytes))[4]);    
    s.motor_throttle_1 = FIX_ENDIANNESS_32((reinterpret_cast<const float*>(bytes))[8]);    
};
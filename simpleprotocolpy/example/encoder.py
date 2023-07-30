import sys
sys.path.append("../src/")
from simpleprotocol import Encoder
from myprotocol import *

def bytearray_to_packet_str(packet_ba: bytearray) -> str:
    return "0x " + "".join(["%02X " % x for x in packet_ba])

if __name__ == "__main__":
    p = MyPacket()

    p.u8_a = 0x99
    p.u8_b = 0x98
    p.u8_c = 0x97
    p.u8_d = 0x96
    p.u16_a = 0x6789
    p.u16_b = 0x1234
    p.u32_a = 0xabcd1234

    encoder = Encoder()
    payload = p.to_bytes()
    encoder.encode(payload)
    
    packet = encoder.get_packet_bytes()
    print(bytearray_to_packet_str(packet))
    
    
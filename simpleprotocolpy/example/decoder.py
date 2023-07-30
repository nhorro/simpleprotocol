import sys
sys.path.append("../src/")
from simpleprotocol import Decoder
from myprotocol import *

def packet_str_to_bytearray(packet_str: str) -> bytearray:
    return bytearray([int(x,16) for x in packet_str.split(" ")[1:]])

def handle_packet(payload):
    print("Good packet!")

    print(payload)
    my_packet = unpack('>BBBBHHI', payload)
    print(my_packet)

    p = MyPacket()
    p.from_bytes(payload)

    for f in p.get_fields():
        print("{}: 0x{:0x}".format(f, getattr(p, f) ))

def handle_error(ec):
    print(f"Error! {ec}")

if __name__ == "__main__":
    decoder = Decoder(user_handler_fn=handle_packet, user_error_handler_fn=handle_error)
    test_packet_str = "0x 40 3C 0C 99 98 97 96 67 89 12 34 AB CD 12 34 B4 0A"
    test_packet = packet_str_to_bytearray(test_packet_str)
    for x in test_packet:
        decoder.feed(x)

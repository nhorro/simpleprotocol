from struct import unpack, pack
import sys
sys.path.append("../src/")
from simpleprotocol import BaseMessage

class MyPacket(BaseMessage):
    def __init__(self):        
        self.u8_a = 0
        self.u8_b = 0
        self.u8_c = 0
        self.u8_d = 0
        self.u16_a = 0
        self.u16_b = 0
        self.u32_a = 0                

        # see: https://docs.python.org/3/library/struct.html
        self.format = '>BBBBHHI'
        BaseMessage.__init__(self)
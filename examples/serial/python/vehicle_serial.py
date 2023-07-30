import sys
sys.path.append("../../../simpleprotocolpy/src")
from simpleprotocol import Decoder, Encoder
import tctm

from serialif import SerialIF

class VehicleSerialIF(SerialIF):  
    def __init__(self, port, baudrate):
        SerialIF.__init__(self, port, baudrate, self.on_data)
        self.decoder = Decoder(
            user_handler_fn=self.handle_packet, 
            user_error_handler_fn=self.handle_error)
        self.encoder = Encoder()
        self.start_listening()

    def on_data(self, c):        
        self.decoder.feed(ord(c))
    
    def handle_packet(self, payload):
        print("Good packet!. Payload:", payload)
        self.send_report()

    def handle_error(self, ec):
        print("Some error:", ec)

    def shutdown(self):
        self.stop_listening()
    
    def send_report(self):
        tm = tctm.MotorReport()

        self.motor_directions = 0x87654321

        self.motor_tickcount_0 = 0x105A3212
        self.motor_tickcount_1 = 0x105A3234
        self.motor_tickcount_2 = 0x105A3256
        self.motor_tickcount_3 = 0x105A3278
        
        self.motor_rpm_0 = 0x105A32A1
        self.motor_rpm_1 = 0x105A32A2
        self.motor_rpm_2 = 0x105A32A3
        self.motor_rpm_3 = 0x105A32A4

        self.encoder.encode(tm.to_bytes())
        self.send_data(self.encoder.get_packet_bytes())

vehicle = VehicleSerialIF("/dev/virtualport", 9600)
input()
vehicle.shutdown()



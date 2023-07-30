import sys
sys.path.append("../../../simpleprotocolpy/src")
from simpleprotocol import Decoder, Encoder
import tctm

from serialif import SerialIF

class GroundControlSerialIF(SerialIF):  
    def __init__(self, port, baudrate):
        SerialIF.__init__(self, port, baudrate, self.on_data)        
        self.decoder = Decoder(
            user_handler_fn=self.handle_packet, 
            user_error_handler_fn=self.handle_error)
        self.encoder = Encoder()
        self.start_listening()

    def on_data(self, c):        
        self.decoder.feed(ord(c))        

    def shutdown(self):
        self.stop_listening()

    def handle_packet(self, payload):
        print("GC: Good packet!. Payload:", payload)        
        self.handle_motor_report(payload)

    def handle_error(self, ec):
        print("GC: Some error:", ec)

    def set_motor_torques(self):
        tc = tctm.SetMotorTorquesCmd()        
        self.encoder.encode(tc.to_bytes())  
        encoded_packet = self.encoder.get_packet_bytes()
        print(encoded_packet)
        self.send_data(encoded_packet)

    # Reports
    def handle_packet(self, payload):
        report = tctm.MotorReport()
        report.from_bytes(payload)
        print(report)



gc = GroundControlSerialIF("/dev/tty0", 9600)

# Send data at any time
gc.set_motor_torques()
input()
gc.shutdown()
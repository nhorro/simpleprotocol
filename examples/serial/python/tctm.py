
import sys
sys.path.append("../../../simpleprotocolpy/src")
from simpleprotocol import BaseMessage
    

# Commands
# ------------------------------------------------------------------------------------------------------------------------------

class SetMotorTorquesCmd(BaseMessage):
    CMD_ID = 0x10000000
    def __init__(self):        
        
        # Field default values here
        self.opcode = SetMotorTorquesCmd.CMD_ID        

        self.motor_throttle_0 = 0
        self.motor_throttle_1 = 0
        self.motor_throttle_2 = 0
        self.motor_throttle_3 = 0

        # Binary struct here
        # See: https://docs.python.org/3/library/struct.html
        self.format = '>I4I'
        BaseMessage.__init__(self)


    
# Reports
# ------------------------------------------------------------------------------------------------------------------------------

class MotorReport(BaseMessage):
    REPORT_ID = 0x20000000
    def __init__(self):        
        
        # Field default values here
        self.opcode = MotorReport.REPORT_ID        

        self.motor_directions = 0

        self.motor_tickcount_0 = 0
        self.motor_tickcount_1 = 0
        self.motor_tickcount_2 = 0
        self.motor_tickcount_3 = 0
        
        self.motor_rpm_0 = 0
        self.motor_rpm_1 = 0
        self.motor_rpm_2 = 0
        self.motor_rpm_3 = 0

        # Binary struct here
        # See: https://docs.python.org/3/library/struct.html
        self.format = '>I9I'
        BaseMessage.__init__(self)
#include "groundcontrol.h"
#include <iostream>

int main(int argc, const char* argv[]) 
{
    GroundControl gc("/dev/tty0", 9600);

    gc.start_listening();

    // Wait for user input or some other event
    std::cout << "Press Enter to send and stop..." << std::endl;
    std::cin.get();

    // Example: Send data
    gc.cmd_set_motor_torques(0.5,0.6,0x3);

    // Stop listening gracefully
    gc.stop_listening();

    return 0;
}




#include "serialif.h"

class Vehicle : public SerialIF {
public:
    Vehicle(const std::string& port, unsigned int baudrate);
private:
    void HandleData(const std::string& data);
};

Vehicle::Vehicle(const std::string& port, unsigned int baudrate)
    :
        SerialIF(port, baudrate, std::bind(&Vehicle::HandleData, this, std::placeholders::_1))
{

}

void Vehicle::HandleData(const std::string& data)
{
    std::cout << "Vehicle received: " << data;
}

int main() 
{
    Vehicle vehicle("/dev/virtualport", 9600);

    vehicle.start_listening();

    // Wait for user input or some other event
    std::cout << "Press Enter to send and stop..." << std::endl;
    std::cin.get();

    // Example: Send data
    //vehicle.send_data("Hello, I'm vehicle!\n");

    // Stop listening gracefully
    vehicle.stop_listening();

    return 0;
}




#include "groundcontrol.h"

static void print_raw_packet(const uint8_t* packet_bytes, size_t n)
{
    std::printf("0x ");
    
    for(size_t i=0;i< n; i++ )
    {
        std::printf("%02X ", uint32_t{packet_bytes[i]} );
    }
    std::printf("\n");
}

GroundControl::GroundControl(const std::string& port, unsigned int baudrate)
    :
        SerialIF(port, baudrate, std::bind(&GroundControl::_handle_received_bytes, this, std::placeholders::_1))
{

}

GroundControl::~GroundControl()
{
}


// Required by serialif

void GroundControl::_handle_received_bytes(const std::vector<uint8_t>& data)
{
    for(const uint8_t& c: data)
    {
        feed(c);
    }
    //std::cout << "Ground Control Station received: " << data;
}

// Commands

void GroundControl::cmd_set_motor_torques(float a, float b, uint32_t flags)
{
    set_motor_torques cmd;
    cmd.motor_throttle_0 = a;
    cmd.motor_throttle_1 = b;
        
    // Serialize the packet bytes    
    to_bytes<set_motor_torques>(cmd, encoder.get_payload_buffer());
    encoder.calc_crc_and_close_packet(sizeof(cmd));
    std::vector<uint8_t> packet(
        &encoder.get_packet_bytes()[0],
        &encoder.get_packet_bytes()[encoder.get_total_length()]);
    send_data(packet);
};


// Reports

void GroundControl::handle_packet(const uint8_t* payload, uint8_t n)
{
    std::printf("Payload (raw):\n");
    print_raw_packet(payload, n);
            
    motor_report p;
    from_bytes<motor_report>(p, payload);

    std::printf("Parsed:\n");
    motor_report::print(p);
}
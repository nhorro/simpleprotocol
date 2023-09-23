#pragma once

#include "serialif.h"
#include "telecommands.h"
#include "telemetry.h"
#include "simpleprotocol/encoder.hpp"
#include "simpleprotocol/decoder.hpp"

class GroundControl : 
    public SerialIF,
    public protocol::packet_decoder {
public:
    GroundControl(const std::string& port, unsigned int baudrate);
    ~GroundControl();

    // Commands
    void cmd_set_motor_torques(float a, float b, uint32_t flags);

private:
    protocol::packet_encoder encoder;
    protocol::packet_decoder::error_code last_communication_error;

    void _handle_received_bytes(const std::vector<uint8_t>& data);
    void handle_packet(const uint8_t* payload, uint8_t n) override;
    void set_error(error_code ec) override { last_communication_error = ec;   }
    protocol::packet_decoder::error_code get_last_comm_error() { return last_communication_error; }

    // Reports
};
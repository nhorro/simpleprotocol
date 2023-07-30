#include <any>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "myprotocol.h"
#include "simpleprotocol/encoder.hpp"
#include "simpleprotocol/decoder.hpp"

void print_raw_packet(const uint8_t* packet_bytes, size_t n)
{
    std::printf("0x ");
    
    for(size_t i=0;i< n; i++ )
    {
        std::printf("%02X ", uint32_t{packet_bytes[i]} );
    }
    std::printf("\n");
}


class my_application: public protocol::packet_decoder {
public:
    my_application()
    {

    }

    ~my_application()
    {

    }

    void handle_packet(const uint8_t* payload, uint8_t n) override
    {
        std::printf("Payload (raw):\n");
        print_raw_packet(payload, n);
            
        my_packet p;
        from_bytes<my_packet>(p, payload);

        std::printf("Parsed:\n");
        my_packet::print(p);
    }

    void set_error(error_code ec) override {
        last_communication_error = ec;
    }

    protocol::packet_decoder::error_code get_last_comm_error() { return last_communication_error; }

private:
    protocol::packet_decoder::error_code last_communication_error;

};

int main()
{
    std::printf("Encoding and transmssion\n"
                "------------------------\n\n" );

    // 1. Encode a packet
    protocol::packet_encoder pe;

    // 1.1 Set individual fields using struct fields.
    my_packet p;

    // 8bit fields
    p.u8_a = 0x99;
    p.u8_b = 0x98;
    p.u8_c = 0x97;
    p.u8_d = 0x96;

    // 16bit fields
    p.u16_a = 0x6789;
    p.u16_b = 0x1234;

    // 32bit fields
    p.u32_a = 0xABCD1234;

    my_packet::print(p);
            
    // Serialize the packet bytes    
    to_bytes<my_packet>(p, pe.get_payload_buffer());
    pe.calc_crc_and_close_packet(sizeof(my_packet));
    
    std::printf("Encoded packet:\n");
    print_raw_packet(pe.get_packet_bytes(),pe.get_total_length());

    std::printf("\nReception and decoding\n"
                  "----------------------\n\n" );

    const uint8_t* packet_bytes = pe.get_packet_bytes();
    size_t n = pe.get_total_length();

    my_application app;
    for(size_t i=0;i< n; i++ )
    {
        app.feed(packet_bytes[i]);
    }

    protocol::packet_decoder::error_code ec = app.get_last_comm_error();
    if(ec)
    {
        printf("Error code: %d\n", ec);
    }
}
#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <boost/asio.hpp>

class SerialIF {
public:
    SerialIF(const std::string& port, unsigned int baudrate, 
        std::function<void(const std::vector<uint8_t>&)> callback);
    void start_listening();
    void stop_listening();
    void send_data(const std::vector<uint8_t>& data);
private:
    void _listen();

    std::string port_;
    unsigned int baudrate_;
    std::function<void(const std::vector<uint8_t>&)> callback_;
    boost::asio::io_context io_context_;
    boost::asio::io_context::work work_;
    boost::asio::serial_port serial_port_;
    std::array<char, 128> read_buffer_;
    std::thread io_thread_;
};
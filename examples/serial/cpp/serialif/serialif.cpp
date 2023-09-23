#include "serialif.h"

SerialIF::SerialIF( const std::string& port, unsigned int baudrate, 
                    std::function<void(const std::vector<uint8_t>&)> callback)
    : 
        port_(port), 
        baudrate_(baudrate), 
        callback_(callback), 
        io_context_(), 
        work_(io_context_), 
        serial_port_(io_context_) 
{

}

void SerialIF::start_listening() 
{
    serial_port_.open(port_);
    serial_port_.set_option(boost::asio::serial_port_base::baud_rate(baudrate_));
    start_listening();
    io_thread_ = std::thread([this]() {
        io_context_.run();
    });
}

void SerialIF::stop_listening() 
{
    io_context_.stop();
    if (io_thread_.joinable()) {
        io_thread_.join();
    }
    serial_port_.close();
}

void SerialIF::send_data(const std::vector<uint8_t>& data) 
{
    boost::asio::async_write(serial_port_, boost::asio::buffer(data),
        [this,data](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                //std::cout << "Sent: " << data;
            } else {
                std::cerr << "Send error: " << error.message() << std::endl;
            }
        }
    );
}

void SerialIF::_listen() {
    serial_port_.async_read_some(boost::asio::buffer(read_buffer_),
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::vector<uint8_t> data(read_buffer_.begin(), read_buffer_.begin() + bytes_transferred);
                callback_(data);
                _listen(); // Continue reading
            } else {
                std::cerr << "Read error: " << error.message() << std::endl;
                // Handle read error, or stop listening
            }
        }
    );
}
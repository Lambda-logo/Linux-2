#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class ChatSession {
public:
    ChatSession(boost::asio::io_service& io_service, tcp::socket socket) : socket_(std::move(socket)) {}

    void start() {
        read();
    }

    void deliver(const std::string& message) {
        boost::asio::async_write(socket_, boost::asio::buffer(message + "\n"),
            [this](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    read();
                }
            });
    }

private:
    void read() {
        boost::asio::async_read_until(socket_, receiveBuffer_, '\n',
            [this](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&receiveBuffer_);
                    std::string message;
                    std::getline(is, message);
                    std::cout << "Received message: " << message << std::endl;
                    read();
                }
                else {
                    socket_.close();
                }
            });
    }

    tcp::socket socket_;
    boost::asio::streambuf receiveBuffer_;
};

class ChatServer {
public:
    ChatServer(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
        : acceptor_(io_service, endpoint), socket_(io_service) {
        startAccept();
    }

private:
    void startAccept() {
        acceptor_.async_accept(socket_,
            [this](const boost::system::error_code& ec) {
                if (!ec) {
                    std::make_shared<ChatSession>(socket_.get_io_service(), std::move(socket_))->start();
                }

                startAccept();
            });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

class ChatClient {
public:
    ChatClient(boost::asio::io_service& io_service, const tcp::endpoint& endpoint) : socket_(io_service) {
        socket_.async_connect(endpoint,
            [this](const boost::system::error_code& ec) {
                if (!ec) {
                    std::make_shared<ChatSession>(socket_.get_io_service(), std::move(socket_))->start();
                }
            });
    }

private:
    tcp::socket socket_;
};

int main() {
    try {
        boost::asio::io_service io_service;

        tcp::endpoint endpoint(tcp::v4(), 8888); // Порт для связи

        ChatServer server(io_service, endpoint);

        ChatClient client(io_service, endpoint);

        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
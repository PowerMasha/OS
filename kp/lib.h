#ifndef OSKP_LIB_H
#define OSKP_LIB_H

#include <memory>
#include <stdexcept>
#include <exception>
#include <zmq.hpp>

const std::string CONNECT_PREFIX =  "tcp://localhost:";
const std::string BIND_PREFIX  = "tcp://*:";

class Message {
public:
    static zmq::message_t CreateFromString(const std::string& msg_string);
    static std::string GetStringFromMessage(const zmq::message_t& msg);
};

class Socket {
public:
    explicit Socket(int socket_type);
    Socket(const Socket&) = delete;
    Socket(Socket&&) = delete;
    virtual ~Socket() noexcept;

    virtual void Attach(int port) = 0;
    virtual void SendMessage(const std::string& msg, bool non_block);
    virtual std::string ReceiveMessage();

protected:
    int socket_type_;
    zmq::context_t* context_ = nullptr;
    zmq::socket_t* socket_ = nullptr;
};

class ReqSocket : public Socket {
public:
    ReqSocket();
    void Attach(int port) override;
};

class RepSocket : public Socket {
public:
    RepSocket();
    void Attach(int port) override;
};

class PubSocket : public Socket {
public:
    PubSocket();
    void Attach(int port) override;
};

class SubSocket : public Socket {
public:
    SubSocket();
    void Attach(int port) override;
};



#endif //OSKP_LIB_H

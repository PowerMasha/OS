#include "lib.h"

zmq::message_t Message::CreateFromString(const std::string& msg_string) {
    zmq::message_t result(msg_string.size());
    memcpy(result.data(), msg_string.c_str(), msg_string.size());
    return std::move(result);
}

std::string Message::GetStringFromMessage(const zmq::message_t& msg) {
    return std::string((const char*)msg.data(), msg.size());

}

Socket::Socket(int socket_type)
: context_(new zmq::context_t(1)), socket_(new zmq::socket_t(*context_, socket_type)), socket_type_(socket_type) {}

Socket::~Socket() noexcept {
    delete socket_;
    delete context_;
}

void Socket::SendMessage(const std::string& msg, bool non_block) {
    zmq::message_t to_send = Message::CreateFromString(msg);
    zmq::send_flags flags = non_block ? zmq::send_flags::dontwait : zmq::send_flags::none;
    zmq::send_result_t res = socket_->send(to_send, flags); //std::optional<size_t>
}

std::string Socket::ReceiveMessage() {
    zmq::message_t received;
    zmq::recv_result_t res = socket_->recv(received);
    return Message::GetStringFromMessage(received);
}

RepSocket::RepSocket()
: Socket(ZMQ_REP) {}

void RepSocket::Attach(int port) {
    socket_->connect(CONNECT_PREFIX + std::to_string(port));
}

ReqSocket::ReqSocket()
: Socket(ZMQ_REQ) {}

void ReqSocket::Attach(int port) {
    socket_->bind(BIND_PREFIX + std::to_string(port));
}

PubSocket::PubSocket()
: Socket(ZMQ_PUB) {}

void PubSocket::Attach(int port) {
    socket_->bind(BIND_PREFIX + std::to_string(port));
}

SubSocket::SubSocket()
: Socket(ZMQ_SUB) {
    socket_->setsockopt(ZMQ_SUBSCRIBE, "", 0);
}

void SubSocket::Attach(int port) {
    socket_->connect(CONNECT_PREFIX + std::to_string(port));
}
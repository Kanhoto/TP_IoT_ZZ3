#include <iostream>
#include <string>
#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("my_cpp_client");
const std::string TOPIC("my_topic");

class callback : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "Connection lost" << std::endl;
    }

    void message_arrived(const std::string& topic, mqtt::message_ptr msg) override {
        std::string payload = msg->to_string();
        std::string xor_result = xor_operation(payload);
        std::cout << "Received message: " << payload << std::endl;
        std::cout << "XOR result: " << xor_result << std::endl;
    }

    void delivery_complete(mqtt::idelivery_token_ptr token) override {}

    void on_failure(const mqtt::itoken& tok) override {}

    void on_success(const mqtt::itoken& tok) override {}
};

std::string xor_operation(const std::string& input) {
    std::string output(input.length(), ' ');
    for (std::size_t i = 0; i < input.length(); ++i) {
        output[i] = input[i] ^ 0x55;  // XOR with 0x55
    }
    return output;
}

int main() {
    try {
        mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
        callback cb;
        client.set_callback(cb);
        mqtt::connect_options conn_opts;
        conn_opts.set_keep_alive_interval(20);
        conn_opts.set_clean_session(true);
        client.connect(conn_opts)->wait();
        client.subscribe(TOPIC)->wait();
        while (true) {
            // The loop will run indefinitely, listening for messages
        }
        client.unsubscribe(TOPIC)->wait();
        client.disconnect()->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }
    return 0;
}

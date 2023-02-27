#include <iostream>
#include <mosquitto.h>

//#include "AesCyphering.cpp"

const char MQTT_HOST[] = "198.27.70.149";
const int MQTT_PORT = 443;
const char MQTT_TOPIC[] = "isima/vadi/rx";

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result == 0) {
        std::cout << "Connected to MQTT broker" << std::endl;
        // Subscribe to the desired topic
        mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0);
    } else {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
    }
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    std::cout << "Received message on topic " << message->topic << std::endl << std::endl << "message payload: " << (char *)message->payload << std::endl << std::endl;
}

int main() {
    // Initialize the Mosquitto library
    mosquitto_lib_init();
    
    // Create a new MQTT client instance
    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if (mosq == NULL) {
        std::cerr << "Failed to create MQTT client instance" << std::endl;
        return 1;
    }
    
    // Set up the connection parameters
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    const int KeepAlive = 60;
    mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, KeepAlive);
    
    // Enter the network loop to listen for incoming messages
    mosquitto_loop_forever(mosq, -1, 1);
    
    // Cleanup and exit
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}
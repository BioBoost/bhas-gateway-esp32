#include "driver/gpio.h"
#include "driver/twai.h"
#include "message.h"
#include "message_printer.h"
#include "json_encoder.h"

// TODO: I think we should be able to make the mbed library compatible with ESP
// of we extract all the mbed specific stuff to separate library.

using BHAS::Communication::Message;
using BHAS::Logging::MessagePrinter;
using BHAS::Communication::Encoders::JSONEncoder;

enum class MessageType : uint8_t {
  NONE =      0x00,
  HELLO =     0x01,
  EVENT =     0x02,
  ALERT =     0x03,
  CONFIG =    0x04,
  PERIODIC =  0x05,
  WARNING =   0x06,
  ERROR =     0x07,
  ALIVE =     0x08
};

void process_can_message(twai_message_t& message) {
  //Process received message
  if (message.extd) return;       // Not supporting extended format

  Message bhasMessage(
    message.data[0],
    static_cast<uint8_t>(message.identifier),
    message.data[1],
    static_cast<Message::Type>(message.data[2])
  );

  bhasMessage.payload(message.data+3, message.data_length_code-3);

  char buffer[128];
  MessagePrinter::print(buffer, bhasMessage);
  printf("Received: %s\n", buffer);

  printf("Or as JSON: %s\n", JSONEncoder::message_to_json_string(bhasMessage).c_str());
}

void check_for_can_message() {
  //Wait for message to be received
  twai_message_t message;
  auto result = twai_receive(&message, pdMS_TO_TICKS(100));

  if (result == ESP_OK) {
    // TODO: Process message
    process_can_message(message);
  } else if (result == ESP_ERR_TIMEOUT) {
    return;
  } else {
      printf("Failed to receive message\n");
      return;
  }
}

extern "C" void app_main()
{
    //Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(
      GPIO_NUM_14,        // TX
      GPIO_NUM_32,        // RX
      TWAI_MODE_NORMAL
    );
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_100KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    //Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
        printf("Driver installed\n");
    } else {
        printf("Failed to install driver\n");
        return;
    }

    //Start TWAI driver
    if (twai_start() == ESP_OK) {
        printf("Driver started\n");
    } else {
        printf("Failed to start driver\n");
        return;
    }

  // if (twai_transmit(&message, pdMS_TO_TICKS(1000)) == ESP_OK) {
  //     printf("Message queued for transmission\n");
  // } else {
  //     printf("Failed to queue message for transmission\n");
  // }

  while (true) {
    check_for_can_message();
  }

}
#pragma once

#include "message.h"
#include <string>
#include "nlohmann_json.hpp"
#include "message_printer.h"

namespace BHAS::Communication::Encoders {

  class JSONEncoder {

    public:

    public:
      static std::string message_to_json_string(const Message& message) {
        using json = nlohmann::json;
        using BHAS::Logging::MessagePrinter;

        json jsonObj;
        jsonObj["source_id"] = message.source_id();
        jsonObj["destination_id"] = message.destination_id();
        jsonObj["entity_id"] = message.entity_id();
        jsonObj["type"] = MessagePrinter::message_type_as_string(message.type());

        const uint8_t * payload = message.payload();
        for (size_t i = 0; i < message.payload_size(); i++) {
          jsonObj["payload"].push_back(payload[i]);
        }

        return jsonObj.dump();
      }

  };

};
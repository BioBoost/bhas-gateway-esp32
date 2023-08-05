#pragma once

#include <stdint.h>
#include <stddef.h>

namespace BHAS::Communication {

  class Message {

    public:
      enum class Type : uint8_t {
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

    public:
      Message();
      Message(uint8_t sourceId, uint8_t destinationId, uint8_t entityId, Message::Type type);

    public:
      void source_id(uint8_t id);
      void destination_id(uint8_t id);
      void entity_id(uint8_t id);
      void type(Message::Type type);
      void payload(const uint8_t * payload, size_t size);

    public:
      uint8_t source_id() const;
      uint8_t destination_id() const;
      uint8_t entity_id() const;
      Message::Type type() const;
      const uint8_t * payload() const;
      size_t payload_size() const;

    private:
      uint8_t _sourceId = 0;
      uint8_t _destinationId = 0;
      uint8_t _entityId = 0;
      Message::Type _type = Message::Type::NONE;

      static const size_t MAX_PAYLOAD_SIZE = 5;     // TODO: CAN property ! Should not be dependency here !

      uint8_t _payload[MAX_PAYLOAD_SIZE] = { 0 };
      size_t _payloadSize = 0;

  };

};
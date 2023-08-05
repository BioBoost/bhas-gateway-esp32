#include "message.h"
#include <cstring>

namespace BHAS::Communication {

  Message::Message() { }

  Message::Message(uint8_t sourceId, uint8_t destinationId, uint8_t entityId, Message::Type messageType) {
    source_id(sourceId);
    destination_id(destinationId);
    entity_id(entityId);
    type(messageType);
  }

  void Message::source_id(uint8_t id) {
    _sourceId = id;
  }

  void Message::destination_id(uint8_t id) {
    _destinationId = id;
  }

  void Message::entity_id(uint8_t id) {
    _entityId = id;
  }

  void Message::type(Message::Type type) {
    _type = type;
  }

  void Message::payload(const uint8_t * payload, size_t size) {
    memcpy(_payload, payload, size);
    _payloadSize = size;
  }

  uint8_t Message::source_id() const {
    return _sourceId;
  }

  uint8_t Message::destination_id() const {
    return _destinationId;
  }

  uint8_t Message::entity_id() const {
    return _entityId;
  }

  Message::Type Message::type() const {
    return _type;
  }

  const uint8_t * Message::payload() const {
    return _payload;
  }

  size_t Message::payload_size() const {
    return _payloadSize;
  }

};
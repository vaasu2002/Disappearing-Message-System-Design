#pragma once

#include <vector>
#include <optional>
#include "../Message.h"

namespace DMS {
    /*
    * @interface IMessageQueue
    * @brief Generic interface for a basic message queue
    * Can be used for any tyoe of queue (FIFO, priority, or any custom type)
    */
    class IMessageQueue {
    public:
        virtual ~IMessageQueue() = default;
        // Enqueue a single message
        virtual void publish(const Message& msg) = 0;

        // Enqueue multiple messages in a batch
        virtual void publishBatch(const std::vector<Message>& batch) = 0;

        // Dequeue a single message if available
        virtual std::optional<Message> comsume() = 0;

        // Dequeue a batch of messages(up to maxBatchSize)  if available
        virtual std::vector<Message> comsumeBatch(size_t maxBatchSize) = 0;

        // Returns the number of messages currently in the queue
        virtual size_t size() const = 0;

        // Shutdowns the queue gracefully.
        virtual void shutdown() = 0;
    };
}
# Disappearing Message System Design

The disappearing message feature ensures messages are automatically deleted after a specified time period (like WhatsApp's disappearing messages or Snapchat).

## Core Components
- **Delay Queue (Priority Queue)-**
  Maintains a time-ordered queue of messages scheduled for deletion, where the message with the earliest expiry time is always at the head.
- **Worker Threads Pool-**
  Continuously monitors the delay queue and executes message deletion tasks when their expiry time arrives.
- **Load Balancer-**
  Distributes incoming message deletion requests across multiple delay queue instances and ensures high availability.
- **Message Management Microservice-**
  Handles the core business logic of sending messages to delay queue and executing the actual message deletion from database.

### Delay Queue - Kafka-like Pattern
Here I will be trying to implement kafka like two-topic architecture. The delay queue which I will be making is just an abstraction built on top of a main queue. The job of delay queue is not to process anything but hold the message until their scheduled time and push them into main queue when delay is over. There will set of worker threads responsible for reading from delay queue and adding to main queue. There will be some worker threads reading from main queue too.
```
             ┌────────────────────────────────────────┐
┌──────────┐ |    ┌─────────────┐     ┌────────────┐  |  ┌──────────┐
│ Producer │─|───>│ Delay Queue │────>│ Main Queue │──|─>│ Consumer │
└──────────┘ |    └─────────────┘     └────────────┘  |  └──────────┘
             └────────────────────────────────────────┘
                         Virtual Delay Queue
```
| Component                        | Responsibility                                                                                             |
| -------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `Producer`                       | Pushes message into `DelayQueue`.                                                                          |
| `DelayQueue`                     | Holds messages until their expiration time is reached.                                                     |
| `DelayWorker`                    | Continuously checks the `DelayQueue`, and if expiration time is reached pushes the message to `MainQueue`. |
| `MainQueue`                      | Simple FIFO queue where messages are pushed.                                                               |
| `MainWorker`                     | Reads messages from the `MainQueue` and processes them.                                                    |

The delay queue system is composed of two primary components: the MainTopic static library and the DelayQueue service. The MainTopic library abstracts a message queue and provides a clean, thread-safe interface for publishing and consuming messages. It acts as the central message hub for downstream consumers and can be integrated into any service requiring access to the main message stream. The DelayQueue is a standalone service that manages messages intended for delayed delivery, internally organizing them based on expiration timestamps. It is monitored by one or more DelayWorker threads that continuously check for expired messages. Once a message reaches its expiration time, it is forwarded to the MainTopic through the static interface. This modular design promotes clean separation of concerns, easy testing, and future extensibility toward real-world inter-process or distributed messaging systems.




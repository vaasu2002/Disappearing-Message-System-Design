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

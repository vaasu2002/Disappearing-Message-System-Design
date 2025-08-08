#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "MessageUtility.h"

namespace DMS {
	/**
	* @class Message
	* @brief Represents a message with metadata
	*
	* @details
	* This class encapsulates all required information for a message.
	*/
	class Message {
		std::string uuid_; // Unique ID for this message
		std::string chatUUID_; // ID of the chat(might be group or personal) this message belongs to
		std::string content_; // Message content
		std::string sender_; // Sender Identifier
		std::chrono::system_clock::time_point expirationAt_; // Expiration time
		std::chrono::system_clock::time_point createdAt_; // Creation time
		std::chrono::system_clock::time_point updatedAt_; // Latest updated time
	public:
		Message() = default;
		Message(const std::string& chatUUID, const std::string& content,
			const std::string& sender, std::chrono::system_clock::time_point expirationAt)
			: uuid_(MessageUtils::generateUUID()), chatUUID_(chatUUID), content_(content), sender_(sender),
			expirationAt_(expirationAt) {

			createdAt_ = MessageUtils::now();
			updatedAt_ = createdAt_;
		}
		Message(const Message&) = default;
		Message& operator=(const Message&) = default;

		// Getters->
		const std::string& getUUID() const { return uuid_; }
		const std::string& getChatUUID() const { return chatUUID_; }
		const std::string& getContent() const { return content_; }
		const std::string& getSender() const { return sender_; }
		std::chrono::system_clock::time_point getCreatedAt() const { return createdAt_; }
		std::chrono::system_clock::time_point getUpdatedAt() const { return updatedAt_; }
		std::chrono::system_clock::time_point getExpirationAt() const { return expirationAt_; }

		// Setters->
		void setContent(const std::string& content) {
			content_ = content;
			updatedAt_ = MessageUtils::now();
		}
		void setExpirationAt(std::chrono::system_clock::time_point expiration) {
			expirationAt_ = expiration;
			updatedAt_ = MessageUtils::now();
		}

		/**
		 * @brief Serializes the message to a readable string.
		 * @return A string representation of the message for logging/debugging
		*/
		std::string toString() const {
			std::ostringstream oss;

			std::time_t expiration_time = std::chrono::system_clock::to_time_t(expirationAt_);

			oss << "Message[uuid=" << uuid_
				<< ", chatUUID=" << chatUUID_
				<< ", sender=" << sender_
				<< ", content=" << content_
				<< ", expired=" << (MessageUtils::isExpired(expirationAt_) ? "true" : "false")
				<< ", expirationAt=" << MessageUtils::formatTimestamp(expirationAt_)
				<< "]";

				return oss.str();
		}
	};
}
#endif // !MESSAGE_H
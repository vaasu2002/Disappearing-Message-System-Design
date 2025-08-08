#pragma once

#ifndef MESSAGE_UTILS_H
#define MESSAGE_UTILS_H

#include <string>
#include <chrono>
#include <random>
#include <iomanip>

// Disappearing Message System
namespace DMS {
	/**
	 * @class MessageUtils
	 * @brief Provides utility functions for the Message class.
	*/
	class MessageUtils {
	public:
		/**
		 * @brief Generates a new UUID (universally unique identifier).
		 * @return A string representing the UUID.
		 */
		static std::string generateUUID() {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::uniform_int_distribution<> dis(0, 15);
			static const char* hex_digits = "0123456789abcdef";

			std::stringstream ss;
			for (int i = 0; i < 32; ++i) {
				ss << hex_digits[dis(gen)];
				if (i == 7 || i == 11 || i == 15 || i == 19)
					ss << "-";
			}
			return ss.str();
		}

		/**
		 * @brief Converts a std::chrono::system_clock::time_point to a human-readable string.
		 * @param tp The time_point to format.
		 * @return A string representation in the format YYYY-MM-DD HH:MM:SS.
		 */
		static std::string formatTimestamp(const std::chrono::system_clock::time_point& tp) {
			std::time_t time = std::chrono::system_clock::to_time_t(tp);
			std::tm local_tm = *std::localtime(&time);

			std::ostringstream oss;
			oss << std::put_time(&local_tm, "%F %T"); // e.g., "2025-08-06 12:30:00"
			return oss.str();
		}

		/**
		 * @brief Gets the current system time as a time_point.
		 * @return The current time_point.
		 */
		static std::chrono::system_clock::time_point now() {
			return std::chrono::system_clock::now();
		}

		/**
		 * @brief Checks if the given expiration time is already passed.
		 * @param expirationAt The expiration time to check.
		 * @return True if expired, false otherwise.
		 */
		static bool isExpired(const std::chrono::system_clock::time_point& expirationAt) {
			return std::chrono::system_clock::now() > expirationAt;
		}
	};
}
#endif // !MESSAGE_UTILS_H
#include "DisappearMessagingSystem.h"

int main() {
	DMS::Message msg(
		"chatid_434", 
		"this is the message content",
		"this is the message content",
		DMS::MessageUtils::now()
	);
	std::cout<< msg.toString() << std::endl;
	return 0;
}
#pragma once
#include <string>
#include <vector>

#include <iostream>

class MessageStore
{
public:	
	bool ProcessInput(); // returns true when finished
	void Terminate();

private:
	void CreateUser();
	void SendMessage();
	void ReceiveAllMessagesForUser();


	bool Exists(std::string userToCheck);
	std::vector<std::string> users;

	struct Message {
		std::string sender;
		std::string receiver;
		std::string message;
	};
	std::vector<Message*> messages;
};

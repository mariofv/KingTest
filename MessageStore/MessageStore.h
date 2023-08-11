#pragma once
#include <string>
#include <vector>

#include <iostream>

using namespace std;

class MessageStore
{
public:	
	bool ProcessInput(); // returns true when finished
	void Terminate();

private:
	bool Exists(std::string userToCheck);
	std::vector<std::string> users;

	struct Message {
		std::string sender;
		std::string receiver;
		std::string message;
	};
	std::vector<Message*> messages;
};

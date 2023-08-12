#pragma once
#include <string>
#include <vector>
#include <map>

class MessageStore
{
public:	
	bool ProcessInput(); // returns true when finished
	void Terminate();

private:
	struct User 
	{
		User(unsigned int id, const std::string username) : id(id), username(username) {}

		unsigned int id;
		std::string username;
	};

	void CreateUser();
	void SendMessage();
	void ReceiveAllMessagesForUser();

	bool Exists(const std::string usernameToCheck) const;
	bool Exists(unsigned int userIdToCheck) const;

	User* GetUser(const std::string username) const;
	User* GetUser(unsigned int userId) const;

	struct Message
	{
		unsigned int senderId;
		unsigned int receiverId;
		std::string message;
	};

private:
	unsigned int currentId = 0;
	std::vector<User*> users;
	std::map<std::string, User*> usernameRegistry;

	std::vector<Message*> messages;
};

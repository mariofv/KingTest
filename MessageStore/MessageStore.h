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
		User(unsigned int p_Id, const std::string& p_Username) : m_Id(p_Id), m_Username(p_Username) {}

		unsigned int m_Id;
		std::string m_Username;
	};

	void CreateUser();
	void SendMessage();
	void ReceiveAllMessagesForUser();

	bool Exists(const std::string& p_UsernameToCheck) const;
	bool Exists(unsigned int p_UserIdToCheck) const;

	User* GetUser(const std::string& p_Username) const;
	User* GetUser(unsigned int p_UserId) const;

	struct Message
	{
		unsigned int m_SenderId;
		unsigned int m_ReceiverId;
		std::string m_Message;
	};

private:
	unsigned int m_CurrentId = 0;
	std::vector<User*> m_Users;
	std::map<std::string, User*> m_UsernameRegistry;

	std::vector<Message*> m_Messages;
};

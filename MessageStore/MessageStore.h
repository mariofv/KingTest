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
	struct Message
	{
		unsigned int m_SenderId = 0;
		unsigned int m_ReceiverId = 0;
		std::string m_Message;
	};

	struct User 
	{
		User(unsigned int p_Id, const std::string& p_Username) : m_Id(p_Id), m_Username(p_Username) {}

		~User()
		{
			for (unsigned int i = 0; i < m_Inbox.size(); ++i)
			{
				delete m_Inbox[i];
			}
		}

		unsigned int m_Id;
		std::string m_Username;
		std::vector<Message*> m_Inbox;
	};

	void CreateUser();
	void SendMessage();
	void ReceiveAllMessagesForUser();

	bool Exists(const std::string& p_UsernameToCheck) const;
	bool Exists(unsigned int p_UserIdToCheck) const;

	User* GetUser(const std::string& p_Username) const;
	User* GetUser(unsigned int p_UserId) const;

private:
	unsigned int m_CurrentId = 0;
	std::vector<User*> m_Users;
	std::map<std::string, User*> m_UsernameRegistry;
};

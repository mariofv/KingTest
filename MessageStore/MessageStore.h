#pragma once

#include <string>
#include <vector>
#include <map>
#include <ctime>

class MessageStore
{
public:	
	bool ProcessInput(); // Returns true when finished
	void Terminate();

private:
	struct Message
	{
		unsigned int m_SenderId = 0;
		unsigned int m_ReceiverId = 0;
		std::time_t m_Timestamp = 0;
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

			for (unsigned int i = 0; i < m_Sent.size(); ++i)
			{
				delete m_Sent[i];
			}
		}

		unsigned int m_Id;
		std::string m_Username;
		std::vector<Message*> m_Inbox;
		std::vector<Message*> m_Sent;
	};

	void CreateUser();
	void SendMessage();
	void ReceiveAllMessagesForUser();
	void ReportAllMessagesOfAllSenders() const;

	bool Exists(const std::string& p_UsernameToCheck) const;
	bool Exists(unsigned int p_UserIdToCheck) const;

	User* GetUser(const std::string& p_Username) const;
	User* GetUser(unsigned int p_UserId) const;

private:
	unsigned int m_CurrentId = 0;
	std::vector<User*> m_Users;
	std::map<std::string, User*> m_UsernameRegistry;
};

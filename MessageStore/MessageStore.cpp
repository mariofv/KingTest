#include "MessageStore.h"

#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

bool MessageStore::ProcessInput() 
{
	bool ret = false;

	// Clear screen
	for (unsigned int i = 0; i < 80; ++i)
	{
		cout << endl;
	}

	// Show options
	cout << "Please select an option:" << endl;
	cout << "1. Create User" << endl;
	cout << "2. Send Message" << endl;
	cout << "3. Receive All Messages For User" << endl;
	cout << "4. Report All Messages of All Senders" << endl;
	cout << "5. Quit" << endl;

	unsigned int option;
	cin >> option;
	if (cin.fail())
	{
		option = 0;
		cin.clear();
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	cout << endl;

	switch (option)
	{
	case 1:
		CreateUser();
		break;

	case 2:
		SendMessage();
		break;

	case 3:
		ReceiveAllMessagesForUser();
		break;

	case 4:
		ReportAllMessagesOfAllSenders();
		break;

	case 5:
		cout << "Quitting!" << endl;
		ret = true;
		break;

	default:
		cout << "Invalid Option Selected" << endl;
	}

	cout << endl <<"Enter any key and press return to continue.....";
	string anyKey;
	getline(cin, anyKey);
	return ret;
}


void MessageStore::CreateUser()
{
	cout << "Please enter name: ";
	string newUsername;
	getline(cin, newUsername);
	cout << endl;

	if (Exists(newUsername))
	{
		cout << "ERROR: User already exists!" << endl;
		return;
	}

	User* createdUser = new User(m_CurrentId++, newUsername);
	m_Users.push_back(createdUser);

	m_UsernameRegistry[newUsername] = createdUser;

	cout << "User " << newUsername << " added!" << endl;
}

void MessageStore::SendMessage()
{
	cout << "From: ";
	string senderUsername;
	getline(cin, senderUsername);
	cout << endl;

	if (!Exists(senderUsername))
	{
		cout << "ERROR: User doesn't exist!" << endl;
		return;
	}

	cout << "To: ";
	string receiverUsername;
	getline(cin, receiverUsername);
	cout << endl;

	if (!Exists(receiverUsername))
	{
		cout << "ERROR: User doesn't exist!" << endl;
		return;
	}

	cout << "Message: ";
	string messageText;
	getline(cin, messageText);

	User* sender = GetUser(senderUsername);
	User* receiver = GetUser(receiverUsername);

	Message* senderMessage = new Message();
	senderMessage->m_SenderId = sender->m_Id;
	senderMessage->m_ReceiverId = receiver->m_Id;
	senderMessage->m_Timestamp = time(0);
	senderMessage->m_Message = messageText;
	sender->m_Sent.push_back(senderMessage);

	Message* receiverMessage = new Message(*senderMessage);
	receiver->m_Inbox.push_back(receiverMessage);

	cout << endl;
	cout << "Message Sent!" << endl;
}

void MessageStore::ReceiveAllMessagesForUser()
{
	cout << "Enter name of user to receive all messages for: " << endl;
	string username;
	getline(cin, username);
	cout << endl;

	if (!Exists(username))
	{
		cout << "ERROR: User doesn't exist!" << endl;
		return;
	}

	User* user = GetUser(username);

	cout << endl << "===== BEGIN MESSAGES =====" << endl;

	for (unsigned int i = 0; i < user->m_Inbox.size(); ++i)
	{
		Message* message = user->m_Inbox[i];
		User* sender = GetUser(message->m_SenderId);

		cout << "Message " << i << endl;
		cout << "From: " << sender->m_Username << endl;
		cout << "Timestamp: " << message->m_Timestamp << endl;
		cout << "Content: " << message->m_Message << endl << endl;

		delete message;
	}
	user->m_Inbox.clear();

	cout << endl << "===== END MESSAGES =====" << endl;	
}

void MessageStore::ReportAllMessagesOfAllSenders() const
{
	for (unsigned int i = 0; i < m_Users.size(); ++i)
	{
		User* user = m_Users[i];
		if (user->m_Sent.empty())
		{
			continue;
		}

		cout << user->m_Username << " (" << user->m_Sent.size() << " messages):" << endl;

		for (unsigned int j = 0; j < user->m_Sent.size(); ++j)
		{
			Message* message = user->m_Sent[j];
			User* receiver = GetUser(message->m_ReceiverId);
			cout << '\t' << message->m_Timestamp << ", " << receiver->m_Username << endl;
		}
	}
}

void MessageStore::Terminate()
{
	for (unsigned int i = 0; i < m_Users.size(); ++i)
	{
		delete m_Users[i];
	}
}

bool MessageStore::Exists(const string& p_UsernameToCheck) const
{
	return m_UsernameRegistry.find(p_UsernameToCheck) != m_UsernameRegistry.end();
}

bool MessageStore::Exists(unsigned int p_UserIdToCheck) const
{
	return p_UserIdToCheck < m_Users.size() && m_Users[p_UserIdToCheck] != nullptr;
}

MessageStore::User* MessageStore::GetUser(const std::string& p_Username) const
{
	if (!Exists(p_Username))
	{
		throw runtime_error("A user with username " + p_Username + " doesn't exist!");
	}

	return m_UsernameRegistry.at(p_Username);
}

MessageStore::User* MessageStore::GetUser(unsigned int p_UserId) const
{
	if (!Exists(p_UserId))
	{
		throw runtime_error("A user with user id  " + to_string(p_UserId) + " doesn't exist!");
	}

	return m_Users[p_UserId];
}

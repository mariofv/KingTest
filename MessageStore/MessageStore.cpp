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
	cout << "4. Quit" << endl;

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

	User* createdUser = new User(currentId++, newUsername);
	users.push_back(createdUser);

	usernameRegistry[newUsername] = createdUser;

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

	Message* message = new Message;
	message->senderId = sender->id;
	message->receiverId = receiver->id;
	message->message = messageText;
	messages.push_back(message);

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
	int messageNumber = 0;
	bool areMessagesPending;
	do
	{
		areMessagesPending = false;
		for (unsigned int i = 0; i < messages.size(); ++i)
		{
			if (messages[i]->receiverId == user->id)
			{
				User* sender = GetUser(messages[i]->senderId);

				cout << "Message " << ++messageNumber << endl;
				cout << "From: " << sender->username << endl;
				cout << "Content: " << messages[i]->message << endl << endl;
				delete messages[i];
				messages.erase(messages.begin() + i);
				areMessagesPending = true;
				break;
			}
		}
	} while (areMessagesPending);

	cout << endl << "===== END MESSAGES =====" << endl;	
}

void MessageStore::Terminate()
{
	for (unsigned int i = 0; i < users.size(); ++i)
	{
		delete users[i];
	}

	for (unsigned int i = 0; i < messages.size(); ++i)
	{
		delete messages[i];
	}
}

bool MessageStore::Exists(const string& usernameToCheck) const
{
	return usernameRegistry.find(usernameToCheck) != usernameRegistry.end();
}

bool MessageStore::Exists(unsigned int userIdToCheck) const
{
	return userIdToCheck < users.size() && users[userIdToCheck] != nullptr;
}

MessageStore::User* MessageStore::GetUser(const std::string& username) const
{
	if (!Exists(username))
	{
		throw runtime_error("A user with username " + username + " doesn't exist!");
	}

	return usernameRegistry.at(username);
}

MessageStore::User* MessageStore::GetUser(unsigned int userId) const
{
	if (!Exists(userId))
	{
		throw runtime_error("A user with user id  " + to_string(userId) + " doesn't exist!");
	}

	return users[userId];
}

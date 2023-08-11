
#include "MessageStore.h"

bool MessageStore::ProcessInput() 
{
	bool ret = false;

	// Clear screen
	for (int i = 0; i < 80; ++i)
	{
		cout << endl;
	}

	// Show options
	cout << "Please select an option:" << endl;
	cout << "1. Create User" << endl;
	cout << "2. Send Message" << endl;
	cout << "3. Receive All Messages For User" << endl;
	cout << "4. Quit" << endl;

	std::string option;
	std::getline(std::cin, option);
	cout << endl;

	if (option == "1")
	{
		CreateUser();
	}
	else if (option == "2")
	{
		SendMessage();
	} 
	else if (option == "3") 
	{
		ReceiveAllMessagesForUser();
	} 
	else if (option == "4") 
	{
		cout << "Quitting!" << endl;
		ret = true;
	}
	else
	{
		cout << "Invalid Option Selected" << endl;
	}

	cout << endl <<"Enter any key and press return to continue.....";
	std::string anyKey;
	std::getline(std::cin, anyKey);
	return ret;
}


void MessageStore::CreateUser()
{
	cout << "Please enter name: ";
	std::string newUserName;
	std::getline(std::cin, newUserName);
	cout << endl;

	if (Exists(newUserName))
	{
		cout << "ERROR: User already exists!" << endl;
	}
	else
	{
		users.push_back(newUserName);
		cout << "User " << newUserName << " added!" << endl;
	}
}

void MessageStore::SendMessage()
{
	cout << "From: ";
	std::string sender;
	std::getline(std::cin, sender);
	cout << endl;

	if (Exists(sender) == false)
	{
		cout << "ERROR: User doesn't exist!" << endl;
	}
	else
	{
		cout << "To: ";
		std::string receiver;
		std::getline(std::cin, receiver);
		cout << endl;
		if (Exists(receiver) == false)
		{
			cout << "ERROR: User doesn't exist!" << endl;
		}
		else
		{
			cout << "Message: ";
			std::string messageText;
			std::getline(std::cin, messageText);
			cout << endl;
			cout << "Message Sent!" << endl;

			Message* message = new Message;
			message->sender = sender;
			message->receiver = receiver;
			message->message = messageText;
			messages.push_back(message);
		}
	}
}

void MessageStore::ReceiveAllMessagesForUser()
{
	cout << "Enter name of user to receive all messages for: " << endl;
	std::string user;
	std::getline(std::cin, user);
	cout << endl;

	if (Exists(user) == true)
	{
		cout << endl << "===== BEGIN MESSAGES =====" << endl;
		int messageNumber = 0;
		bool areMessagesPending;
		do
		{
			areMessagesPending = false;
			for (unsigned int i = 0; i < messages.size(); ++i)
			{
				if (messages[i]->receiver == user) {
					cout << "Message " << ++messageNumber << endl;
					cout << "From: " << messages[i]->sender << endl;
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
	else
	{
		cout << "ERROR: User doesn't exist!" << endl;
	}
}

void MessageStore::Terminate()
{
	for (unsigned int i = 0; i < messages.size(); ++i)
	{
		delete messages[i];
	}
}

bool MessageStore::Exists(std::string userToCheck)
{
	for (unsigned int i = 0; i < users.size(); ++i)
	{
		if (users[i] == userToCheck)
		{
			return true;
		}
	}
	return false;
}

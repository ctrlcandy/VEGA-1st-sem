﻿#include "contactManager.h"
#include "vector.h"

#include <iostream>
#include<limits>



void menu()
{
	Vector<Contact>* vector = createVector<Contact>();

	std::cout << "List of available commands :" << std::endl
		<< "1. Create contact" << std::endl
		<< "2. Delete contact" << std::endl
		<< "3. Edit contact" << std::endl
		<< "4. Show contact(s)" << std::endl
		<< "5. Exit" << std::endl;

	int command;
	while (true)
	{
		std::cout << "Main menu command: ";
		std::cin >> command;

		switch (command)
		{
		case 1:
			addContact(vector);
			break;
		case 2:
			deleteContact(vector);
			break;
		case 3:
			editContact(vector);
			break;
		case 4:
			showContacts(vector);
			break;
		case 5:
			return;
		default:
			std::cout << "Enter correct number to run command" << std::endl;

			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());

			break;
		}
	}
}

Contact createContact()
{
	std::cout << "Contact creation" << std::endl;
	Contact c;

	std::cout << "Enter name: " << std::endl;
	std::cin.ignore();
	std::cin.getline(c.name, 80);


	std::cout << "Enter phone number: " << std::endl;
	std::cin >> c.phone;

	std::cout << "Enter group: " << std::endl
		<< "1. NO_GROUP" << std::endl
		<< "2. FAMILY" << std::endl
		<< "3. FRIENDS" << std::endl
		<< "4. COLLEAGUES" << std::endl;
	std::cin >> c.group;

	if (c.group != 2 && c.group != 3 && c.group != 4) {
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());

		c.group = NO_GROUP;
	}

	return c;
}

template <typename Contact>
void addContact(Vector<Contact>* v)
{
	Contact c = createContact();
	append(v, c);
}

template <typename Contact>
void deleteContact(Vector<Contact>* vector)
{
	std::cout << "Enter name: " << std::endl;
	char name[80];
	std::cin.ignore();
	std::cin.getline(name, 80);

	for (size_t i = 0; i < getSize(vector); i++)
	{
		if (strcmp(vector->data[i].name, name) == 0) {
			erase(vector, i);
			return;
		}
	}
	std::cout << "No such name found" << std::endl;
}

template <typename Contact>
void editContact(Vector<Contact>* vector)
{
	std::cout << "Edit contact" << std::endl;
	std::cout << "Enter name : " << std::endl;
	char name[80];
	std::cin.ignore();
	std::cin.getline(name, 80);

	for (size_t i = 0; i < getSize(vector); i++)
	{
		if (strcmp(vector->data[i].name, name) == 0) {
			int command;

			std::cout << "Edit contact field" << std::endl
				<< "1. Edit name" << std::endl
				<< "2. Edit phone number" << std::endl
				<< "3. Edit group" << std::endl
				<< "4. Back" << std::endl;

			while (true)
			{
				std::cout << "Command: " << std::endl;
				std::cin >> command;

				switch (command)
				{
				case 1:
					std::cout << "Enter new name : " << std::endl;
					char newName[80];
					std::cin.ignore();
					std::cin.getline(newName, 80);

					strcpy_s(vector->data[i].name, newName);
					return;
				case 2:
					std::cout << "Enter new phone number : " << std::endl;
					char newPhone[12];
					std::cin >> newPhone;

					strcpy_s(vector->data[i].phone, newPhone);
					return;
				case 3:
					std::cout << "Enter new group : " << std::endl
						<< "1. NO_GROUP" << std::endl
						<< "2. FAMILY" << std::endl
						<< "3. FRIENDS" << std::endl
						<< "4. COLLEAGUES" << std::endl;

					int newGroup;
					std::cin >> newGroup;

					if (newGroup == 2)
						vector->data[i].group = FAMILY;
					else if (newGroup == 3)
						vector->data[i].group = FRIENDS;
					else if (newGroup == 4)
						vector->data[i].group = COLLEAGUES;
					else
						vector->data[i].group = NO_GROUP;

					return;
				case 4:
					return;
				default:
					std::cout << "Enter correct number to run command" << std::endl;
				}
			}
		}
	}
	std::cout << "No such name found" << std::endl;
}

template <typename Contact>
void showContacts(Vector<Contact>* vector)
{
	std::cout << "Print contact(s):" << std::endl
		<< "1. By name" << std::endl
		<< "2. By phone number" << std::endl
		<< "3. By group" << std::endl
		<< "4. All contacts" << std::endl
		<< "5. Back" << std::endl;

	int command;
	std::cin >> command;

	while (true)
	{
		switch (command)
		{
		case 1:
			char name[80];
			std::cin.ignore();
			std::cin.getline(name, 80);

			for (size_t i = 0; i < getSize(vector); i++)
				if (strcmp(vector->data[i].name, name) == 0) {
					printContact(vector, vector->data[i], i);
					return;
				}
				else
					std::cout << "No such name found" << std::endl;

			return;
		case 2:
			char phone[12];
			std::cin >> phone;

			for (size_t i = 0; i < getSize(vector); i++)
				if (strcmp(vector->data[i].phone, phone) == 0) {
					printContact(vector, vector->data[i], i);
					return;
				}
				else
					std::cout << "No such phone found" << std::endl;

			return;
		case 3:
			std::cout << "Enter group : " << std::endl
				<< "1. NO_GROUP" << std::endl
				<< "2. FAMILY" << std::endl
				<< "3. FRIENDS" << std::endl
				<< "4. COLLEAGUES" << std::endl;

			int group;
			std::cin >> group;

			if (group != 1 && group != 2 && group != 3 && group != 4)
				std::cout << "Enter correct number to run command" << std::endl;
			else {
				for (size_t i = 0; i < getSize(vector); i++)
				{
					if (vector->data[i].group == group)
						printContact(vector, vector->data[i], i);
				}
			}

			return;
		case 4:
			for (size_t i = 0; i < getSize(vector); i++)
				printContact(vector, vector->data[i], i);
			return;
		case 5:
			return;
		default:
			std::cout << "Enter correct number to run command" << std::endl;
		}
	}
}

template <typename Contact>
void printContact(Vector<Contact>* v, Contact data, size_t i)
{
	std::cout << "*" << " [";
	switch (v->data[i].group)
	{
	case NO_GROUP:
		std::cout << "NO_GROUP";
		break;
	case FAMILY:
		std::cout << "FAMILY";
		break;
	case FRIENDS:
		std::cout << "FRIENDS";
		break;
	case COLLEAGUES:
		std::cout << "COLLEAGUES";
		break;
	}
	std::cout << "] " << v->data[i].name << " --- " << v->data[i].phone << std::endl;
}
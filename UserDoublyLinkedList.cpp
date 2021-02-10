/*
 * UserDoublyLinkedList.cpp
 *
 *  Created on: 25 Kas 2020
 *      Author: Beyza
 */

#include "UserDoublyLinkedList.h"

UserDoublyLinkedList::UserDoublyLinkedList()
{
	headUser = NULL;
}

// insert the given user to the library system
void UserDoublyLinkedList::insertUser(User& user)
{
	if (headUser == NULL) {
		struct nodeUser* node = new nodeUser;
		node->data = user;
		node->next = node->prev = node;
		headUser = node;
		return;
	}

	else if (headUser->data.getUserId() == -1) {
		headUser->data = user;
		return;
	}

	else {
		nodeUser* last = headUser->prev;
		struct nodeUser* node = new nodeUser;
		node->data = user;
		node->next = headUser;
		node->prev = last;
		headUser->prev = last->next = node;
	}
}

// find the user id which equals to given id and delete the user that has the given
// id from the library system
void UserDoublyLinkedList::deleteUser(int userId)
{
	if (headUser == NULL) {
		return;
	}
	else {
		struct nodeUser* temp;
		temp = headUser;
		if (temp->data.getUserId() == userId) {
			nodeUser* pr = temp->prev;
			pr->next = temp->next;
			nodeUser* nx = temp->next;
			nx->prev = temp->prev;
			if (temp->next == temp) {
				headUser = temp;
				temp->data.setUserId(-1);
				temp->data.setUserName("empty");
				temp->data.getCheckedOut().deleteAll();
			}
			else {
				headUser = temp->next;
				temp->data.getCheckedOut().deleteAll();
				delete temp;
			}
			return;
		}
		while (temp->next != headUser)
		{
			if (temp->data.getUserId() == userId) {
				nodeUser* pr = temp->prev;
				pr->next = temp->next;
				nodeUser* nx = temp->next;
				nx->prev = temp->prev;
				temp->data.getCheckedOut().deleteAll();
				delete temp;
				return;
			}
			temp = temp->next;
			if (temp->next == headUser) {
				if (temp->data.getUserId() == userId) {
					nodeUser* pr = temp->prev;
					pr->next = temp->next;
					nodeUser* nx = temp->next;
					nx->prev = temp->prev;
					temp->data.getCheckedOut().deleteAll();
					delete temp;
					return;
				}
			}
		}
	}
}

// check the user exists
bool UserDoublyLinkedList::searchUser(int userId)
{
	struct nodeUser* temp = headUser;
	if (headUser == NULL) {
		return false;
	}
	if (headUser->data.getUserId() == -1) {
		return false;
	}
	if (temp->next == headUser) {
		if (temp->data.getUserId() == userId) {
			return true;
		}
		return false;
	}
	while (temp->next != headUser) {
		if (temp->data.getUserId() == userId) {
			return true;
		}
		temp = temp->next;
		if (temp->next == headUser) {
			if (temp->data.getUserId() == userId) {
				return true;
			}
			return false;
		}
	}
	return false;
}

// display all movies in the library
void UserDoublyLinkedList::displayAllMovie(std::fstream& output)
{
	struct nodeUser* temp = headUser;
	if (headUser == NULL) {
		return;
	}
	while (temp->next != headUser) {
		temp->data.getCheckedOut().displayMovieWithUserId(temp->data.getUserId(), output);
		temp = temp->next;
		if (temp->next == headUser) {
			temp->data.getCheckedOut().displayMovieWithUserId(temp->data.getUserId(), output);
			return;
		}
	}
	if (temp->next == headUser && temp->data.getUserId() != -1) {
		temp->data.getCheckedOut().displayMovieWithUserId(temp->data.getUserId(), output);
		return;
	}
}


// display the user that has the given id
void UserDoublyLinkedList::displayUser(int userId, std::fstream& output)
{
	struct nodeUser* temp = headUser;
	if (headUser == NULL) {
		return;
	}
	if (headUser->data.getUserId() == -1) {
		return;
	}
	if (temp->next == headUser) {
		if (temp->data.getUserId() == userId) {
			output << "User id: " << temp->data.getUserId() << " " << "User name: " << temp->data.getUserName() << std::endl;
			output << "User " << temp->data.getUserId() << " checked out the following movies:" << std::endl;
			temp->data.getCheckedOut().displayMovie(output);
		}
		return;
	}
	while (temp->next != headUser) {
		if (temp->data.getUserId() == userId) {
			output << "User id: " << temp->data.getUserId() << " " << "User name: " << temp->data.getUserName() << std::endl;
			output << "User " << temp->data.getUserId() << " checked out the following movies:" << std::endl;
			temp->data.getCheckedOut().displayMovie(output);
			return;
		}
		temp = temp->next;
		if (temp->next == headUser) {
			if (temp->data.getUserId() == userId) {
				output << "User id: " << temp->data.getUserId() << " " << "User name: " << temp->data.getUserName() << std::endl;
				output << "User " << temp->data.getUserId() << " checked out the following movies:" << std::endl;
				temp->data.getCheckedOut().displayMovie(output);
				return;
			}
		}
	}
}

// search for the movie that has the given id and return the id of the user that owns the
// specified movie
int UserDoublyLinkedList::checkEveryUserList(int movieId)
{
	User user;
	int userId = -1;
	struct nodeUser* temp = headUser;
	if (headUser == NULL || headUser->data.getUserId() == -1) {
		return userId;
	}
	else {
		if (temp->data.getCheckedOut().searchMovie(movieId)) {
			userId = temp->data.getUserId();
		}
		while (temp->next != headUser) {
			if (temp->data.getCheckedOut().searchMovie(movieId)) {
				userId = temp->data.getUserId();
			}
			temp = temp->next;
			if (temp->data.getCheckedOut().searchMovie(movieId)) {
				userId = temp->data.getUserId();
			}
		}
	}
	return userId;
}

// get the user which has the given user id if it exists
User* UserDoublyLinkedList::getUser(int userId)
{
	struct nodeUser* temp = headUser;
	if (headUser == NULL || headUser->data.getUserId() == -1) {
		return &headUser->data;
	}
	else {
		while (temp->next != headUser) {
			if (temp->data.getUserId() == userId) {
				return &temp->data;
			}
			temp = temp->next;
			if (temp->data.getUserId() == userId) {
				return &temp->data;
			}
		}
		return &headUser->data;
	}
}






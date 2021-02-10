/*
 * User.h
 *
 *  Created on: 24 Kas 2020
 *      Author: Beyza
 */

#ifndef USER_H_
#define USER_H_

#pragma once
#include <string>
#include "MovieDoublyLinkedList.h"

class User {
	private:
		int userId = -1;
		std::string userName;
		//MovieDoublyLinkedList checkedOut;
	public:
		MovieDoublyLinkedList checkedOut;
		// constructor
		User(int id, std::string name);
		User();

		// setters
		void setUserId(int id) { userId = id; }
		void setUserName(std::string name) { userName = name; }

		// getters
		int getUserId() { return userId; }
		std::string getUserName() { return userName; }
		MovieDoublyLinkedList& getCheckedOut() { return this->checkedOut; }
};



#endif /* USER_H_ */

/*
 * UserDoublyLinkedList.h
 *
 *  Created on: 25 Kas 2020
 *      Author: Beyza
 */

#ifndef USERDOUBLYLINKEDLIST_H_
#define USERDOUBLYLINKEDLIST_H_

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "User.h"
struct nodeUser {
    User data;
    struct nodeUser* next; // Pointer to next node
    struct nodeUser* prev; // Pointer to previous node
};


class UserDoublyLinkedList {
	nodeUser* headUser;
public:
    // constructor
    UserDoublyLinkedList();

    // functions
    void insertUser(User& user);
    void deleteUser(int userId);
    bool searchUser(int userId);
    void displayAllMovie(std::fstream& output);
    void displayUser(int userId, std::fstream& output);
    int checkEveryUserList(int movieId);
    User* getUser(int userId);
};




#endif /* USERDOUBLYLINKEDLIST_H_ */

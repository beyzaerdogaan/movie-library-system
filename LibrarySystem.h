/*
 * LibrarySystem.h
 *
 *  Created on: 25 Kas 2020
 *      Author: Beyza
 */

#ifndef LIBRARYSYSTEM_H_
#define LIBRARYSYSTEM_H_

#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "UserDoublyLinkedList.h"
#include "SinglyLinkedList.h"

class LibrarySystem {
public:
	LibrarySystem();
	LibrarySystem(std::string commandFile, std::string outputFile);
	~LibrarySystem();

	std::fstream input;
	std::fstream output;
	std::vector<std::string> command;
	std::vector<std::string> commandControl;
	UserDoublyLinkedList userList;
	SinglyLinkedList uncheckedMovies;

	// functions
	void addMovie(const int movieId, const std::string movieTitle, const int year);
	void deleteMovie(const int movieId);
	void addUser(const int userId, const std::string userName);
	void deleteUser(const int userId);
	void checkoutMovie(const int movieId, const int userId);
	void returnMovie(const int movieId);
	void showAllMovie();
	void showMovie(const int movieId);
	void showUser(const int userId);
};



#endif /* LIBRARYSYSTEM_H_ */

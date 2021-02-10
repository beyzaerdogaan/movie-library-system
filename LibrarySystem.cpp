/*
 * LibrarySystem.cpp
 *
 *  Created on: 25 Kas 2020
 *      Author: Beyza
 */

#include "LibrarySystem.h"
using namespace std;


LibrarySystem::LibrarySystem()
{
}

LibrarySystem::LibrarySystem(std::string commandFile, std::string outputFile)
{
	string line;
	input.open(commandFile, ios::in);
	output.open(outputFile, ios::out);
	output << "===Movie Library System===" << std::endl;
	if (getline(input, line)) {
		stringstream ss(line);
		string item;
		while(getline(ss, item, '\t')) {
			command.push_back(item);
		}
		output << "\n===" << command[0] << "()" << " method test===" << std::endl;
		command.clear();
	}
	input.close();
	input.open(commandFile, ios::in);
	while (getline(input, line)) {
		stringstream ss(line);
		string item;
		while(getline(ss, item, '\t')) {
			command.push_back(item);
		}
		if (!commandControl.empty()) {
			if (commandControl[0] != command[0]) {
				output << "\n===" << command[0] << "()" << " method test===" << std::endl;
			}
		}

		if (command[0] == "addMovie") {
			addMovie(stoi(command[1]), command[2], stoi(command[3]));
		}
		else if (command[0] == "deleteMovie") {
			deleteMovie(stoi(command[1]));
		}
		else if (command[0] == "addUser") {
			addUser(stoi(command[1]), command[2]);
		}
		else if (command[0] == "deleteUser") {
			deleteUser(stoi(command[1]));
		}
		else if (command[0] == "checkoutMovie") {
			checkoutMovie(stoi(command[1]), stoi(command[2]));
		}
		else if (command[0] == "showUser") {
			showUser(stoi(command[1]));
		}
		else if (command[0] == "showMovie") {
			showMovie(stoi(command[1]));
		}
		else if (command[0] == "showAllMovie") {
			showAllMovie();
		}
		else if (command[0] == "returnMovie") {
			returnMovie(stoi(command[1]));
		}
		if (!commandControl.empty()) {
			if (commandControl[0] != command[0]) {
				commandControl.clear();
			}
		}
		commandControl = command;
		command.clear();
	}
	input.close();
	output.close();
}

LibrarySystem::~LibrarySystem()
{
}

// addMovie method checks movies in the library and if movie does not exist, adds the specified
// movie to the library.
void LibrarySystem::addMovie(const int movieId, const string movieTitle, const int year)
{
	if (!uncheckedMovies.searchMovie(movieId) && userList.checkEveryUserList(movieId) == -1) {
		Movie movie(movieId, movieTitle, year);
		uncheckedMovies.insertMovie(movie);
		output << "Movie " << movieId << " has been added" << std::endl;
	}
	else {
		output << "Movie " << movieId << " already exists" << std::endl;
	}
}

// deleteMovie method checks movies in the library and if movie exists, deletes the specified
// movie from the library.
void LibrarySystem::deleteMovie(const int movieId)
{
	int userId = userList.checkEveryUserList(movieId);
	if (uncheckedMovies.searchMovie(movieId)) {
		output << "Movie " << movieId << " has not been checked out" << std::endl;
		uncheckedMovies.deleteMovie(movieId);
		output << "Movie " << movieId << " has been deleted" << std::endl;
	}
	else if (userId != -1) {
		User* u = userList.getUser(userId);
		output << "Movie " << movieId << " has been checked out" << std::endl;
		u->getCheckedOut().deleteMovie(movieId);
		output << "Movie " << movieId << " has been deleted" << std::endl;
	}
	else {
		output << "Movie " << movieId << " does not exist" << std::endl;
	}
}

// addUser method checks if an user exists with inputted userId and if not, adds user to
// the library.
void LibrarySystem::addUser(const int userId, const std::string userName)
{
	if (!userList.searchUser(userId)) {
		User user(userId, userName);
		userList.insertUser(user);
		output << "User " << userId << " has been added" << std::endl;
	}
	else {
		output << "User " << userId << " already exists" << std::endl;
	}
}

// deleteUser method checks if an user exists with inputted userId and if exists, deletes the
// specified user from the library.
void LibrarySystem::deleteUser(const int userId)
{
	if (!userList.searchUser(userId)) {
		output << "User " << userId << " does not exist" << std::endl;
	}
	else {
		userList.deleteUser(userId);
		output << "User " << userId << " has been deleted" << std::endl;
	}
}

// checkoutMovie method checks if the user exists in the library and also checks if the movie
// exists in unchecked movies. Then it allows the user to check the specified movie
void LibrarySystem::checkoutMovie(const int movieId, const int userId)
{
	if (!uncheckedMovies.searchMovie(movieId)) {
		output << "Movie " << movieId << " does not exist for checkout" << std::endl;
	}
	else if (!userList.searchUser(userId)) {
		output << "User " << userId << " does not exist for checkout" << std::endl;
	}
	else {
		userList.getUser(userId)->getCheckedOut().insertMovie(uncheckedMovies.getMovie(movieId));
		uncheckedMovies.deleteMovie(movieId);
		output << "Movie " << movieId << " has been checked out by User " << userId << std::endl;
	}
}

// returnMovie method checks that if the movie is checked or not and if the movie is checked,
// deletes the movie from user's movie list and adds it back to the library.
void LibrarySystem::returnMovie(const int movieId)
{
	if (uncheckedMovies.searchMovie(movieId)) {
		output << "Movie " << movieId << " has not been checked out" << std::endl;
	}

	else if (userList.checkEveryUserList(movieId) != -1) {
		int userId = userList.checkEveryUserList(movieId);
		User* u = userList.getUser(userId);
		Movie* m = u->getCheckedOut().getMovie(movieId);
		uncheckedMovies.insertMovie(*m);
		u->getCheckedOut().deleteMovie(movieId);
		output << "Movie " << movieId << " has been returned" << std::endl;
	}

	else {
		output << "Movie " << movieId << " not exist in the library" << std::endl;
	}
}

// showAllMovie method shows all unchecked and checked movies in the library. It also shows
// the information of if it's checked or who checked it.
void LibrarySystem::showAllMovie()
{
	output << "Movie id - Movie name - Year - Status" << std::endl;
	uncheckedMovies.displayMovie(output);
	userList.displayAllMovie(output);
}

// showMovie method shows all of the information about the specified movie.
void LibrarySystem::showMovie(const int movieId)
{
	if (uncheckedMovies.searchMovie(movieId)) {
		output << uncheckedMovies.getMovie(movieId).getMovieId() << " "
				<< uncheckedMovies.getMovie(movieId).getMovieTitle() << " " <<
				uncheckedMovies.getMovie(movieId).getMovieYear() <<
				" Not checked out"<< std::endl;
	}
	else if (userList.checkEveryUserList(movieId) != -1) {
		int userId = userList.checkEveryUserList(movieId);
		User* u = userList.getUser(userId);
		output << u->getCheckedOut().getMovie(movieId)->getMovieId() << " "
				<< u->getCheckedOut().getMovie(movieId)->getMovieTitle() << " "
				<< u->getCheckedOut().getMovie(movieId)->getMovieYear()
				<< " Checked out by User " << userId << std::endl;
	}
	else {
		output << "Movie with the id " << movieId << " does not exist" << std::endl;
	}
}

// showUser method shows all of the information about the specified user.
void LibrarySystem::showUser(const int userId)
{
	if (userList.searchUser(userId)) {
		userList.displayUser(userId, output);
	}
	else {
		output << "User " << userId << " does not exist" << std::endl;
	}
}


/*
 * MovieDoublyLinkedList.cpp
 *
 *  Created on: 23 Kas 2020
 *      Author: Beyza
 */

#include "MovieDoublyLinkedList.h"

MovieDoublyLinkedList::MovieDoublyLinkedList()
{
	head = NULL;
}

// insert the given movie to the library system
void MovieDoublyLinkedList::insertMovie(Movie movie)
{
	if (head == NULL) {
		struct nodeMovie* node = new nodeMovie;
		node->data = movie;
		node->next = node->prev = node;
		head = node;
		return;
	}

	else if (head->data.getMovieId() == -1) {
		head->data = movie;
		return;
	}

	else {
		nodeMovie* last = head->prev;
		struct nodeMovie* node = new nodeMovie;
		node->data = movie;
		node->next = head;
		node->prev = last;
		head->prev = last->next = node;
	}
}

// find the movie id which equals to given id and delete the movie that has the given id
// from the library system
void MovieDoublyLinkedList::deleteMovie(int movieId)
{
	if (head == NULL || head->data.getMovieId() == -1) {
		return;
	}
	else {
		struct nodeMovie* temp;
		temp = head;
		if (temp->data.getMovieId() == movieId) {
			nodeMovie* pr = temp->prev;
			pr->next = temp->next;
			nodeMovie* nx = temp->next;
			nx->prev = temp->prev;
			if (temp->next == temp) {
				head = temp;
				temp->data.setMovieId(-1);
				temp->data.setMovieTitle("empty");
				temp->data.setMovieYear(-1);
			}
			else {
				head = head->next;
				delete temp;
			}
			return;
		}
		while (temp->next != head)
		{
			if (temp->data.getMovieId() == movieId) {
				nodeMovie* pr = temp->prev;
				pr->next = temp->next;
				nodeMovie* nx = temp->next;
				nx->prev = temp->prev;
				delete temp;
				return;
			}
			temp = temp->next;
			if (temp->next == head) {
				if (temp->data.getMovieId() == movieId) {
					nodeMovie* pr = temp->prev;
					pr->next = temp->next;
					nodeMovie* nx = temp->next;
					nx->prev = temp->prev;
					delete temp;
					return;
				}
			}
		}
	}
}

// check the movie exists
bool MovieDoublyLinkedList::searchMovie(int movieId)
{
	struct nodeMovie* temp = head;
	if (head == NULL) {
		return false;
	}
	if (head->data.getMovieId() == -1) {
		return false;
	}
	if (temp->next == head) {
		if (temp->data.getMovieId() == movieId) {
			return true;
		}
		return false;
	}
	while (temp->next != head) {
		if (temp->data.getMovieId() == movieId) {
			return true;
		}
		temp = temp->next;
		if (temp->next == head) {
			if (temp->data.getMovieId() == movieId) {
				return true;
			}
			return false;
		}
	}
	return false;
}

// display all movies that owned by the user
void MovieDoublyLinkedList::displayMovie(std::fstream& output)
{
	struct nodeMovie* temp = head;
	if (head == NULL) {
		return;
	}
	output << "Movie id - Movie name - Year" << std::endl;
	while (temp->next != head) {
		output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " " << temp->data.getMovieYear() << std::endl;
		temp = temp->next;
		if (temp->next == head) {
			output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " " << temp->data.getMovieYear() << std::endl;
			return;
		}
	}
	if (temp->next == temp && temp->data.getMovieId() != -1) {
		output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " " << temp->data.getMovieYear() << std::endl;
		return;
	}
}

// display all movies that owned by the user with the user's information
void MovieDoublyLinkedList::displayMovieWithUserId(int userId, std::fstream& output)
{
	struct nodeMovie* temp = head;
	if (head == NULL) {
		return;
	}
	while (temp->next != head) {
		output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " "
				<< temp->data.getMovieYear() <<  " Checked out by User " << userId << std::endl;
		temp = temp->next;
		if (temp->next == head) {
			output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " "
					<< temp->data.getMovieYear() <<  " Checked out by User " << userId << std::endl;
			return;
		}
	}
	if (temp->next == temp && temp->data.getMovieId() != -1) {
		output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " "
				<< temp->data.getMovieYear() << " Checked out by User " << userId << std::endl;
		return;
	}
}

// get the movie which has the given movie id if it exists
Movie* MovieDoublyLinkedList::getMovie(int movieId)
{
	//Movie movie;
	struct nodeMovie* temp = head;
	if (head == NULL || head->data.getMovieId() == -1) {
		return &head->data;
	}
	else {
		while (temp->next != head) {
			if (temp->data.getMovieId() == movieId) {
				return &temp->data;
			}
			temp = temp->next;
			if (temp->data.getMovieId() == movieId) {
				return &temp->data;
			}
		}
		return &temp->data;
	}
}

// delete all movies that the user has from the system
void MovieDoublyLinkedList::deleteAll()
{
	if (head == NULL || head->data.getMovieId() == -1) {
		return;
	}
	else {
		struct nodeMovie* temp = head;
		while (temp->next != head) {
			temp = temp->next;
			deleteMovie(temp->data.getMovieId());
		}
		deleteMovie(head->data.getMovieId());
	}
}




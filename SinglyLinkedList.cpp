/*
 * SinglyLinkedList.cpp
 *
 *  Created on: 24 Kas 2020
 *      Author: Beyza
 */

#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList()
{
	head = NULL;
}

void SinglyLinkedList::insertMovie(Movie& movie)
{
	if (head == NULL) {
		struct nodeSingly* node = new nodeSingly;
		node->data = movie;
		node->next = node;
		head = node;
		return;
	}

	else if (head->data.getMovieId() == -1) {
		head->data = movie;
		return;
	}

	else {
		struct nodeSingly* temp = head;
		struct nodeSingly* last = new nodeSingly;
		struct nodeSingly* node = new nodeSingly;
		if (temp->next == head) {
			node->data = movie;
			node->next = head;
			head->next = node;
			delete last;
			return;
		}
		while (temp->next != head) {
			temp = temp->next;
			if (temp->next == head) {
				last = temp;
				node->data = movie;
				node->next = head;
				last->next = node;
				return;
			}
		}
	}
}


void SinglyLinkedList::deleteMovie(int movieId)
{
	if (head == NULL || head->data.getMovieId() == -1) { return; }

	else {
		if (head->next == head) {
			if (head->data.getMovieId() == movieId) {
				head->data.setMovieId(-1);
				head->data.setMovieTitle("empty");
				head->data.setMovieYear(-1);
			}
			else {
				return;
			}
		}
		else {
			struct nodeSingly* temp = head;
			if (temp->data.getMovieId() == movieId) {
				struct nodeSingly* temp2 = head;
				while (temp2->next != head) {
					temp2 = temp2->next;
					if (temp2->next == head) {
						temp2->next = head->next;
						head = temp2;
						delete temp;
						return;
					}
				}
			}
			else {
				struct nodeSingly* temp3 = head->next;
				struct nodeSingly* last = head;
				while (temp3->next != head) {
					if (temp3->data.getMovieId() == movieId) {
						last->next = temp3->next;
						delete temp3;
						return;
					}
					temp3 = temp3->next;
					last = last->next;
					if (temp3->next == head) {
						if (temp3->data.getMovieId() == movieId) {
							last->next = temp3->next;
							delete temp3;
							return;
						}
					}
				}
				if (temp3->next == head) {
					if (temp3->data.getMovieId() == movieId) {
						last->next = temp3->next;
						delete temp3;
						return;
					}
				}
			}
		}
	}
}


bool SinglyLinkedList::searchMovie(int movieId)
{
	struct nodeSingly* temp = head;
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


void SinglyLinkedList::displayMovie(std::fstream& output)
{
	struct nodeSingly* temp = head;
	if (head == NULL) {
		return;
	}
	while (temp->next != head) {
		output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " "
				<< temp->data.getMovieYear() << " Not checked out" << std::endl;
		temp = temp->next;
		if (temp->next == head) {
			output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " "
					<< temp->data.getMovieYear() << " Not checked out" << std::endl;
			return;
		}
	}
	if (temp->next == head && temp->data.getMovieId() != -1) {
		output << temp->data.getMovieId() << " " << temp->data.getMovieTitle() << " "
				<< temp->data.getMovieYear() << " Not checked out" << std::endl;
		return;
	}
}

int SinglyLinkedList::howManyMovie()
{
	int count = 1;
	struct nodeSingly* temp = head;
	if (head == NULL || head->data.getMovieId() == -1) {
		return 0;
	}
	else {
		while (temp->next != head) {
			count += 1;
			temp = temp->next;
		}
	}
	return count;
}

Movie SinglyLinkedList::getMovie(int movieId)
{
	struct nodeSingly* temp = head;
	Movie movie;
	if (head == NULL) {
		return movie;
	}
	if (head->data.getMovieId() == -1) {
		return movie;
	}
	if (temp->next == head) {
		if (temp->data.getMovieId() == movieId) {
			return temp->data;
		}
	}
	while (temp->next != head) {
		if (temp->data.getMovieId() == movieId) {
			return temp->data;
		}
		temp = temp->next;
		if (temp->next == head) {
			if (temp->data.getMovieId() == movieId) {
				return temp->data;
			}
		}
	}
	return movie;
}



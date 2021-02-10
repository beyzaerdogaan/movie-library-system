/*
 * SinglyLinkedList.h
 *
 *  Created on: 24 Kas 2020
 *      Author: Beyza
 */

#ifndef SINGLYLINKEDLIST_H_
#define SINGLYLINKEDLIST_H_

#include <iostream>
#include <string>
#include "Movie.h"
#include <fstream>
struct nodeSingly {
    Movie data;
    struct nodeSingly* next; // Pointer to next node
};


class SinglyLinkedList {
	nodeSingly* head;
public:
    // constructor
	SinglyLinkedList();

    // functions
    void insertMovie(Movie& movie);
    void deleteMovie(int movieId);
    bool searchMovie(int movieId);
    void displayMovie(std::fstream& output);
    int howManyMovie();
    Movie getMovie(int movieId);
};






#endif /* SINGLYLINKEDLIST_H_ */

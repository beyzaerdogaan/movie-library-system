/*
 * MovieDoublyLinkedList.h
 *
 *  Created on: 23 Kas 2020
 *      Author: Beyza
 */

#ifndef MOVIEDOUBLYLINKEDLIST_H_
#define MOVIEDOUBLYLINKEDLIST_H_

#pragma once
#include <iostream>
#include <string>
#include "Movie.h"
#include <fstream>
struct nodeMovie {
    Movie data;
    struct nodeMovie* next; // Pointer to next node
    struct nodeMovie* prev; // Pointer to previous node
};


class MovieDoublyLinkedList {
	nodeMovie* head;
public:
    // constructor
    MovieDoublyLinkedList();

    // functions
    void insertMovie(Movie movie);
    void deleteMovie(int movieId);
    bool searchMovie(int movieId);
    void displayMovie(std::fstream& output);
    void displayMovieWithUserId(int userId, std::fstream& output);
    Movie* getMovie(int movieId);
    void deleteAll();
};



#endif /* MOVIEDOUBLYLINKEDLIST_H_ */

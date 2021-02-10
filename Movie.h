/*
 * Movie.h
 *
 *  Created on: 23 Kas 2020
 *      Author: Beyza
 */

#pragma once
#include <string>

class Movie {
	private:
		int movieId = 0;
		std::string movieTitle;
		int movieYear = 0;
		int whoCheckedOut = 0;
	public:
		// constructor
		Movie(int id, std::string title, int year);
		Movie();

		// setters
		void setMovieId(int id) { movieId = id; }
		void setMovieTitle(std::string title) { movieTitle = title; }
		void setMovieYear(int year) { movieYear = year; }
		void setWhoCheckedOut(int userId) { whoCheckedOut = userId; }

		// getters
		int getMovieId() { return movieId; }
		std::string getMovieTitle() { return movieTitle; }
		int getMovieYear() { return movieYear; }
		int getWhoCheckedOut() { return whoCheckedOut; }
};



/*
 * Movie.cpp
 *
 *  Created on: 23 Kas 2020
 *      Author: Beyza
 */

#include "Movie.h"

Movie::Movie(int id, std::string title, int year)
{
	setMovieId(id);
	setMovieTitle(title);
	setMovieYear(year);
}

Movie::Movie() {}


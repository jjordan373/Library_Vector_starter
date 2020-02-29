#include "../includes_usr/fileIO.h"
#include "../includes_usr/constants.h"
using namespace std;
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */


int loadBooks(std::vector<book> &books, const char* filename)
{

	if (books.size() <= 0) {
			return NO_BOOKS_IN_LIBRARY;

	}

	string store = "";
	books.clear();
	ifstream file;
	file.open(filename);
	if (file.is_open() == false) {
		return COULD_NOT_OPEN_FILE;

	}


	while(getline(file, store)) {
		stringstream stream(store);
		string title, id, author, loan, state = "";
		getline(stream, id, ',');
		getline(stream, title, ',');
		getline(stream, author, ',');
		getline(stream, state, ',');
		getline(stream, loan, ',');
		book bk;
		bk.book_id = stoi(id, nullptr, 10);
		bk.title = title;
		bk.author = author;
		bk.state = static_cast<book_checkout_state>(stoi(state, nullptr, 10));
		bk.loaned_to_patron_id = stoi(loan, nullptr, 10);
		books.push_back(bk);

	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{

	if (books.size() <= 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	ofstream file;
	file.open(filename);
	if (file.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

	for (int i = 0; i <= books.size() - 1; i++) {
		file<<to_string(books[i].book_id)+","+books[i].title+","+books[i].author+","
				+to_string(books[i].state)+","+to_string(books[i].loaned_to_patron_id)+"\n";
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{

	patrons.clear();

	if (patrons.size() <= 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	string store = "";
	ifstream file;
	file.open(filename);
	if (file.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

	while (getline(file, store)) {
		stringstream stream(store);
		string id, name, books = "";
		patron pat;
		getline(stream, id, ',');
		getline(stream, name, ',');
		getline(stream, books, ',');
		pat.patron_id = stoi(id, nullptr, 10);
		pat.name = name;
		pat.number_books_checked_out = stoi(books, nullptr, 10);
		patrons.push_back(pat);

	}

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{

	if (patrons.size() <= 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	ofstream file;
	file.open(filename);
	if (file.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

	for (int i = 0; i <= patrons.size() - 1; i++) {
		file<<to_string(patrons[i].patron_id)+","+patrons[i].name
				+","+to_string(patrons[i].number_books_checked_out)+"\n";
	}

	return SUCCESS;
}

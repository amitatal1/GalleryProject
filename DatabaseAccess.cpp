#include "DatabaseAccess.h"
#include <io.h>

bool DatabaseAccess::open()
{


	std::string dbFileName = "galleryDB.sqlite";

	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (file_exist != 0)
	{
		createTables(db);
		return true;
	}



}

void DatabaseAccess::close()
{
	db = nullptr;
	sqlite3_close(db);
}

void DatabaseAccess::createTables()
{
	const char* sqlStatement = // creating users table
		"CREATE TABLE if not exists Users \
		(ID INTEGER PRIMARY\
		KEY AUTOINCREMENT NOT NULL,\
		NAME TEXT NOT NULl); ";

	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	std::cout << res;
	sqlStatement =
		"CREATE TABLE if not exists Albums (\
		(ID INTEGER PRIMARY\
		KEY AUTOINCREMENT NOT NULL,\
		NAME TEXT NOT NULl\
		CREATION_DATE DATETIME  NOT NULL\
		USER_ID integer not null\
		FOREIGN KEY (USER_ID)\
		REFERENCES Users(ID)); ";

	res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	std::cout << res;

	sqlStatement =
		"CREATE TABLE if not exists Pictures (\
		(ID INTEGER PRIMARY\
		KEY AUTOINCREMENT NOT NULL,\
		NAME TEXT NOT NULl\
		LOCATION TEXT NOT NULL\
		CREATION_DATE DATETIME  NOT NULL\
		ALBUM_ID integer not null\
		FOREIGN KEY (ALBUM_ID)\
		REFERENCES Albums(ID)); ";

	res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	std::cout << res;

	sqlStatement =
		"CREATE TABLE if not exists Pictures (\
		(ID INTEGER PRIMARY\
		KEY AUTOINCREMENT NOT NULL,\
		USER_ID integer NOT NULl\
		PICTURE_ID integer not null\
		FOREIGN KEY (ALBUM_ID)\
		REFERENCES Albums(ID)); ";

	res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	std::cout << res;
}

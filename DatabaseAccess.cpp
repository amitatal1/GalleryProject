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
		createTables();
		return true;
	}
    
}

void DatabaseAccess::close()
{
    sqlite3_close(db);
	db = nullptr;
}

const std::list<Album> DatabaseAccess::getAlbums()
{
    return std::list<Album>();
}

const std::list<Album> DatabaseAccess::getAlbumsOfUser(const User& user)
{
    return std::list<Album>();
}

void DatabaseAccess::createAlbum(const Album& album)
{
    
}


void DatabaseAccess::deleteAlbum(const std::string& albumName, int userId)
{
    std::string stringSql =
    "DELETE FROM Albums WHERE name = "+albumName+" and User_id =" + std::to_string(userId)+";";

    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

bool DatabaseAccess::doesAlbumExists(const std::string& albumName, int userId)
{
    return false;
}

Album DatabaseAccess::openAlbum(const std::string& albumName)
{
    return Album();
}

void DatabaseAccess::closeAlbum(Album& pAlbum)
{
}

void DatabaseAccess::printAlbums()
{
}

void DatabaseAccess::addPictureToAlbumByName(const std::string& albumName, const Picture& picture)
{
}

void DatabaseAccess::removePictureFromAlbumByName(const std::string& albumName, const std::string& pictureName)
{
    
}

void DatabaseAccess::tagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId)
{
    std::string stringSql =
        "INSERT INTO Tags (USER_ID, PICTURE_ID) "
        "SELECT "+std::to_string(userId)+ ", Pictures.ID FROM Pictures "
        "INNER JOIN Albums ON Pictures.ALBUM_ID = Albums.ID "
        "WHERE Albums.NAME = "+albumName+"  AND Pictures.NAME = "+ pictureName + "; ";

    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }

}

void DatabaseAccess::untagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId)
{
    std::string stringSql =
        "DELETE FROM Tags WHERE USER_ID = " + std::to_string(userId) + " AND PICTURE_ID IN "
        "(SELECT Pictures.ID FROM Pictures "
        "INNER JOIN Albums ON Pictures.ALBUM_ID = Albums.ID "
        "WHERE Albums.NAME = '" + albumName + "' AND Pictures.NAME = '" + pictureName + "');";


    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

void DatabaseAccess::printUsers()
{
}

User DatabaseAccess::getUser(int userId)
{
}

void DatabaseAccess::createUser(User& user)
{
    std::string stringSql =
        "INSERT INTO USERS (id,name) values("+std::to_string(user.getId())+","+user.getName() + ")"; // ,aybe you shoukd enter the id to the user and not the oppostie, bo awarew to that (past Amit)


    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

void DatabaseAccess::deleteUser(const User& user)
{

    std::string stringSql =
        "DELETE FROM USERS where id=" + std::to_string(user.getId()) + ";";


    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

bool DatabaseAccess::doesUserExists(int userId)
{
    return false;
}

int DatabaseAccess::countAlbumsOwnedOfUser(const User& user)
{
    return 0;
}

int DatabaseAccess::countAlbumsTaggedOfUser(const User& user)
{
    return 0;
}

int DatabaseAccess::countTagsOfUser(const User& user)
{
    return 0;
}

float DatabaseAccess::averageTagsPerAlbumOfUser(const User& user)
{
    return 0.0f;
}

User DatabaseAccess::getTopTaggedUser()
{
}

Picture DatabaseAccess::getTopTaggedPicture()
{
}

std::list<Picture> DatabaseAccess::getTaggedPicturesOfUser(const User& user)
{
    return std::list<Picture>();
}

void DatabaseAccess::createTables()
{
    const char* sqlStatement = // creating users table
        "CREATE TABLE if not exists Users \
        (ID INTEGER PRIMARY\
        KEY AUTOINCREMENT NOT NULL,\
        NAME TEXT NOT NULL); \
        \
        CREATE TABLE if not exists Albums (\
        ID INTEGER PRIMARY\
        KEY AUTOINCREMENT NOT NULL,\
        NAME TEXT NOT NULL,\
        CREATION_DATE DATETIME NOT NULL,\
        USER_ID INTEGER NOT NULL,\
        FOREIGN KEY (USER_ID)\
        REFERENCES Users(ID)); \
        \
        CREATE TABLE if not exists Pictures (\
        ID INTEGER PRIMARY\
        KEY AUTOINCREMENT NOT NULL,\
        NAME TEXT NOT NULL,\
        LOCATION TEXT NOT NULL,\
        CREATION_DATE DATETIME NOT NULL,\
        ALBUM_ID INTEGER NOT NULL,\
        FOREIGN KEY (ALBUM_ID)\
        REFERENCES Albums(ID)); \
        \
        CREATE TABLE if not exists Tags (\
        ID INTEGER PRIMARY\
        KEY AUTOINCREMENT NOT NULL,\
        USER_ID INTEGER NOT NULL,\
        PICTURE_ID INTEGER NOT NULL,\
        FOREIGN KEY (PICTURE_ID)\
        REFERENCES Pictures(ID)); ";

    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr,nullptr);
    
    if (res != SQLITE_OK) 
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}


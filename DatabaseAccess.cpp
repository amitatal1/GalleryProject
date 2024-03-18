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
    std::list<User> users;

    std::string stringSql =
        "select * from Users ;";

    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, callbackGetUser, &users, nullptr);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    auto iter = users.begin();
    std::cout << "User List:\n\n";
        

    while (iter != users.end())
    {
        std::cout << iter->getName() << " , "
            << iter->getId() << "\n";
        ++iter;
    }
}

User DatabaseAccess::getUser(int userId)
{
    User user(0,"");
    std::string stringSql =
        "select from Users where id=" + std::to_string(userId) + ";";
           
    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, callbackGetUser, &user, nullptr);
    if (res != SQLITE_OK) 
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
    return user;
}

void DatabaseAccess::createUser(User& user)
{
    std::string stringSql =
        "INSERT INTO USERS (id,name) values("+std::to_string(user.getId())+","+user.getName() + ")"; // maybe you shoukd enter the id to the user and not the oppostie, bo awarew to that (past Amit)


    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);
    if (res != SQLITE_OK) 
    {
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
    User user(0, "");
    std::string stringSql =
        " SELECT Users.ID, Users.NAME, COUNT(*) AS Tag_Count\
        FROM Users\
        JOIN Pictures ON Users.ID = Pictures.USER_ID\
        JOIN Tags ON Pictures.ID = Tags.PICTURE_ID\
        GROUP BY Users.ID\
        ORDER BY Tag_Count DESC\
        LIMIT 1;";

    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, callbackGetUser, &user, nullptr);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
  
}

Picture DatabaseAccess::getTopTaggedPicture()
{
    Picture pic(0, "");
    std::string stringSql =  " SELECT  p.*,\
        COUNT(*) AS Tag_Count\
        FROM\
        Pictures AS p\
        JOIN\
        Tags AS t ON p.ID = t.PICTURE_ID\
        GROUP BY\
        p.ID\
        ORDER BY\
        Tag_Count DESC\
        LIMIT 1;";



    const char* sqlStatement = stringSql.c_str();
    int res = sqlite3_exec(db, sqlStatement, callbackGetPicture, &pic, nullptr);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }


    //getting the tags' list
    stringSql = " SELECT * FROM TAGS WHERE PICTURE_ID=" + std::to_string(pic.getId()) + ";";


    const char* sqlStatement2 = stringSql.c_str();
    res = sqlite3_exec(db, sqlStatement2, callbackGetTagsList, &pic, nullptr);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    
    return pic;
         
}




int DatabaseAccess::callbackGetPicture(void* data, int argc, char** argv, char** azColName) 
{
    Picture* pic = static_cast<Picture*>(data);

    for (int i = 0; i < argc; i++)
    {
        if (std::string(azColName[i]) == "ID")
        {
            pic->setId(atoi(argv[i]));
        }
        else if (std::string(azColName[i]) == "NAME") 
        {
            pic->setName(std::string(argv[i]));
        }
        else if (std::string(azColName[i]) == "LOCATION")
        {
            pic->setPath(std::string(argv[i]));

        }
        else if (std::string(azColName[i]) == "CREATION_DATE")
        {
            pic->setCreationDate(std::string(argv[i]));
        }
    }


    

    return 0;
}

int DatabaseAccess::callbackGetTagsList(void* data, int argc, char** argv, char** azColName)
{
    Picture* pic = static_cast<Picture*>(data);

    for (int i = 0; i < argc; i++)
    {
        if (std::string(azColName[i]) == "USER_ID")
        {
            pic->tagUser(atoi(argv[i]));
        }
      
    }
    return 0;
}

std::list<Picture> DatabaseAccess::getTaggedPicturesOfUser(const User& user)
{
    return std::list<Picture>();
}

int DatabaseAccess::callbackGetUsersList(void* data, int argc, char** argv, char** azColName)
{
    std::list<User> * users = static_cast<std::list<User>*>(data);

    User user(0,"");
    for (int i = 0; i < argc; i++)
    {
        if (std::string(azColName[i]) == "ID")
        {
            user.setId(atoi(argv[i]));
        }
        else if (std::string(azColName[i]) == "NAME") {
            user.setName(argv[i]);
        }
    }
    users->push_back(user);
    return 0;

}



int DatabaseAccess::callbackGetUser(void* data, int argc, char** argv, char** azColName)
{
    User* user = static_cast<User*>(data);

    for (int i = 0; i < argc; i++)
    {
        if (std::string(azColName[i]) == "ID")
        {
            user->setId(atoi(argv[i]));
        }
        else if (std::string(azColName[i]) == "NAME") {
            user->setName(argv[i]);
        }
    }
    return 0;

}

void DatabaseAccess::createTables()
{
    const char* sqlStatement =
        "CREATE TABLE IF NOT EXISTS Users ( \
            ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
            NAME TEXT NOT NULL \
        ); \
        \
        CREATE TABLE IF NOT EXISTS Albums ( \
            ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
            NAME TEXT NOT NULL, \
            CREATION_DATE TEXT NOT NULL, \
            USER_ID INTEGER NOT NULL, \
            FOREIGN KEY (USER_ID) REFERENCES Users(ID) ON DELETE CASCADE \
        ); \
        \
        CREATE TABLE IF NOT EXISTS Pictures ( \
            ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
            NAME TEXT NOT NULL, \
            LOCATION TEXT NOT NULL, \
            CREATION_DATE TEXT NOT NULL, \
            ALBUM_ID INTEGER NOT NULL, \
            FOREIGN KEY (ALBUM_ID) REFERENCES Albums(ID) ON DELETE CASCADE \
        ); \
        \
        CREATE TABLE IF NOT EXISTS Tags ( \
            ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
            USER_ID INTEGER NOT NULL, \
            PICTURE_ID INTEGER NOT NULL, \
            FOREIGN KEY (PICTURE_ID) REFERENCES Pictures(ID) ON DELETE CASCADE \
        );";

    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, nullptr);

    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}


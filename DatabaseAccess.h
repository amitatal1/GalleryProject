#pragma once
#include "IDataAccess.h"
#include "sqlite3.h"
#include "Album.h"

class DatabaseAccess
	:public IDataAccess
{
public:
	virtual bool open() override;
	virtual void close() override ;
	virtual void clear() override {};

	// album related
	virtual const std::list<Album> getAlbums() override;
	virtual const std::list<Album> getAlbumsOfUser(const User& user) override;
	virtual void createAlbum(const Album& album) override;
	virtual void deleteAlbum(const std::string& albumName, int userId) override;
	virtual bool doesAlbumExists(const std::string& albumName, int userId) override;
	virtual Album openAlbum(const std::string& albumName) override;
	virtual void closeAlbum(Album& pAlbum) override;
	virtual void printAlbums() override;


    // picture related
	virtual void addPictureToAlbumByName(const std::string& albumName, const Picture& picture) override;
	virtual void removePictureFromAlbumByName(const std::string& albumName, const std::string& pictureName) override;
	virtual void tagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId) override;
	virtual void untagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId) override;

	// user related
	virtual void printUsers() override;
	virtual User getUser(int userId) override;
	virtual void createUser(User& user ) override;
	virtual void deleteUser(const User& user) override;
	virtual bool doesUserExists(int userId) override ;
	

	// user statistics
	virtual int countAlbumsOwnedOfUser(const User& user) override;
	virtual int countAlbumsTaggedOfUser(const User& user) override;
	virtual int countTagsOfUser(const User& user) override;
	virtual float averageTagsPerAlbumOfUser(const User& user) override;

	// queries
	virtual User getTopTaggedUser() override;
	virtual Picture getTopTaggedPicture() override;
	virtual std::list<Picture> getTaggedPicturesOfUser(const User& user) override;
	


	

private:

	//callback functions:
	static int callbackGetUsersList(void* data, int argc, char** argv, char** azColName);
	static int callbackGetUser(void* data, int argc, char** argv, char** azColName);
	static int callbackGetTagsList(void* data, int argc, char** argv, char** azColName);
	static int callbackGetAlbums(void* data, int argc, char** argv, char** azColName);
	static int callbackGetPicturesList(void* data, int argc, char** argv, char** azColName);

	static int exec_cmd(std::string cmd,void* data, int (*callback)(void*, int, char**, char**));


	void createTables();
	static sqlite3* db;
};
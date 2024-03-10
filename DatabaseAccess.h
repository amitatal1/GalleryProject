#pragma once
#include "IDataAccess.h"
#include "sqlite3.h"
class DatabaseAccess
	:public IDataAccess
{
public:
	virtual bool open() override;
	virtual void close() override ;
	virtual void clear() override {};
private:
	void createTables();
	sqlite3* db;
};
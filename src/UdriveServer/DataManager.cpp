#include "DataManager.h"


DataManager::DataManager() : path("./database"), columnFamilyHandler(3){
	Options options;
	options.create_if_missing = true;
	Status status = DB::Open(options, this->path, &this->database);
	if (status.ok()){
		database->CreateColumnFamily(ColumnFamilyOptions(), kDefaultColumnFamilyName, &this->columnFamilyHandler[0]);
		database->CreateColumnFamily(ColumnFamilyOptions(), "users", &this->columnFamilyHandler[1]);
		database->CreateColumnFamily(ColumnFamilyOptions(), "documents", &this->columnFamilyHandler[2]);
		for (ColumnFamilyHandle *columnFamiliy : this->columnFamilyHandler)
			delete columnFamiliy;
		delete this->database;
	}

	vector<ColumnFamilyDescriptor> columnFamiliesDescriptor;
	columnFamiliesDescriptor.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName, ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(ColumnFamilyDescriptor("users", ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(ColumnFamilyDescriptor("documents", ColumnFamilyOptions()));
	DB::Open(DBOptions(), this->path, columnFamiliesDescriptor, &this->columnFamilyHandler, &this->database);
}

DataManager::~DataManager(){
	for (ColumnFamilyHandle *columnFamiliy : this->columnFamilyHandler)
		delete columnFamiliy;
	delete this->database;
}

DataManager& DataManager::Instance(){
	static DataManager instance;
	return instance;
}

User * DataManager::getUser(const string& key){
	string value = "";
	this->database->Get(ReadOptions(), this->columnFamilyHandler[1], key, &value);
	if (value != "")
		return new User(value);
	else
		return NULL;
}

bool DataManager::saveUser(const User& user){
	string key = user.getUsername();
	string value = user.getJsonString();
	Status status = this->database->Put(WriteOptions(), this->columnFamilyHandler[1], key, value);
	return status.ok();
}


#include "DataManager.h"


DataManager::DataManager() : path("./database"), columnFamilyHandler(3){
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, this->path, &this->database);
	if (status.ok()){
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), rocksdb::kDefaultColumnFamilyName, &this->columnFamilyHandler[0]);
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "users", &this->columnFamilyHandler[1]);
		database->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "documents", &this->columnFamilyHandler[2]);
		for (rocksdb::ColumnFamilyHandle *columnFamiliy : this->columnFamilyHandler)
			delete columnFamiliy;
		delete this->database;
	}

	std::vector<rocksdb::ColumnFamilyDescriptor> columnFamiliesDescriptor;
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor(rocksdb::kDefaultColumnFamilyName, rocksdb::ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor("users", rocksdb::ColumnFamilyOptions()));
	columnFamiliesDescriptor.push_back(rocksdb::ColumnFamilyDescriptor("documents", rocksdb::ColumnFamilyOptions()));
	rocksdb::DB::Open(rocksdb::DBOptions(), this->path, columnFamiliesDescriptor, &this->columnFamilyHandler, &this->database);
}

DataManager::~DataManager(){
	for (rocksdb::ColumnFamilyHandle *columnFamiliy : this->columnFamilyHandler)
		delete columnFamiliy;
	delete this->database;
}

DataManager& DataManager::Instance(){
	static DataManager instance;
	return instance;
}

User * DataManager::getUser(const std::string& key){
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), this->columnFamilyHandler[1], key, &value);
	if (value != "")
		return new User(value);
	else
		return NULL;
}

bool DataManager::saveUser(const User& user){
	std::string key = user.getUsername();
	std::string value = user.getJsonString();
	rocksdb::Status status = this->database->Put(rocksdb::WriteOptions(), this->columnFamilyHandler[1], key, value);
	return status.ok();
}


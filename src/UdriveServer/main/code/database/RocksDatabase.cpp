#include "../../include/database/RocksDatabase.h"

RocksDatabase::RocksDatabase(){
	this->database = NULL;
}

RocksDatabase::RocksDatabase(const std::string& path): path(path){
	init();
}

void RocksDatabase::init(){
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, this->path, &this->database);
}

RocksDatabase::~RocksDatabase(){
	if (this->database != NULL){
		delete this->database;
	    this->database = NULL;
	}
}

std::string RocksDatabase::getValue(const std::string& key) const{
	std::string value = "";
	this->database->Get(rocksdb::ReadOptions(), key, &value);
	return value;
}

bool RocksDatabase::saveValue(const std::string& key, const std::string& value){
	batch.Put(key, value);
	rocksdb::Status status = this->database->Write(rocksdb::WriteOptions(),&batch);
	return status.ok();
}

void RocksDatabase::deleteRecord(const std::string& key){
	batch.Delete(key);
	this->database->Write(rocksdb::WriteOptions(), &batch);
}

std::vector<std::string> RocksDatabase::getAllValues() const{
	std::vector<std::string> vector;
	rocksdb::Iterator* iterator = this->database->NewIterator(rocksdb::ReadOptions());
	for (iterator->SeekToFirst(); iterator->Valid(); iterator->Next())
		vector.push_back(iterator->value().ToString());
	delete iterator;
	return vector;
}

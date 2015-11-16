#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/UpdateFileService.h"
#include "UpdateFileServiceFixture.h"

using ::testing::Return;
using ::testing::_;


TEST_F(UpdateFileServiceFixture,invalidUsername) {

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly((Return("")));

	std::string responseFromService = updateFileService->execute( username, token, "" , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );

}

TEST_F(UpdateFileServiceFixture,invalidToken) {
	userNotSavedInDb.setToken("555");
	std::string data2 = userNotSavedInDb.getJsonString();

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly(Return(data2));

	std::string responseFromService = updateFileService->execute( username, token, "" , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(UpdateFileServiceFixture,invalidFile) {
	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly(Return(dataUser));

	fileBuscado = new File(stringJsonFileChange,userDB);

	EXPECT_CALL(fileDB,getValue( _ ) )
				.WillOnce(Return(""));

	std::string responseFromService = updateFileService->execute( username, token, "" , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_INVALID_FILE );

	delete fileBuscado;
}

TEST_F(UpdateFileServiceFixture, permisonDenied) {
//TODO
}

TEST_F(UpdateFileServiceFixture, errorSavingData) {
//TODO
}

TEST_F(UpdateFileServiceFixture, updateFisicoOk) {

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly(Return(dataUser));

	fileBuscado = new File(stringJsonFileChange,userDB);

	EXPECT_CALL(fileDB,getValue( fileId ))
		.WillOnce(Return( fileBuscado->getJsonString() ));

	Json::StreamWriterBuilder builder;
	Json::Value jsonFileChange;
	jsonFileChange["data"]		= "CAMBIE EL CONTENIDO DEL ARCHIVO!!!";
	builder.settings_["indentation"] = "\t";
	std::string fileChange =  Json::writeString(builder,jsonFileChange);

	EXPECT_CALL(fileDB,saveValue( fileId , _ ))
					.WillOnce(Return( true ));

	std::stringstream convert;
	convert << (version+1);
	std::string versionAumentada = convert.str();

	EXPECT_CALL(dataDB,saveValue( fileId + "_" + versionAumentada , _ ))
					.WillOnce(Return( true ));

	EXPECT_CALL(userDB,saveValue( username , _ ))
					.WillOnce(Return( true ));

	std::string responseFromService = updateFileService->execute( username, token, fileChange , fileId );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	fileId , jsonData["data"]["id"].asCString()  );
	EXPECT_EQ(	fileName 	 , jsonData["data"]["name"].asCString()  );
	//EXPECT_EQ(	lastModified 	 , jsonData["data"]["lastModified"].asCString()  );
	EXPECT_EQ(	extension 	 , jsonData["data"]["extension"].asCString()  );
	EXPECT_EQ(	version+1 	 , jsonData["data"]["version"].asInt()  );

	delete fileBuscado;
}

TEST_F(UpdateFileServiceFixture, updateMetadatosOk) {

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly(Return(dataUser));

	//el otro usuario con el que vamos a compartir el file
	User otroUser(getJsonUser("julian","1234516","julian@fiuba.com"));
	EXPECT_CALL(userDB,getValue( "julian" ) )
		.WillRepeatedly(Return( otroUser.getJsonString() ));

	fileBuscado = new File(stringJsonFileChange,userDB);

	EXPECT_CALL(fileDB,getValue( fileId ))
		.WillOnce(Return( fileBuscado->getJsonString() ));

	Json::Value folderJson =getJsonFolder("sharedwith_" + otroUser.getUsername(),"compartida");
	Folder folder( folderJson );

	EXPECT_CALL(folderDB,getValue( "sharedwith_" + otroUser.getUsername() ))
		.WillOnce(Return( folder.getJsonString() ) );

	EXPECT_CALL(folderDB,saveValue( "sharedwith_" + otroUser.getUsername(), _ ))
		.WillOnce(Return( true ));


	Json::StreamWriterBuilder builder;
	Json::Value jsonFileChange;
	jsonFileChange["name"] 	 	= nuevoNombre;
	jsonFileChange["id"]		= fileId;
	jsonFileChange["extension"] = extension;
	jsonFileChange["owner"]		= username;
	jsonFileChange["lastUser"]	= username;
	jsonFileChange["deleted"]	= 0;

	Json::Value labels;
	labels["description"] = nuevaLabel;

	jsonFileChange["labels"].append(labels);

	Json::Value usuarios;
	usuarios["username"] = otroUser.getUsername();

	jsonFileChange["users"].append(usuarios);

	builder.settings_["indentation"] = "\t";
	std::string fileChange =  Json::writeString(builder,jsonFileChange);

	EXPECT_CALL(fileDB,saveValue( fileId , _ ))
					.WillOnce(Return( true ));

	std::cout << jsonFileChange << std::endl;

	std::string responseFromService = updateFileService->execute( username, token, fileChange , fileId );

	std::cout << responseFromService << std::endl;

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	fileId , jsonData["data"]["id"].asCString()  );
	EXPECT_EQ(	nuevoNombre	 , jsonData["data"]["name"].asCString()  );
	//EXPECT_EQ(	lastModified 	 , jsonData["data"]["lastModified"].asCString()  );
	EXPECT_EQ(	extension 	 , jsonData["data"]["extension"].asCString()  );
	EXPECT_EQ(	version 	 , jsonData["data"]["version"].asInt()  );
	EXPECT_EQ(	nuevaLabel 	 , jsonData["data"]["labels"][0]["description"].asCString()  );
	EXPECT_EQ(	otroUser.getUsername() 	 , jsonData["data"]["users"][0]["username"].asCString()  );
	EXPECT_EQ(	0	 , jsonData["data"]["deleted"].asInt()  );

	delete fileBuscado;
}

TEST_F(UpdateFileServiceFixture, sacarFileDeLaCarpetaTrash) {

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly(Return(dataUser));

	//el otro usuario con el que vamos a compartir el file
	User otroUser(getJsonUser("julian","1234516","julian@fiuba.com"));
	EXPECT_CALL(userDB,getValue( "julian" ) )
		.WillRepeatedly(Return( otroUser.getJsonString() ));

	Folder folderTrash(getJsonFolder("trash_" + username,"trashFolder"));
	EXPECT_CALL(folderDB,getValue( "trash_" + username ))
		.WillOnce(Return( folderTrash.getJsonString() ));
	EXPECT_CALL(folderDB,saveValue( "trash_" + username, _ ))
		.WillOnce(Return( true ));

	Folder folderTrash2(getJsonFolder("trash_" + otroUser.getUsername(),"trashFolder"));
	EXPECT_CALL(folderDB,getValue( "trash_" + otroUser.getUsername() ))
		.WillOnce(Return( folderTrash2.getJsonString() ));
	EXPECT_CALL(folderDB,saveValue( "trash_" + otroUser.getUsername(), _ ))
		.WillOnce(Return( true ));

	Folder folderRecovered1(getJsonFolder("recovered_" + username,"recoveredFolder"));
	EXPECT_CALL(folderDB,getValue( "recovered_" + username ))
		.WillOnce(Return( folderRecovered1.getJsonString() ));
	EXPECT_CALL(folderDB,saveValue( "recovered_"  + username, _ ))
		.WillOnce(Return( true ));

	Folder folderRecovered2(getJsonFolder("recovered_" + otroUser.getUsername(),"recoveredFolder"));
	EXPECT_CALL(folderDB,getValue( "recovered_" + otroUser.getUsername() ))
		.WillOnce(Return( folderRecovered2.getJsonString() ));
	EXPECT_CALL(folderDB,saveValue( "recovered_"  + otroUser.getUsername(), _ ))
		.WillOnce(Return( true ));

	//ESTE FILE ESTA BORRADO !! NOSOTROS lo queremos recuperar
	jsonFileData["deleted"]		= 1;
	Json::StreamWriterBuilder b;
	b.settings_["indentation"] = "\t";
	stringJsonFileChange =  Json::writeString(b,jsonFileData);

	fileBuscado = new File(stringJsonFileChange,userDB);
	EXPECT_CALL(fileDB,getValue( fileId ))
		.WillOnce(Return( fileBuscado->getJsonString() ));

	Json::Value folderJson =getJsonFolder("sharedwith_" + otroUser.getUsername(),"compartida");
	Folder folder( folderJson );
	EXPECT_CALL(folderDB,getValue( "sharedwith_" + otroUser.getUsername() ))
		.WillOnce(Return( folder.getJsonString() ) );
	EXPECT_CALL(folderDB,saveValue( "sharedwith_" + otroUser.getUsername(), _ ))
		.WillOnce(Return( true ));


	Json::StreamWriterBuilder builder;
	Json::Value jsonFileChange;
	jsonFileChange["name"] 	 	= nuevoNombre;
	jsonFileChange["id"]		= fileId;
	jsonFileChange["extension"] = extension;
	jsonFileChange["owner"]		= username;
	jsonFileChange["lastUser"]	= username;
	jsonFileChange["deleted"]	= 0;

	Json::Value labels;
	labels["description"] = nuevaLabel;

	jsonFileChange["labels"].append(labels);

	Json::Value usuarios;
	usuarios["username"] = otroUser.getUsername();

	jsonFileChange["users"].append(usuarios);

	builder.settings_["indentation"] = "\t";
	std::string fileChange =  Json::writeString(builder,jsonFileChange);

	EXPECT_CALL(fileDB,saveValue( fileId , _ ))
		.WillOnce(Return( true ));

	//std::cout << jsonFileChange << std::endl;

	std::string responseFromService = updateFileService->execute( username, token, fileChange , fileId );

	//std::cout << responseFromService << std::endl;

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	fileId , jsonData["data"]["id"].asCString()  );
	EXPECT_EQ(	nuevoNombre	 , jsonData["data"]["name"].asCString()  );
	//EXPECT_EQ(	lastModified 	 , jsonData["data"]["lastModified"].asCString()  );
	EXPECT_EQ(	extension 	 , jsonData["data"]["extension"].asCString()  );
	EXPECT_EQ(	version 	 , jsonData["data"]["version"].asInt()  );
	EXPECT_EQ(	nuevaLabel 	 , jsonData["data"]["labels"][0]["description"].asCString()  );
	EXPECT_EQ(	otroUser.getUsername() 	 , jsonData["data"]["users"][0]["username"].asCString()  );
	EXPECT_EQ(	0	 , jsonData["data"]["deleted"].asInt()  );

	delete fileBuscado;
}

TEST_F(UpdateFileServiceFixture, updateFisicoErrorSavingData) {
//TODO
}


TEST_F(UpdateFileServiceFixture, updateMetadatosErrorSavingData) {
//TODO
}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

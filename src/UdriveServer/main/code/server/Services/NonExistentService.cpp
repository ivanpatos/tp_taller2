#include "../../../include/server/Services/NonExistentService.h"
#include "../../../include/server/HttpResponse.h"


NonExistentService::NonExistentService(){
}

NonExistentService::~NonExistentService(){
}

const char* NonExistentService::name() const{
	return "NonExistentService";
}

std::string NonExistentService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	LOG(ERROR) << "Se solicito un servicio no existente, usuario: " + username + " token: " + token;
	return HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_REQUEST);
}

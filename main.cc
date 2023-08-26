#include <drogon/drogon.h>
#include <clickhouse/client.h>

using namespace drogon;

typedef std::function<void(const HttpResponsePtr &)> Callback;

auto create_response(Json::Value jsonBody, std::string status, std::string message, HttpStatusCode sc = HttpStatusCode::k400BadRequest) {
    jsonBody["status"] = status;
    jsonBody["message"] = message;

    auto response = HttpResponse::newHttpJsonResponse(jsonBody);
    if ( sc == HttpStatusCode::k400BadRequest ) { response->setStatusCode(sc); }
    
    return response;
}

void create_service(const HttpRequestPtr &request, Callback &&callback) {
    Json::Value jsonBody;
    
    auto requestBody = request->getJsonObject();

    if (requestBody == nullptr){callback(create_response(jsonBody, "error", "Not enouth data in request.")); return; }
    if (!requestBody-> isMember("service_name")){callback(create_response(jsonBody, "error", "no `service_name` in request.")); return; }
    if (!requestBody-> isMember("service_url")){callback(create_response(jsonBody, "error", "no `service_url` in request.")); return; }

    auto service_name = requestBody->get("service_name", "guest").asString();
    auto service_url = requestBody->get("service_url", "guest").asString();
    LOG_INFO << "Service with data { 'service_name': '" + service_name + "', 'service_url': '" + service_url + "' } has been created!";
    callback(create_response(jsonBody, "success", "Service has been created!"));
    return;
}

void login_at_service(const HttpRequestPtr &request, Callback &&callback) {
    Json::Value jsonBody;

    auto requestBody = request->getJsonObject();

    if (requestBody == nullptr) {callback(create_response(jsonBody, "error", "No user data")); return; }
    if (!requestBody->isMember("username")){callback(create_response(jsonBody, "error", "no `username` in user_data.")); return; }
    if (!requestBody->isMember("password")){callback(create_response(jsonBody, "error", "no `password` in user_data.")); return; }
    if (!requestBody->isMember("service_public_token")){callback(create_response(jsonBody, "error", "no `service_public_token` in user_data."));}

    auto username = requestBody->get("username", "guest").asString();
    auto password = requestBody->get("password", "guest").asString();
    auto service_public_token = requestBody->get("service_public_token", "guest").asString();
    
    LOG_INFO << "User with uuid has been authorized at service UUID: "<<"google.com as uuid.";
    callback(create_response(jsonBody, "success", "SUPERTOKENFORAUTOHRIZEDEXPIREDAT12MINS"));
    return;
}

void create_user(const HttpRequestPtr &request, Callback &&callback) {
    Json::Value jsonBody;

    auto requestBody = request->getJsonObject();

    if (requestBody==nullptr){callback(create_response(jsonBody, "error", "No user data.")); return;}
    if (!requestBody->isMember("username")){callback(create_response(jsonBody, "error", "no `username` in user data.")); return;}
    if (!requestBody->isMember("password")){callback(create_response(jsonBody, "error", "no `password` in user data.")); return;}
    if (!requestBody->isMember("service_public_token")){callback(create_response(jsonBody, "error", "no `service_public_token` in user data.")); return;}

    auto username = requestBody->get("username", "guest").asString();
    auto password = requestBody->get("password", "guest").asString();
    auto service_public_token = requestBody->get("service_public_token", "guest").asString();

    LOG_INFO << "User has been created for service UUID: "<<"google.com as uuid.";
    callback(create_response(jsonBody, "success", "SUPERTOKENFORAUTOHRIZEDEXPIREDAT12MINS"));
    return;

}

void service_passport(const HttpRequestPtr &request, Callback &&callback) {
    return;
}

void user_passport(const HttpRequestPtr &request, Callback &&callback) {
    return;
}

class AuthV3Server {
public:
    int run() {
        drogon::app().addListener("0.0.0.0",80);

        LOG_INFO << "Server started at 0.0.0.0:80";

        drogon::app()
        .registerHandler("/create-service", &create_service, {Post});
        drogon::app()
        .registerHandler("/login-in-service", &login_at_service, {Post});
        drogon::app()
        .registerHandler("/create-user", &create_user, {Post});

        //Load config file
        drogon::app().loadConfigFile("../config.json");
        //Run HTTP framework,the method will block in the internal event loop
        drogon::app().run();
        return 0;
    }    
};

int main() {
    AuthV3Server server;
    server.run();
    
}

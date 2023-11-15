#include "AuthenticationControllerTest.h"

#include "authentication/models/LoginSuccess.h"
#include "cpr/api.h"
#include "cpr/response.h"

struct LoginPayload {
  std::string email;
  std::string password;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginPayload, email, password)
};

TEST_F(AuthenticationControllerTest, Login_ExampleLoginData_Succeeds) {
  const core::Result<std::string, Error> exampleEmail =
      secretsManager->getSecret(
          config["AuthenticationControllerTest"]["ExampleEmailSecretId"]);
  const core::Result<std::string, Error> examplePassword =
      secretsManager->getSecret(
          config["AuthenticationControllerTest"]["ExamplePasswordSecretId"]);

  LoginPayload payload = LoginPayload{.email = exampleEmail.unwrap(),
                                      .password = examplePassword.unwrap()};

  nlohmann::json payloadJson = payload;

  cpr::Response response = cpr::Post(cpr::Url{config["Test"]["Url"]},
                                     cpr::Body{payloadJson.dump()}, sslOptions);

  nlohmann::json responseJson = response.text;
  LoginSuccess loginSuccess = responseJson.get<LoginSuccess>();

  ASSERT_EQ(200L, response.status_code);
  ASSERT_FALSE(loginSuccess.accessToken.empty());
  ASSERT_FALSE(loginSuccess.idToken.empty());
  ASSERT_FALSE(loginSuccess.refreshToken.empty());
  ASSERT_TRUE(loginSuccess.expiresIn > 0LU);
}
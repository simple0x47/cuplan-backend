#include "DummyControllerTest.h"

#include <chrono>
#include <cpr/cpr.h>
#include <thread>

TEST_F(DummyControllerTest, ReceivesReplyCorrectly) {
  core::ConfigurationReader configReader = getConfigurationReader();
  nlohmann::json config = configReader.read().unwrap();

  // wait for apiRunner to initialize
  std::this_thread::sleep_for(std::chrono::seconds(
      config["DummyControllerTest"]["SleepWaitingForApiRunner"]));

  std::string url =
      std::string(config["Test"]["Url"]) + std::string("/dummy");

  cpr::SslOptions sslOptions =
      cpr::Ssl(cpr::ssl::VerifyHost{false}, cpr::ssl::VerifyPeer{false},
               cpr::ssl::VerifyStatus{false});
  const cpr::Response response = cpr::Get(cpr::Url{std::move(url)}, sslOptions);

  ASSERT_EQ(200L, response.status_code);
  ASSERT_EQ(std::string("dummy"), response.text);
}
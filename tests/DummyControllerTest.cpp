#include "DummyControllerTest.h"

#include <chrono>
#include <curl/curl.h>
#include <thread>

size_t writeCallback(void *contents, size_t size, size_t nmemb,
                     std::string *output);

TEST_F(DummyControllerTest, ReceivesReplyCorrectly) {
  core::ConfigurationReader configReader = getConfigurationReader();
  nlohmann::json config = configReader.read().unwrap();

  // wait for apiRunner to initialize
  std::this_thread::sleep_for(std::chrono::seconds(
      config["DummyControllerTest"]["SleepWaitingForApiRunner"]));

  curl_global_init(CURL_GLOBAL_DEFAULT);

  CURL *curl = curl_easy_init();
  std::string responseData;
  CURLcode response = CURLE_FAILED_INIT;

  if (curl) {
    const std::string url = std::string(config["DummyControllerTest"]["Url"]) +
                            std::string("/dummy");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 0L);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    response = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  if (response != CURLE_OK) {
    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(response)
              << std::endl;
    FAIL();
  }

  ASSERT_EQ(std::string("dummy"), responseData);
}

size_t writeCallback(void *contents, size_t size, size_t nmemb,
                     std::string *output) {
  const size_t totalSize = size * nmemb;
  output->append(static_cast<char *>(contents), totalSize);

  return totalSize;
}
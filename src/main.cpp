#include "core/ConfigurationReader.h"
#include "core/Constants.h"
#include "routes.h"

#include <crow.h>
#include <crow/middlewares/cors.h>

#include <iostream>

core::Result<nlohmann::json, Error> getConfiguration();

int main() {
  const core::Result<nlohmann::json, Error> result = getConfiguration();

  if (!result.isOk()) {
    std::cerr << "failed to read configuration: " + result.unwrapErr().message()
              << std::endl;
    return -1;
  }

  nlohmann::json config = result.unwrap();

  crow::App<crow::CORSHandler> app;

  initializeRoutes(app);

  auto &cors = app.get_middleware<crow::CORSHandler>();
  cors.global().origin(config["Server"]["CORS"]["Origin"]);

  app.ssl_chainfile(config["Server"]["Ssl"]["FullChain"],
                    config["Server"]["Ssl"]["Key"])
      .port(config["Server"]["Port"])
      .multithreaded()
      .run();

  return 0;
}

core::Result<nlohmann::json, Error> getConfiguration() {
  const char *environment = std::getenv(core::CUPLAN_ENVIRONMENT_ENV);

  if (environment == nullptr) {
    environment = core::DEVELOPMENT_ENVIRONMENT;
  }

  core::ConfigurationReader reader(environment);

  return reader.read();
}
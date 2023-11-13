#include <crow.h>

#include <iostream>

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")([]() { return "Hello world"; });

  app.port(5123).multithreaded().run();

  return 0;
}
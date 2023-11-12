#include <iostream>

#include "crow_all.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
       return "Hello World";
    });

    app.port(10000).multithreaded().run();

    return 0;
}
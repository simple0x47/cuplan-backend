#include "routes.h"

void initializeRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/add/<int>/<int>")
  ([](int a, int b) { return std::to_string(a + b); });
}
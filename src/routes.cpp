#include "routes.h"

#include <crow/middlewares/cors.h>

void initializeRoutes(crow::App<crow::CORSHandler> &app) {
  CROW_ROUTE(app, "/add/<int>/<int>")
  ([](int a, int b) { return std::to_string(a + b); });
}
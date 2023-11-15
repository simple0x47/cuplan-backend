#include "routes.h"

#include <crow/middlewares/cors.h>

void initializeRoutes(crow::App<crow::CORSHandler> &app) {
#ifndef NDEBUG
  // dummy route for testing purposes
  CROW_ROUTE(app, "/dummy")
  ([]() { return "dummy"; });
#endif
}
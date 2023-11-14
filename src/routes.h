#ifndef ROUTES_H
#define ROUTES_H
#include <crow/app.h>
#include <crow/middlewares/cors.h>

void initializeRoutes(crow::App<crow::CORSHandler> &app);

#endif // ROUTES_H

#ifndef AUTHENTICATIONCONTROLLER_H
#define AUTHENTICATIONCONTROLLER_H

#include <crow/app.h>
#include <crow/middlewares/cors.h>

namespace authentication::controllers {
void initializeRoutes(crow::App<crow::CORSHandler> &app);
} // namespace authentication::controllers

#endif // AUTHENTICATIONCONTROLLER_H

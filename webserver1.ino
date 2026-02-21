#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "server";
const char* password = "64";

ESP8266WebServer server(80);

// --- Login credentials ---
String loginUser = "admin";
String loginPass = "1234";

void handleLoginPage() {
  String page =
    "<html>"
    "<head><title>Login</title></head>"
    "<body style='font-family:Arial;'>"
    "<h2>ESP8266 Login Page</h2>"
    "<form action='/login' method='POST'>"
    "Username: <input type='text' name='user'><br><br>"
    "Password: <input type='password' name='pass'><br><br>"
    "<input type='submit' value='Login'>"
    "</form>"
    "</body></html>";

  server.send(200, "text/html", page);
}

void handleLogin() {
  if (server.hasArg("user") && server.hasArg("pass")) {
    String user = server.arg("user");
    String pass = server.arg("pass");

    if (user == loginUser && pass == loginPass) {
      server.send(200, "text/html",
                  "<h1>Login Successful!</h1>"
                  "<p>Welcome to the ESP8266 Control Panel</p>");
    } else {
      server.send(200, "text/html",
                  "<h1>Login Failed!</h1>"
                  "<p>Invalid username or password</p>"
                  "<a href='/'>Try Again</a>");
    }
  }
}

void setup() {
  WiFi.softAP(ssid, password);

  server.on("/", handleLoginPage);   // Login page
  server.on("/login", handleLogin);  // Handle login POST
  server.begin();
}

void loop() {
  server.handleClient();
}
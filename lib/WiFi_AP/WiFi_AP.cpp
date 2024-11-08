#include "WiFi_AP.h"

IPAddress local_IP(LOCAL_IP);
IPAddress gateway(LOCAL_GATEWAY);
IPAddress subnet(LOCAL_SUBNET);

WebServer server(80);

String html = "<!DOCTYPE html>"
                "<html><head><title>Configurar WiFi</title>"
                "<style>"
                "body { font-family: Arial, sans-serif; display: flex; flex-direction: column; align-items: center; margin: 0; }"
                "nav { width: 100%; background-color: #4CAF50; overflow: hidden; }"
                "nav a { float: left; display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none; }"
                "nav a:hover { background-color: #45a049; }"
                "h1 { font-size: 2em; text-align: center; margin-top: 20px; }"
                "form { max-width: 300px; width: 100%; margin: 20px 0; }"
                "input[type=\"text\"], input[type=\"password\"] { width: 100%; padding: 8px; margin: 8px 0; box-sizing: border-box; }"
                "input[type=\"submit\"] { width: 100%; padding: 10px; background-color: #4CAF50; color: white; border: none; cursor: pointer; }"
                "input[type=\"submit\"]:hover { background-color: #45a049; }"
                "</style></head><body>"
                "<nav><a href=\"#\">Este WIFI</a><a href=\"#\">Conectar a</a></nav>"
                "<h1>Configurar WiFi</h1>"
                "<form action=\"/setwifi\" method=\"POST\">"
                "<label for=\"ssid\">SSID:</label>"
                "<input type=\"text\" id=\"ssid\" name=\"ssid\" required><br>"
                "<label for=\"password\">Password:</label>"
                "<input type=\"password\" id=\"password\" name=\"password\" required><br>"
                "<input type=\"submit\" value=\"Guardar\">"
                "</form></body></html>";

void generateAP( ) {
    WiFi.softAP(SSID_THIS, PASS_THIS);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    server.on("/", handleRoot);
    server.on("/setwifi", HTTP_POST, handleSetWiFi);
    server.begin();
    Serial.println("Servidor HTTP iniciado");
}

void handleRoot( ) {
    server.send(200, "text/html", html);
}

void handleSetWiFi( ) {
    if (server.hasArg("ssid") && server.hasArg("password")) {
        String ssid_ap = server.arg("ssid");
        String password_ap = server.arg("password");
        
        EEPROM.writeString(ADDR_SSID_TO_CONNECT,ssid_ap);
        EEPROM.writeString(ADDR_PASS_TO_CONNECT,password_ap);
        EEPROM.commit();

        server.send(200, "text/html", html);

        Serial.println("SSID: "+ssid_ap);
        Serial.println("PASS: "+password_ap);
        Serial.println();
        delay(500);
        ESP.restart();
    } else {
        server.send(400, "text/html", "Faltan datos");
    }
}

void server_handleClient() {
    server.handleClient();
}
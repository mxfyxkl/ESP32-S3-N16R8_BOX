#include <all.h>

int wifi(){

    int n = WiFi.scanNetworks();
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>WiFi设置</title></head><body>";
    html += "<h1>WiFi设置</h1>";
    html += "<form method='POST' action='/wifi'>";
    html += "<label for='ssid'>选择WiFi网络:</label>";
    html += "<select name='ssid'>";
    for (int i = 0; i < n; ++i) {
      html += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm)</option>";
    }
    html += "</select><br>";
    html += "<label for='password'>密码:</label>";
    html += "<input type='password' name='password'><br>";
    html += "<input type='submit' value='连接'>";
    html += "</form>";
    html += "<button onclick=\"location.href='/'\">返回</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
return 0;
}
int wifisteup(){
    if (server.hasArg("ssid") && server.hasArg("password")) {
      String ssid = server.arg("ssid");
      String password = server.arg("password");
      Serial.println("连接到 " + ssid + "...");
      Serial.println("密码: " + password);
      wifiConnected = false;
      WiFi.begin(ssid.c_str(), password.c_str());
      server.send(200, "text/html", "<p>正在连接到 " + ssid + "...</p><button onclick=\"location.href='/'\">返回</button>");
    } else {
      server.send(400, "text/html", "<p>缺少SSID或密码</p><button onclick=\"location.href='/'\">返回</button>");
    }
  return 0;
  
}
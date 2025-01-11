#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <all.h>

const char* ssid = "FreshTomato24"; // 替换为你的SSID
const char* password = "88888888"; // 替换为你的密码

bool wifiConnected = false;

// 创建Web服务器对象
WebServer server(80);

void setup() {
  // 初始化串行通信，波特率为115200
  Serial.begin(115200);
  Serial.println("初始化完毕");

  // 设置WiFi为AP+STA模式
  WiFi.mode(WIFI_AP_STA);

  // 开始连接到WiFi网络
  WiFi.begin(ssid, password);

  // 设置AP模式的IP地址、网关和子网掩码
  IPAddress local_IP(192, 168, 25, 1);
    IPAddress gateway(192, 168, 25, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  
  // 启用AP模式，设置SSID和密码
  WiFi.softAP("ESP32-Box", "88888888");
  Serial.println("AP模式已启用");
  
  // 处理根首页URL请求
  server.on("/", HTTP_GET, []() {
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>主页</title>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding: 50px; }";
    html += "h1 { color: #333; }";
    html += "ul { list-style-type: none; padding: 0; }";
    html += "li { margin: 10px 0; }";
    html += "a { text-decoration: none; color: white; background-color: #007BFF; padding: 10px 20px; border-radius: 5px; }";
    html += "a:hover { background-color: #0056b3; }";
    html += "</style>";
    html += "</head><body>";
    html += "<h1>主页</h1>";
    html += "<ul>";
    html += "<li><a href='/device_info'>设备信息</a></li>";
    html += "<li><a href='/hello'>你好页面</a></li>";
    html += "<li><a href='/update'>固件升级</a></li>";
    html += "<li><a href='/wifi'>WiFi设置</a></li>";
    html += "</ul>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });
  
  // 处理设备信息页面请求
  server.on("/device_info", HTTP_GET, device_info);
  
    // 处理你好页面请求
    server.on("/hello", HTTP_GET, []() {
      String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>你好</title></head><body>";
      html += "<h1>你好这是测试页。<a>没有具体韩式</a></h1>";
      html += "<button onclick=\"location.href='/'\">返回</button>";
      html += "</body></html>";
      server.send(200, "text/html", html);
    });

  // 处理固件升级页面请求
  server.on("/update", HTTP_GET,update);
  // 处理固件上传请求
  server.on("/update", HTTP_POST, updateok,updatelogo);

  // 处理WiFi设置页面请求
  server.on("/wifi", HTTP_GET, wifi);
  // 处理WiFi连接请求
  server.on("/wifi", HTTP_POST,wifisteup);
  // 启动Web服务器
  server.begin();
}

void loop() {
  // 检查WiFi连接状态
  if (WiFi.status() == WL_CONNECTED && !wifiConnected) {
    wifiConnected = true;
    Serial.println("WiFi连接成功");
    Serial.println(WiFi.localIP());
  } else if (WiFi.status() != WL_CONNECTED && wifiConnected) {
    wifiConnected = false;
    Serial.println("WiFi连接断开");
  }

  // 处理客户端请求
  server.handleClient();

  // 其他主循环代码
  //delay(1000);
}
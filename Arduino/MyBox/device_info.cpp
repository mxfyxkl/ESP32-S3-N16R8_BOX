#include <Arduino.h>
#include "all.h"

String getDeviceInfo() {
    String info = "\n设备信息：\n";
    info += "芯片型号： " + String(ESP.getChipModel()) + "\n";
    info += "芯片修改： " + String(ESP.getChipRevision()) + "\n";
    info += "CPU频率： " + String(ESP.getCpuFreqMHz()) + " MHz\n";
    info += "闪存大小： " + String(ESP.getFlashChipSize() / (1024 * 1024)) + " MB\n";
    info += "堆大小： " + String(ESP.getHeapSize() / 1024) + " KB\r\n";
    info += "已用堆: " + String(ESP.getFreeHeap() / 1024) + " KB\n";
    info += "SDK 版本: " + String(ESP.getSdkVersion()) + "\n";
    return info;
}

int device_info(){
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>设备信息</title></head><body>";
    html += "<h1>设备信息</h1>";
    html += "<p>IP地址: " + WiFi.localIP().toString() + "</p>";
    html += "<p>MAC地址: " + WiFi.macAddress() + "</p>";
    html += "<p>信号强度: " + String(WiFi.RSSI()) + " dBm</p><div>";
    html += getDeviceInfo();
    html += "</div><button onclick=\"location.href='/'\">返回</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
    return 0;
}
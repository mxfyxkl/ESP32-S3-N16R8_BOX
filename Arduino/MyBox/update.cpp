#include <all.h>


int update(){
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>固件升级</title></head><body>";
    html += "<h1>固件升级</h1>";
    html += "<form method='POST' action='/update' enctype='multipart/form-data'>";
    html += "<input type='file' name='update'>";
    html += "<input type='submit' value='上传并升级'>";
    html += "</form>";
    html += "<button onclick=\"location.href='/'\">返回</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
    return 0;

  }

int updateok(){
    // 上传完成后，发送响应并重启ESP32
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
    return 0;
    }

int updatelogo(){
    // 处理上传数据
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      // 开始上传文件
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { // 以最大可用大小开始
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // 写入上传的数据到闪存
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      // 上传完成
      if (Update.end(true)) { // true表示设置大小为当前进度
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
    return 0;
    }
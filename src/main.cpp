#include <M5StickCPlus2.h>

const char* menuItems[] = {
  "IR",
  "WIFI", 
  "BT",
  "cwlee",
  "jebane"
};
const int MENU_ITEM_COUNT = 5;

int currentMenuIndex = 0;
bool inMenu = true;

void drawBatteryPercentage() {
  int32_t batteryLevel = M5.Power.getBatteryLevel();
  
  if (batteryLevel > 80) {
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.setTextSize(2);
  }
  else if (batteryLevel >= 50 && batteryLevel <= 80) {
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Lcd.setTextSize(2);
  }
  else {
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setTextSize(2);
  }
  
  M5.Lcd.setCursor(M5.Lcd.width() - 50, 0);
  M5.Lcd.print(batteryLevel);
  M5.Lcd.print("%");
}

void drawMenu() {
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(PURPLE);
  M5.Lcd.setTextSize(3);
  
  drawBatteryPercentage();
  
  int startIndex = max(0, currentMenuIndex - 2);
  int endIndex = min(MENU_ITEM_COUNT - 1, startIndex + 4);
  
  for (int i = startIndex; i <= endIndex; i++) {
    if (i == currentMenuIndex) {
      M5.Lcd.setTextColor(BLACK, PURPLE);
    } else {
      M5.Lcd.setTextColor(PURPLE, BLACK);
    }
    
    M5.Lcd.setCursor(10, 20 + (i - startIndex) * 30);
    M5.Lcd.println(menuItems[i]);
  }
}

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);  
  drawMenu();
}

void loop() {
  M5.update();
  
  if (M5.BtnPWR.wasPressed()) {
    if (currentMenuIndex > 0) {
      currentMenuIndex--;
      drawMenu();
    }
  }
  
  if (M5.BtnB.wasPressed()) {
    if (currentMenuIndex < MENU_ITEM_COUNT - 1) {
      currentMenuIndex++;
      drawMenu();
    }
  }
  
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.setTextColor(PURPLE);
    M5.Lcd.println("wybranko: ");
    M5.Lcd.println(menuItems[currentMenuIndex]);
    delay(2000);  // Show selection for 2 seconds
    drawMenu();
  }
  
  delay(50);  // Small delay to prevent rapid updates
}
#include <Keyboard.h>
#include <Mouse.h>
#include <MouseTo.h>
// Transmitting rate
#define BAUD_RATE 57200
// Serial used talking to wifi chip
#define WIFI_SERIAL Serial1

String buf = "";
String last = "";

int interval = 100;

void print_line(String line) {
  Serial.println(line);
  int spc = line.indexOf(" ");
  if (spc == -1) {
    press_key(line);
    Keyboard.releaseAll();
    delay(interval);
    return;
  }
  String op = line.substring(0, spc);
  if (op == "STRING") {
    for (unsigned int i = spc + 1; i < line.length(); i++)
      Keyboard.write(line[i]);
  } else if (op == "DELAY") {
    int s = line.substring(spc + 1).toInt();
    delay(s);
  } else if (op == "DEFAULTDELAY") {
    interval = line.substring(spc + 1).toInt();
  } else if (op == "REPLAY") {
    int s = line.substring(spc + 1).toInt();
    while (s--)
      print_line(last);
  } else if(op == "MOVE") {
    line = line.substring(spc+1);
    spc = line.indexOf(" ");
    int x = line.substring(0, spc).toInt();
    int y = line.substring(spc+1).toInt();

    MouseTo.setTarget(x,y, true);
    while(!MouseTo.move()){};
    } else if (op == "SCREEN")
  {
    line = line.substring(spc+1);
    spc = line.indexOf(" ");
    int xlen = line.substring(0, spc).toInt();
    int ylen = line.substring(spc+1).toInt();

    MouseTo.setScreenResolution(xlen, ylen);
  }
  else if (op == "REM") {}
  else {
    String remain = line;
    while (remain.length() > 0) {
      spc = remain.indexOf(" ");
      if (spc == -1) {
        press_key(remain);
        remain = "";
      } else {
        press_key(remain.substring(0, spc));
        remain = remain.substring(spc + 1);
      }
      delay(100);
    }
  }

  Keyboard.releaseAll();
  delay(interval);
}

void press_key(String key) {
  Serial.println(key);
  if (key.length() == 1) Keyboard.press(char(key[0]));
  else if (key.equals("HOLD")) {Mouse.press();}
  else if (key.equals("CLICK")) {Mouse.click();}
  else if (key.equals("ENTER")) Keyboard.press(KEY_RETURN);
  else if (key.equals("CTRL")) Keyboard.press(KEY_LEFT_CTRL);
  else if (key.equals("SHIFT")) Keyboard.press(KEY_LEFT_SHIFT);
  else if (key.equals("ALT")) Keyboard.press(KEY_LEFT_ALT);
  else if (key.equals("GUI")) Keyboard.press(KEY_LEFT_GUI);
  else if (key.equals("UP") || key.equals("UPARROW")) Keyboard.press(KEY_UP_ARROW);
  else if (key.equals("DOWN") || key.equals("DOWNARROW")) Keyboard.press(KEY_DOWN_ARROW);
  else if (key.equals("LEFT") || key.equals("LEFTARROW")) Keyboard.press(KEY_LEFT_ARROW);
  else if (key.equals("RIGHT") || key.equals("RIGHTARROW")) Keyboard.press(KEY_RIGHT_ARROW);
  else if (key.equals("DELETE")) Keyboard.press(KEY_DELETE);
  else if (key.equals("PAGEUP")) Keyboard.press(KEY_PAGE_UP);
  else if (key.equals("PAGEDOWN")) Keyboard.press(KEY_PAGE_DOWN);
  else if (key.equals("HOME")) Keyboard.press(KEY_HOME);
  else if (key.equals("ESC")) Keyboard.press(KEY_ESC);
  else if (key.equals("BACKSPACE")) Keyboard.press(KEY_BACKSPACE);
  else if (key.equals("INSERT")) Keyboard.press(KEY_INSERT);
  else if (key.equals("TAB")) Keyboard.press(KEY_TAB);
  else if (key.equals("END")) Keyboard.press(KEY_END);
  else if (key.equals("CAPSLOCK")) Keyboard.press(KEY_CAPS_LOCK);
  else if (key.equals("F1")) Keyboard.press(KEY_F1);
  else if (key.equals("F2")) Keyboard.press(KEY_F2);
  else if (key.equals("F3")) Keyboard.press(KEY_F3);
  else if (key.equals("F4")) Keyboard.press(KEY_F4);
  else if (key.equals("F5")) Keyboard.press(KEY_F5);
  else if (key.equals("F6")) Keyboard.press(KEY_F6);
  else if (key.equals("F7")) Keyboard.press(KEY_F7);
  else if (key.equals("F8")) Keyboard.press(KEY_F8);
  else if (key.equals("F9")) Keyboard.press(KEY_F9);
  else if (key.equals("F10")) Keyboard.press(KEY_F10);
  else if (key.equals("F11")) Keyboard.press(KEY_F11);
  else if (key.equals("F12")) Keyboard.press(KEY_F12);
  else if (key.equals("SPACE")) Keyboard.press(' ');
  else
    Serial.println("please check your script");
}


void setup() {
  Serial.begin(BAUD_RATE);
  WIFI_SERIAL.begin(BAUD_RATE);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Mouse.begin();
  MouseTo.setCorrectionFactor(1);
  MouseTo.setMaxJump(100);
  Keyboard.begin();
}

void loop() {
  if (WIFI_SERIAL.available())
    buf = WIFI_SERIAL.readStringUntil('\0');

  buf.replace("\r", "\n");
  buf.replace("\n\n", "\n");
  while (buf.length() > 0) {
    int ret = buf.indexOf("\n");
    if (ret == -1) {
      print_line(buf);
      buf = "";
    } else {
      last = buf.substring(0, ret);
      print_line(last);
      buf = buf.substring(ret + 1);
    }
  }
  WIFI_SERIAL.write(0x99);
}

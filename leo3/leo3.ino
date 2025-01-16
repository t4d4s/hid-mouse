#include <Mouse.h>
#include <usbhub.h> 

USB Usb; 
USBHub Hub(&Usb);  

int dx;
int dy;
int lmb;
int rmb;
int mmb;

#include <hidboot.h> 
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb); 

const int signalPin = 5;

class MouseRptParser : public MouseReportParser 
{ 
  protected: 
    void OnMouseMove  (MOUSEINFO *mi); 
    void OnLeftButtonUp (MOUSEINFO *mi); 
    void OnLeftButtonDown (MOUSEINFO *mi); 
    void OnRightButtonUp  (MOUSEINFO *mi); 
    void OnRightButtonDown  (MOUSEINFO *mi); 
    void OnMiddleButtonUp (MOUSEINFO *mi); 
    void OnMiddleButtonDown (MOUSEINFO *mi);
};  

void MouseRptParser::OnMouseMove(MOUSEINFO *mi)  
{ 
  dx = mi->dX; 
  dy = mi->dY; 
};  

void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) 
{  
  lmb = 0; 
}; 

void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) 
{ 
  lmb = 1; 
}; 

void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) 
{  
  rmb = 0; 
};  

void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi)  
{ 
  rmb = 1; 
};  

void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) 
{ 
  mmb = 0; 
}; 

void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi)
{ 
  mmb = 1;
}; 

MouseRptParser Prs; 

void setup() {
  Mouse.begin();
  Usb.Init(); 
  HidMouse.SetReportParser(0, &Prs); 
  
  pinMode(signalPin, INPUT);
}

void loop() {
  Usb.Task();
  
  Mouse.move(dx, dy);

  dx = 0;
  dy = 0;

  if (digitalRead(signalPin) == HIGH) {
    Mouse.click(MOUSE_LEFT);
  }

  if (lmb == 1) {
    Mouse.press(MOUSE_LEFT);
  } else {
    Mouse.release(MOUSE_LEFT);
  }

  if (rmb == 1) {
    Mouse.press(MOUSE_RIGHT);
  } else {
    Mouse.release(MOUSE_RIGHT);
  }

  if (mmb == 1) {
    Mouse.press(MOUSE_MIDDLE);
  } else {
    Mouse.release(MOUSE_MIDDLE);
  }
}

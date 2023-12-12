/**
 * Author: htns
 * Description: Maps CapsLock to Ctrl in Windows.
 */
#pragma once

#include <windows.h>

LRESULT f(int n, WPARAM w, LPARAM l) {
  return n>=0 && w<258 && *(int*)l==20 ? 
         keybd_event(17,0,w%2*2,0),1 : 
         CallNextHookEx(0,n,w,l);
}

int main() {
  SetWindowsHookEx(13,f,GetModuleHandle(0),0);
  MSG m; while (GetMessage(&m,0,0,0)) TranslateMessage(&m), DispatchMessage(&m);
}

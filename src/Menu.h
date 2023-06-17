#pragma once

#include <windows.h>
#include <conio.h>


#include "readFile.h";

#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


class Window
{
public:
	~Window() { };

    static void GoToXY(short x, short y)
    {
        SetConsoleCursorPosition(hStdOut, { x, y });
    }

    static void ConsoleCursorVisible(bool show, short size)
    {
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
        structCursorInfo.bVisible = show;
        structCursorInfo.dwSize = size;
        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
    }

    void ConsoleWindow()
    {
        SetConsoleTitle(L"Clown");
        ConsoleCursorVisible(false, 100);
        int active_menu = 0;
        const int MENU_SIZE = 5;
        char Menu[MENU_SIZE][15] = { "encrypt", "decrypt", "use saved file", "save file", "Exit"};


        char ch;
        while (true)
        {
            int x = 50, y = 11;
            GoToXY(x, y);

            for (int i = 0; i < MENU_SIZE; i++)
            {
                if (i == active_menu)
                {
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                }
                else
                {
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
                }
                GoToXY(x, y++);
                std::cout << Menu[i] << std::endl;
            }

            ch = _getch();
            switch (ch)
            {
            case ESC:
                exit(0);
                system("cls");
            case ENTER:
                switch (active_menu)
                {
                case 0:
                {
                    system("cls");
                    GoToXY(x, y);
                    


                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);

                    std::cout << "Enter file for input: ";
                    const char* in = input_file();

                   
                    GoToXY(x, 12);
                    std::cout << "Enter file for output: ";
                    const char* out = input_file();

                    GoToXY(x, 14);
                    std::cout << "Enter key-pass: ";
                    const char* key = input_key();

                    std::cout << " Compiling encrypt.. \ " << Menu[active_menu] << "\" ";
                    read_encrypt_file(in, out, key);

                    Sleep(500);
                    system("cls");
                    GoToXY(x, y);
                    
                    Sleep(5000);
                    system("cls");
                    break;
                }
                case 1:
                {
                    system("cls");
                    GoToXY(x, y);

                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);

                    std::cout << "Enter file for input: ";
                    const char* in = input_file();

                    GoToXY(x, 12);
                    std::cout << "Enter file for output: ";
                    const char* out = input_file();

                    GoToXY(x, 14);
                    std::cout << "Enter key-pass: ";
                    const char* key = input_key();
                    
                    std::cout << " Compiling decrypt.. \ " << Menu[active_menu] << "\" ";    
                    read_dencrypt_file(in, out, key);
                    Sleep(500);
                    system("cls");
                    GoToXY(x, y);
                    std::cout << "Completly dencrypted.";
                    Sleep(1000);
                    system("cls");

                    break;
                }
                case 2:
                {
                    system("cls");
                    GoToXY(x, y);

                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED |
                        FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                    std::cout << "Enter key-pass: ";
                    const char* key = input_key();
                                        
                    use_save_file(key);
                    Sleep(500);
                    system("cls");
                    

                    GoToXY(x, y);
                    std::cout << "Success" << std::endl;
                                            
                    Sleep(1000);
                    system("cls");
                    break;
                }
                case 3:
                {
                    system("cls");
                    
                    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED |
                        FOREGROUND_GREEN | FOREGROUND_INTENSITY);                    
                    
                    FILE* ptr_null;
                    errno_t err = fopen_s(&ptr_null, "C:/links/linksClown.txt", "w");
                    fclose(ptr_null);

                    x = 30;
                    y = 9;
                    GoToXY(x, y);
                    std::cout << "Enter file for input: ";                    
                    save_link(input_file());

                    y = 12;
                    GoToXY(x, y);
                    std::cout << "Enter file for output: ";  
                    save_link(input_file());
                                       
                    std::cout << "File successful recorded";
                    Sleep(500);
 
                    system("cls");
                    break;
                }
                case 4:
                    exit(0);
                    system("cls");
                    break;
                }
               
            case UP:
                if (active_menu > 0)
                {
                    active_menu--;
                }
                break;
            case DOWN:
                if (active_menu < MENU_SIZE - 1)
                {
                    active_menu++;
                }
                break;
            }
        }
        system("cls");
        _getch();
    }    
    static const char* input_file()
    {
        char* str = new char[100];
        std::cin.getline(str, 100, 10);
        for (int i = 0; i < strlen(str); ++i)
        {
            if (str[i] == 92)
            {
                str[i] = '/';
            }
        }
        return str;
    }

    static const char* input_key()
    {        
        char* str = new char[64];
        std::cin.getline(str, 100, 10);        
        return str;
    }


};



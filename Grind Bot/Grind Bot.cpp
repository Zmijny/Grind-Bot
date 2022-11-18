#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <future>
#include <fstream>
#include <string>

std::string weapon;
int null;
bool bgstatus;

void AmmoBoxRefresh()
{
	//for some fucking reason always uses 2 ammunition boxes. To be fixed
	INPUT ab;
	ab.type = INPUT_KEYBOARD;
	ab.ki.wScan = 0x0B;

	ab.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &ab, sizeof(INPUT));
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	ab.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ab, sizeof(INPUT));

	bgstatus = false;
}

//uses a Ammo Box after a certain ammount of time
void bufferedFileLoader()
{
	while (true)
	{
		if (weapon == "Bawoo" || "bawoo")
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(360000));
		}
		else if (weapon == "Hawky" || "hawky")
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(210000));
		}
		else
		{
			std::cout << "wrong weapon or text!!!\n The program will continue but it won't use Amunition Boxes!!";
			return;
		}
		bgstatus = true;
		if (bgstatus != false)
		{
			AmmoBoxRefresh();
		}
	}
}

void main()
{
	start:
		std::cout << "\t\t\t\tYOU ARE USING THIS PROGRAM AT YOUR OWN RISK\n\n";
		std::cout << "To start the bot press F5, to stop F6\n";
		std::cout << "IMPORTANT: Activate GBM and put your ammuniton box on the last slot in your skillbar!!!!\n";
		null = _getch();
		
	if (GetKeyState(VK_F5) & 0x8000)
	{
		//read config file
		std::ifstream config;
		config.open("config.txt");
		int screen_width, screen_height;
		std::string line;

		for (int i = 1; i <= 4; i++)
			config >> line;
		screen_width = stoi(line);
			
		for(int i = 1; i <= 3; i++)
			config >> line;
		screen_height = stoi(line);

		for(int i = 1; i <= 3; i++)
			config >> line;
		weapon = line;

		//keyboard input
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wVk = VkKeyScanA('s');
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;

		//start counter
		system("CLS");
		std::cout << "Grind Bot will start in:\n";
		Sleep(500);
		for (int i = 5; i >= 1; i--)
		{
			Sleep(1000);
			std::cout << i << "\n";
		}

		//initialize the program
		SetCursorPos((screen_width / 2), (screen_height / 2));
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		std::future<void> backgroundThread = std::async(std::launch::async,
			bufferedFileLoader);
		AmmoBoxRefresh();
		
		//loop for holding "s"
		while (true)
		{
			//0x0B = 0 | 0x0A = 9 |  ||550x bawoo 546x hawks
			ip.ki.dwFlags = KEYEVENTF_SCANCODE;
			ip.ki.wScan = 0x1F;
			SendInput(1, &ip, sizeof(INPUT));
			Sleep(8);

			//closes the program
			if (GetAsyncKeyState(VK_F6))
			{
				ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				std::exit(EXIT_SUCCESS);
				return;
			}

		}		
					
	}
	system("CLS");
	if (GetAsyncKeyState(VK_F6))
		return;
	else
		goto start;
}


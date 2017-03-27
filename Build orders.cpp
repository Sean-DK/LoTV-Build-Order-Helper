// Build orders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <conio.h>

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::vector<std::string> stringsplit(const std::string& s, const std::string& delim) {
	std::vector<std::string> result;
	std::string str = s;
	do {
		if (delim == "" || str == "") return result;
		else if (str.find(delim) == 0) str.erase(str.begin());
		else if (str.find(delim) > 0 && str.find(delim) < 32767) {
			result.push_back(str.substr(0, str.find(delim)));
			str.erase(str.begin(), str.begin() + str.find(delim) + delim.size());
		}
		else {
			result.push_back(str);
			return result;
		}
	} while (1);
}

int clockToInt(const std::string& str) {
	int min, sec;
	std::string minutes, seconds;
	minutes = stringsplit(str, ":")[0];
	seconds = stringsplit(str, ":")[1];
	min = std::stoi(minutes, nullptr, 10);
	sec = std::stoi(seconds, nullptr, 10);
	return (min * 60) + sec;
}

int getTime(const clock_t& clock) {
	int time;
	clock_t clock_now = std::clock();
	time = int((clock_now - clock)) / CLOCKS_PER_SEC;
	return time;
}

void outputSound(const std::string& action) {
	std::string str;
	str = "Sounds\\" + action + ".wav";
	PlaySound(s2ws(str).c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

int main()
{
	int time;
	int current = 0; //keep track of where we are in the build
	clock_t clock;
	std::vector<int> timing;	//vector containing timings (i.e. "0:12 Barracks" this holds the "0:12")
	std::vector<std::string> action;	//vector containing actions (i.e. "0:12 Barracks" this holds the "Barracks")

	std::ifstream file;
	std::string str;
	std::cout << "File name: ";
	std::getline(std::cin, str);
	str = "E:\\Users\\Sean\\Documents\\LoTV Build Orders\\" + str + ".txt";
	std::cout << str << "\n";
	file.open(str);
	if (file.is_open()) {
		while (std::getline(file, str)) {
			timing.push_back(clockToInt(stringsplit(str, ",")[0]));
			action.push_back(stringsplit(str, ",")[1]);
		}
		std::cout << "Successfully read file.";
		file.close();
	}
	else {
		std::cout << "Could not open file.\n";
		return 0;
	}
	std::cout << " Press enter when the game starts.\n";
	while (1) if (_kbhit()) if (_getch() == 0x0D) break;
	system("cls");
	clock = std::clock();
	PlaySound(TEXT("Sounds\\glhf.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (current < timing.size()) {
		Sleep(50);
		time = getTime(clock);
		system("cls");
		if (current > 0) std::cout << "Current:\n" << action[current - 1] << "\n\n";
		std::cout << "Upcoming:\n" << action[current] << " in " << timing[current] - time << " seconds.";
		if (time == timing[current]) {
			outputSound(action[current]);
			current++;
		}
	}
	system("pause");
    return 0;
}


//extra hash stuff in case i need it some time

//create hash table for sound files
//std::vector<std::string> sounds;
//sounds.resize(1000);
//createSoundHash(sounds);
//read build order file

//int hash(const std::string& str) {
//	int first, mid, last;
//	mid = std::abs(str[str.size() / 2] - '0');
//	first = std::abs((str[0] - '0') * mid);
//	last = std::abs((str[str.size() - 1] - '0')* mid);
//	return (first + mid + last) / 7;
//}
//
//void createSoundHash(std::vector<std::string> &vec) {
//	std::string soundName = "+1 armor";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "+1 attack";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "+1_1";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Armory";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Banshee cloak";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Barracks";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Combat shield";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Command center";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Concussive shells";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Engineering bay";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Factory";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Fusion core";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Ghost academy";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Liberator range";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Orbital";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Planetary";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Reactor_barracks";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Reactor_factory";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Reactor_starport";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Refinery";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Sensor tower";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Starport";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Stimpack";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Supply depot";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Swap_barracks_factory";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Swap_barracks_starport";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Swap_factory_starport";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Tech lab_barracks";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Teach lab_factory";
//	vec[hash(soundName)] = soundName;
//
//	soundName = "Tech lab_starport";
//	vec[hash(soundName)] = soundName;
//}
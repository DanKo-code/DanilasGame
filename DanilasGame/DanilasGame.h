#pragma once

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <thread>

#include <mutex>

#define ENEMY_SYMBOL 'B' // ����������� ����� �� �����
#define PLAYER_SYMBOL 'C' // ����������� ������ �� �����
#define GUN_SYMBOL '+' 
#define BULLET_SYMBOL '+' 
#define TIME_OUT 200 // �������� ����� (������ �������� - ������� ��������)
#define START_ANIMATION 20 //��������� ���� � ����� ������ (������� �������� - ������� ��������) 

using namespace std;

class DanilasGame
{
public:

	//Danilas_Game(); // �����������
	~DanilasGame(); // ��� �������� �������
	void Create_Field(const short& Field_Width, const short& Field_Height); // �������� ����

	void Create_Enemy(); // ��������� ������� �����
	void Create_Player(); // ��������� ������� ������

	void Move_Player();
	void Move_Gun();

	void Move_Enemy();

private:
	int Field_Width = 0;
	int Field_Height = 0;

	int EnemyX = 0;
	int EnemyY = 0;

	short PlayerX = 0;
	short PlayerY = 0;

	short GunX = PlayerX + 1;
	short GunY = PlayerY + 1;

	short BulletX = PlayerX + 2;
	short BulletY = PlayerY + 2;

	enum Colors
	{
		BLACK, BLUE, GREEN, CLOUDY_BLUE, RED, PURPLE, YELLOW, WHITE, GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CLOUDY_BLUE, LIGHT_RED, LIGHT_YELLOW, BRIGHT_WHITE
	};

	mutex SavePrint;

	int Generate_Random_X()
	{
		return (rand() % this->Field_Width) + 1;
	}
	int Generate_Random_Y()
	{
		return rand() % (this->Field_Height) + 1;
	}

	void Creat_Different_X()
	{
		for (;;)
		{
			this->PlayerX = Generate_Random_X();
			if (this->EnemyX == this->PlayerX) continue;
			else break;
		}
	}
	void Creat_Different_Y()
	{
		for (;;)
		{
			this->PlayerY = Generate_Random_Y();
			if (this->EnemyY == this->PlayerY) continue;
			else break;
		}
	}

	void Move_Logic();
	void Move_Gun_Logic();

	/////////////////////////////////////////////////������ � ��������/////////////////////////////////////////////////////////////////

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ������ ���������� ����	
	CONSOLE_CURSOR_INFO MyCursor = { 25,true }; // �������� ������ �������

	void Change_Symbol_Color(const int& color);
	void HIDE_CURSOR(const bool& visability);
	void GoToXY(const short& x, const short& y, const char& symbol); // ����������� ������ �� �����������
};
#include "DanilasGame.h"

////Конструктор
//Danilas_Game::Danilas_Game()
//{
//	mutex SavePrint;
//}

DanilasGame::~DanilasGame()
{
	GoToXY(0, (this->Field_Height + 5), ' ');
}

// Создание поля
void DanilasGame::Create_Field(const short& Field_Width, const short& Field_Height)
{
	HIDE_CURSOR(false);

	this->Field_Width = Field_Width;
	this->Field_Height = Field_Height;

	Change_Symbol_Color(Colors::RED); // изменил цвет на красный

	for (short i = 0; i < Field_Width + 2; i++)
	{
		GoToXY(i, 0, 'X');
		std::this_thread::sleep_for(std::chrono::microseconds(START_ANIMATION));
	}

	for (short i = 1; i < Field_Height + 2; i++)
	{
		GoToXY(Field_Width + 2 - 1, i, 'X');
		std::this_thread::sleep_for(std::chrono::microseconds(START_ANIMATION));
	}

	for (short i = Field_Width + 2 - 2; i >= 0; i--)
	{
		GoToXY(i, Field_Height + 2 - 1, 'X');
		std::this_thread::sleep_for(std::chrono::microseconds(START_ANIMATION));
	}

	for (short i = Field_Height + 2 - 2; i != 0; i--)
	{
		GoToXY(0, i, 'X');
		std::this_thread::sleep_for(std::chrono::microseconds(START_ANIMATION));
	}

	Change_Symbol_Color(Colors::WHITE); // изменил цвет на обычный

	HIDE_CURSOR(true);
}

// Стартовая позиция врага
void DanilasGame::Create_Enemy()
{
	srand(time(NULL)); // чтобы числа при перезапуске не повторялись

	this->EnemyX = Generate_Random_X();
	this->EnemyY = Generate_Random_Y();

	// Случай одновременного совпадения X Y
	if (this->EnemyX == this->PlayerX && this->EnemyY == this->PlayerY)
	{
		if (rand() % 2)
		{
			if (rand() % 2)
				Creat_Different_X();
			else
				Creat_Different_Y();
		}
		else
		{
			Creat_Different_X();
			Creat_Different_Y();
		}
	}

	// Случай совпадения X
	else if (this->EnemyX == this->PlayerX)
	{
		if (rand() % 2)
			Creat_Different_X();

	}

	// Случай одновременного совпадения Y
	else if (this->EnemyY == this->PlayerY)
	{
		if (rand() % 2)
			Creat_Different_Y();
	}

	// Случай одновременного НЕсовпадения X Y
	else
	{
		if (rand() % 2)
		{
			if (rand() % 2)
				this->PlayerX = this->EnemyX;
			else
				this->PlayerY = this->EnemyY;
		}
	}

	GoToXY(this->EnemyX, this->EnemyY, ENEMY_SYMBOL);
}

// Стартовая позиция игрока
void DanilasGame::Create_Player()
{
	this->PlayerX = Generate_Random_X();
	this->PlayerY = Generate_Random_Y();

	// Случай одновременного совпадения X Y
	if (this->EnemyX == this->PlayerX && this->EnemyY == this->PlayerY)
	{
		if (rand() % 2)
		{
			if (rand() % 2)
				Creat_Different_X();
			else
				Creat_Different_Y();
		}
		else
		{
			Creat_Different_X();
			Creat_Different_Y();
		}
	}

	// Случай совпадения X
	else if (this->EnemyX == this->PlayerX)
	{
		if (rand() % 2)
			Creat_Different_X();

	}

	// Случай одновременного совпадения Y
	else if (this->EnemyY == this->PlayerY)
	{
		if (rand() % 2)
			Creat_Different_Y();
	}

	// Случай одновременного НЕсовпадения X Y
	else
	{
		if (rand() % 2)
		{
			if (rand() % 2)
				this->PlayerX = this->EnemyX;
			else
				this->PlayerY = this->EnemyY;
		}
	}

	GoToXY(this->PlayerX, this->PlayerY, PLAYER_SYMBOL);

	this->GunX = this->PlayerX + 1;
	this->GunY = this->PlayerY;

	this->BulletX = this->PlayerX + 2;
	this->BulletY = this->PlayerY;

	GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
	GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);
}

void DanilasGame::Move_Player()
{
	thread playerThread([&]() {this->Move_Logic(); });
	playerThread.detach();
}

void DanilasGame::Move_Gun()
{
	thread gunThread([&]() {this->Move_Gun_Logic(); });
	gunThread.detach();
}

void DanilasGame::Move_Gun_Logic()
{
	short ButtonCod;

	for (;;)
	{
		_kbhit();
		ButtonCod = _getch();

		switch (ButtonCod)
		{

			//UP
		case 119:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX;
			this->GunY = this->PlayerY - 1;

			this->BulletX = this->PlayerX;
			this->BulletY = this->PlayerY - 2;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//DOWN
		case 115:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX;
			this->GunY = this->PlayerY + 1;

			this->BulletX = this->PlayerX;
			this->BulletY = this->PlayerY + 2;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//RIGHT
		case 100:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX + 1;
			this->GunY = this->PlayerY;

			this->BulletX = this->PlayerX + 2;
			this->BulletY = this->PlayerY;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);
			break;
		}

		//LEFT
		case 97:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX - 1;
			this->GunY = this->PlayerY;

			this->BulletX = this->PlayerX - 2;
			this->BulletY = this->PlayerY;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);
			break;
		}

		}
	}
}

void DanilasGame::Move_Logic()
{
	short ButtonCod;

	short temp;

	for (;;)
	{
		/*_kbhit();*/
		ButtonCod = _getch();

		temp = _getch();

		if (temp) ButtonCod = temp;

		switch (ButtonCod)
		{

			//UP
		case 72:
		{
			GoToXY(this->PlayerX, this->PlayerY, ' ');
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->PlayerY--;
			this->GunY--;
			this->BulletY--;

			if (!this->PlayerY || !this->GunY || !this->BulletY)
			{
				GoToXY(this->PlayerX, ++(this->PlayerY), PLAYER_SYMBOL);
				GoToXY(this->GunX, ++(this->GunY), GUN_SYMBOL);
				GoToXY(this->BulletX, ++(this->BulletY), BULLET_SYMBOL);

				break;
			}

			GoToXY(this->PlayerX, this->PlayerY, PLAYER_SYMBOL);
			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//DOWN
		case 80:
		{
			GoToXY(this->PlayerX, this->PlayerY, ' ');
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->PlayerY++;
			this->GunY++;
			this->BulletY++;

			if ((this->PlayerY == this->Field_Height + 2 - 1) || (this->GunY == this->Field_Height + 2 - 1) || (this->BulletY == this->Field_Height + 2 - 1))
			{
				//this->PlayerY--;

				GoToXY(this->PlayerX, --(this->PlayerY), PLAYER_SYMBOL);
				GoToXY(this->GunX, --(this->GunY), GUN_SYMBOL);
				GoToXY(this->BulletX, --(this->BulletY), BULLET_SYMBOL);

				break;
			}

			GoToXY(this->PlayerX, this->PlayerY, PLAYER_SYMBOL);
			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//LEFT
		case 75:
		{
			GoToXY(this->PlayerX, this->PlayerY, ' ');
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->PlayerX--;
			this->GunX--;
			this->BulletX--;

			if (!PlayerX || !this->GunX || !this->BulletX)
			{
				//PlayerX++;

				GoToXY(++(this->PlayerX), this->PlayerY, PLAYER_SYMBOL);
				GoToXY(++(this->GunX), this->GunY, GUN_SYMBOL);
				GoToXY(++(this->BulletX), this->BulletY, BULLET_SYMBOL);

				break;
			}

			GoToXY(this->PlayerX, this->PlayerY, PLAYER_SYMBOL);
			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//RIGHT
		case 77:
		{
			GoToXY(this->PlayerX, this->PlayerY, ' ');
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->PlayerX++;
			this->GunX++;
			this->BulletX++;

			if ((this->PlayerX == this->Field_Width + 2 - 1) || (this->GunX == this->Field_Width + 2 - 1) || (this->BulletX == this->Field_Width + 2 - 1))
			{
				//this->PlayerX--;

				GoToXY(--(this->PlayerX), this->PlayerY, PLAYER_SYMBOL);
				GoToXY(--(this->GunX), this->GunY, GUN_SYMBOL);
				GoToXY(--(this->BulletX), this->BulletY, BULLET_SYMBOL);

				break;
			}

			GoToXY(this->PlayerX, this->PlayerY, PLAYER_SYMBOL);
			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);
			break;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//UP
		case 119:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX;
			this->GunY = this->PlayerY - 1;

			this->BulletX = this->PlayerX;
			this->BulletY = this->PlayerY - 2;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//DOWN
		case 115:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX;
			this->GunY = this->PlayerY + 1;

			this->BulletX = this->PlayerX;
			this->BulletY = this->PlayerY + 2;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);

			break;
		}

		//RIGHT
		case 100:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX + 1;
			this->GunY = this->PlayerY;

			this->BulletX = this->PlayerX + 2;
			this->BulletY = this->PlayerY;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);
			break;
		}

		//LEFT
		case 97:
		{
			GoToXY(this->GunX, this->GunY, ' ');
			GoToXY(this->BulletX, this->BulletY, ' ');

			this->GunX = this->PlayerX - 1;
			this->GunY = this->PlayerY;

			this->BulletX = this->PlayerX - 2;
			this->BulletY = this->PlayerY;

			GoToXY(this->GunX, this->GunY, GUN_SYMBOL);
			GoToXY(this->BulletX, this->BulletY, BULLET_SYMBOL);
			break;
		}
		}
	}
}

void DanilasGame::Move_Enemy()
{
	HIDE_CURSOR(false);
	for (;;)
	{
		if (this->EnemyX == this->PlayerX && this->EnemyY == this->PlayerY) break;

		if (this->EnemyX != this->PlayerX && this->EnemyY != this->PlayerY)
		{
			if (this->EnemyX < this->PlayerX && this->EnemyY > this->PlayerY)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				/*this->EnemyX++;
				this->EnemyY--;*/

				GoToXY(++(this->EnemyX), --(this->EnemyY), ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
			if (this->EnemyX > this->PlayerX && this->EnemyY < this->PlayerY)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				/*this->EnemyX--;
				this->EnemyY++;*/

				GoToXY(--(this->EnemyX), ++(this->EnemyY), ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
			if (this->EnemyX > this->PlayerX && this->EnemyY > this->PlayerY)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				/*this->EnemyX--;
				this->EnemyY--;*/

				GoToXY(--(this->EnemyX), --(this->EnemyY), ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
			if (this->EnemyX < this->PlayerX && this->EnemyY < this->PlayerY)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				/*this->EnemyX++;
				this->EnemyY++;*/

				GoToXY(++(this->EnemyX), ++(this->EnemyY), ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
		}

		if (this->EnemyY != this->PlayerY)
		{
			if (this->EnemyX == this->PlayerX && this->EnemyY < this->PlayerY)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				/*this->EnemyY++;*/

				GoToXY(this->EnemyX, ++(this->EnemyY), ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
			if (this->EnemyX == this->PlayerX && this->EnemyY > this->PlayerY)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				//this->EnemyY--;

				GoToXY(this->EnemyX, --(this->EnemyY), ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
		}

		if (this->EnemyX != this->PlayerX)
		{
			if (this->EnemyX < this->PlayerX)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				//this->EnemyX++;

				GoToXY(++(this->EnemyX), this->EnemyY, ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
			if (this->EnemyX > this->PlayerX)
			{
				GoToXY(this->EnemyX, this->EnemyY, ' ');

				/*this->EnemyX--;*/

				GoToXY(--(this->EnemyX), this->EnemyY, ENEMY_SYMBOL);
				std::this_thread::sleep_for(std::chrono::milliseconds(TIME_OUT));
				continue;
			}
		}
	}
	HIDE_CURSOR(true);
}

/////////////////////////////////////////////////Работа с консолью/////////////////////////////////////////////////////////////////

// Поменять цвет символа
void DanilasGame::Change_Symbol_Color(const int& color)
{
	SetConsoleTextAttribute(hConsole, color);
}

// Спрятать курсор
void DanilasGame::HIDE_CURSOR(const bool& visability)
{
	GetConsoleCursorInfo(hConsole, &MyCursor);
	MyCursor.bVisible = visability;
	SetConsoleCursorInfo(hConsole, &MyCursor);
}

// Переместить курсор по координатам
void DanilasGame::GoToXY(const short& x, const short& y, const char& symbol)
{
	this->SavePrint.lock();

	COORD Axes = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Axes);
	cout << symbol;

	this->SavePrint.unlock();
}
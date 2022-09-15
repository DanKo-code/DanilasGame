#include "DanilasGame.h"

int main()
{
	DanilasGame Test;

	Test.Create_Field(80, 40);

	Test.Create_Enemy();

	Test.Create_Player();

	Test.Move_Player();

	Test.Move_Enemy();

	Test.Move_Gun();


}
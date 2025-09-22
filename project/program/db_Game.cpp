#include "db_Game.h"
#include<string>

GameDataBase::GameDataBase()
{
	std:: string path = "data/csv/player.csv";
	playerTable_.LoadFromCsv(path);
}

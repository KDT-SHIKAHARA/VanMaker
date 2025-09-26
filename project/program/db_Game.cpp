#include "db_Game.h"
#include<string>

GameDataBase::GameDataBase()
{
	playerTable_.LoadFromCsv("data/csv/player.csv");
	enemyTable_.LoadFromCsv("data/csv/enemy.csv");
	animDataTable_.LoadFromCsv("data/csv/anim_data.csv");

}

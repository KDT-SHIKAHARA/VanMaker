#include "db_Game.h"
#include<string>

GameDataBase::GameDataBase()
{
	playerTable_.LoadFromCsv("data/csv/player.csv");
	enemyTable_.LoadFromCsv("data/csv/enemy.csv");
	animDataTable_.LoadFromCsv("data/csv/anim_data.csv");
	enemySizeTable_.LoadFromCsv("data/csv/enemy_size.csv");
	weaponDataTable_.LoadFromCsv("data/csv/weapon.csv");
	imageTable_.LoadFromCsv("data/csv/image_data.csv");
	dropExpTable_.LoadFromCsv("data/csv/dropexp.csv");
	expTable_.LoadFromCsv("data/csv/exp_table.csv");
}

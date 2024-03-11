
#ifndef GAME_MAP_H	
#define GAME_MAP_H

#include "CommonFunction.h"
#include "BaseObject.h"
#define MAX_TILE 20

class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	void SetMap(Map& map_data) { game_map_ = map_data; };
	Map getMap()const { return game_map_; };

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILE];

};

#endif
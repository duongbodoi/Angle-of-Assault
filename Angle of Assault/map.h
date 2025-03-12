#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
#include<vector>
#include <sstream>
#include<map>
#include<set>
class TileMat :public Ltexture {
public:
	TileMat() { ; }
	~TileMat() { ; }


private:

};


class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }
	void loadmap(string path);
	void load_tile(SDL_Renderer* renderer);
	void draw_map(SDL_Renderer* renderer);
	Map getmap() { return game_map_; }
	void setmap(Map& mapdata) { game_map_ = mapdata; };
private:
	Map game_map_;
	map<string, TileMat> tilemat;// cac dang tile map

};
static set<string> nametilemat;

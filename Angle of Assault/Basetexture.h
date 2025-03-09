#pragma once
#include"Mainfunc.h"
class Ltexture {
public:
	Ltexture();
	~Ltexture();
	void set_rect(const int x, const int y) { mrect.x = x, mrect.y = y; }
	SDL_Rect get_rect() const { return mrect; }
	SDL_Texture* get_texture() const { return mTexture; }
	bool loadfromfile(std::string file, SDL_Renderer* screen);
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void free();
protected:
	SDL_Texture* mTexture;
	SDL_Rect mrect;
};
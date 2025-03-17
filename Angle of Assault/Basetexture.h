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
	bool loadfromtext(SDL_Renderer* screen,string text, SDL_Color color, string path_font);
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void render360(SDL_Renderer*des,int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void free();
protected:
	SDL_Texture* mTexture;
	SDL_Rect mrect;
};
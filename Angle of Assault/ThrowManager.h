#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
class throw_move :public Ltexture {
public:
	enum shotarrow {
		reload_ = 0,
		shot_ = 1,
	};
	throw_move();
	~throw_move();
	void Handle_event(SDL_Event e, SDL_Renderer* renderer);
	void arrow_shot(SDL_Rect archer_rect);
	void show(SDL_Renderer* des);
	virtual bool load_img(std::string file, SDL_Renderer* renderer);
	void set_clip();
	int v0 = 1;
	int phi = 30;
	double time = 0;
	double x0=0, y0=0;
private:
	double vel_x, vel_y;
	double x_pos, y_pos;
	Input input_type;
	int width_frame;
	int heightframe;
	int frame;
	SDL_Rect frame_clip[8];
};
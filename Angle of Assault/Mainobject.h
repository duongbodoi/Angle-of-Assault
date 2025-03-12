#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
class mObject :public Ltexture {
public:
	mObject();
	~mObject();
	enum animate {
		walk_r = 0,
		walk_l = 1,
		reload_ = 2,
		shot_ = 3,
	};
	virtual bool load_img(std::string file, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void Handle_event(SDL_Event e, SDL_Renderer* renderer);
	void set_clip();
	void move(Map& mapdata);
	void setmap_xy(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void Ghimmap(Map& mapdata);
	void checkmap(Map& mapdata);
	int getx_pos() { return x_pos; };
	int gety_pos() { return y_pos; };
	const int v = 2;

private:
	double vel_x, vel_y;
	double x_pos, y_pos;
	int width_frame;
	int heightframe;
	SDL_Rect frame_clip[8];
	Input input_type;
	int frame;
	int status;
	int map_x_;
	int map_y_;
};
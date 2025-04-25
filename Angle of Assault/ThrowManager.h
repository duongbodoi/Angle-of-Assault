#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
class throw_move :public Ltexture {
public:
	
	throw_move();
	~throw_move();
	void Handle_event(SDL_Event e, SDL_Renderer* renderer);
	void arrow_shot(double x, double y, Map& mapdata);
	void show(SDL_Renderer* des);
	virtual bool load_img(std::string file, SDL_Renderer* renderer);
	void set_clip();
	void Ghimmap(Map& mapdata);
	void checkmap(Map& mapdata);
	void setmap_xy(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	Input get_input() { return input_type; };
	void set_intput(int x) { input_type.shot = x; };
	bool getcolider() { return colider; };
	void set_colider(bool check) { colider = check; };
	int getx_pos() { return x_pos; };
	int gety_pos() { return y_pos; };
	int v0 = 0;
	int phi = 0;
	double time = 0;
	double x0=0, y0=0;
	int v0_last = 0;
	void setpause(bool k) { pause = k; };
	bool getpause() { return pause; };
private:
	double vel_x, vel_y;
	double x_pos, y_pos;
	Input input_type;
	int width_frame;
	int heightframe;
	int frame;
	SDL_Rect frame_clip[8];
	int map_x_;
	int map_y_;
	bool colider;
	bool pause;
};
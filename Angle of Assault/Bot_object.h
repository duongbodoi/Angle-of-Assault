#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
class bot_object :public Ltexture {
public:
	bot_object();
	~bot_object();
	enum animate {
		walk_r = 0,
		walk_l = 1,
		reload_ = 2,
		shot_ = 3,
	};
	virtual bool load_img(std::string file, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void set_clip();
	void move(Map& mapdata,bool turn);
	void ai_control();
	void setmap_xy(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void Ghimmap(Map& mapdata);
	void checkmap(Map& mapdata);
	int getx_pos() { return x_pos; };
	int gety_pos() { return y_pos; };
	Input get_input() { return input_type; };
	void set_intputshot(int x) { input_type.shot = x; };
	void set_inputangle(int x) { input_type.angle = x; };
	void set_inputreload(int x) { input_type.reload = x; };
	void reset();
	const int v = 4;
	const int HPmax = 100;
	int hp = 100;
	void setpause(bool k) { pause = k; };
	bool getpause(){ return pause; };
private:
	bool pause;
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
	int smax;
	int ide_num;
	int Rmax;
	int	Lmax;
	int idemax;
};
#pragma once
#include"Mainfunc.h"
#include"Basetexture.h"
#include"Mainobject.h"
#include"ThrowManager.h"
#include"map.h"
#include"object_bar.h"
#include"Timer.h";
#include"Bot_object.h"
#include"bot_throw.h"
enum status {
	button_in=0,
	button_out=1,
};
class button :public Ltexture {
public:
	
	
	button() ;
	void handleEvent(SDL_Event* e);
	void show(SDL_Renderer* des);
	void set_start(bool k) { start = k; };
	bool get_start() { return start; };
	virtual bool load_img(std::string file, SDL_Renderer* renderer);
	void set_clip();

private:
	status current_status;
	bool start;
	SDL_Rect frame_clip[2];
	int width_frame;
	int heightframe;
};
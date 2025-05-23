﻿#include"Bot_object.h"
bot_object::bot_object() {
	vel_x = 0;
	vel_y = 0;
	x_pos = 2500;
	y_pos = 0;
	frame = 0;
	width_frame = 0;
	heightframe = 0;
	status = -1;

	input_type.reload = 0;
	input_type.right = 0;
	input_type.shot = 0;
	map_x_ = 0;
	map_y_ = 0;
	smax = 0;
	Rmax = 0;
	Lmax = 0;
	idemax = 0;
	pause = false;
}
bot_object::~bot_object() {

}

bool bot_object::load_img(std::string file, SDL_Renderer* renderer) {
	bool ret = Ltexture::loadfromfile(file, renderer);
	if (ret == true) {
		width_frame = 74;
		heightframe = mrect.h;
		mrect.w = width_frame;
		mrect.h = width_frame;
	}
	return ret;
}
void bot_object::set_clip() {
	if (width_frame > 0 and heightframe > 0) {
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame;
		frame_clip[0].h = heightframe;

		frame_clip[1].x = width_frame;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame;
		frame_clip[1].h = heightframe;

		frame_clip[2].x = width_frame * 2;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = heightframe;

		frame_clip[3].x = width_frame * 3;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame;
		frame_clip[3].h = heightframe;

		frame_clip[4].x = width_frame * 4;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame;
		frame_clip[4].h = heightframe;

		frame_clip[5].x = width_frame * 5;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame;
		frame_clip[5].h = heightframe;

		frame_clip[6].x = width_frame * 6;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame;
		frame_clip[6].h = heightframe;

		frame_clip[7].x = width_frame * 7;
		frame_clip[7].y = 0;
		frame_clip[7].w = width_frame;
		frame_clip[7].h = heightframe;


	}
}
void bot_object::show(SDL_Renderer* des) {
	static int last_status = -1;

	bool need_reload_img = (status != last_status);

	if (need_reload_img) {
		if (status == reload_ || status == shot_) {
			load_img("img/sasuke_reload.png", des);
		}
		else if (status == walk_r) {
			load_img("img/sasukeR.png", des);
		}
		else if (status == walk_l) {
			load_img("img/sasukeL.png", des);
		}
		last_status = status;
	}

	// Xử lý animation
	if (input_type.shot == 1) {
		frame += 2;
		if (pause) frame -= 2;
		if (frame / 16 >= 5) {
			frame = 15; 
			input_type.shot = 0;  
			status = -1;  
		}
	}
	else if (input_type.reload == 1) {
		frame = 16;  // Giữ nguyên trạng thái nạp đạn
	}
	else if (input_type.left == 1 || input_type.right == 1) {
		frame += 1;
		if (pause) frame -= 1;
		if (frame / 16 >= 7) { 
			frame = 0;
		}
	}
	else {
		frame = 15;  
	}

	// Render object
	mrect.x = x_pos - map_x_;
	mrect.y = y_pos - map_y_;
	SDL_Rect* current_clip = &frame_clip[frame / 16];
	SDL_Rect offset = { mrect.x, mrect.y, width_frame, heightframe };
	SDL_RenderCopy(des, mTexture, current_clip, &offset);
}



void bot_object::move(Map& mapdata,bool turn) {
	vel_x = 0;
	vel_y += 2;
	if (pause) vel_y -= 2;
	if (vel_y >= 10) vel_y = 10;
	if (input_type.left == 1) 
	{
		vel_x -= v;
		if (pause) vel_x += v;
	}
	else if (input_type.right == 1) 
	{
		vel_x += v;
		if (pause) vel_x -= v;
	}
	if (input_type.jumb == 1)
	{
		vel_y = -30;
		input_type.jumb = 0;
	}
	checkmap(mapdata);
	if(turn)
	{
		Ghimmap(mapdata);
	}
}
void bot_object::Ghimmap(Map& mapdata) {
	mapdata.start_x = x_pos - SCREEN_WIDTH / 2;
	if (mapdata.start_x < 0) mapdata.start_x = 0;
	else if (mapdata.start_x + SCREEN_WIDTH >= mapdata.max_x) mapdata.start_x = mapdata.max_x - SCREEN_WIDTH;
	mapdata.start_y = y_pos - SCREEN_HEIGHT / 2;

	if (mapdata.start_y < 0) mapdata.start_y = 0;
	else if (mapdata.start_y + SCREEN_HEIGHT >= mapdata.max_y) mapdata.start_y = mapdata.max_y - SCREEN_HEIGHT;

}
void bot_object::checkmap(Map& mapdata) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//
	int h_min = heightframe < 64 ? heightframe : 64;
	x1 = (x_pos + vel_x) / 64;
	x2 = (x_pos + vel_x + width_frame - 1) / 64;

	y1 = y_pos / 64;
	y2 = (y_pos + h_min - 1) / 64;

	if (x1 >= 0 and x2 < MAX_MAP_X and y1 >= 0 and y2 < MAX_MAP_Y) {
		if (vel_x > 0) {
			if (mapdata.tile[y1][x2] != "0" or mapdata.tile[y2][x2] != "0") {
				x_pos = x2 * 64;
				x_pos -= width_frame + 1;
				vel_x = 0;
			}
		}
		else {
			if (mapdata.tile[y1][x1] != "0" or mapdata.tile[y2][x1] != "0") {
				x_pos = (x1 + 1) * 64;
				vel_x = 0;
			}
		}

	}

	//
	int w_min = width_frame < 64 ? width_frame : 64;
	x1 = (x_pos + vel_x) / 64;
	x2 = (x_pos + w_min) / 64;

	y1 = (y_pos + vel_y) / 64;
	y2 = (y_pos + vel_y + heightframe - 1) / 64;
	if (x1 >= 0 and x2 < MAX_MAP_X and y1 >= 0 and y2 < MAX_MAP_Y) {
		if (vel_y > 0) {
			if (mapdata.tile[y2][x1] != "0" or mapdata.tile[y2][x2] != "0") {
				y_pos = y2 * 64;
				y_pos -= heightframe + 1;
				vel_y = 0;
			}
		}

	}
	x_pos += vel_x;
	y_pos += vel_y;
	smax += vel_x;

}
void bot_object::ai_control() {
	if (input_type.right == 1) {
		ide_num++;
		if (pause) ide_num--;
		status = walk_r;
		if (smax > Rmax) {
			smax = 0;
			input_type.left = 1;
			input_type.right = 0;
		}
		if (x_pos + vel_x >= 49 * 64) {
			smax = 0;
			input_type.left = 1;
			input_type.right = 0;
		}
	}
	if (input_type.left == 1) {
		status = walk_l;
		ide_num++;
		if (pause) ide_num--;
		if (smax < -Lmax) {
			smax = 0;
			input_type.left = 0;
			input_type.right = 1;
		}
		if (x_pos - vel_y <= 64 * 31) {
			smax = 0;
			input_type.left = 0;
			input_type.right = 1;
		}
	}
	if (ide_num >= idemax) {
		input_type.left = 0;
		input_type.right = 0;
		ide_num = 0;
		input_type.angle = 1;

	}
	if (input_type.reload == 1) {
		status = reload_;
		
		input_type.angle = 0;
	}
	if (input_type.shot == 1 && status != shot_) {
		status = shot_;
		input_type.reload = 0;
		input_type.angle = 0;
	}
}

void bot_object::reset() {
	
	input_type.right = randomxy(0,1);
	if (input_type.right == 1) {
		input_type.left = 0;
		status = walk_r;

	}
	else {
		input_type.left = 1;
		status = walk_l;
	}
	input_type.reload = 0;
	input_type.shot = 0;
	input_type.angle = 0;

	smax = 0;
	ide_num = 0;
	Rmax = randomxy(130, 300);
	Lmax = randomxy(130, 300);
	idemax = randomxy(50, 150);
}

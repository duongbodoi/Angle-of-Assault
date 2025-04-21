#include"bot_throw.h"
bot_throw::bot_throw() {
	vel_x = 0;
	vel_y = 0;
	x_pos = 0;
	y_pos = 0;
	input_type.reload = 0;
	input_type.shot = 0;
	map_x_ = 0;
	map_y_ = 0;
	
}
bot_throw::~bot_throw() {

}
void bot_throw::arrow_shot(double x, double y, Map& mapdata) {
	x0 = x + 25;
	y0 = y + 20;
	double radian = phi * PI / 180;
	if (input_type.angle == 1) {
		if (input_type.aim_down == 1) {
			phi--;
		}
		if (input_type.aim_up == 1) {
			phi++;
		}
	}
	if (input_type.reload == 1) {
		v0 += 1;
		if (v0 >= 200) v0 = 200;
		time = 0;
		x_pos = x0;
		y_pos = y0;
		vel_x = v0 * cos(radian);
		vel_y = v0 * sin(radian);

	}
	if (input_type.shot == 1) {
		time += 0.1;
		vel_x = v0 * cos(radian) * time;
		vel_y = v0 * sin(radian) - 9.8 * time;
		x_pos = x0 - v0 * cos(radian) * time;;
		y_pos = y0 - (v0 * sin(radian) * time - 0.5 * 9.8 * time * time);

	}
	Ghimmap(mapdata);
	checkmap(mapdata);
}
void bot_throw::Ghimmap(Map& mapdata) {
	mapdata.start_x = x_pos - SCREEN_WIDTH / 2;
	if (mapdata.start_x < 0) mapdata.start_x = 0;
	else if (mapdata.start_x + SCREEN_WIDTH >= mapdata.max_x) mapdata.start_x = mapdata.max_x - SCREEN_WIDTH;
	mapdata.start_y = y_pos - SCREEN_HEIGHT / 2;

	if (mapdata.start_y < 0) mapdata.start_y = 0;
	else if (mapdata.start_y + SCREEN_HEIGHT >= mapdata.max_y) mapdata.start_y = mapdata.max_y - SCREEN_HEIGHT;

}
void bot_throw::checkmap(Map& mapdata) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//
	int h_min = heightframe < 64 ? heightframe : 64;
	x1 = (x_pos) / 64;
	x2 = (x_pos + width_frame - 1) / 64;

	y1 = y_pos / 64;
	y2 = (y_pos + h_min - 1) / 64;

	if (x1 >= 0 and x2 < MAX_MAP_X and y1 >= 0 and y2 < MAX_MAP_Y) {
		if (vel_x > 0) {
			if (mapdata.tile[y1][x2] != "0" or mapdata.tile[y2][x2] != "0") {
				x_pos = x2 * 64;
				x_pos -= width_frame + 1;
				//v0 = 0;
				time = 0;
				input_type.shot = 0;
				set_colider(true);
			}
		}
		else {
			if (mapdata.tile[y1][x1] != "0" or mapdata.tile[y2][x1] != "0") {
				x_pos = (x1 + 1) * 64;
				input_type.shot = 0;
				//v0 = 0;
				time = 0;
				set_colider(true);

			}
		}

	}

	//
	int w_min = width_frame < 64 ? width_frame : 64;
	x1 = (x_pos) / 64;
	x2 = (x_pos + w_min) / 64;

	y1 = (y_pos) / 64;
	y2 = (y_pos + heightframe - 1) / 64;
	if (x1 >= 0 and x2 < MAX_MAP_X and y1 >= 0 and y2 < MAX_MAP_Y) {
		if (vel_y > 0) {
			if (mapdata.tile[y2][x1] != "0" or mapdata.tile[y2][x2] != "0") {
				y_pos = y2 * 64;
				y_pos -= heightframe + 1;
				//v0 = 0;
				time = 0;
				input_type.shot = 0;
				set_colider(true);

			}
		}

	}

	//
	if (x_pos<0 or x_pos>mapdata.max_x or y_pos > mapdata.max_y)
	{
		//v0 = 0;
		time = 0;
		input_type.shot = 0;
		set_colider(true);

	}
	if (colider) {
		input_type.angle = 0;
		input_type.reload = 0;
		input_type.shot = 0;
		//v0 = 0;
		time = 0;
	}
}
void bot_throw::show(SDL_Renderer* des) {
	if (input_type.shot == 1) {
		frame++;
		if (frame / 4 >= 2) frame = 0;
		mrect.x = x_pos - map_x_;
		mrect.y = y_pos - map_y_;
		SDL_Rect* current_clip = &frame_clip[frame / 4];
		SDL_Rect offset = { mrect.x,mrect.y,width_frame,heightframe };
		SDL_RenderCopy(des, mTexture, current_clip, &offset);
	}
	if (input_type.reload == 1) {
		frame++;
		if (frame / 4 >= 2) frame = 0;
		mrect.x = x_pos - map_x_;
		mrect.y = y_pos - map_y_;
		SDL_Rect* current_clip = &frame_clip[frame / 4];
		SDL_Rect offset = { mrect.x,mrect.y,width_frame,heightframe };
		SDL_RenderCopyEx(des, mTexture, current_clip, &offset, 120, NULL, SDL_FLIP_NONE);
	}


}

bool bot_throw::load_img(std::string file, SDL_Renderer* renderer) {
	bool ret = Ltexture::loadfromfile(file, renderer);
	if (ret == true) {
		width_frame = mrect.w / 2;
		heightframe = mrect.h;
		mrect.w = width_frame;
		mrect.h = heightframe;
	}
	return ret;
}
void bot_throw::set_clip() {
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


	}
}
void bot_throw::ai_control() {
	if (input_type.angle == 1) {
		if (phi == phi_shot) {
			input_type.angle = 0;
			input_type.reload = 1;
			input_type.aim_up = 0;
			input_type.aim_down = 0;
		}
		if (phi > phi_shot) {
			input_type.aim_down = 1;
			input_type.aim_up = 0;
		}
		if (phi < phi_shot) {
			input_type.aim_up = 1;
			input_type.aim_down = 0;

		}
	}
	if (input_type.reload == 1) {
		input_type.angle = 0;
		if (v0 == v0_shot) {
			input_type.reload = 0;
			input_type.shot = 1;
			input_type.angle = 0;
		}
	}
	if (input_type.shot == 1) {
		input_type.angle = 0;
		input_type.reload = 0;
	}
}
void bot_throw::reset(double x,double y) {
	x_pos = 1;
	y_pos = 1;
	v0_last = v0;
	v0 = 0;
	input_type.aim_down = 0;
	input_type.aim_up = 0;
	input_type.angle = 0;
	input_type.reload = 0;
	input_type.shot = 0;
	phi_shot = randomxy(20, 60);
	cout << phi_shot;
	v0_shot = caculate(x, y);
}
int bot_throw::caculate(double x,double y) {
	double dx = x0-x;
	double dy = y0-y;
	double radian = phi_shot * PI / 180;
	double tan_theta = tan(radian);
	double cos_theta = cos(radian);
	double v0_sq = (9.8 * dx * dx) / (2 * cos_theta * cos_theta * (dy + dx * tan_theta));
	return sqrt(v0_sq);
}

#include"Mainobject.h"
mObject::mObject() {
	vel_x = 0;
	vel_y = 0;
	x_pos = 15;
	y_pos = 0;
	frame = 0;
	width_frame = 0;
	heightframe = 0;
	status = -1;
}
mObject::~mObject() {

}
bool mObject::load_img(std::string file, SDL_Renderer* renderer) {
	bool ret = Ltexture::loadfromfile(file, renderer);
	if (ret == true) {
		width_frame = 94;
		heightframe = mrect.h;
	}
	return ret;
}
void mObject::set_clip() {
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
void mObject::show(SDL_Renderer* des) {
	if (status == walk_l) {
		load_img("img/moveL.png", des);
	}
	else if (status == reload_ or status == shot_) {
		load_img("img/shot_reload.png", des);

	}
	else if (status == walk_r) {
		load_img("img/moveR.png", des);
	}

	if (input_type.left == 1 or input_type.right == 1) {
		frame++;
		if (frame / 16 >= 8) {
			frame = 16;
		}
	}
	else if (input_type.reload == 1) {
		frame++;
		if (frame / 16 >= 1) {
			frame = 16;
		}
	}
	else if (input_type.shot == 1) {
		frame += 3;
		if (frame / 16 >= 4) {
			input_type.shot = 0;
		}
	}
	else {
		frame = 15;
	}

	mrect.x = x_pos-map_x_;
	mrect.y = y_pos-map_y_;
	SDL_Rect* current_clip = &frame_clip[frame / 16];
	SDL_Rect offset = { mrect.x,mrect.y,width_frame,heightframe };
	SDL_RenderCopy(des, mTexture, current_clip, &offset);
}
void mObject::Handle_event(SDL_Event e, SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN and e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			
			status = walk_r;
			input_type.right = 1;
			input_type.left = 0;
			break;
		}
		case SDLK_LEFT:
		{
			
			
				
				status = walk_l;
				input_type.left = 1;
				input_type.right = 0;
			

			break;
		}
		case SDLK_SPACE:
		{
			status = reload_;
			input_type.reload = 1;
			break;
		}
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP and e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status = -1;
			
			input_type.right = 0;
			

			break;
		}
		case SDLK_LEFT:
		{
			status = -2;
			
			input_type.left = 0;
			break;

		}
		case SDLK_SPACE:
		{

			status = shot_;
			input_type.reload = 0;
			input_type.shot = 1;
			break;

		}
		default:
			break;
		}
	}
}
void mObject::move(Map& mapdata) {
	vel_x = 0;
	vel_y += 2;
	if (vel_y >= 10) vel_y = 10;
	if (input_type.left == 1) vel_x -= v;
	else if (input_type.right == 1) vel_x += v;
	x_pos += vel_x;
	y_pos += vel_y;
	Ghimmap(mapdata);
}
void mObject::Ghimmap(Map& mapdata) {
	mapdata.start_x = x_pos - SCREEN_WIDTH / 2;
	if (mapdata.start_x < 0) mapdata.start_x = 0;
	else if (mapdata.start_x + SCREEN_WIDTH >= mapdata.max_x) mapdata.start_x = mapdata.max_x - SCREEN_WIDTH;
	mapdata.start_y = y_pos - SCREEN_HEIGHT / 2;

	if (mapdata.start_y < 0) mapdata.start_y = 0;
	else if (mapdata.start_y + SCREEN_HEIGHT >= mapdata.max_y) mapdata.start_y = mapdata.max_y - SCREEN_HEIGHT;

}


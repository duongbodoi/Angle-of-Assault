#include"ThrowManager.h"
throw_move::throw_move() {
	vel_x = 0;
	vel_y = 0;
	x_pos = 0;
	y_pos = 300;
	
}
throw_move::~throw_move() {

}
void throw_move::Handle_event(SDL_Event e, SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.repeat == 0 and e.key.keysym.sym == SDLK_SPACE) v0 = 50;
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
		{
			input_type.reload = 1;
			input_type.shot = 0;
			break;
		}
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP and e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{

		case SDLK_SPACE:
		{
			input_type.reload = 0;
			input_type.shot = 1;
			break;

		}
		default:
			break;
		}
	}
}
void throw_move::arrow_shot(SDL_Rect archer_rect) {
	x0 = archer_rect.x + 5;
	y0 = archer_rect.y - 20;
	double radian = phi * PI / 180;
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
		x_pos = x0 + v0 * cos(radian) * time;;
		y_pos = y0 - (v0 * sin(radian) * time - 0.5 * 9.8 * time * time);

	}
}
void throw_move::show(SDL_Renderer* des) {
	if (input_type.shot == 1) {
		frame++;
		if (frame / 4 >= 2) frame = 0;
		mrect.x = x_pos;
		mrect.y = y_pos;
		SDL_Rect* current_clip = &frame_clip[frame / 4];
		SDL_Rect offset = { mrect.x,mrect.y,width_frame,heightframe };
		SDL_RenderCopy(des, mTexture, current_clip, &offset);
	}
	if (input_type.reload == 1) {
		frame++;
		if (frame / 4 >= 2) frame = 0;
		mrect.x = x_pos;
		mrect.y = y_pos;
		SDL_Rect* current_clip = &frame_clip[frame / 4];
		SDL_Rect offset = { mrect.x,mrect.y,width_frame,heightframe };
		SDL_RenderCopy(des, mTexture, current_clip, &offset);
	}


}

bool throw_move::load_img(std::string file, SDL_Renderer* renderer) {
	bool ret = Ltexture::loadfromfile(file, renderer);
	if (ret == true) {
		width_frame = mrect.w / 3;
		heightframe = mrect.h;
	}
	return ret;
}
void throw_move::set_clip() {
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
#include"menu.h"
button::button() {
	mrect = { 0,0,0,0 };
	current_status = button_out;
	start = false;
	width_frame = 0;
	heightframe = 0;
}

void button::handleEvent(SDL_Event* e) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if (x < mrect.x) inside = false;
		if (x >= mrect.x and x > (mrect.x + width_frame)) inside = false;
		if (y < mrect.y) inside = false;
		if (y > mrect.y and y > mrect.y + heightframe) inside = false;
		if (!inside) {
			current_status=button_out;
		}
		else
		{
			current_status = button_in;
			if (e->type == SDL_MOUSEBUTTONDOWN) start=true;
			
		}
	}
}
bool button::load_img(std::string file, SDL_Renderer* renderer) {
	bool ret = Ltexture::loadfromfile(file, renderer);
	if (ret == true) {
		width_frame = mrect.w;
		heightframe = mrect.h/2;
		mrect.w = width_frame;
		mrect.h = heightframe;
	}
	return ret;
}
void button::set_clip() {
	if (width_frame > 0 and heightframe > 0) {
		frame_clip[button_in].x = 0;
		frame_clip[button_in].y = 0;
		frame_clip[button_in].w = width_frame;
		frame_clip[button_in].h = heightframe;

		frame_clip[button_out].x = 0;
		frame_clip[button_out].y = heightframe;
		frame_clip[button_out].w = width_frame;
		frame_clip[button_out].h = heightframe;
	}
}
void button::show(SDL_Renderer* des) {
	SDL_Rect* current_clip = &frame_clip[current_status];
	SDL_Rect offset = { mrect.x, mrect.y, width_frame, heightframe };
	SDL_RenderCopy(des, mTexture, current_clip, &offset);
}
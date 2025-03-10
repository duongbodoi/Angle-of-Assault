#include"Mainfunc.h"
#include"Basetexture.h"
bool Init() {
	bool check = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		check = false;
		cout << "error init";
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow("duongbodoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		check = false;
		cout << "error window";
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			cout << "error renderer";
			check = false;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			int imgflag = IMG_INIT_PNG;
			if (!(IMG_Init(imgflag) && imgflag)) {
				check = false;
				cout << "error IMG";
			}
		}
	}
	return check;
}
void close() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_QUIT;
}
class Ldot {
public:
	const int screendot_w = 20;
	const int screendot_h = 20;
	const int dot_vel = 10;
	Ldot();
	void handle_event(SDL_Event* e);
	void render();
	void move();

private:
	int velx, vely;
	int movex, movey;

};
Ldot::Ldot() {
	velx = 0;
	vely = 0;
	movex = 0;
	movey = 0;

}
void Ldot::handle_event(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
		switch (e->key.keysym.sym)
		{
		
		case SDLK_LEFT: velx -= dot_vel; break;
		case SDLK_RIGHT: velx += dot_vel; break;

		default:
			break;
		}
	}
	else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
		switch (e->key.keysym.sym)
		{
		
		case SDLK_LEFT: velx += dot_vel; break;
		case SDLK_RIGHT: velx -= dot_vel; break;

		default:
			break;
		}
	}
}
void Ldot::move() {
	movex += velx;
	if (movex < 0 or movex + screendot_w>1160) {
		movex -= velx;
	}
	movey += vely;
	if (movey < 0 or movey + screendot_h>800) {
		movey -= vely;
	}
}
double phi;
Ldot dot;
void Ldot::render() {
	SDL_Rect offset = { movex,movey,screendot_w,screendot_h };
	SDL_RenderFillRect(renderer, &offset);
}
class Dshot {
public:
	int shot_w = 30, shot_h = 30;
	int v0 = 100;
	Dshot();
	void handle_event(SDL_Event* e);
	void fire();
	void render();
private:
	int amo_x, amo_y;
	bool reload;
	bool start;
	double time;
	
	
};
Dshot shot;
Dshot::Dshot() {
	amo_x = 0;
	amo_y = 0;
	reload = true;
	start = false;
	time = 0;
	phi = 0;
}
void Dshot::render() {
	SDL_Rect offset = { amo_x,amo_y,shot_w,shot_h };
	SDL_RenderFillRect(renderer, &offset);
}
void Dshot::handle_event(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		if (e->key.repeat == 0 and e->key.keysym.sym == SDLK_r) v0 = 10;
		switch (e->key.keysym.sym)
		{
		case SDLK_r: {
			reload = true;
			v0 += 5;
			if (v0 >= 300) v0 = 300;
			start = false;
			break;
		}
		

		}

	}
	if (e->type == SDL_KEYUP) {
		switch (e->key.keysym.sym)
		{
		case SDLK_r: {
			reload = false;
			start = true;
			break;
		}
		

		}




	}
}
void Dshot::fire() {
	
	double radian = phi * PI / 180;

	if (reload) {
		time = 0;
		amo_x = 0;
		amo_y = 400;
	}
	if (start) {
		time += 0.1;
		amo_x = v0 * cos(radian) * time;;
		amo_y = 400 - (v0 * sin(radian) * time - 0.5 * 9.8 * time * time);
		if (amo_y >= 600) start = false;
	}

}
int main(int argv, char* argc[]) {
	if (!Init()) {
		cout << "error init";
	}
	else {
		bool running = true;
		SDL_Event e;
		Ltexture arrow;
		arrow.loadfromfile("img/angle.png", renderer);

		while (running) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					running = false;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					printf("Mouse Clicked at: (%d, %d)\n", x, y);
				}
				dot.handle_event(&e);
				shot.handle_event(&e);
				if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym)
					{
					case SDLK_UP: {
						phi += 1;
						if (phi >= 90) phi = 90;

						break;
					}
					case SDLK_DOWN: {
						phi -= 1;
						if (phi <= 0) phi = 0;
						break;
					}

					}




				}
			}
				dot.move();
				shot.fire();
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				SDL_Point centre = { 51 - 40,396 - 379 };
				arrow.render360(renderer,40,379,NULL,-phi,&centre,SDL_FLIP_NONE);
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				dot.render();
				shot.render();
				SDL_RenderPresent(renderer);
			}
			close();
		}
		return 0;
	}


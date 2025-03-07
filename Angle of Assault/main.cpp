#include"Mainfunc.h"
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
int main(int argv, char* argc[]) {
	return 0;
}
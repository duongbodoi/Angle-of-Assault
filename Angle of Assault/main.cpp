#include"Mainfunc.h"
#include"Basetexture.h"
#include"Mainobject.h"
#include"ThrowManager.h"
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
	if (!Init()) return -1;
	// naruto
	mObject naruto;
	naruto.load_img("img/moveR.png", renderer);
	naruto.set_clip();
	//rasengan
	throw_move rasengan;
	rasengan.load_img("img/rasengan.png", renderer);
	rasengan.set_clip();
	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
					running = false;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) { // cai nay giup ho tro cho ra vi tri toa do x,y tren man hinh window de de dang render ra man hinh
					int x, y;
					SDL_GetMouseState(&x, &y);
					printf("Mouse Clicked at: (%d, %d)\n", x, y);
			}

			naruto.Handle_event(e, renderer);
			rasengan.Handle_event(e, renderer);


				
		}
		naruto.move();
		rasengan.arrow_shot(naruto.get_rect());
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		naruto.show(renderer);
		rasengan.show(renderer);
		SDL_RenderPresent(renderer);
		
		
	}
	close();
	return 0;
}
	


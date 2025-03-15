#include"Mainfunc.h"
#include"Basetexture.h"
#include"Mainobject.h"
#include"ThrowManager.h"
#include"map.h"
#include"object_bar.h"
double x_onmap;
double y_onmap;
Ltexture angle;
Ltexture arrow;
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
	//map
	GameMap game_map;
	game_map.loadmap("map.txt");
	game_map.load_tile(renderer);
	//background
	Ltexture background;
	background.loadfromfile("img/backgr.png", renderer);
	//
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
		//move
		Map mapdata = game_map.getmap();
		Map mapdata_shot = game_map.getmap();
		naruto.setmap_xy(mapdata.start_x, mapdata.start_y);
		naruto.move(mapdata);
		rasengan.setmap_xy(mapdata_shot.start_x, mapdata_shot.start_y);
		rasengan.arrow_shot(naruto.getx_pos(), naruto.gety_pos(), mapdata_shot);
		//Render window
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//Render background
		if (naruto.get_input().shot == 0 or rasengan.get_input().shot == 0)
		{
			game_map.setmap(mapdata);
			SDL_Rect bigmap = { mapdata.start_x,mapdata.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
			background.render(renderer, &bigmap);
		}
		if (rasengan.get_input().shot == 1 or naruto.get_input().shot == 1)
		{
			game_map.setmap(mapdata_shot);
			SDL_Rect bigmap = { mapdata_shot.start_x,mapdata_shot.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
			background.render(renderer, &bigmap);
		}
		//Render object
		game_map.draw_map(renderer);
		naruto.show(renderer);
		rasengan.show(renderer);
		// demo threat
		x_onmap=2300;
		y_onmap=600;
		SDL_Rect rectA = rasengan.get_rect();
		rectA.w /= 3;
		if (naruto.get_input().shot == 0 or rasengan.get_input().shot == 0)
		{
			SDL_Rect rectB = { x_onmap - mapdata.start_x, y_onmap - mapdata.start_y, 100, 600 };
			SDL_RenderFillRect(renderer, &rectB);
			if (SDL_HasIntersection(&rectA, &rectB)) rasengan.set_intput(0);

		}
		if (rasengan.get_input().shot == 1 or naruto.get_input().shot == 1)
		{
			SDL_Rect rectB = { x_onmap - mapdata_shot.start_x, y_onmap - mapdata_shot.start_y, 100, 600 };
			SDL_RenderFillRect(renderer, &rectB);
			if (SDL_HasIntersection(&rectA, &rectB)) rasengan.set_intput(0);

		}
		//
		if (naruto.get_input().reload == 1) {

			draw_powerbar(renderer, rasengan.v0, naruto.get_rect().x - 50, naruto.get_rect().y + 100);
			
		}
		if (naruto.get_input().left != 1 and naruto.get_input().right != 1) {
			draw_angle_control(renderer, rasengan.phi, naruto.get_rect().x + 50, naruto.get_rect().y - 225, angle, arrow);
		}
		SDL_RenderPresent(renderer);
		
		
	}
	close();
	return 0;
}
	


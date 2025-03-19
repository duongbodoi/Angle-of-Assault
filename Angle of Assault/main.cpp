#include"Mainfunc.h"
#include"Basetexture.h"
#include"Mainobject.h"
#include"ThrowManager.h"
#include"map.h"
#include"object_bar.h"
#include"Timer.h";
#include"Bot_object.h"
stringstream text;
stringstream your_text;
stringstream bot_text;
SDL_Color color = { 255,15,0 };
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
	if (TTF_Init() == -1) {
		cout << "TTF_Init failed: " << TTF_GetError() << endl;
	}
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
void close();


int main(int argv, char* argc[]) {
	//
	Timer time;
	Ltexture time_text;
	Timer your_time;
	Ltexture your_turn;
	Timer bot_time;
	Ltexture bot_turn;
	//
	if (!Init()) return -1;
	// naruto
	mObject naruto;
	naruto.load_img("img/moveR.png", renderer);
	naruto.set_clip();
	//sasuke
	bot_object sasuke;
	sasuke.load_img("img/sasukeR.png", renderer);
	sasuke.set_clip();
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
	// Time
	time.start();
	your_time.start();
	while (running) {
		//Time 
		int real_time = time.get_tick() / 1000;
		if (your_time.is_started()) {
			bot_time.stop();
			if (your_time.get_tick() >= 15 * 1000) {
				bot_time.start();
				sasuke.reset();
				
			}
			if (naruto.get_input().reload == 1) {
				your_time.paused();
			}
			if (rasengan.getcolider()) 
			{
				bot_time.start();
				sasuke.reset();
			}
		}
		if (bot_time.is_started()) {
			your_time.stop();
			rasengan.set_colider(false);
			if (bot_time.get_tick() >= 15 * 1000) {
				your_time.start();
			}
		}


		//
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
		//Render window
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);


		//move
		Map mapdata = game_map.getmap();
		Map mapdata_shot = game_map.getmap();
		Map bot_mapdata = game_map.getmap();
		Map bot_mapdata_shot = game_map.getmap();
		naruto.setmap_xy(mapdata.start_x, mapdata.start_y);
		naruto.move(mapdata,your_time.is_started());
		rasengan.setmap_xy(mapdata_shot.start_x, mapdata_shot.start_y);
		rasengan.arrow_shot(naruto.getx_pos(), naruto.gety_pos(), mapdata_shot);
		
		sasuke.setmap_xy(bot_mapdata.start_x, bot_mapdata.start_y);
		sasuke.move(bot_mapdata, bot_time.is_started());
		//Render background
		if(your_time.is_started())
		{	
			
			if (naruto.get_input().shot == 0 or rasengan.get_input().shot == 0)
			{
				sasuke.setmap_xy(mapdata.start_x, mapdata.start_y);
				//sasuke.move(mapdata,bot_time.is_started());
				game_map.setmap(mapdata);
				SDL_Rect bigmap = { mapdata.start_x,mapdata.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
				background.render(renderer, &bigmap);
			}
			if (rasengan.get_input().shot == 1 or naruto.get_input().shot == 1)
			{
				sasuke.setmap_xy(mapdata_shot.start_x, mapdata_shot.start_y);
				//sasuke.move(mapdata_shot,bot_time.is_started());
				game_map.setmap(mapdata_shot);
				SDL_Rect bigmap = { mapdata_shot.start_x,mapdata_shot.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
				background.render(renderer, &bigmap);
			}
		}
		if (bot_time.is_started()) {
			sasuke.ai_control();
			if (sasuke.get_input().shot == 0 )
			{
				game_map.setmap(bot_mapdata);
				SDL_Rect bigmap = { bot_mapdata.start_x,bot_mapdata.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
				background.render(renderer, &bigmap);
			}
			
		}
		//Render object
		game_map.draw_map(renderer);
		naruto.show(renderer);
		rasengan.show(renderer);
		sasuke.show(renderer);
		// object_bar
		if (naruto.get_input().reload == 1) {

			draw_powerbar(renderer, rasengan.v0, naruto.get_rect().x - 50, naruto.get_rect().y + 100);
			
		}
		if (naruto.get_input().left != 1 and naruto.get_input().right != 1) {
			draw_angle_control(renderer, rasengan.phi, naruto.get_rect().x + 50, naruto.get_rect().y - 225, angle, arrow);
		}
		// demo time
		
		
		
		text.str("");
		text << "Time : " << real_time<<" s";
		
		time_text.loadfromtext(renderer,text.str(), color, "font.ttf");
		time_text.set_rect(1060, 15);
		time_text.render(renderer); 
		
		if(your_time.is_started())
		{
			
			your_text.str("");
			your_text << "Your turn: " << 15 - your_time.get_tick() / 1000 << " s";

			your_turn.loadfromtext(renderer, your_text.str(), color, "font.ttf");
			your_turn.set_rect(500, 20);
			your_turn.render(renderer);
		}
		if(bot_time.is_started())
		{
			
			bot_text.str("");
			bot_text << "Bot turn: " << 15 - bot_time.get_tick() / 1000 << " s";

			bot_turn.loadfromtext(renderer, bot_text.str(), color, "font.ttf");
			bot_turn.set_rect(500, 20);
			bot_turn.render(renderer);
		}
		//
		
		SDL_RenderPresent(renderer);
		
		time_text.free();
		your_turn.free();
		bot_turn.free();
		angle.free();
		arrow.free();
	}
	close();
	return 0;
}

void close() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_QUIT;
}


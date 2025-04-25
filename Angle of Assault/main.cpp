#include"Mainfunc.h"
#include"Basetexture.h"
#include"Mainobject.h"
#include"ThrowManager.h"
#include"map.h"
#include"object_bar.h"
#include"Timer.h";
#include"Bot_object.h"
#include"bot_throw.h"
#include"menu.h"
#include"mixer.h"
stringstream text;
stringstream your_text;
stringstream bot_text;
SDL_Color color = { 255,15,0 };
Ltexture angle_sasuke;
Ltexture arrow_sasuke;
Ltexture angle_naruto;
Ltexture arrow_naruto;
Ltexture hp_sasuke;
Ltexture hp_naruto;
SDL_Rect sasuke_rect;
SDL_Rect naruto_rect;
SDL_Rect rasengan_rect;
SDL_Rect chidori_rect;
Ltexture you_win;
Ltexture bot_win;
//
bool pause=false;
bool end_ = false;
//
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
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				check = false;
				cout << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
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
	//
	you_win.loadfromtext(renderer, "You win >.< Congratulate !!", color, "font.ttf");
	bot_win.loadfromtext(renderer, "Bot win ;) you lose :(", color, "font.ttf");
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
	//chidori
	bot_throw chidori;
	chidori.load_img("img/chidori.png", renderer);
	chidori.set_clip();
	//map
	GameMap game_map;
	game_map.loadmap("map.txt");
	game_map.load_tile(renderer);
	//background
	Ltexture background;
	background.loadfromfile("img/backgr.png", renderer);
	Ltexture backgroundstart;
	backgroundstart.loadfromfile("img/start4.png", renderer);
	//
	bool running = true;
	SDL_Event e;
	// Time
	
	//
	Mix_Music* music = Mix_LoadMUS("mixer/bgr.mp3");
	Mix_PlayMusic(music, -1);
	// button
	Ltexture win;
	win.loadfromfile("img/win.png", renderer);
	Ltexture lose;
	lose.loadfromfile("img/lose.png", renderer);
	Ltexture pausemenu;
	pausemenu.loadfromfile("img/pause.png", renderer);
	button gButton;
	button exit;
	button x;
	gButton.load_img("img/play.png", renderer);
	gButton.set_clip();
	exit.load_img("img/exiti.png", renderer);
	exit.set_clip();
	x.load_img("img/x.png", renderer);
	x.set_clip();
	button how;
	how.load_img("img/how.png", renderer);
	how.set_clip();
	button b_continue;
	b_continue.load_img("img/continue.png", renderer);
	b_continue.set_clip();
	button main_menu;
	main_menu.load_img("img/main.png", renderer);
	main_menu.set_clip();
	Ltexture tuto;
	tuto.loadfromfile("img/tutorial.png", renderer);
	// sound
	SoundEffect rasen_sound;
	rasen_sound.Load("mixer/rasengann.wav");
	SoundEffect chido_sound;
	chido_sound.Load("mixer/chidodii.wav");
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
			if(gButton.get_start())
			{
				if(!pause)
				{
					naruto.Handle_event(e, renderer);
					rasengan.Handle_event(e, renderer);
				}

				if (e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_ESCAPE) {
					pause = true;
				}
			}
			if(!gButton.get_start())
			{
				gButton.handleEvent(&e);
				exit.handleEvent(&e);
				how.handleEvent(&e);
				x.handleEvent(&e);
			}
			if (pause) {
				if(end_) exit.handleEvent(&e);
				else b_continue.handleEvent(&e);
				main_menu.handleEvent(&e);
			}
		}
		if (exit.get_start()) {
			close();
		}
		if (main_menu.get_start()) {
			pause = false;
			gButton.set_start(false);
			end_ = false;
			naruto.hp = 100;
			sasuke.hp = 100;
		}
		if (b_continue.get_start()) {
			pause = false;
			time.unpaused();
			bot_time.unpaused();
			your_time.unpaused();
		}
		if (!pause) {
			main_menu.set_start(false);
			b_continue.set_start(false);
			sasuke.setpause(false);
			chidori.setpause(false);
			rasengan.setpause(false);
		}
		if (pause) {
			time.paused();
			your_time.paused();
			bot_time.paused();
			sasuke.setpause(true);
			chidori.setpause(true);
			rasengan.setpause(true);
		}
		if (!gButton.get_start()) {
			backgroundstart.render(renderer,NULL);
			gButton.set_rect(479,252);
			gButton.show(renderer);
			exit.set_rect(479, 252 + 100);
			exit.show(renderer);
			how.set_rect(479, 252 + 100*2);
			how.show(renderer);
			if (how.get_start()) {
				tuto.set_rect(380, 30);
				tuto.render(renderer);
				x.set_rect(380 + tuto.get_rect().w, 30);
				x.show(renderer);
				if (x.get_start()) how.set_start(false);
			}
			else x.set_start(false);
		}
		if(gButton.get_start())
		{
			
			if (!time.is_started()) time.start();
			if (!your_time.is_started() and !bot_time.is_started()) your_time.start();
			//Time 
			int real_time = time.get_tick() / 1000;
			if (your_time.is_started()) {
				bot_time.stop();
				chidori.set_colider(false);
				chido_sound.setcheck(false);
				if (your_time.get_tick() >= 15 * 1000) {
					bot_time.start();
					chidori.reset(naruto.getx_pos(), naruto.gety_pos());
					sasuke.reset();
					SDL_Delay(100);
					
				}
				if (naruto.get_input().reload == 1 and !rasen_sound.IsPlaying() and !rasen_sound.getcheck()) {
					your_time.paused();
					rasen_sound.Play();
					rasen_sound.setcheck(true);
				}
				if (rasengan.getcolider())
				{
					bot_time.start();
					chidori.reset(naruto.getx_pos(), naruto.gety_pos());
					sasuke.reset();
					SDL_Delay(100);
				}
			}
			if (bot_time.is_started()) {
				rasen_sound.setcheck(false);
				your_time.stop();
				rasengan.set_colider(false);
				if (bot_time.get_tick() >= 15 * 1000) {
					your_time.start();
					SDL_Delay(100);

				}
				if (sasuke.get_input().reload == 1 and !chido_sound.IsPlaying() and !chido_sound.getcheck()) {
					bot_time.paused();
					chido_sound.Play();
					chido_sound.setcheck(true);
				}
				if (chidori.getcolider()) {
					your_time.start();
					SDL_Delay(100);

				}
			}


			//
			//Render window
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);


			//move
			Map mapdata = game_map.getmap();
			Map mapdata_shot = game_map.getmap();
			Map bot_mapdata = game_map.getmap();
			Map bot_mapdata_shot = game_map.getmap();
			naruto.setmap_xy(mapdata.start_x, mapdata.start_y);
			naruto.move(mapdata, your_time.is_started());
			rasengan.setmap_xy(mapdata_shot.start_x, mapdata_shot.start_y);
			rasengan.arrow_shot(naruto.getx_pos(), naruto.gety_pos(), mapdata_shot);

			sasuke.setmap_xy(bot_mapdata.start_x, bot_mapdata.start_y);
			sasuke.move(bot_mapdata, bot_time.is_started());
			chidori.setmap_xy(bot_mapdata_shot.start_x, bot_mapdata_shot.start_y);
			chidori.arrow_shot(sasuke.getx_pos(), sasuke.gety_pos(), bot_mapdata_shot);
			//Render background
			if (your_time.is_started())
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
					sasuke_rect = sasuke.get_rect();
					sasuke_rect.x = sasuke.getx_pos(); sasuke_rect.y = sasuke.gety_pos();
					rasengan_rect = rasengan.get_rect();
					rasengan_rect.x = rasengan.getx_pos(); rasengan_rect.y = rasengan.gety_pos();

					//sasuke.move(mapdata_shot,bot_time.is_started());
					game_map.setmap(mapdata_shot);
					SDL_Rect bigmap = { mapdata_shot.start_x,mapdata_shot.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
					background.render(renderer, &bigmap);
					// xu li va cham
					if (SDL_HasIntersection(&rasengan_rect, &sasuke_rect) && !rasengan.getcolider()) {
						sasuke.hp -= 20;

						rasengan.set_colider(true);
						rasengan.set_intput(0);
					}


				}
			}
			if (bot_time.is_started()) {
				sasuke.ai_control();
				chidori.ai_control();
				if (sasuke.get_input().angle == 1) chidori.set_inputangle(1);
				if (chidori.get_input().reload == 1) sasuke.set_inputreload(1);
				if (chidori.get_input().reload == 0) sasuke.set_inputreload(0);
				if (chidori.get_input().shot == 1 && sasuke.get_input().shot == 0) {
					sasuke.set_intputshot(1);
				}

				if (sasuke.get_input().shot == 0 or chidori.get_input().shot == 0)
				{
					naruto.setmap_xy(bot_mapdata.start_x, bot_mapdata.start_y);
					game_map.setmap(bot_mapdata);
					SDL_Rect bigmap = { bot_mapdata.start_x,bot_mapdata.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
					background.render(renderer, &bigmap);
				}
				if (sasuke.get_input().shot == 1 or chidori.get_input().shot == 1)
				{

					naruto.setmap_xy(bot_mapdata_shot.start_x, bot_mapdata_shot.start_y);
					chidori_rect = chidori.get_rect();
					chidori_rect.x = chidori.getx_pos(); chidori_rect.y = chidori.gety_pos();
					naruto_rect = naruto.get_rect();
					naruto_rect.x = naruto.getx_pos(); naruto_rect.y = naruto.gety_pos();

					game_map.setmap(bot_mapdata_shot);
					SDL_Rect bigmap = { bot_mapdata_shot.start_x,bot_mapdata_shot.start_y,SCREEN_WIDTH,SCREEN_HEIGHT };
					background.render(renderer, &bigmap);
					if (SDL_HasIntersection(&chidori_rect, &naruto_rect)) {
						if (!chidori.getcolider()) {
							naruto.hp -= 20;

							chidori.set_colider(true);
						}

					}

				}
			}
			//end game
			if (sasuke.hp <= 0)
			{
				end_ = true;
				sasuke.hp = 0;
				
				you_win.render(renderer);
				
			}
			if (naruto.hp <= 0)
			{
				end_ = true;
				naruto.hp = 0;
				bot_win.render(renderer);
			}
			//Render object
			game_map.draw_map(renderer);
			naruto.show(renderer);
			rasengan.show(renderer);
			sasuke.show(renderer);
			chidori.show(renderer);
			// object_bar
			draw_HP(renderer, naruto.hp, naruto.HPmax, naruto.get_rect().x + 25, naruto.get_rect().y - 6);
			draw_HP(renderer, sasuke.hp, sasuke.HPmax, sasuke.get_rect().x + 22, sasuke.get_rect().y - 6);
			if (chidori.get_input().reload == 1) {

				draw_powerbar(renderer, chidori.v0, sasuke.get_rect().x - 50, sasuke.get_rect().y + 100, chidori.v0_last);

			}
			if (sasuke.get_input().left != 1 and sasuke.get_input().right != 1 and bot_time.is_started()) {
				draw_angle_control_R(renderer, chidori.phi, sasuke.get_rect().x - 200, sasuke.get_rect().y - 200, angle_sasuke, arrow_sasuke);
			}


			if (naruto.get_input().reload == 1) {

				draw_powerbar(renderer, rasengan.v0, naruto.get_rect().x - 50, naruto.get_rect().y + 100, rasengan.v0_last);

			}
			if (naruto.get_input().left != 1 and naruto.get_input().right != 1 and your_time.is_started()) {
				draw_angle_control_L(renderer, rasengan.phi, naruto.get_rect().x + 50, naruto.get_rect().y - 225, angle_naruto, arrow_naruto);
			}

			// demo time



			text.str("");
			text << "Time : " << real_time << " s";

			time_text.loadfromtext(renderer, text.str(), color, "font.ttf");
			time_text.set_rect(1000, 15);
			time_text.render(renderer);

			if (your_time.is_started())
			{

				your_text.str("");
				your_text << "Your turn: " << 15 - your_time.get_tick() / 1000 << " s";

				your_turn.loadfromtext(renderer, your_text.str(), color, "font.ttf");
				your_turn.set_rect(520, 20);
				your_turn.render(renderer);
			}
			if (bot_time.is_started())
			{

				bot_text.str("");
				bot_text << "Bot turn: " << 15 - bot_time.get_tick() / 1000 << " s";

				bot_turn.loadfromtext(renderer, bot_text.str(), color, "font.ttf");
				bot_turn.set_rect(520, 20);
				bot_turn.render(renderer);
			}
		}
		//
		if (pause) {
			pausemenu.set_rect(290, 14);
			pausemenu.render(renderer);
			main_menu.set_rect(480, 190 + 80);
			main_menu.show(renderer);
			if(!end_)
			{
				b_continue.set_rect(480, 100 + 80 * 3 + 30);
				b_continue.show(renderer);
			}
			else {
				exit.set_rect(480, 100 + 80 * 3 + 30);
				exit.show(renderer);
				win.set_rect(500, 14);
				lose.set_rect(500, 14);
				if (naruto.hp == 0) {
					lose.render(renderer);
				}
				else win.render(renderer);
			}
			
		}
		//
		if (end_) {
			pause = true;
		}
		SDL_RenderPresent(renderer);
		
		time_text.free();
		your_turn.free();
		bot_turn.free();
		angle_sasuke.free();
		arrow_sasuke.free();
		angle_naruto.free();
		arrow_naruto.free();
	
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


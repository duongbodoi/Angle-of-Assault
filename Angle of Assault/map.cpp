#include"map.h"
#include<fstream> // de doc toa do vat the tu file
void GameMap::loadmap(string path) {
    ifstream file;
    file.open(path.c_str());
    if (!file.is_open()) {
        return;
    }
    for (int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++) {

            //
            file >> game_map_.tile[i][j];
            string val = game_map_.tile[i][j];
            if (val != "0") {
                nametilemat.insert(val);
                if (j > game_map_.max_x) {
                    game_map_.max_x = j;
                }
                if (i > game_map_.max_y) {
                    game_map_.max_y = i;
                }
            }
        }
    }
    game_map_.max_x = (game_map_.max_x + 1) * TILE_SIZE; // dua ve kich thuoc that trong map lon
    game_map_.max_y = (game_map_.max_y + 1) * TILE_SIZE;

    game_map_.start_x = 0;  
    game_map_.start_y = 0;

    file.close();
}
void GameMap::load_tile(SDL_Renderer* screen) {
    for (string x : nametilemat) {
        stringstream ss;
        ss << "map_sprite/" << x << ".png";
        string name = ss.str();
        ifstream file(name);
        if (!file.is_open()) continue;
        file.close();
        tilemat[x].loadfromfile(name, screen);
    }
}
void GameMap::draw_map(SDL_Renderer* screen) {
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;


    map_x = game_map_.start_x / TILE_SIZE;
    x1 = (game_map_.start_x % 64) * (-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : 64);
    map_y = game_map_.start_y / TILE_SIZE;
    y1 = (game_map_.start_y % 64) * (-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : 64);
    for (int i = y1; i < y2; i += 64) {
        map_x = game_map_.start_x / TILE_SIZE;
        for (int j = x1; j < x2; j += 64) {
            string val = game_map_.tile[map_y][map_x];
            if (val != "0") {
                tilemat[val].set_rect(j, i);
                tilemat[val].render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}


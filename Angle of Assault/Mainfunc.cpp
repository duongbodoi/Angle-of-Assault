#include"Mainfunc.h"
int randomxy(int x, int y) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <> dis(x, y);
	return dis(gen);
}
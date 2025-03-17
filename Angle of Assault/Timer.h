#pragma once
#include"Mainfunc.h"
class Timer {
public:
	Timer();
	~Timer();
	void start();
	void stop();
	void paused();
	void unpaused();
	int get_tick();
	bool is_paused();
	bool is_started();
private:
	int start_tick;
	int pause_tick;

	bool is_paused_;
	bool is_started_;
};
#include"Timer.h";
Timer::Timer() {
	start_tick = 0;
	pause_tick = 0;

	is_paused_ = false;
	is_started_ = false;
}
Timer::~Timer() {

}
void Timer::start() {
	is_started_ = true;
	is_paused_ = false;
	start_tick = SDL_GetTicks();
}
void Timer::stop() {
	is_started_ = false;
	is_paused_ = false;

}
void Timer::paused() {
	if (is_started_ == true and is_paused_ == false) {
		is_paused_ = true;
		pause_tick = SDL_GetTicks() - start_tick; // tg dang pause
	}
}
void Timer::unpaused() {
	if (is_paused_ == true) {
		is_paused_ = false;
		start_tick = SDL_GetTicks() - pause_tick; // chay tiep tu luc pause
		pause_tick = 0;
	}
}
int Timer::get_tick() {
	if (is_started_ == true) {
		if (is_paused_ == true) {
			return pause_tick;
		}
		else {
			int current_time = SDL_GetTicks() - start_tick;
			return current_time;
		}
	}
	return 0;
}
bool Timer::is_started() {
	return is_started_;
}
bool Timer::is_paused() {
	return is_paused_;
}

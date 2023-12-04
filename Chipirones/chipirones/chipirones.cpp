#include "chipirones.h"

long chipirones::rand_value(float min, float max) {
	std::random_device device;
	std::mt19937 engine(device());
	std::uniform_real_distribution<> random_value(min, max);
	return (long) random_value(engine);
}

void chipirones::disable_modules() {
	cheat->clicker_enabled = false;

	std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Wait for the iterations to finish to evade crashes.
}

void chipirones::check_keybinds() {
	bool checking_clicker = true;
	bool checking_reach = true;
	for (;!cheat->thread_stopped;std::this_thread::sleep_for(std::chrono::milliseconds(10))) {
		if (cheat->setting_hotkey) continue;

		if (checking_clicker) {
			if (GetAsyncKeyState(cheat->clicker_hotkey) & 0x8000) {
				cheat->clicker_enabled = !cheat->clicker_enabled;
				checking_clicker = false;
			}
		}
		else if (!GetAsyncKeyState(cheat->clicker_hotkey)) 
			checking_clicker = true;

		if (checking_reach) {
			if (GetAsyncKeyState(cheat->reach_hotkey) & 0x8000) {
				cheat->reach_enabled = !cheat->reach_enabled;
				checking_reach = false;
			}
		}
		else if (!GetAsyncKeyState(cheat->reach_hotkey))
			checking_reach = true;
	}
}

void chipirones::update_drop_times() {
	cheat->cps_drop_start = chipirones::rand_value(90, 150);
	cheat->cps_drop_end = chipirones::rand_value(cheat->cps_drop_start * 1.25, cheat->cps_drop_start * 1.55);
}
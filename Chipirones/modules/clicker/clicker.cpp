#include "../modules.h"
#include "../../chipirones/chipirones.h"


void manage_cps_drop(size_t* count, std::chrono::milliseconds* time_to_sleep, float release_values[2]) {
	cheat->cps_drop_clicks++;
	if (++* count == cheat->cps_drop_start) {
		// Incrementing sleep time + release times + min/max cps to create a cps drop.
		*time_to_sleep = std::chrono::milliseconds(chipirones::rand_value(5, 10));
		release_values[0] = { 0.3f };
		release_values[1] = { 0.9f };
	}
	else if (*count >= cheat->cps_drop_end) {
		// Reset times to default ones
		*time_to_sleep = std::chrono::milliseconds(chipirones::rand_value(2, 4));
		release_values[0] = { 0.1f };
		release_values[1] = { 0.5f };

		cheat->update_drop_times();
		cheat->cps_drop_clicks = 0;
		*count = 0;
	}
}

void clicker::handle() {
	std::chrono::milliseconds time_to_sleep = std::chrono::milliseconds(chipirones::rand_value(2, 4));
	float release_values[2]{0.1f, 0.5f};
	cheat->update_drop_times();
	// Checking if main thread changed atomic bool to stop this thread
	for (size_t count = 0; !cheat->thread_stopped;std::this_thread::sleep_for(time_to_sleep)) {

		if (!GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON) || !cheat->clicker_enabled) continue; // Must be holding left click and not holding right click.
		HWND window = GetForegroundWindow();

		bool is_valid = false;

		std::string title(GetWindowTextLength(window) + 1, L'\0');
		GetWindowText(window, &title[0], title.size());

		// Window must be a valid minecraft instance. We are just checking for the name.
		if (title.find("1.8.9") != std::string::npos || title.find("Minecraft") != std::string::npos || title.find("1.7.10") != std::string::npos) is_valid = true;

		if (!is_valid) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			continue;
		}
		float min_value = 1000 / cheat->cps[0];
		float max_value = 1000 / cheat->cps[1];

		if (cheat->cps_drop_enabled && count >= cheat->cps_drop_start) {
			min_value = 1000 / (cheat->cps[0] - 3);
			max_value = 1000 / (cheat->cps[1] - 2);
		}

		SendMessageW(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
		std::this_thread::sleep_for(std::chrono::milliseconds(chipirones::rand_value(release_values[0], release_values[1]))); // Rand value for releasing left mouse click.
		SendMessageW(window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(0, 0));
		if (cheat->cps_drop_enabled) manage_cps_drop(&count, &time_to_sleep, release_values);
		cheat->clicks++;
		std::this_thread::sleep_for(std::chrono::milliseconds(chipirones::rand_value(min_value, max_value)));
	}
}
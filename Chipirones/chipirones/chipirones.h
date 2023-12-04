#include <random>
#include <Windows.h>
#include <thread>
#include <chrono>

#pragma once

class chipirones {
public:
	static long rand_value(float min, float max);
	static void check_keybinds();
	void disable_modules();
	std::atomic_bool thread_stopped = false;
	bool setting_hotkey = false;

	bool clicker_enabled = false;
	float cps[2] = { 9.0f, 13.f };

	int clicks{};
	int cps_drop_clicks{};
	void update_drop_times();
	bool cps_drop_enabled = true;
	int cps_drop_start;
	int cps_drop_end;
	int clicker_hotkey{};

	bool reach_enabled = false;
	float reach_distance = 0.1f;
	int reach_hotkey{};
};

inline auto cheat = std::make_unique<chipirones>();
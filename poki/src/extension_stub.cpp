#if !defined(DM_PLATFORM_HTML5)

#include "extension.h"

static void timer_delay(lua_State *L, double delay, int callback) {
	lua_getglobal(L, "timer");
	lua_getfield(L, -1, "delay");
	lua_remove(L, -2); // Pop timer.

	lua_pushnumber(L, delay); // Duration.
	lua_pushboolean(L, false); // Repeat.
	lua_rawgeti(L, LUA_REGISTRYINDEX, callback); // Callback.
	luaL_unref(L, LUA_REGISTRYINDEX, callback);

	lua_call(L, 3, 0);
}

static int wrap_function(lua_State *L) {
	lua_pushvalue(L, lua_upvalueindex(1)); // Script instance.
	dmScript::SetInstance(L);

	lua_pushvalue(L, lua_upvalueindex(2)); // Callback.
	lua_pushvalue(L, lua_upvalueindex(3)); // Argument.
	lua_call(L, 1, 0);
	return 0;
}

static int set_is_initialized(lua_State *L) {
	lua_getglobal(L, "poki");
	lua_pushboolean(L, true);
	lua_setfield(L, -2, "is_initialized");
	lua_pop(L, 1);
	return 0;
}

static int extension_init(lua_State *L) {
	dmLogInfo("init");
	if (lua_isfunction(L, 1) && lua_gettop(L) == 1) {
		double delay = 1.0;
		int callback = luaL_ref(L, LUA_REGISTRYINDEX);
		timer_delay(L, delay, callback);

		lua_pushcfunction(L, set_is_initialized);
		int set_is_initialized_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		timer_delay(L, delay, set_is_initialized_ref);
	}
	return 0;
}

static int extension_set_debug(lua_State *L) {
	dmLogInfo("set_debug");
	return 0;
}

static int extension_game_loading_start(lua_State *L) {
	dmLogInfo("game_loading_start");
	return 0;
}

static int extension_game_loading_finished(lua_State *L) {
	dmLogInfo("game_loading_finished");
	return 0;
}

static int extension_gameplay_start(lua_State *L) {
	dmLogInfo("gameplay_start");
	return 0;
}

static int extension_gameplay_stop(lua_State *L) {
	dmLogInfo("gameplay_stop");
	return 0;
}

static int extension_commercial_break(lua_State *L) {
	dmLogInfo("commercial_break");
	if (lua_isfunction(L, 1) && lua_gettop(L) == 1) {
		int callback = luaL_ref(L, LUA_REGISTRYINDEX);
		timer_delay(L, 1, callback);
	}
	return 0;
}

static int extension_rewarded_break(lua_State *L) {
	dmLogInfo("rewarded_break");
	if (lua_isfunction(L, 1) && lua_gettop(L) == 1) {
		dmScript::GetInstance(L); // Script instance.
		lua_pushvalue(L, 1); // Callback.
		lua_pushboolean(L, true); // Success = true
		lua_pushcclosure(L, wrap_function, 3); // Wrapped callback.
		int callback = luaL_ref(L, LUA_REGISTRYINDEX);
		timer_delay(L, 1, callback);
	}
	return 0;
}

static int extension_happy_time(lua_State *L) {
	dmLogInfo("happy_time");
	return 0;
}

static const luaL_reg lua_functions[] = {
	{"init", extension_init},
	{"set_debug", extension_set_debug},
	{"game_loading_start", extension_game_loading_start},
	{"game_loading_finished", extension_game_loading_finished},
	{"gameplay_start", extension_gameplay_start},
	{"gameplay_stop", extension_gameplay_stop},
	{"commercial_break", extension_commercial_break},
	{"rewarded_break", extension_rewarded_break},
	{"happy_time", extension_happy_time},
	{0, 0}
};

dmExtension::Result APP_INITIALIZE(dmExtension::AppParams *params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result APP_FINALIZE(dmExtension::AppParams *params) {
	return dmExtension::RESULT_OK;
}

dmExtension::Result INITIALIZE(dmExtension::Params *params) {
	lua_State *L = params->m_L;
	luaL_register(L, EXTENSION_NAME_STRING, lua_functions);

	lua_pushboolean(L, false);
	lua_setfield(L, -2, "is_initialized");

	lua_pushboolean(L, false);
	lua_setfield(L, -2, "is_ads_blocked");

	lua_pop(params->m_L, 1);

	return dmExtension::RESULT_OK;
}

dmExtension::Result UPDATE(dmExtension::Params *params) {
	return dmExtension::RESULT_OK;
}

void EXTENSION_ON_EVENT(dmExtension::Params *params, const dmExtension::Event *event) {
	switch (event->m_Event) {
		case dmExtension::EVENT_ID_ACTIVATEAPP:
			break;
		case dmExtension::EVENT_ID_DEACTIVATEAPP:
			break;
		case dmExtension::EVENT_ID_ICONIFYAPP:
			break;
		case dmExtension::EVENT_ID_DEICONIFYAPP:
			break;
	}
}

dmExtension::Result FINALIZE(dmExtension::Params *params) {
	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, EXTENSION_NAME_STRING, APP_INITIALIZE, APP_FINALIZE, INITIALIZE, UPDATE, EXTENSION_ON_EVENT, FINALIZE)

#endif

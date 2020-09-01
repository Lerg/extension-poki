#if defined(DM_PLATFORM_HTML5)

#include <emscripten.h>

#include "extension.h"
#include "utils.h"

typedef void (*Callback_v)();
typedef void (*Callback_vi)(const int arg1);

// The Emscripten JS methods from lib/web/poki.js
extern "C" {
	void ExtensionPokiJS_init(Callback_vi callback);
	void ExtensionPokiJS_set_debug(bool is_debug);
	void ExtensionPokiJS_game_loading_start();
	void ExtensionPokiJS_game_loading_finished();
	void ExtensionPokiJS_gameplay_start();
	void ExtensionPokiJS_gameplay_stop();
	void ExtensionPokiJS_commercial_break(Callback_v callback);
	void ExtensionPokiJS_rewarded_break(Callback_vi callback);
	void ExtensionPokiJS_happy_time(double intensity);
}

static dmScript::LuaCallbackInfo *init_callback = NULL;
static dmScript::LuaCallbackInfo *commercial_break_callback = NULL;
static dmScript::LuaCallbackInfo *rewarded_break_callback = NULL;

static void extension_init_callback(const int is_ads_blocked) {
	lua_State *L = dmScript::GetCallbackLuaContext(init_callback);
	DM_LUA_STACK_CHECK(L, 0);

	lua_getglobal(L, "poki");

	lua_pushboolean(L, true);
	lua_setfield(L, -2, "is_initialized");

	if (is_ads_blocked == 1) {
		lua_pushboolean(L, true);
		lua_setfield(L, -2, "is_ads_blocked");
	}

	lua_pop(L, 1); // poki

	if (!dmScript::SetupCallback(init_callback)) {
		return;
	}
	lua_pop(L, 1);

	lua_call(L, 0, 0);

	dmScript::TeardownCallback(init_callback);
	dmScript::DestroyCallback(init_callback);
}

static void extension_commercial_break_callback() {
	lua_State *L = dmScript::GetCallbackLuaContext(commercial_break_callback);
	DM_LUA_STACK_CHECK(L, 0);

	if (!dmScript::SetupCallback(commercial_break_callback)) {
		return;
	}
	lua_pop(L, 1);

	lua_call(L, 0, 0);

	dmScript::TeardownCallback(commercial_break_callback);
	dmScript::DestroyCallback(commercial_break_callback);
}

static void extension_rewarded_break_callback(const int success) {
	lua_State *L = dmScript::GetCallbackLuaContext(rewarded_break_callback);
	DM_LUA_STACK_CHECK(L, 0);

	if (!dmScript::SetupCallback(rewarded_break_callback)) {
		return;
	}
	lua_pop(L, 1);

	lua_pushboolean(L, success == 1 ? true : false);

	lua_call(L, 1, 0);

	dmScript::TeardownCallback(rewarded_break_callback);
	dmScript::DestroyCallback(rewarded_break_callback);
}

static int extension_init(lua_State *L) {
	utils::check_arg_count(L, 1);
	if (lua_isfunction(L, 1)) {
		init_callback = dmScript::CreateCallback(L, 1);
		ExtensionPokiJS_init((Callback_vi)extension_init_callback);
	}
	return 0;
}

static int extension_set_debug(lua_State *L) {
	utils::check_arg_count(L, 1);
	if (lua_isboolean(L, 1)) {
		ExtensionPokiJS_set_debug(lua_toboolean(L, 1));
	}
	return 0;
}

static int extension_game_loading_start(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_game_loading_start();
	return 0;
}

static int extension_game_loading_finished(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_game_loading_finished();
	return 0;
}

static int extension_gameplay_start(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_gameplay_start();
	return 0;
}

static int extension_gameplay_stop(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_gameplay_stop();
	return 0;
}

static int extension_commercial_break(lua_State *L) {
	utils::check_arg_count(L, 1);
	if (lua_isfunction(L, 1)) {
		commercial_break_callback = dmScript::CreateCallback(L, 1);
		ExtensionPokiJS_commercial_break((Callback_v)extension_commercial_break_callback);
	}
	return 0;
}

static int extension_rewarded_break(lua_State *L) {
	utils::check_arg_count(L, 1);
	if (lua_isfunction(L, 1)) {
		rewarded_break_callback = dmScript::CreateCallback(L, 1);
		ExtensionPokiJS_rewarded_break((Callback_vi)extension_rewarded_break_callback);
	}
	return 0;
}

static int extension_happy_time(lua_State *L) {
	utils::check_arg_count(L, 1);
	if (lua_isnumber(L, 1)) {
		ExtensionPokiJS_happy_time(lua_tonumber(L, 1));
	}
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
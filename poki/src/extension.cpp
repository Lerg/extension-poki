#if defined(DM_PLATFORM_HTML5)

#include <extension.h>
#include <emscripten.h>

// The Emscripten JS methods from lib/web/poki.js
extern "C" void ExtensionPokiJS_init();
extern "C" void ExtensionPokiJS_set_debug();
extern "C" void ExtensionPokiJS_game_loading_start();
extern "C" void ExtensionPokiJS_game_loading_finished();
extern "C" void ExtensionPokiJS_gameplay_start();
extern "C" void ExtensionPokiJS_gameplay_stop();
extern "C" void ExtensionPokiJS_commercial_break();
extern "C" void ExtensionPokiJS_rewarded_break();

static int EXTENSION_INIT(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_init();
	return 0;
}

static int EXTENSION_SET_DEBUG(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_set_debug();
	return 0;
}

static int EXTENSION_GAME_LOADING_START(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_game_loading_start();
	return 0;
}

static int EXTENSION_GAME_LOADING_FINISHED(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_game_loading_finished();
	return 0;
}

static int EXTENSION_GAMEPLAY_START(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_gameplay_start();
	return 0;
}

static int EXTENSION_GAMEPLAY_STOP(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_gameplay_stop();
	return 0;
}

static int EXTENSION_COMMERCIAL_BREAK(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_commercial_break();
	return 0;
}

static int EXTENSION_REWARDED_BREAK(lua_State *L) {
	utils::check_arg_count(L, 0);
	ExtensionPokiJS_rewarded_break();
	return 0;
}

static const luaL_reg lua_functions[] = {
	{"init", EXTENSION_INIT},
	{"set_debug", EXTENSION_SET_DEBUG},
	{"game_loading_start", EXTENSION_GAME_LOADING_START},
	{"game_loading_finished", EXTENSION_GAME_LOADING_FINISHED},
	{"gameplay_start", EXTENSION_GAMEPLAY_START},
	{"gameplay_stop", EXTENSION_GAMEPLAY_STOP},
	{"commercial_break", EXTENSION_COMMERCIAL_BREAK},
	{"rewarded_break", EXTENSION_REWARDED_BREAK},
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
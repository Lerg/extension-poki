#ifndef extension_h
#define extension_h

// The name of the extension affects Lua module name and Java package name.
#define EXTENSION_NAME poki

// Convert extension name to C const string.
#define STRINGIFY(s) #s
#define STRINGIFY_EXPANDED(s) STRINGIFY(s)
#define EXTENSION_NAME_STRING STRINGIFY_EXPANDED(EXTENSION_NAME)

#include <dmsdk/sdk.h>

// Each extension must have unique exported symbols. Construct function names based on the extension name.
#define FUNCTION_NAME(extension_name, function_name) Extension_ ## extension_name ## _ ## function_name
#define FUNCTION_NAME_EXPANDED(extension_name, function_name) FUNCTION_NAME(extension_name, function_name)

#define APP_INITIALIZE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, AppInitialize)
#define APP_FINALIZE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, AppFinalize)
#define INITIALIZE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, Initialize)
#define UPDATE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, Update)
#define FINALIZE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, Finalize)

// The following functions are implemented for each platform.
// Lua API.
#define EXTENSION_INIT FUNCTION_NAME_EXPANDED(EXTENSION_NAME, init)
int EXTENSION_INIT(lua_State *L);

#define EXTENSION_SET_DEBUG FUNCTION_NAME_EXPANDED(EXTENSION_NAME, set_debug)
int EXTENSION_SET_DEBUG(lua_State *L);

#define EXTENSION_GAME_LOADING_START FUNCTION_NAME_EXPANDED(EXTENSION_NAME, game_loading_start)
int EXTENSION_GAME_LOADING_START(lua_State *L);

#define EXTENSION_GAME_LOADING_FINISHED FUNCTION_NAME_EXPANDED(EXTENSION_NAME, game_loading_finished)
int EXTENSION_GAME_LOADING_FINISHED(lua_State *L);

#define EXTENSION_GAMEPLAY_START FUNCTION_NAME_EXPANDED(EXTENSION_NAME, gameplay_start)
int EXTENSION_GAMEPLAY_START(lua_State *L);

#define EXTENSION_GAMEPLAY_STOP FUNCTION_NAME_EXPANDED(EXTENSION_NAME, gameplay_stop)
int EXTENSION_GAMEPLAY_STOP(lua_State *L);

#define EXTENSION_COMMERCIAL_BREAK FUNCTION_NAME_EXPANDED(EXTENSION_NAME, commercial_break)
int EXTENSION_COMMERCIAL_BREAK(lua_State *L);

#define EXTENSION_REWARDED_BREAK FUNCTION_NAME_EXPANDED(EXTENSION_NAME, rewarded_break)
int EXTENSION_REWARDED_BREAK(lua_State *L);

// Extension lifecycle functions.
#define EXTENSION_INITIALIZE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, initialize)
#define EXTENSION_UPDATE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, update)
#define EXTENSION_ON_EVENT FUNCTION_NAME_EXPANDED(EXTENSION_NAME, on_event)
#define EXTENSION_APP_ACTIVATE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, app_activate)
#define EXTENSION_APP_DEACTIVATE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, app_deactivate)
#define EXTENSION_FINALIZE FUNCTION_NAME_EXPANDED(EXTENSION_NAME, finalize)
void EXTENSION_INITIALIZE(lua_State *L);
void EXTENSION_UPDATE(lua_State *L);
void EXTENSION_APP_ACTIVATE(lua_State *L);
void EXTENSION_APP_DEACTIVATE(lua_State *L);
void EXTENSION_FINALIZE(lua_State *L);

#endif

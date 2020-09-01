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

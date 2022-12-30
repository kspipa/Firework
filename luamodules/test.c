#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int luaAdd(lua_State* L, int a, int b) {
   lua_getglobal(L, "add");
   lua_pushnumber(L, a);
   lua_pushnumber(L, b);
   lua_call(L, 2, 1);
   int sum = (int)lua_tointeger(L, -1);
   lua_pop(L, 1);
   return sum;
}

int main(int argc, char *argv[]) {
   lua_State* L;
   L = luaL_newstate();
   luaL_openlibs(L);
   lua_close(L);
   printf( "Press enter to exit..." );
   getchar();
   return 0;
}


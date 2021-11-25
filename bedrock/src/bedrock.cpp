#include <memory>
#include <optional>
#include <SDL.h>
#include <SDL_video.h>

#include <lua.h>
#include <lualib.h>
#include <Luau/Compiler.h>

const std::string INIT_SCRIPT = R"(
    require("core/main")({})
)";

// TODO: Remove these methods and tidy them up. They're here
// for testing purposes only.
std::optional<std::string> readFile(const std::string& name)
{
#ifdef _WIN32
    FILE* file = _wfopen(fromUtf8(name).c_str(), L"rb");
#else
    FILE* file = fopen(name.c_str(), "rb");
#endif

    if (!file)
        return std::nullopt;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    if (length < 0)
    {
        fclose(file);
        return std::nullopt;
    }
    fseek(file, 0, SEEK_SET);

    std::string result(length, 0);

    size_t read = fread(result.data(), 1, length, file);
    fclose(file);

    if (read != size_t(length))
        return std::nullopt;

    return result;
}

static int finishrequire(lua_State* L)
{
    if (lua_isstring(L, -1))
        lua_error(L);

    return 1;
}

static int lua_require(lua_State* L)
{
    std::string name = luaL_checkstring(L, 1);
    std::string chunkname = "=" + name;

    luaL_findtable(L, LUA_REGISTRYINDEX, "_MODULES", 1);

    // return the module from the cache
    lua_getfield(L, -1, name.c_str());
    if (!lua_isnil(L, -1))
        return finishrequire(L);
    lua_pop(L, 1);

    std::optional<std::string> source = readFile(name + ".luau");
    if (!source)
    {
        source = readFile(name + ".lua"); // try .lua if .luau doesn't exist
        if (!source)
            luaL_argerrorL(L, 1, ("error loading " + name).c_str()); // if neither .luau nor .lua exist, we have an error
    }

    // module needs to run in a new thread, isolated from the rest
    lua_State* GL = lua_mainthread(L);
    lua_State* ML = lua_newthread(GL);
    lua_xmove(GL, L, 1);

    // new thread needs to have the globals sandboxed
    luaL_sandboxthread(ML);

    // now we can compile & run module on the new thread
    std::string bytecode = Luau::compile(*source);
    if (luau_load(ML, chunkname.c_str(), bytecode.data(), bytecode.size(), 0) == 0)
    {
        int status = lua_resume(ML, L, 0);

        if (status == 0)
        {
            if (lua_gettop(ML) == 0)
                lua_pushstring(ML, "module must return a value");
            else if (!lua_istable(ML, -1) && !lua_isfunction(ML, -1))
                lua_pushstring(ML, "module must return a table or function");
        }
        else if (status == LUA_YIELD)
        {
            lua_pushstring(ML, "module can not yield");
        }
        else if (!lua_isstring(ML, -1))
        {
            lua_pushstring(ML, "unknown error while running module");
        }
    }

    // there's now a return value on top of ML; stack of L is MODULES thread
    lua_xmove(ML, L, 1);
    lua_pushvalue(L, -1);
    lua_setfield(L, -4, name.c_str());

    return finishrequire(L);
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // NOTE: At some point it will make sense to have a precompiled
    // and signed luau script to initialise the engine. This will
    // prevent users from accidentally changing the init script. It
    // should cuase no issues to anyone. For now, we'll just use a
    // string to hold the script.

    // Initialize core lua state
    std::unique_ptr<lua_State, void (*)(lua_State*)> globalState(luaL_newstate(), lua_close);
    lua_State* L = globalState.get();

    // Open standard libraries
    luaL_openlibs(L);

    // Register require function (temporary, will be moved)
    lua_pushcfunction(L, lua_require, "require");
    lua_setglobal(L, "require");

    // Run init script
    std::string init_script_bytecode = Luau::compile(INIT_SCRIPT);

    if (luau_load(L, "=INIT_SCRIPT", init_script_bytecode.data(), init_script_bytecode.size(), 0) != 0) {
        printf("Luau Error: %s\n", lua_tostring(L, -1));
        return 1;
    }

    if (lua_pcall(L, 0, 0, 0) != 0) {
        printf("Luau Error: %s\n", lua_tostring(L, -1));
        return 1;
    }

    return 0;
}
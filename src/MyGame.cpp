/*
 * MyGame.cpp
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */
#include "MyGame.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <SDL++/SDLException.hpp>
#include <misc/debug.h>
#include <misc/Log.h>
#include <Lua/CLuaManager.h>

#include "CParam.h"

void MyGame::Init(const std::string& config) {

	CGameEngine::Init();

	InitParam(config);
	InitSDL();
	InitLua();

	imageLoader = new gcn::SDLImageLoader();
	gcn::Image::setImageLoader(imageLoader);
	graphics = new gcn::SDLGraphics();
	graphics->setTarget(screen);
	input = new gcn::SDLInput();

	font = new gcn::ImageFont("fixedfont.bmp",
			" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	gcn::Widget::setGlobalFont(font);

	gui = new gcn::Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);

	L_(debug) << "MyGame::Init";

}

void MyGame::Cleanup() {

	CGameEngine::Cleanup();

	delete gui;
	delete font;
	delete input;
	delete graphics;
	delete imageLoader;

	TTF_Quit();
//	IMG_Quit();
	SDL_Quit();

	L_(debug) << "MyGame::Cleanup";

}

gcn::Gui& MyGame::getGui() const {

	return *gui;

}
gcn::SDLInput& MyGame::getInput() const {

	return *input;

}
SDL_Surface* MyGame::getScreen() {

	return screen;

}
/*
 * Procedimientos privados.
 */
void MyGame::InitParam(const std::string& config) {

	pt::ptree pt;
	pt::read_ini(config, pt);

	param.screen.X = pt.get("screen.width", 640);
	param.screen.Y = pt.get("screen.height", 480);
	param.screen.full = pt.get("screen.fullscreen", false);
	param.gamedata = pt.get<std::string> ("game.gamedata");
	param.lua = pt.get<std::string>("game.lua");

}
void MyGame::InitSDL() {

	int bpp;
	int flags = SDL_HWSURFACE | SDL_SRCALPHA | SDL_RLEACCEL;

	// initialize SDL
	THROW_SDL_EXCEPTION_IF((-1 == SDL_Init(SDL_INIT_VIDEO)), "Can't initialize SDL:");

	// Init SDL_image
//	THROW_SDL_EXCEPTION_IF(( -1 == IMG_Init(IMG_INIT_PNG)),"Can't initialize TTF:");

	// Init SDL_ttf
	THROW_SDL_EXCEPTION_IF(( -1 == TTF_Init()),"Can't initialize TTF:");

	// Load Icon Bitmap...
	SDL_Surface* Icon = IMG_Load("icon.bmp"); // No tenemos pantalla aun .......
	THROW_SDL_EXCEPTION_IF(0 == Icon,"Can't load program icon");
	SDL_WM_SetIcon(Icon, NULL);

	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	if (info->vfmt->BitsPerPixel > 8) {
		bpp = info->vfmt->BitsPerPixel;
	} else {
		bpp = 16;
	}
	if (info->hw_available)
		flags |= SDL_DOUBLEBUF;
	if (param.screen.full)
		flags |= SDL_FULLSCREEN;

	SDL_putenv((char *) "SDL_VIDEO_CENTERED=center");
	screen = SDL_SetVideoMode(param.screen.X, param.screen.Y, bpp, flags);
	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

}
void MyGame::InitLua() {

	LuaManager.RunLuaDoFile(param.lua.c_str());

//	RegisterToLuaCrudeTimer(LuaManager->GetLua());
//	RegisterToLuaVector2D(LuaManager->GetLua());
//	RegisterToLuaTelegram(LuaManager->GetLua());
//	RegisterToLuaCActorType(LuaManager->GetLua());
//	RegisterToLuaModel(LuaManager->GetLua());
//	RegisterToLuaGameWorld(LuaManager->GetLua());
//	RegisterToLuaBaseGameEntity(LuaManager->GetLua());
//	RegisterToLuaMovingEntity(LuaManager->GetLua());
//	RegisterToLuaActorMapa(LuaManager->GetLua());
//	RegisterToLuaGoal(LuaManager->GetLua());
//	RegisterToLuaSteeringBehavior(LuaManager->GetLua());


//	RegisterToLuaMessageDispacher(LuaManager->GetLua());
//
//	RegisterToLuaScriptedStateMachine(LuaManager->GetLua());
//	RegisterToLuaCTileMapa(LuaManager->GetLua());
//	RegisterToLuaCActor_PathPlanner(LuaManager->GetLua());

}

 /*
 * MyGame.cpp
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */
#include "MyGame.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <IsoHex/SdlException.hpp>
#include <misc/debug.h>
#include <misc/Log.h>
#include <Lua/CLuaManager.h>

#include "CParam.h"
#include "RegisterToLua.h"

MyGame::MyGame() {

	m_screen_resolution["SMALL"] = MyGame::SMALL;
	m_screen_resolution["MEDIUM"] = MyGame::MEDIUM;
	m_screen_resolution["BIG"] = MyGame::BIG;
}
void MyGame::Init( const std::string& config ) {

	CGameEngine::Init();

	InitParam( config );
	InitSDL();
	InitLua();

	imageLoader = new gcn::SDLImageLoader();
	gcn::Image::setImageLoader( imageLoader );
	graphics = new gcn::SDLGraphics();
	graphics->setTarget( m_screen_ );
	input = new gcn::SDLInput();

	font
			= new
					gcn::ImageFont( "fixedfont.bmp",
									" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" );
	gcn::Widget::setGlobalFont( font );

	gui = new gcn::Gui();
	gui->setGraphics( graphics );
	gui->setInput( input );

	L_(debug)
<<	"MyGame::Init";

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

	L_(debug)
<<	"MyGame::Cleanup";

}

gcn::Gui& MyGame::getGui() const {

	return *gui;

}
gcn::SDLInput& MyGame::getInput() const {

	return *input;

}
void MyGame::flip() {

	SDL_Flip( m_screen_ );

}
void MyGame::changeResolution( 	std::pair <std::string,bool> resol ) {

	int x, y;
	const int bpp = 16;
	int flags = SDL_HWSURFACE | SDL_SRCALPHA | SDL_RLEACCEL;
	m_default_resolution_	= resol; // Posiblemente en otro sitio...
	switch ( m_screen_resolution[m_default_resolution_.first] ) {
		case SMALL: {
			x = 640;
			y = 480;
			break;
		}
		case MEDIUM: {
			x = 800;
			y = 600;
			break;
		}
		case BIG: {
			x = 1024;
			y = 768;
			break;
		}
		default:
			// Lanzar un error .....
			break;

	}
	if ( m_default_resolution_.second ) flags |= SDL_FULLSCREEN;
	m_screen_ = SDL_SetVideoMode( 	x,
									y,
									bpp,
									flags );

}
const std::pair <std::string,bool>  MyGame::getResolution() const {
	return m_default_resolution_;
}
int MyGame::getPosResolution(){
	return m_screen_resolution[m_default_resolution_.first];
}
//-------------------------------------------------------------------------------
// Procedimientos privados.
//-------------------------------------------------------------------------------
void MyGame::InitParam( const std::string& config ) {

	pt::ptree pt;
	pt::read_ini( 	config,
					pt );

	param.screen.resolution = pt.get < std::string > (	"screen.resolution",
														"SMALL" );

	param.screen.full = pt.get( "screen.fullscreen",
								false );
	param.gamedata = pt.get < std::string > ( "game.gamedata" );
	param.lua = pt.get < std::string > ( "game.lua" );

}
void MyGame::InitSDL() {

	// initialize SDL
	THROW_SDL_EXCEPTION_IF( ( -1 == SDL_Init( SDL_INIT_VIDEO ) ),
							"Can't initialize SDL:" );

	// Init SDL_image
	//	THROW_SDL_EXCEPTION_IF(( -1 == IMG_Init(IMG_INIT_PNG)),"Can't initialize TTF:");

	// Init SDL_ttf
	THROW_SDL_EXCEPTION_IF( ( -1 == TTF_Init() ),
							"Can't initialize TTF:" );

	// Load Icon Bitmap...
	SDL_Surface* Icon = IMG_Load( "icon.bmp" ); // No tenemos pantalla aun .......
	THROW_SDL_EXCEPTION_IF( 0 == Icon,
							"Can't load program icon" );
	SDL_WM_SetIcon( Icon,
					NULL );
	SDL_putenv( (char *) "SDL_VIDEO_CENTERED=center" );

	std::pair < std::string, bool > resol( 	param.screen.resolution,
											param.screen.full );
	changeResolution( resol );

	SDL_EnableUNICODE( 1 );
	SDL_EnableKeyRepeat( 	SDL_DEFAULT_REPEAT_DELAY,
							SDL_DEFAULT_REPEAT_INTERVAL );

}
void MyGame::InitLua() {

	LuaManager.RunLuaDoFile( param.lua );

	RegisterToLuaCrudeTimer( LuaManager.GetLua() );
	RegisterToLuaVector2D( LuaManager.GetLua() );
	RegisterToLuaTelegram( LuaManager.GetLua() );
	RegisterToLuaCActorType( LuaManager.GetLua() );
	RegisterToLuaModel( LuaManager.GetLua() );
	RegisterToLuaGameWorld( LuaManager.GetLua() );
	RegisterToLuaBaseGameEntity( LuaManager.GetLua() );
	RegisterToLuaMovingEntity( LuaManager.GetLua() );
	RegisterToLuaActorMapa( LuaManager.GetLua() );
	RegisterToLuaGoal( LuaManager.GetLua() );
	RegisterToLuaSteeringBehavior( LuaManager.GetLua() );

	//	RegisterToLuaMessageDispacher(LuaManager.GetLua());
	//
	//	RegisterToLuaScriptedStateMachine(LuaManager.GetLua());
	//	RegisterToLuaCTileMapa(LuaManager.GetLua());
	//	RegisterToLuaCActor_PathPlanner(LuaManager.GetLua());

}

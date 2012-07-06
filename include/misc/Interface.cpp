/*
 * Interface.cpp
 *
 *  Created on: 21/01/2010
 *      Author: 79481180
 */

#include "Interface.h"

#include <stdexcept>

#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Log.h"

Interface::Interface( const std::string& icon,
                      const std::string& font,
                      const ScreenResolutionType& res )
{

  m_screenTypes_["SMALL"] = Interface::SMALL;
  m_screenTypes_["MEDIUM"] = Interface::MEDIUM;
  m_screenTypes_["BIG"] = Interface::BIG;

  initSDL( icon,
           res );
  initGuichan( font );

}

Interface::~Interface()
{

  stopGuichan();
  stopSDL();

}
int Interface::indexResolution( const std::string& index ) const
{

  return m_screenTypes_.at( index );

}
void Interface::changeScreenResolution( const ScreenResolutionType& res )
{

  int x;
  int y;

  int flags = SDL_SWSURFACE;
  m_default_resolution_ = res; // Posiblemente en otro sitio...
  switch ( m_screenTypes_[m_default_resolution_.first] )
  {
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
      x = 0;
      y = 0;
      break;

  }
  if ( m_default_resolution_.second ) flags |= SDL_FULLSCREEN;
  m_screen_ = SDL_SetVideoMode( x,
                                y,
                                0,
                                flags );

}
const Interface::ScreenResolutionType& Interface::actualResolution() const
{
  return m_default_resolution_;
}
gcn::Gui& Interface::screen() const
{

  return *m_gui_;

}
bool Interface::input() const
{

  SDL_Event event;
  bool final;

  final = false;
  while ( SDL_PollEvent( &event ) && !final ) {

    if ( event.type == SDL_QUIT )
      final = true;
    else
      m_input_->pushInput( event );
  }
  m_gui_->logic();
  return final;

}
void Interface::flip() const
{

  SDL_Flip( m_screen_ );

}
//-------------------------------------------------------------------------------
//
//	Metodos privados.
//
//-------------------------------------------------------------------------------
void Interface::initSDL( const std::string& icon,
                         const ScreenResolutionType& res )
{

  // initialize SDL
  if ( SDL_Init( SDL_INIT_VIDEO ) ) {
    throw std::runtime_error( "Can't initialize SDL" );
  }

  /*
   const SDL_VideoInfo* info = SDL_GetVideoInfo();
   L_(info) <<	"hardware available? " << info->hw_available;
   L_(info) << "window manager available? " << info->wm_available;
   L_(info) << "hardware blits accelerated? " << info->blit_hw;
   L_(info) << "hardware color key blits accelerated? " << info->blit_hw_CC;
   L_(info) << "hardware aplha blits accelerated? " << info->blit_hw_A;
   L_(info) << "software blits accelerated? " << info->blit_sw;
   L_(info) << "software color blits accelerated? " << info->blit_sw_CC;
   L_(info) << "software alpha blits accelerated? " << info->blit_sw_A;
   L_(info) << "color fills accelerated? " << info->blit_fill;
   L_(info) << "video memory (kB)? " << info->video_mem;
   L_(info) << "bits-per-pixel? " << info->vfmt->BitsPerPixel;
   L_(info) << " ------------- ";
   */

#if (( SDL_IMAGE_PATCHLEVEL == 10) && (SDL_IMAGE_MINOR_VERSION == 2) && (SDL_IMAGE_MAJOR_VERSION == 1))
  // Init SDL_image
  int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
  int initted = IMG_Init( flags );
  if ( ( initted & flags ) != flags ) {

    throw std::runtime_error( "Can't initialize IMG" );

  }
#endif
  // Init SDL_ttf
  if ( TTF_Init() ) {

    throw std::runtime_error( "Can't initialize TTF" );

  }

  // Load Icon Bitmap...
  SDL_Surface* Icon = IMG_Load( icon.c_str() ); // No tenemos pantalla aun .......
  if ( 0 == Icon ) {
    throw std::runtime_error( "Can't load program icon" );
  }
  SDL_WM_SetIcon( Icon,
                  NULL );
  SDL_putenv( (char *) "SDL_VIDEO_CENTERED=center" );

  changeScreenResolution( res );

  SDL_EnableUNICODE( 1 );
  SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY,
                       SDL_DEFAULT_REPEAT_INTERVAL );

}
void Interface::initGuichan( const std::string& font )
{

  m_imageLoader_ = new gcn::SDLImageLoader();
  gcn::Image::setImageLoader( m_imageLoader_ );
  m_graphics_ = new gcn::SDLGraphics();
  m_graphics_->setTarget( m_screen_ );
  m_input_ = new gcn::SDLInput();

  m_font_ =
      new gcn::ImageFont( font,
                          " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" );
  gcn::Widget::setGlobalFont( m_font_ );

  m_gui_ = new gcn::Gui();
  m_gui_->setGraphics( m_graphics_ );
  m_gui_->setInput( m_input_ );

}
void Interface::stopGuichan()
{

  delete m_gui_;
  delete m_font_;
  delete m_input_;
  delete m_graphics_;
  delete m_imageLoader_;

}
void Interface::stopSDL()
{

  TTF_Quit();
#if (( SDL_IMAGE_PATCHLEVEL == 10) && (SDL_IMAGE_MINOR_VERSION == 2) && (SDL_IMAGE_MAJOR_VERSION == 1))
  IMG_Quit();
#endif
  SDL_Quit();

}

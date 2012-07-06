/*
 * Interface.h
 *
 *  Created on: 21/01/2010
 *      Author: 79481180
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <utility>
#include <string>
#include <map>

#include <boost/utility.hpp>

namespace gcn {

  class Gui;
  class ImageFont;
  class SDLInput;
  class SDLGraphics;
  class SDLImageLoader;

}
class SDL_Surface;

class Interface : public boost::noncopyable
{
  public:

    typedef std::pair < std::string, bool > ScreenResolutionType;
    enum Resolution
    {

      SMALL = 0,
      MEDIUM,
      BIG

    };
    Interface( const std::string& icon,
               const std::string& font,
               const ScreenResolutionType& res );
    virtual ~Interface();

    int indexResolution( const std::string& index ) const;
    void changeScreenResolution( const ScreenResolutionType& res );
    const ScreenResolutionType& actualResolution() const;

    gcn::Gui& screen() const;
    bool input() const;
    void flip() const;

  private:

    ScreenResolutionType m_default_resolution_; // Resolucion actual de la pantalla.
    std::map < std::string, Resolution > m_screenTypes_;

    gcn::Gui* m_gui_;
    gcn::ImageFont* m_font_;
    gcn::SDLInput* m_input_;
    gcn::SDLGraphics* m_graphics_;
    gcn::SDLImageLoader* m_imageLoader_;
    SDL_Surface* m_screen_;

    void setVideoMode( Resolution );
    void initSDL( const std::string& icon,
                  const ScreenResolutionType& res );
    void initGuichan( const std::string& font );
    void stopGuichan();
    void stopSDL();

};

#endif /* INTERFACE_H_ */

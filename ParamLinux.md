# Compilación #

Los parámetros que he utilizado en el entorno de compilación Linux son los siguientes:
```
 -D_DEBUG -I{raiz}/src -I{raiz}/include -I/usr/include/lua5.1
```

Donde **{raiz}** es el directorio raíz donde esta situado el árbol de directorios de la aplicación.


# Enlace ( link ) #

Las librerías utilizadas en el enlace de la aplicación son las siguientes:
```
  xmlgui
  guichan_sdl
  guichan
  isohex
  SDL_gfx
  SDL_image
  SDL_ttf
  SDL
  luabind
  lua5.1
  tinyxml
  boost_thread
  boost_program_options
  boost_system
  boost_filesystem
  nvwa
```
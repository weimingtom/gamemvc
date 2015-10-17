# DEBUG #

  * Compilacion:

> _Preprocesador_

```
BOOST_THREAD_USE_LIB
_DEBUG
```

> _Includes_

```
"${workspace_loc:/${ProjName}/include}"
"${workspace_loc:/${ProjName}/src}"
"c:\mingw\msys\1.0\local\include"
```

> _Miscellaneous_

```
Other flags: -c -fmessage-length=0 -mthreads -Wno-delete-non-virtual-dtor
```

**Nota:**_-Wno-delete-non-virtual-dtor Es para que el compilador no de warnings con las librerias de BOOST con los destructores de clases._

  * Enlace:


> _Libraries (-l)_

```
boost_system-mt
boost_thread-mt
boost_program_options-mt
guichan_sdl
xmlgui
isohex
guichan
SDL_image
SDL_ttf
SDL_gfx
SDL
tinyxml
luabind
lua
tiff
jpeg
png
z
freetype
winmm
gdi32
nvwa
```

> _Library search path (-L)_

```
"c:\mingw\msys\1.0\local\lib"
```

_Miscellaneous_

```
Linker flags: -static -mthreads
```


# RELEASE #

  * Compilación:

```
BOOST_THREAD_USE_DLL
LUABIND_DYNAMIC_LINK
```

  * Enlace:

```
mingw32
SDLmain
boost_filesystem-mt
boost_system-mt
boost_thread-mt
boost_program_options-mt
guichan_sdl
xmlgui
isohex
guichan
SDL_image
SDL_ttf
SDL_gfx
SDL
tinyxml
luabind
lua
```
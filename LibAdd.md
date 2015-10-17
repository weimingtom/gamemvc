Paso a detallar la instalación de las diferentes librerías adicionales que van a ser usadas en el desarrollo de las diferentes aplicaciones.




---


# SDL #

Nos bajamos el siguiente fichero con el código fuente de la librería [SDL-1.2.tar.gz](http://www.libsdl.org/tmp/SDL-1.2.tar.gz) desempaquetando su contenido en el directorio definido en la variable de entorno HOME y ejecutamos los siguientes comandos en la pantalla de terminal de MSYS:
```
$ cd SDL-1.2.15/
$ ./configure && make && make install
```
Con esto tenemos instalada la librería de SDL, podemos comprobar su correcto funcionamiento con el siguiente procedimiento:
```
$ cd test/
$ ./configure && make
```
Y ejecutamos uno de los test  y comprobamos el resultado:
```
$ export SDL_STDIO_REDIRECT=0
$ testvidinfo.exe 
Video driver: windib
Current display: 1280x1024, 32 bits-per-pixel
        Red Mask = 0x00ff0000
        Green Mask = 0x0000ff00
        Blue Mask = 0x000000ff
Fullscreen video modes:
        1280x1024x32
        1280x960x32
        1280x768x32
        1280x720x32
        1280x600x32
        1152x864x32
        1024x1280x32
        1024x768x32
        960x1280x32
        864x1152x32
        800x600x32
        768x1280x32
        768x1024x32
        720x1280x32
        640x480x32
        640x400x32
        600x1280x32
        600x800x32
        512x384x32
        480x640x32
        400x640x32
        400x300x32
        384x512x32
        320x240x32
        320x200x32
A window manager is available
```
**Nota:** _La salida de este programa depende de la configuración hardware de la maquina donde se ejecuta_.
_Para utilizar directx con SDL hemos de bajar previamente el siguiente fichero [directx-devel.tar.gz](http://www.libsdl.org/extras/win32/cygwin/directx-devel.tar.gz) y extraemos su contenido en C:\MinGW. Yo no he encontrado mas rapidez, pero se puede probar_


---


# SDL\_gfx #

Descargamos los fuentes de la librería de [SDL\_gfx-2.0.23.tar.gz](http://www.ferzkopp.net/Software/SDL_gfx-2.0/SDL_gfx-2.0.23.tar.gz) y extraemos los ficheros en el directorio apuntado por la variable HOME, realizando los siguientes mandatos para crear la librería:
```
$ ./configure
$ make
$ make install
```
Podemos comprobar el correcto funcionamiento de la librería construyendo los programas de test mediante los siguientes comando:
```
$ cd Test/
$ ./configure --disable-shared
$ make
```
Podemos ejecutar los test para comprobar la correcta instalación de la librería mediante los siguientes comando:
```
TestABGR.exe
TestFonts.exe
TestFramerate.exe
TestGfxBlit.exe
TestGfxPrimitives.exe
TestGfxTexture.exe
TestImageFilter.exe
TestRotozoom.exe
TestShrink.exe
```

**Nota:** _He tenido que configurar los test con --disable-shared ya que la herramienta libtool me da errores si no lo hago asi._


---


# PNG #

Descargamos el código fuente de la librería [libpng-1.6.12](http://prdownloads.sourceforge.net/libpng/libpng-1.6.12.tar.gz?download) y extraemos los fuentes en el directorio donde apunta la variable de entorno HOME.
Construimos la librería con:
```
$ ./configure
$ make
```
Comprobamos el funcionamiento de la misma con:
```
$ make test
Running tests.  For details see pngtest-log.txt
Running test-pngtest.sh
  PASS: pngtest --strict pngtest.png
PASS: test-pngtest.sh
Running test-pngvalid-simple.sh
  PASS: pngvalid --standard
  PASS: pngvalid --standard --progressive-read
  PASS: pngvalid --standard --interlace
  PASS: pngvalid --standard --progressive-read --interlace
  PASS: pngvalid --size
  PASS: pngvalid --size --progressive-read
  PASS: pngvalid --transform
PASS: test-pngvalid-simple.sh
Running test-pngvalid-full.sh
  PASS: pngvalid --gamma-threshold
  PASS: pngvalid --gamma-transform
  PASS: pngvalid --gamma-sbit
  PASS: pngvalid --gamma-16-to-8
  PASS: pngvalid --gamma-background
  PASS: pngvalid --gamma-alpha-mode
  PASS: pngvalid --gamma-transform --expand16
  PASS: pngvalid --gamma-background --expand16
  PASS: pngvalid --gamma-alpha-mode --expand16
PASS: test-pngvalid-full.sh
==================
All 3 tests passed
==================
```
Instalamos la misma con:
```
$ make install
```


---


# JPEG #

Nos descargamos el siguiente paquete [jpegsrc.v9a.tar.gz](http://www.ijg.org/files/jpegsrc.v9a.tar.gz) y extraemos su contenido en el directorio donde apunta la variable home (C:\home\RAFAEL) en mi caso.
Construimos he instalamos la librería con:
```
$ ./configure
$ make
$ make install
```


---


# TIFF #

Descargamos el codigo fuente del siguiente enlace [tiff-4.0.3.tar.gz](ftp://ftp.remotesensing.org/pub/libtiff/tiff-4.0.3.tar.gz) y extraemos los fuentes en el directorio que apunta la variable de entorno HOME.
```
$ ./configure
$ make
$ make install
```
Una vez instalada la librería podemos comprobar el funcionamiento de la misma ejecutando:
```
$ make check

..........
PASS: ascii_tag.exe
PASS: long_tag.exe
PASS: short_tag.exe
PASS: strip_rw.exe
PASS: rewrite.exe
PASS: bmp2tiff_palette.sh
PASS: bmp2tiff_rgb.sh
PASS: gif2tiff.sh
PASS: ppm2tiff_pbm.sh
PASS: ppm2tiff_pgm.sh
PASS: ppm2tiff_ppm.sh
PASS: tiffcp-g3.sh
PASS: tiffcp-g3-1d.sh
PASS: tiffcp-g3-1d-fill.sh
PASS: tiffcp-g3-2d.sh
PASS: tiffcp-g3-2d-fill.sh
PASS: tiffcp-g4.sh
PASS: tiffcp-logluv.sh
PASS: tiffcp-thumbnail.sh
PASS: tiffdump.sh
PASS: tiffinfo.sh
PASS: tiffcp-split.sh
PASS: tiffcp-split-join.sh
PASS: tiff2ps-PS1.sh
PASS: tiff2ps-PS2.sh
PASS: tiff2ps-PS3.sh
PASS: tiff2ps-EPS1.sh
PASS: tiff2pdf.sh
PASS: tiffcrop-doubleflip-logluv-3c-16b.sh
PASS: tiffcrop-doubleflip-minisblack-1c-16b.sh
PASS: tiffcrop-doubleflip-minisblack-1c-8b.sh
PASS: tiffcrop-doubleflip-minisblack-2c-8b-alpha.sh
PASS: tiffcrop-doubleflip-miniswhite-1c-1b.sh
PASS: tiffcrop-doubleflip-palette-1c-1b.sh
PASS: tiffcrop-doubleflip-palette-1c-4b.sh
PASS: tiffcrop-doubleflip-palette-1c-8b.sh
PASS: tiffcrop-doubleflip-rgb-3c-16b.sh
PASS: tiffcrop-doubleflip-rgb-3c-8b.sh
PASS: tiffcrop-extract-logluv-3c-16b.sh
PASS: tiffcrop-extract-minisblack-1c-16b.sh
PASS: tiffcrop-extract-minisblack-1c-8b.sh
PASS: tiffcrop-extract-minisblack-2c-8b-alpha.sh
PASS: tiffcrop-extract-miniswhite-1c-1b.sh
PASS: tiffcrop-extract-palette-1c-1b.sh
PASS: tiffcrop-extract-palette-1c-4b.sh
PASS: tiffcrop-extract-palette-1c-8b.sh
PASS: tiffcrop-extract-rgb-3c-16b.sh
PASS: tiffcrop-extract-rgb-3c-8b.sh
PASS: tiffcrop-extractz14-logluv-3c-16b.sh
PASS: tiffcrop-extractz14-minisblack-1c-16b.sh
PASS: tiffcrop-extractz14-minisblack-1c-8b.sh
PASS: tiffcrop-extractz14-minisblack-2c-8b-alpha.sh
PASS: tiffcrop-extractz14-miniswhite-1c-1b.sh
PASS: tiffcrop-extractz14-palette-1c-1b.sh
PASS: tiffcrop-extractz14-palette-1c-4b.sh
PASS: tiffcrop-extractz14-palette-1c-8b.sh
PASS: tiffcrop-extractz14-rgb-3c-16b.sh
PASS: tiffcrop-extractz14-rgb-3c-8b.sh
PASS: tiffcrop-R90-logluv-3c-16b.sh
PASS: tiffcrop-R90-minisblack-1c-16b.sh
PASS: tiffcrop-R90-minisblack-1c-8b.sh
PASS: tiffcrop-R90-minisblack-2c-8b-alpha.sh
PASS: tiffcrop-R90-miniswhite-1c-1b.sh
PASS: tiffcrop-R90-palette-1c-1b.sh
PASS: tiffcrop-R90-palette-1c-4b.sh
PASS: tiffcrop-R90-palette-1c-8b.sh
PASS: tiffcrop-R90-rgb-3c-16b.sh
PASS: tiffcrop-R90-rgb-3c-8b.sh
PASS: tiff2rgba-logluv-3c-16b.sh
PASS: tiff2rgba-minisblack-1c-16b.sh
PASS: tiff2rgba-minisblack-1c-8b.sh
PASS: tiff2rgba-minisblack-2c-8b-alpha.sh
PASS: tiff2rgba-miniswhite-1c-1b.sh
PASS: tiff2rgba-palette-1c-1b.sh
PASS: tiff2rgba-palette-1c-4b.sh
PASS: tiff2rgba-palette-1c-8b.sh
PASS: tiff2rgba-rgb-3c-16b.sh
PASS: tiff2rgba-rgb-3c-8b.sh
===================
All 78 tests passed
===================
..........
```


---


# SDL\_image #

Descargamos el codigo fuente de [SDL\_image-1.2.12.tar.gz](http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12.tar.gz) y extraemos los ficheros en el directorio apuntado por la variable HOME, realizando los siguientes mandatos para crear la librería:
```
$ ./configure
$ make
$ make install
```

**Nota:** _No he podido incluir la libreria libwebp ya que me da problema al compilarla_.

---




# freetype #

Descargamos el código fuente de [freetype-2.4.9.tar.gz](http://sourceforge.net/projects/freetype/files/freetype2/2.4.9/freetype-2.4.9.tar.gz/download) y descomprimimos su contenido en el directorio apuntado por la variable global HOME, construimos he instalamos la librería con los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```


---


# SDL\_ttf #
Nos bajamos los fuentes de [SDL\_ttf-2.0.11.tar.gz](http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11.tar.gz) y extraemos su contenido en el directorio apuntado por la variable HOME. Creamos la librería con los siguientes mandatos:
```
$ ./configure
$ make
```
y podemos comprobar la librería con los siguientes mandatos:
```
$ showfont C:/windows/fonts/arial.ttf 32 "Hello world."
$ showfont -solid C:/windows/fonts/arial.ttf 32 "Hello world."
$ glfont C:/windows/fonts/arial.ttf 32 "Hello world."
```
despues de comprobar su correcto funcionamiento, procedemos a instalar la librería con el siguiente comando:
```
$ make install
```


---


# guichan #

Nos bajamos la version [guichan-0.9.5-ub.tar.gz](http://www.telefonica.net/web2/yque/files/guichan-0.9.5-ub.tar.gz), se descomprime en el directorio apuntado por la variable de entorno HOME. Se configura y se crea la librería con los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```
**_Tip_**: Queda por añadir el test que ya existía.


---


# isohexlib #

Librería de interface para distintos tipos de mapas Isometricos y rectangulares, con rombos o bien con hexagonos, basado en el proyecto IsoHexLib, necesita guichan y SDL para poderse utilizar. Nos bajamos la version [isohexlib-0.1.3-ub.tar.gz](http://www.telefonica.net/web2/yque/files/isohexlib-0.1.3-ub.tar.gz), se descomprime en el directorio apuntado por la variable de entorno HOME. Se configura y se crea la librería con los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```
**_Tip_**: Añadir programa de test?.


---


# TinyXML #

Descargamos el codigo fuente de: [tinyxml-2.5.3-ub.tar.gz](http://www.telefonica.net/web2/yque/files/tinyxml-2.5.3-ub.tar.gz) desempaquetando su contenido en el directorio definido por la variable de entorno HOME. Están modificadas las funciones de instalación y compilación para que funcione con autotools y genere una librería DLL. He habilitado el parámetro de compilación -DTIXML\_USE\_STL, luego se ha de tener en cuenta a la hora de utilizar la librería. Para generar la misma ejecutamos los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```


---


# BOOST #

Conjunto de librerías de código abierto preparadas para extender las capacidades del lenguaje de  programación C++. Descargamos los fuentes de
[boost\_1\_49\_0.tar.gz](http://sourceforge.net/projects/boost/files/boost/1.49.0/boost_1_49_0.tar.gz/download) se desempaquetan en el directorio raíz definido en la variable de entorno HOME. Realizamos los siguientes pasos para la instalación de los ficheros de cabecera de las librerías.

```
$ ./bootstrap.sh --with-toolset=mingw
$ mv project-config.jam project-config.jam.bien
$ b2 toolset=gcc --build-type=complete threading=multi variant=release --layout=tagged --without-mpi --without-python install --prefix=/usr/local/qq
$ mkdir /usr/local/qq/bin
$ mv /usr/local/qq/lib/*.dll /usr/local/qq/bin/.
$ cp -R /usr/local/qq/* /usr/local/.
$ rm -rf /usr/local/qq
```

**Nota:**_Una forma burda de pasar los datos de un diectorio a otro pero no se me ocurre de momento otra._

```
$ b2 --without-mpi --without-python variant=release threading=multi link=static,shared cxxflags=--Wno-unused-local-typedefs
```


---


# xmlgui #

Librería usada para la definición de entornos guichan  mediante una estructura xml, permite definir los widgets de las interfaces de SDL en XML, resulta muy comodo para la definición de las pantallas. Se descargan los fuentes de [xmlgui-0.1.1-ub.tar.gz](http://www.telefonica.net/web2/yque/files/xmlgui-0.1.1-ub.tar.gz) , se desempaqueta y se instala con los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```
Podemos comprobar el correcto funcionamiento de la misma con los siguientes mandatos:
```
$ xmlgui
```
Nos ha de aparecer una pantalla con este resultado:

![http://gamemvc.googlecode.com/svn/wiki/images/LibAdd/xmlgui.png](http://gamemvc.googlecode.com/svn/wiki/images/LibAdd/xmlgui.png)


---


# LUA #

Librería de soporte de lenguaje de programación imperativo y estructurado, bastante ligero que fue diseñado como lenguaje de script con una semántica extensible. Se descargan los fuentes de [lua-5.1.4-ub.tar.gz](http://www.telefonica.net/web2/yque/files/lua-5.1.4-ub.tar.gz) y los desempaquetamos en el directorio definido por la variable global HOME, para crear la librería ejecutamos los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```
Podemos comprobar la correcta instalación con los siguientes mandatos:
```
$ lua -i
Lua 5.1.4  Copyright (C) 1994-2008 Lua.org, PUC-Rio
> print("Hola")
Hola
> os.exit()
```


---



# LUABIND #

Luabind es un API para C++ que encapsula más limpiamente el registro de funciones y clases para LUA. Descargamos los fuentes de : [luabind-0.9.1a-ub.tar.gz](http://www.telefonica.net/web2/yque/files/luabind-0.9.1a-ub.tar.gz) y extraemos los fuentes en el directorio señalado por la variable de entorno HOME. Construimos e instalamos la librería con los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```


---


# nvwa #

Librería test asignación de memoria dinámica, la bajamos de [nvwa-0.0.1.tar.gz](http://www.telefonica.net/web2/yque/files/nvwa-0.0.1.tar.gz) y extraemos los fuentes en el directorio señalado por la variable de entorno HOME. Construimos e instalamos la librería con los siguientes mandatos:
```
$ ./configure
$ make
$ make install
```
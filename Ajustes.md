Vamos a definir los pasos a ejecutar para ajustar los dos entornos para poder compilar e instalar los paquetes necesarios para el desarrollo de las aplicaciones.




---


# MINGW #

En este entorno vamos a realizar los siguientes pasos para ajustar el entorno:


  * PKG-CONFIG

> Nos bajamos el paquete [msys-pkg-config-win32.zip](http://www.johnnypops.co.uk/mingw/msys-pkg-config-win32.zip) y extraemos su contenido en el directorio c:\MinGW\msys\1.0.

> Hemos de modificar el fichero C:\MinGW\msys\1.0\bin\pkg-config para que refleje la ubicación del programa, ha de quedar con este contenido:
```
#! /bin/sh
/mingw/msys/1.0/bin/aliased/pkg-config.exe $* --prefix-variable=/usr/local
exit $?
```

  * MASM y YASM

> Nos bajamos el [masm.exe](http://www.libsdl.org/extras/win32/mingw32/nasm.exe) y lo copiamos en el directorio /mingw/bin ( c:\MinGW\bin ).

> Bajamos tambien el compilador [yasm-0.8.0-win32.exe](http://www.tortall.net/projects/yasm/releases/yasm-0.8.0-win32.exe) y lo copiamos en el directorio /mingw/bin ( c:\MinGW\bin ) con el nombre yasm.exe.


  * ZIP

Instalamos el paquete de desarrollo:

> mingw-get install mingw32-libz

  * ACLOCAL

Para que las autotools encuentren el fichero SDL.m4 creamos en /mingw/share/aclocal el fichero dirlist con el siguiente contenido:

```
   /usr/local/share/aclocal
```

Esto le indica a las autotools que ademas del directorio por defecto a buscar las macros m4 incluya también los directorios que se encuentren en el fichero dirlist.


---


# MSYS #


  * HOME

> Definimos la variable de entorno HOME, que ha de apuntar al directorio donde vamos a manejar nuestros fuentes, librerías, paquetes etc...

![http://gamemvc.googlecode.com/svn/wiki/images/MSYS-DTK/home.png](http://gamemvc.googlecode.com/svn/wiki/images/MSYS-DTK/home.png)

> En mi caso he definido la variable HOME apuntando al directorio c:\home\RAFAEL, que es el que utilizare para todos los procesos de pruebas desarrollos etc.

  * TERMINAL

> Con esto ya podemos pinchar en el icono de MSYS y obtendremos un terminal muy del estilo de Unix:

![http://gamemvc.googlecode.com/svn/wiki/images/MSYS/Pantalla.png](http://gamemvc.googlecode.com/svn/wiki/images/MSYS/Pantalla.png)


> De la misma manera y en el mismo directorio creamos un fichero .profile para posteriormente poder manejar la creación de librerías y aplicaciones. El contenido del mencionado fichero es el siguiente:
```
# points builds at their dependencies
export set LIBRARY_PATH=/usr/local/bin:/usr/local/lib
export set CPATH=/usr/local/include
export set PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:/mingw/lib/pkgconfig
```


---


# Comprobación #

Una vez terminado este proceso hemos de tener un entorno que nos permite el configurar e instalar las diferentes librerías que vamos a utilizar en nuestros desarrollos.

Podemos comprobar las versiones instaladas mediante los siguientes mandatos en un terminal de MSYS:

```
$ pkg-config --version
0.20

$ nasm.exe -v
NASM version 0.98.31 compiled on May 18 2002

$ yasm --version
yasm 0.8.0.2194
Compiled on Apr  9 2009.
Copyright (c) 2001-2008 Peter Johnson and other Yasm developers.
Run yasm --license for licensing overview and summary.
```
He utilizado [mingw-get-inst-20120426](http://sourceforge.net/projects/mingw/files/Installer/mingw-get-inst/mingw-get-inst-20120426/), que nos proporciona un entorno de compilación  y depuración con g++ y gdb.

Utilizando el propio instalador se instala automaticamente el entorno, así como todos los paquetes del sistema base suplementarios.

El directorio de instalación por defecto es el C:\MinGW que es el que voy a utilizar a lo largo de todo el documento.

Selecciono el paquete de **C** y **C++**  en la instalación..

<img src='http://gamemvc.googlecode.com/svn/wiki/images/MinGW/ScreenShot001.png' width='320' height='240' />

..asi como el paquete de **`MinGW Developer ToolKit`** que es el que nos añade el entorno de MSYS con su interface tipo unix y algunas herramientas de utilidad.

<img src='http://gamemvc.googlecode.com/svn/wiki/images/MinGW/ScreenShot002.png' width='320' height='240' />

Despues de instalar este paquete ya tenemos las diferentes utilidades que nos permiten compilar y depurar programas de C++ en un entorno de Windows, ademas de darnos una interface muy similar a un terminal TTY de unix.
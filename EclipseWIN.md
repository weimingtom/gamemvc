Paso a describir los pasos que he seguido para instalar un entorno de desarrollo con Eclipse bajo windows. El paquete que he utilizado es [eclipse-cpp-galileo-SR1-win32.zip](http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/galileo/SR1/eclipse-cpp-galileo-SR1-win32.zip&url=http://ftp.man.poznan.pl/eclipse/technology/epp/downloads/release/galileo/SR1/eclipse-cpp-galileo-SR1-win32.zip&mirror_id=488) que después de descargarlo lo desempaqueto en el directorio eclipse dentro de c:\Archivos de Programa\, y acto seguido saco un acceso directo al mismo en el escritorio de windows.

Arranco Eclipse y me pide el directorio donde alojar el workspace del mismo:
El cual lo configuro con el valor de la variable de entorno HOME, que he utilizado para alojar todos los paquetes y ejecuciones de configuración hasta ahora.
Ahora paso a instalar las diferentes utilidades que voy a utilizar dentro del entorno de eclipse.

Perfil de edicion [rafael.xml](http://www.telefonica.net/web2/yque/files/rafael.xml)



---

# SVN #
Subeclipse es un plug-in para el IDE Eclipse dando soporte de subversion dentro del mismo. Añadimos la localización dentro de Eclipse:

Hecho esto seleccionamos los paquetes a instalar:
Y pulsamos install. Nos sale una pantalla de este estilo:
Procedemos con Next y aceptamos la instalación. Al terminar nos aparece una pantalla como esta:
Pulsamos a YES y esperamos a que se reactive Eclipse.


---

# XML #
Vamos a instalar un pequeño editor de XML dentro de Eclipse de la misma forma que hemos instalado el soporte de SVN.
Para esto seleccionamos lo siguiente:
Pulsamos Install igual que la vez anterior y validamos la instalación:
Esperamos a que nos pida reiniciar Eclipse
Lo cual aceptamos pulsando Yes.


---

# LUA #
Instalamos el soporte de editor para Lua, para lo cual primero hemos de añadir el sitio de descargas para lua:
Seleccionamos el paquete a instalar:
Y procedemos a pulsar Install, aceptamos las licencias y procedemos a su instalación esperando por la pantalla de finalizacion.
Después de aceptar el reinicio de Eclipse ya tenemos los elementos necesarios para empezar a realizar desarrollos con Eclipse y las librerías instaladas anteriormente.
**_No logro que funcione correctamente_**

  * Con el dbg dentro del eclipse no se ve la salida de stderr.
  * Con el SDL activado ( sin quitar el main ) no se ve la salida de stderr.

  1. Añadir en el evironment global de eclipse la variable Path con el valor c:\msys\1.0\bin para que encuentro los mandatos necesarios para la correcta ejecución Por ejemplo el mandato rm -rf que usa al borrar el proyecto y volver a compilar.
  1. En la compilación debug no hace falta la inclusión de mingw32 , ni de SDLmain, la libreria nvwa ha de ir  la ultima.
  1. Se ha de definir --enable-auto-import como opción en el montaje del programa en formato Release para que sea capaz de encontrar los entry points de algunas librerías con referencias circulares.
  1. En la definición de la ejecución del release se ha de añadir una variable Path en el entorno de ejecución con el valor del Path = c:\msys\1.0\local\bin;${env\_var:Path} que es donde estan las librerías de carga dinámica que voy a utilizar. Si no se incluye el ${env\_var:Path} no funciona.

# Introducción #

Uso de Nvwa para comprobar los errores de software que ocurren cuando un bloque de memoria reservada no es liberada.
Ejecutamos un **new** ( o asignación de memoria dinámica ) sin su correspondiente **delete**.


# Detalles #

**Definición**

Nvwa es una colección de ficheros/clases/plantillas para facilitar la creación y test de aplicaciones en C++.

**Uso**

  * Esconder la definición del main de la biblioteca SDL, para que pueda funcionar la salida en stderr. El problema con esto es que se pierde la posibilidad de grabar de una manera automatica en un fichero la salida tanto de stderr como de stdout.
```

#ifdef main
#undef main
#endif

```
> Se puede redirigir de una manera manual la salida mediante el uso de pipes.
```
$ Debug/TestGameMVC.exe > stdout.txt
```
  * El programa se enlaza ( link ) con todas las librerías de forma estática ( parametro -static del linker g++ ).
  * Se añade la librería **nvwa** al final de la lista de librerías del programa.

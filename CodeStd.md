_**Estamos en definición de ello**_

# Introducción #

Defino las pautas de codificación que deseo seguir en el desarrollo del proyecto. La inmensa mayoría de ellas están basadas en el documento [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml), pero intentando ser adaptadas al IDE Eclipse en sus versiones Galileo y Helios.

# Detalles #

Paso a definir alguno de los detalles que he utilizado en el desarrollo.

## Nombres ##

Los nombres de las funciones, variables, métodos, ficheros han de ser descriptivos. Los tipos y las variables han de representar nombres de objetos, mientras que las funciones y los métodos han de ser verbos de mandatos. Se ha de dar un nombre descriptivo dentro de lo razonable.

### Nombres de ficheros ###

Los nombres de los ficheros tienen el mismo formato que el nombre de la clase que representan. Los ficheros de C++ han de terminar en .cpp y los ficheros de cabecera han de terminar en .h ( _Esto es debido a la forma que lo hace por defecto Eclipse al crear una Clase C++_ ).

### Nombres de los tipos ###

Los nombres de los tipos han de empezar con una letra mayúscula y han de tener una letra mayúscula por cada uno de las palabras que componen el nombre.

### Nombres de variables ###

Los nombres de variables son todo minúsculas, con subrayados entre las palabras. Loas variables miembro de las clases han de terminar en subrayado.

### Nombres de las funciones y los métodos ###

  * Las funciones y los métodos  han de empezar con mayúsculas y una mayúscula por cada palabra que lo compone.
  * Las funciones de acceso y las de modificación ( funciones get y set ), han de ser iguales al nombre de la variable que están obteniendo o poniendo. Sin el subrayado final.

## Comentarios ##

### Estilo de los comentarios ###

Usar o bien // o bien //, siempre que se sea coherente. Dentro de Eclipse, al iniciar un comentario con /`**`, nos genera entradas correspondientes para doxygen. Ejemplo:
```
	/**!
	 *
	 * @param game
	 * @return
	 */
	IntroModel(MyGame& game);
```

### Comentarios de fichero ###

Comenzar cada fichero con una fecha de creación su autor y una pequeña descripción de que es lo que contiene. Los primeros datos como son la fecha y el autor los pone por defecto Eclipse al crear el fichero.

### Comentarios de clase ###

En la definición de cada clase se ha de acompañar por un comentario que describe la misma para que es y como se usa.

### Comentarios de métodos y funciones ###

  * Cada definición de un método o función ha de tener unos comentarios precediendo a la misma que describen que es lo que hace y como se ha de usar. El comentario describe lo que hace el método y no como lo ha de hacer.
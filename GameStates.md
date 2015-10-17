Las ideas plasmadas en este apartado son tomadas de

[Managing Game States in C++](http://gamedevgeek.com/tutorials/managing-game-states-in-c/)

yo voy a utilizarlas e intentar ampliarlas con las experiencias que he ido probando.

Múltiples estados son necesarios en los juegos para realizar el correcto tratamiento de los mismos. Así un juego suele empezar con una parte introductoria, un menú de opciones y finalmente a la parte del juego como tal. Una vez que el juego termina pasas a un estado de terminación de la partida y posiblemente al estado del menú de opciones de nuevo, también en muchos juegos puedes estar en varios estados al mismo tiempo o bien pasar del estado de juego a un estado de menú.

**¿Que es un estado?**

Vamos a definir un estado como programa separado dentro del juego general. Cada estado procesara los eventos del juego de manera diferente y dibujará cosas diferentes en la pantalla. Cada estado ha de atender a sus eventos, actualiza los elementos del juego, y dibuja el siguiente marco en la pantalla. Luego ya tenemos identificados tres métodos que nuestro estado ha de tener.

Así mismo, un estado dentro del juego ha de ser capaz de cargar los recursos que necesite al comienzo y liberarlos cuando termine de utilizarlos. También hemos de tener la oportunidad de  pausar el juego y retomar el mismo en la situación en la cual estaba. Un ejemplo es pausar el juego y visualizar un menú emergente encima del mismo. Por lo tanto nuestra clase base puede tener esta apariencia:
```
class CGameState
{
public:
	virtual void Init;
	virtual void Cleanup;

	virtual void Pause;
	virtual void Resume;

	virtual void HandleEvents;
	virtual void Update;
	virtual void Draw;

};
```
De esta clase base podemos heredar los diferentes estados de nuestro juego, introducción, menú,   y el propio juego en si.

**El gerente de estados**

Necesitamos una manera de gestionar estos estados, un gerente de estados. Necesitamos inicializar la parte gráfica y todos los elementos comunes del juego, asi como al finalizar el mismo necesitamos realizar una limpieza del mismo. Como vamos a utilizar este motor de estados en nuestro bucle principal, necesitamos comprobar si esta funcionando, decirle que termine y manejar el proceso de eventos, actualizar los elementos presentes en el juego, y dibujar el siguiente marco en  la pantalla.
Para permitir la existencia de estos estados del juego, he implementado una pila de estados. Vamos a utilizar un vector STL para implementar esta pila. Vamos a necesitar metodos que nos permitan cambiar de estados, meter estados en la pila, y sacarlos de la misma.
La clase que he implementado como gerente de estados es similar a lo siguiente:
```
class CGameEngine
{
public:

	void Init();
	void Cleanup();

	void ChangeState();
	void PushState();
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;

};
```
/* Compilación: g++ -g -o img test.cpp
 * Ejecución: ./img
 *
 * Luego de la ejecución se generarán 3 imagines: imagen.png,
 * imagen_desplazada_500.png e imagen_desplazada_600.png
 */

#include "moving_image.h"
#include<unistd.h> // para sleep (linux). Usar  
#include<windows.h> // para Windows
#include <stack>
#include <queue>
#include <string>

int main() {
  moving_image im;

  im.draw("imagen.png");
  im.move_down(100);
  im.draw("imagen_desplazada_100.png");
  im.undo();
  im.draw("imagen_desplazada_200.png");
  im.redo();
  im.draw("imagen_desplazada_300.png");
  im.move_left(100);
  im.draw("imagen_desplazada_400.png");
  im.repeat();
  im.draw("imagen_desplazada_500.png");
  im.repeat_all();
 
  // AAAAAA te odio git de vsc 


  /* NOTA 1: Si usan el mismo nombre para las imágenes, entonces cada llamada al
  método draw() sobreescribirá a la imagen */

  /* NOTA 2: Si usan un ciclo while(1) y usan el mismo nombre de imagen,
  entonces se puede generar un efecto de desplazamiento continuo (algo así como
  un video =D ) */
  return 0;
}

/* Compilación: g++ -g -o img test.cpp
 * Ejecución: ./img
 *
 * Luego de la ejecución se generarán 3 imagines: imagen.png,
 * imagen_desplazada_500.png e imagen_desplazada_600.png
 */

#include "moving_image.h"
#include<unistd.h> // para sleep (linux). Usar  
#include<windows.h> // para Windows

int main() {
  moving_image im;

  im.draw("imagen.png");
  im.move_down(100);
  im.rotate();
  sleep(2);
  im.draw("imagen_desplazada_100.png");
  im.move_down(100);
  sleep(2);
  im.draw("imagen_desplazada_200.png");
  im.rotate();
  im.draw("imagen_rotada.png");
  im.move_up(100);
  sleep(2);
  im.draw("imagen_desplazada_300.png");
  im.move_left(100);
  sleep(2);
  im.draw("imagen_desplazada_400.png");
  im.move_right(100);
  sleep(2);
  im.draw("imagen_desplazada_500.png");
  im.rotate();
  im.draw("imagen_rotada_2.png");

  /* NOTA 1: Si usan el mismo nombre para las imágenes, entonces cada llamada al
  método draw() sobreescribirá a la imagen */

  /* NOTA 2: Si usan un ciclo while(1) y usan el mismo nombre de imagen,
  entonces se puede generar un efecto de desplazamiento continuo (algo así como
  un video =D ) */
  return 0;
}

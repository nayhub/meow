#ifndef MOVING_IMG_H
#define MOVING_IMG_H

#include "basics.h"
#include <stack>
#include <queue>
#include <string>

// AA A A A A A A A  A A A A A 

// Clase que representa una imagen como una colección de 3 matrices siguiendo el
// esquema de colores RGB

enum ActionType {
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    ROTATE
};
struct Action {
    ActionType type;
    int param;
};

std::stack<Action> history;
std::stack<Action> undo_history;
std::queue<Action> repeatqueue;
class moving_image {
private:
  unsigned char **red_layer; // Capa de tonalidades rojas
  unsigned char **green_layer; // Capa de tonalidades verdes
  unsigned char **blue_layer; // Capa de tonalidades azules

public:
  // Constructor de la imagen. Se crea una imagen por defecto
  moving_image() {
    // Reserva de memoria para las 3 matrices RGB
    red_layer = new unsigned char*[H_IMG];
    green_layer = new unsigned char*[H_IMG];
    blue_layer = new unsigned char*[H_IMG];
    
    for(int i=0; i < H_IMG; i++) {
      red_layer[i] = new unsigned char[W_IMG];
      green_layer[i] = new unsigned char[W_IMG];
      blue_layer[i] = new unsigned char[W_IMG];
    }

    // Llenamos la imagen con su color de fondo
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++) {
	red_layer[i][j] = DEFAULT_R;
	green_layer[i][j] = DEFAULT_G;
	blue_layer[i][j] = DEFAULT_B;
      }

    // Dibujamos el objeto en su posición inicial
    for(int i=0; i < 322; i++)
      for(int j=0; j < 256; j++) {
	if(!s_R[i][j] && !s_G[i][j] && !s_B[i][j]) {
	  red_layer[INIT_Y+i][INIT_X+j] = DEFAULT_R;
	  green_layer[INIT_Y+i][INIT_X+j] = DEFAULT_G;
	  blue_layer[INIT_Y+i][INIT_X+j] = DEFAULT_B;
	} else {
	  red_layer[INIT_Y+i][INIT_X+j] = s_R[i][j];
	  green_layer[INIT_Y+i][INIT_X+j] = s_G[i][j];
	  blue_layer[INIT_Y+i][INIT_X+j] = s_B[i][j];
	}
  }  
  }

  // Destructor de la clase
  ~moving_image() {
    for(int i=0; i < H_IMG; i++) {
      delete red_layer[i];
      delete green_layer[i];
      delete blue_layer[i];
    }

    delete red_layer;
    delete green_layer;
    delete blue_layer;
  }

  // Función utilizada para guardar la imagen en formato .png
  void draw(const char* nb) {
    _draw(nb);
  }

  // Función que similar desplazar la imagen, de manera circular, d pixeles a la izquierda
  void move_left(int d) {
    unsigned char **tmp_layer = new unsigned char*[H_IMG];
    for(int i=0; i < H_IMG; i++) 
      tmp_layer[i] = new unsigned char[W_IMG];
    
    // Mover la capa roja
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	    tmp_layer[j][i] = red_layer[i][j+d];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[j][i] = red_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	  red_layer[j][i] = tmp_layer[i][j];

    // Mover la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j] = green_layer[i][j+d];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[i][j] = green_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	green_layer[i][j] = tmp_layer[i][j];

    // Mover la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j] = blue_layer[i][j+d];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[i][j] = blue_layer[i][k];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	blue_layer[i][j] = tmp_layer[i][j];

    Action action;
    action.type = MOVE_LEFT;
    action.param = d;

    history.push(action);
    repeatqueue.push(action);
  }

  // DERECHAAAAAAAAA
  void move_right(int d) {
    unsigned char **tmp_layer = new unsigned char*[H_IMG];
    for(int i=0; i < H_IMG; i++) 
      tmp_layer[i] = new unsigned char[W_IMG];
    
    // Mover la capa roja
     for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	    tmp_layer[i][j+d] = red_layer[i][j];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < d; j++)
    	tmp_layer[i][j] = red_layer[i][W_IMG-d+j];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	    red_layer[i][j] = tmp_layer[i][j];

    // Mover la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j+d] = green_layer[i][j];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < d; j++)
    	tmp_layer[i][j] = green_layer[i][W_IMG-d+j];   

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	green_layer[i][j] = tmp_layer[i][j];

    // Mover la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j+d] = blue_layer[i][j];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < d; j++)
    	tmp_layer[i][j] = blue_layer[i][W_IMG-d+j];     

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	blue_layer[i][j] = tmp_layer[i][j];

    Action action;
    action.type = MOVE_RIGHT;
    action.param = d;

    history.push(action);
    repeatqueue.push(action);
  }

// ARRIBAAAAA
  void move_up(int d) {
    unsigned char **tmp_layer = new unsigned char*[H_IMG];
    for(int i=0; i < H_IMG; i++) 
      tmp_layer[i] = new unsigned char[W_IMG];
    
    // Mover la capa roja
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	tmp_layer[j][i] = red_layer[j+d][i];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[j][i] = red_layer[k][i];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	    red_layer[j][i] = tmp_layer[j][i];

    // Mover la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j] = green_layer[j+d][i];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[i][j] = green_layer[k][i];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	green_layer[i][j] = tmp_layer[j][i];

    // Mover la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j] = blue_layer[j+d][i];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=W_IMG-d, k=0; j < W_IMG; j++, k++)
    	tmp_layer[i][j] = blue_layer[k][i];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	blue_layer[i][j] = tmp_layer[j][i];

    Action action;
    action.type = MOVE_UP;
    action.param = d;

    history.push(action);
    repeatqueue.push(action);
  }
  // ABAJOOOOOOOO
  void move_down(int d) {
    unsigned char **tmp_layer = new unsigned char*[H_IMG];
    for(int i=0; i < H_IMG; i++) 
      tmp_layer[i] = new unsigned char[W_IMG];
    
    // Mover la capa roja
     for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
	    tmp_layer[i][j+d] = red_layer[j][i];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < d; j++)
    	tmp_layer[i][j] = red_layer[W_IMG-d+j][i];      

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	red_layer[i][j] = tmp_layer[j][i];

    // Mover la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j+d] = green_layer[j][i];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < d; j++)
    	tmp_layer[i][j] = green_layer[W_IMG-d+j][i];   

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	green_layer[i][j] = tmp_layer[j][i];

    // Mover la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG-d; j++)
    	tmp_layer[i][j+d] = blue_layer[j][i];      
    
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < d; j++)
    	tmp_layer[i][j] = blue_layer[W_IMG-d+j][i];     

    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
    	blue_layer[i][j] = tmp_layer[j][i];

    Action action;
    action.type = MOVE_DOWN;
    action.param = d;

    history.push(action);
    repeatqueue.push(action);
  }

  // ROTATEEEEEEEE

  void rotate() {
    unsigned char **tmp_layer = new unsigned char*[W_IMG];
    for(int i=0; i < W_IMG; i++) 
      tmp_layer[i] = new unsigned char[H_IMG];
    
    // Rotar la capa roja
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	    tmp_layer[j][H_IMG-1-i] = red_layer[i][j];      

    // Copiar de vuelta a la capa original
    for(int i=0; i < W_IMG; i++)
      for(int j=0; j < H_IMG; j++)
	    red_layer[i][j] = tmp_layer[i][j];
    
    // Rotar la capa verde
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	    tmp_layer[j][H_IMG-1-i] = green_layer[i][j];      

    // Copiar de vuelta a la capa original
    for(int i=0; i < W_IMG; i++)
      for(int j=0; j < H_IMG; j++)
	    green_layer[i][j] = tmp_layer[i][j];
    
    // Rotar la capa azul
    for(int i=0; i < H_IMG; i++)
      for(int j=0; j < W_IMG; j++)
	    tmp_layer[j][H_IMG-1-i] = blue_layer[i][j];      

    // Copiar de vuelta a la capa original
    for(int i=0; i < W_IMG; i++)
      for(int j=0; j < H_IMG; j++)
	    blue_layer[i][j] = tmp_layer[i][j];

  history.push({ROTATE, 0});
}

void repeat() {
    if(!history.empty()) {
        Action last_action = history.top();
        history.pop();

         switch(last_action.type) {
            case MOVE_LEFT:
              move_left(last_action.param);
                break;
            case MOVE_RIGHT:
                move_right(last_action.param);
                break;
            case MOVE_UP:
                move_up(last_action.param);
                break;
            case MOVE_DOWN:
                move_down(last_action.param);
                break;
            case ROTATE:
                rotate();
                break;
            default:
                break;
        }
    } else {}
}

void undo() {
    if(!history.empty()) {
        Action last_action = history.top();
        history.pop();

         switch(last_action.type) {
            case MOVE_LEFT:
              move_right(last_action.param);
              undo_history.push(last_action);
                break;
            case MOVE_RIGHT:
                move_left(last_action.param);
                undo_history.push(last_action);
                break;
            case MOVE_UP:
                move_down(last_action.param);
                undo_history.push(last_action);
                break;
            case MOVE_DOWN:
                move_up(last_action.param);
                undo_history.push(last_action);
                break;
            case ROTATE:
                rotate();
                break;
            default:
                break;
        }
    } else {}
}

void redo() {
    if(!undo_history.empty()) {
        Action last_undone_action = undo_history.top();
        undo_history.pop();

          switch(last_undone_action.type) {
            case MOVE_LEFT:
              move_left(last_undone_action.param);
              history.push(last_undone_action);
                break;
            case MOVE_RIGHT:
              move_right(last_undone_action.param);
              history.push(last_undone_action);
                break;
            case MOVE_UP:
              move_up(last_undone_action.param);
              history.push(last_undone_action);
                break;
            case MOVE_DOWN:
              move_down(last_undone_action.param);
              history.push(last_undone_action);
                break;
            case ROTATE:
                rotate();
                break;
            default:
                break;
          }
    } else {}
  }



void repeat_all() {

  this->draw("repeat_imagen.png");
    std::queue<Action> repeatqueue_copy = repeatqueue;

    int contador = 1;
    while(!repeatqueue_copy.empty()) {
        Action action = repeatqueue_copy.front();
        repeatqueue_copy.pop();

          switch(action.type) {
            case MOVE_LEFT:
              move_left(action.param);
                break;
            case MOVE_RIGHT:
              move_right(action.param);
                break;
            case MOVE_UP:
              move_up(action.param);
                break;
            case MOVE_DOWN:
              move_down(action.param);
                break;
            case ROTATE:
                rotate();
                break;
            default:
                break;
          }

    std::string nombreArchivo = "repeat_imagen_desplazada_" + std::to_string(contador) + ".png";
    this->draw(nombreArchivo.c_str());
        
    contador++;
    }
}

private:
  // Función privada que guarda la imagen en formato .png
  void _draw(const char* nb) {
    //    unsigned char rgb[H_IMG * W_IMG * 3], *p = rgb;
    unsigned char *rgb = new unsigned char[H_IMG * W_IMG * 3];
    unsigned char *p = rgb;
    unsigned x, y;

    // La imagen resultante tendrá el nombre dado por la variable 'nb'
    FILE *fp = fopen(nb, "wb");

    // Transformamos las 3 matrices en una arreglo unidimensional
    for (y = 0; y < H_IMG; y++)
        for (x = 0; x < W_IMG; x++) {
            *p++ = red_layer[y][x];    /* R */
            *p++ = green_layer[y][x];    /* G */
            *p++ = blue_layer[y][x];    /* B */
        }
    // La función svpng() transforma las 3 matrices RGB en una imagen PNG 
    svpng(fp, W_IMG, H_IMG, rgb, 0);
    fclose(fp);
}
  
};

#endif

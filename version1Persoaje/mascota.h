#pragma once
#include <string>
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

enum Direccion { Arriba, Abajo, Izquierda, Derecha, Ninguna };

class mascota {
private:
	int x, y, dx, dy;
	char* imagen;
	int W, H;
	int indiceH;
	int indiceW;

public:
	mascota() {
		x = y = dx = dy = 0;
		indiceH = indiceW = 0;
		imagen = new char[260];	
	}
	~mascota() {
		delete[] imagen;
	}

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getx() { return x; }
	int gety() { return y; }
	int getDx() { return dx; }
	int getDy() { return dy; }
	int getW() { return W; }
	int getH() { return H; }

	void cambia_dx_dy(Direccion tecla) {
		switch (tecla) {
		case Arriba: dx = 0; dy = -5; break;
		case Abajo: dx = 0; dy = 5; break;
		case Izquierda: dx = -5; dy = 0; break;
		case Derecha: dx = 5; dy = 0; break;
		default:
			dx = 0; dy = 0; break;
		}

	}

	void setImagen(const char* nueva) {
		strcpy(imagen, nueva);
		Bitmap^ bmp = gcnew Bitmap(gcnew String(imagen));
		W = bmp->Width / 4;
		H = bmp->Height / 4;
		delete bmp;
	}

	void mostrar(Graphics^ gr) {
		try {
			Bitmap^ bmp = gcnew Bitmap(gcnew String(imagen));
			Rectangle porcion = Rectangle(indiceW * W, indiceH * H, W, H);
			Rectangle zoom = Rectangle(x, y, W, H);//se recorta de una imagen(como un sprite)
			gr->DrawImage(bmp, zoom, porcion, GraphicsUnit::Pixel);
			delete bmp;
		}
		catch (...) {
			// Manejo silencioso o log
		}
	}

	void mover(Graphics^ gr, Direccion tecla) {
		if (tecla == Abajo) indiceH = 0;
		if (tecla == Izquierda) indiceH = 1;
		if (tecla == Derecha) indiceH = 2;
		if (tecla == Arriba) indiceH = 3;
		indiceW = (indiceW + 1) % 3; //es para hacer variar las subimagenes de una fila
		x += dx;
		y += dy;
		mostrar(gr);
	}
};

#pragma once
using namespace System;
using namespace System::Drawing;

ref class Diamante {
private:
    int x, y;
    Bitmap^ img;
    int W, H;

public:

    // ===== CONSTRUCTOR =====
    Diamante(int x, int y, String^ ruta)
    {
        img = gcnew Bitmap(ruta);

        // ----------- HACERLO MINI -----------
        W = img->Width / 20;       // ANTES /10 → AHORA muchísimo más pequeño
        H = img->Height / 20;

        if (W < 8) W = 8;
        if (H < 8) H = 8;

        this->x = x;
        this->y = y;
    }

    // ===== DIBUJAR =====
    void mostrar(Graphics^ gr) {
        gr->DrawImage(img, x, y, W, H);
    }

    // ===== RECTÁNGULO DE COLISIÓN =====
    Rectangle getRect() {
        return Rectangle(x, y, W, H);
    }
};


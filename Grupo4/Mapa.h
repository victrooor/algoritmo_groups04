#pragma once
#include "Villano.h"
#include "PersonajePrincipal.h"
#include "Recurso.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class Mapa {
private:
    int x, y, W, H;
    Bitmap^ fondo;
    String^ rutaFondo;

    Villano^ murcielago;
    Villano^ cocodrilo;
    PersonajePrincipal^ protagonista;
    Recurso^ flores;

    Random^ aleatorio;

    bool colisionMurcielago;
    bool colisionCocodrilo;
    bool colisionFlor;

    int contadorFlores;
    int contadorDaño;

public:

    Mapa(int x, int y, String^ rutaFondo, PersonajePrincipal^ protagonista)
        : x(x), y(y), rutaFondo(rutaFondo),
        contadorFlores(0), contadorDaño(0),
        colisionMurcielago(false), colisionCocodrilo(false),
        colisionFlor(false)
    {
        aleatorio = gcnew Random();
        this->protagonista = protagonista;

        fondo = gcnew Bitmap(rutaFondo);
        W = fondo->Width;
        H = fondo->Height;

        murcielago = gcnew Villano(50, 40, "imagenes/Enemigo.png", W, H, 5, 4);
        cocodrilo = gcnew Villano(60, 350, "imagenes/cocodrilo.png", W, H, 3, 4);

        flores = gcnew Recurso(
            aleatorio->Next(50, W - 100),
            aleatorio->Next(50, H - 100),
            "imagenes/flores.png", 3, 1
        );
    }

    ~Mapa() {}

    void mostrarMapa(Graphics^ gr, Keys tecla)
    {
        // -------- MOVER --------
        murcielago->moverMurcielago(W, H);
        cocodrilo->moverCocodrilo(W, H);
        protagonista->mover(tecla);

        // -------- DIBUJAR --------
        gr->DrawImage(fondo, x, y, W, H);
        murcielago->seleccionSprite(gr);
        cocodrilo->seleccionSprite(gr);
        flores->mostrarFlor(gr);
        protagonista->seleccionSprite(gr);
    }

  
    int Daño()
    {
        bool col1 = protagonista->colision(murcielago);
        bool col2 = protagonista->colision(cocodrilo);

        if (col1 && !colisionMurcielago)
            contadorDaño++;
        colisionMurcielago = col1;

        if (col2 && !colisionCocodrilo)
            contadorDaño++;
        colisionCocodrilo = col2;

        return contadorDaño;
    }

   
    int Recolectar()
    {
        bool col = protagonista->colision(flores);

        if (col && !colisionFlor)
            contadorFlores++;

        colisionFlor = col;

        return contadorFlores;
    }
};

        ////
        //bool estaColisionandoDiamante = protagonista->colision(diamantes);
        /*if (estaColisionandoDiamante && !enColisionConDiamante) {
            contadorDiamante++;
        }*/
        /*enColisionConDiamante = estaColisionandoDiamante;
        return contadorDiamantes;*/
    }

};


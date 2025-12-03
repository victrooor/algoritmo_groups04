#pragma once
#include "Mapa.h"
#include <iostream>
using namespace System;

ref class GameManager {
public:
    int tiempoRestante;
    int vidas;
    int objetivoAgua;
    int objetivoMadera;
    int objetivoRoca;

    //ajout des variables !!!!!!
    int contadorDaño;
    int contadorFlores;
    bool colisionMurcielago, colisionCocodrilo, colisionFlor;
    bool derrota;

    GameManager() {
        tiempoRestante = 300; //5 minutos
        vidas = 3;
        objetivoAgua = 50;
        objetivoMadera = 50;
        objetivoRoca = 5;

        // initialisation des variables ajoutées !!!
        contadorDaño=0;
        contadorFlores=0;
        colisionMurcielago = false; colisionCocodrilo = false; colisionFlor = false;
        derrota = false ;
    }

    ~GameManager() {}

    void iniciarJuego() {
        tiempoRestante = 300;
        vidas = 3;
        Console::WriteLine("GameManager: juego iniciado.");
    }

    void actualizarTiempo(int dt) {
        tiempoRestante -= dt;
        if (tiempoRestante < 0) tiempoRestante = 0;
    }

    bool verificarVictoria(int aguaActual, int maderaActual, int rocaActual) {
        return (aguaActual >= objetivoAgua &&
            maderaActual >= objetivoMadera &&
            rocaActual >= objetivoRoca);
    }

    // ajout : méthode Dano()

    /*int Daño() { //esto deberia adaptarse al metodo verificarDerrota de Anjali

        bool col1 = protagonista->colision(antagonista);
        bool col2 = protagonista->colision(cocodrilo);

        if (col1 && !colisionMurcielago)
            contadorDaño++;

        colisionMurcielago = col1;

        if (col2 && !colisionCocodrilo)
            contadorDaño++;

        colisionCocodrilo = col2;

        return contadorDaño;
    }*/



    //bool verificarDerrota() {
    //    
    //    bool col1 = protagonista->colision(antagonista);
    //    bool col2 = protagonista->colision(cocodrilo);

    //    if (col1 && !colisionMurcielago)
    //        contadorDaño++;

    //    colisionMurcielago = col1;

    //    if (col2 && !colisionCocodrilo)
    //        contadorDaño++;

    //    colisionCocodrilo = col2;

    //   /* return contadorDaño;*/
    //    if (contadorDaño > 5) {

    //    }

    //}

    void Dano(bool colMurcielago, bool colCocodrilo) {

        // Colisión con murciélago
        if (colMurcielago && !colisionMurcielago)
            contadorDaño++;

        colisionMurcielago = colMurcielago;

        // Colisión con cocodrilo
        if (colCocodrilo && !colisionCocodrilo)
            contadorDaño++;

        colisionCocodrilo = colCocodrilo;
    }

    void Recolectar() {
        contadorFlores++;
    }

    bool verificarDerrota() {

        if (contadorDaño >= 3) {
            derrota = true;
        }

        return derrota;
    }

    String^ getInfo() {
        return String::Format(
            "INFOS JUEGO : Objetivos -> Agua:{0} Madera:{1} Roca:{2} | Tiempo:{3} | Vidas:{4}",
            objetivoAgua, objetivoMadera, objetivoRoca, tiempoRestante, vidas
        );
    }
};

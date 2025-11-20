# Informe del Trabajo final 

## Diagrama de clases 

```mermaid

classDiagram
    class Mapas {
        -tipoMundo tipo
        -tipObjetos objetoTipo
        -String descripcion
        -List<Recurso*> recursos
        -List<Villano*> vilanos
        -String casa
        +generarMapa()
        +colocarRecursos()
        +colocarVillanos()
    }

    class Recursos {
        -int posx
        -int posy
        -String formalDelRecurso
        -bool activo
        +dibujarRecurso()
        +estadoActivo()
        +desaparecer()
    }

    class Personaje {
        -int x
        -int y
        -String sprite
        -String nombre
        +mover(direccion)
        +dibujar()
        +borrar()
        +int getx()
        +int gety()
        +getSprint()
    }

    class Villano {
        +robar()
        +moverAleatorio()
    }

    class Jugador {
        -int cantidadDiamante
        -int cantidadFlores
        -int cantidadFuenteDeLuz
        +recoger()
        +mostrarInventario()
        +objetino()
    }

    class Aliado {
        +ayuda()
    }

    class GameManager {
        -tiempoRestante
        -vista
        -int objetivoagua = 50
        -int objetivopiedra = 50
        -int objetivoRoca = 5
        +iniciativaNegro
        +actualizarTiempo()
        +verificarVictoria()
        +verificarDerrota()
    }

    Mapas "1" *-- "many" Recursos : contains
    Mapas "1" *-- "many" Personaje: 
    Personaje <|-- Jugador : 
    Jugador --> Recursos : recoger
    GameManager "3" *--  Mapas : manages
    GameManager *-- Jugador 
    Personaje <|-- Villano : inheritance
    Personaje <|-- Aliado : inheritance
    Jugador "1" o-- "1" Recursos : contains
    Menu "1" *-- "1" GameManager : contains
    Mapas "1" o-- "many" Recursos : contains
    note for Jugador "El diamante representa aprender,  las flores representan humanidad y las fuentes de luz la estabilidad IA y humano"

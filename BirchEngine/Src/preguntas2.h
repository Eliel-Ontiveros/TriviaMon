#ifndef PREGUNTAS_H
#define PREGUNTAS_H

class Preguntas {
public:
    static struct Pregunta {
        char enunciado[200];
        char opciones[4][50];
        int respuestaCorrecta;
    };

    static Pregunta preguntasGeografia[];
    static Pregunta preguntasCienciasNaturales[];
    static Pregunta preguntasMatematicas[];
    static Pregunta preguntasHistoriaMexico[];
};

#endif // PREGUNTAS_H
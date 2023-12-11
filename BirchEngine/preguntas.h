#pragma once

#include <cstdlib> // Necesario para la funci�n rand()

enum Categoria
{
    GEOGRAFIA,
    CIENCIAS_NATURALES,
    MATEMATICAS,
    HISTORIA_MEXICO
};

struct Pregunta
{
    char enunciado[200];
    char opciones[4][50];
    int respuestaCorrecta;
};

struct Pregunta preguntasGeografia[] = {
    {"�Cu�l es el r�o m�s largo del mundo?", {"Amazonas", "Nilo", "Yangts�", "Misisipi"}, 0},
    {"�En qu� continente se encuentra la Torre Eiffel?", {"Europa", "Asia", "�frica", "Am�rica"}, 0},
    {"�Cu�l es la monta�a m�s alta del mundo?", {"Kilimanjaro", "Everest", "Aconcagua", "Denali"}, 1},
    {"�Cu�l es el oc�ano m�s grande?", {"Atl�ntico", "�ndico", "Pac�fico", "�rtico"}, 2},
    {"�Cu�l es el pa�s m�s grande del mundo por territorio?", {"China", "Rusia", "Estados Unidos", "India"}, 1},
    {"�En qu� continente se encuentra Australia?", {"�frica", "Europa", "Ocean�a", "Asia"}, 2},
    {"�Cu�l es la capital de Canad�?", {"Ottawa", "Toronto", "Vancouver", "Montreal"}, 0},
    {"�Cu�l es el desierto m�s grande del mundo?", {"Sahara", "Gobi", "Atacama", "Ant�rtico"}, 0},
    {"�En qu� pa�s se encuentra la Gran Muralla China?", {"Jap�n", "China", "Corea del Sur", "Mongolia"}, 1},
    {"�Cu�l es el canal que conecta el oc�ano Atl�ntico con el oc�ano Pac�fico?", {"Canal de Suez", "Canal de Panam�", "Canal de la Mancha", "Canal de Gibraltar"}, 1},
    {"�Cu�l es la capital de Jap�n?", {"Pek�n", "Tokio", "Se�l", "Bangkok"}, 1},
    {"�En qu� pa�s se encuentra la ciudad de Machu Picchu?", {"Per�", "M�xico", "Colombia", "Brasil"}, 0},
    {"�Cu�l es el lago m�s grande de �frica?", {"Lago Victoria", "Lago Tanganica", "Lago Malawi", "Lago Chad"}, 0},
    {"�En qu� continente se encuentra el Polo Norte?", {"Europa", "Am�rica del Norte", "Asia", "Ant�rtida"}, 3},
    {"�Cu�l es la capital de Francia?", {"Berl�n", "Par�s", "Roma", "Madrid"}, 1},
    {"�En qu� pa�s se encuentra la ciudad de Buenos Aires?", {"Argentina", "Brasil", "Chile", "Colombia"}, 0},
    {"�Cu�l es el pa�s m�s poblado del mundo?", {"India", "China", "Estados Unidos", "Indonesia"}, 1},
    {"�En qu� continente se encuentra la selva amaz�nica?", {"�frica", "Asia", "Am�rica del Sur", "Ocean�a"}, 2},
    {"�Cu�l es la capital de Sud�frica?", {"Ciudad del Cabo", "Pretoria", "Johannesburgo", "Durban"}, 0},
    {"�En qu� pa�s se encuentra el Kremlin?", {"Rusia", "China", "Ucrania", "Polonia"}, 0},
    {"�Cu�l es el r�o que atraviesa la ciudad de Nueva York?", {"Hudson", "T�mesis", "Sena", "Danubio"}, 0},
    {"�En qu� oc�ano se encuentra la Gran Barrera de Coral?", {"Atl�ntico", "�ndico", "Pac�fico", "Ant�rtico"}, 2},
    {"�Cu�l es la capital de M�xico?", {"Ciudad de M�xico", "Guadalajara", "Monterrey", "Puebla"}, 0},
    {"�En qu� pa�s se encuentra la ciudad de Roma?", {"Espa�a", "Italia", "Grecia", "Portugal"}, 1},
    {"�Cu�l es el punto m�s alto de la Tierra sobre el nivel del mar?", {"Mont Everest", "Kilimanjaro", "Aconcagua", "Denali"}, 0},
    {"�En qu� continente se encuentra el Polo Sur?", {"Ant�rtida", "Am�rica del Sur", "Asia", "Ocean�a"}, 0},
    {"�Cu�l es el pa�s conocido como 'la tierra del sol naciente'?", {"China", "Jap�n", "Corea del Sur", "Tailandia"}, 1},
};

struct Pregunta preguntasCienciasNaturales[] = {
    {"�Que animal es conocido como el 'Rey de la Selva'?", {"Elefante", "Leon", "Tigre", "Oso"}, 1},
    {"�Cuantas patas tiene una ara�a?", {"4", "6", "8", "10"}, 2},
    {"�Cu�l de los siguientes es un planeta del sistema solar?", {"Luna", "J�piter", "Marte", "Saturno"}, 1},
    {"�Qu� parte de la planta absorbe agua y nutrientes del suelo?", {"Hojas", "Ra�ces", "Tallo", "Flores"}, 1},
    {"�Cu�l es la unidad b�sica de la vida?", {"�tomo", "Mol�cula", "C�lula", "Organismo"}, 2},
    {"�Qu� gas necesitan las plantas para realizar la fotos�ntesis?", {"Ox�geno", "Di�xido de carbono", "Nitr�geno", "Hidr�geno"}, 1},
    {"�Cu�l de los siguientes animales es un mam�fero?", {"Pato", "Tibur�n", "Elefante", "Rana"}, 2},
    {"�Qu� hace que el arco iris tenga diferentes colores?", {"La reflexi�n de la luz", "La refracci�n de la luz", "La absorci�n de la luz", "La difusi�n de la luz"}, 1},
    {"�Cu�l es la capa m�s externa de la Tierra?", {"N�cleo", "Manto", "Corteza", "N�cleo externo"}, 2},
    {"�Qu� animal realiza la metamorfosis completa durante su desarrollo?", {"Mariposa", "Abeja", "Caracol", "Saltamontes"}, 0},
    {"�Cu�l es el �rgano responsable de bombear sangre en nuestro cuerpo?", {"Pulm�n", "Coraz�n", "Ri��n", "H�gado"}, 1},
    {"�Cu�l es la fuerza que mantiene a los objetos en la Tierra?", {"Gravedad", "Magnetismo", "Fricci�n", "Elasticidad"}, 0},
    {"�Cu�l de los siguientes no es un tipo de roca?", {"Granito", "Mercurio", "Pizarra", "M�rmol"}, 1},
    {"�Qu� gas es esencial para la respiraci�n de los seres humanos?", {"Di�xido de carbono", "Ox�geno", "Nitr�geno", "Hidr�geno"}, 1},
    {"�Cu�l es el proceso por el cual las plantas convierten la luz en energ�a?", {"Respiraci�n", "Fotos�ntesis", "Transpiraci�n", "Germinaci�n"}, 1},
    {"�Cu�l es el nombre de la primera fase de la luna?", {"Luna llena", "Cuarto creciente", "Luna nueva", "Cuarto menguante"}, 2},
    {"�Qu� tipo de energ�a se obtiene del sol?", {"Energ�a e�lica", "Energ�a solar", "Energ�a hidroel�ctrica", "Energ�a geot�rmica"}, 1},
    {"�Cu�l es el componente m�s abundante en la atm�sfera de la Tierra?", {"Nitr�geno", "Ox�geno", "Di�xido de carbono", "Arg�n"}, 0},
    {"�Cu�l es la funci�n principal de la clorofila en las plantas?", {"Absorber agua", "Realizar la fotos�ntesis", "Transportar nutrientes", "Producir esporas"}, 1},
    {"�Cu�l de las siguientes no es una caracter�stica de los mam�feros?", {"Ponen huevos", "Tienen gl�ndulas mamarias", "Tienen pelo o pelaje", "Tienen escamas"}, 0},
    {"�Cu�l es la capa m�s interna de la Tierra?", {"N�cleo", "Manto", "Corteza", "N�cleo interno"}, 3},
    {"�Cu�l es el proceso por el cual el agua se convierte en vapor?", {"Evaporaci�n", "Condensaci�n", "Precipitaci�n", "Sublimaci�n"}, 0},
    {"�Cu�l es la funci�n principal de los pulmones en el sistema respiratorio?", {"Bombeo de sangre", "Intercambio de gases", "Digesti�n de alimentos", "Filtraci�n de desechos"}, 1},
    {"�Qu� tipo de energ�a se obtiene de la corriente de agua en movimiento?", {"Energ�a solar", "Energ�a e�lica", "Energ�a hidroel�ctrica", "Energ�a geot�rmica"}, 2},
    {"�Cu�l es el proceso por el cual los l�quidos se convierten en gas?", {"Fusi�n", "Vaporizaci�n", "Solidificaci�n", "Sublimaci�n"}, 1},
    {"�Cu�l es el animal m�s grande del planeta Tierra?", {"Elefante", "Ballena azul", "Jirafa", "Rinoceronte"}, 1},
    {"�Qu� parte del sistema solar es conocida como 'el planeta rojo'?", {"Marte", "Venus", "J�piter", "Saturno"}, 0},
};

struct Pregunta preguntasMatematicas[] = {
    {"�Cuanto es 7 + 9?", {"12", "14", "16", "18"}, 2},
    {"�Cuantos lados tiene un triangulo?", {"3", "4", "5", "6"}, 0},
    {"Si tienes 8 chocolates y comes 3, �Cuantos chocolates te quedan?", {"3", "6", "5", "4"}, 2},
    {"�Cuanto es 9 x 7?", {"63", "70", "56", "59"}, 0},
    {"Si divides 18 entre 3, �Cuanto es?", {"8", "15", "6", "11"}, 2},
    {"�Cuanto es la tercera parte de 27?", {"8", "10", "12", "9"}, 3},
    {"�Cuanto es la mitad de 16?", {"7", "5", "8", "32"}, 2},
    {"Si el cuadrado de un numero es 25, �Cual es el numero?", {"4", "5", "6", "7"}, 1},
    {"�Cuantos lados tiene un hexagono?", {"5", "7", "8", "6"}, 3},
    {"Si tienes 3 docenas de huevos, �Cuantos huevos tienes en total?", {"34", "38", "36", "30"}, 2},
    {"Si un rectangulo tiene lados de 5 cm y 8 cm, �Cuanto mide su perimetro?", {"26", "30", "24", "36"}, 0},
    {"�Cuantos dias hay en dos semanas?", {"7", "14", "15", "8"}, 1},
    {"�Cuanto es 6 x 9?", {"60", "46", "54", "56"}, 2},
    {"�Cuantas caras tiene un cubo?", {"9", "8", "6", "4"}, 2},
    {"�Como se llama el triangulo que tiene un angulo de 90 grados?", {"Triangulo rectangulo", "Triangulo escaleno", "Triangulo equilatero", "Triangulo isoceles"}, 0},
    {"�Como se llama un poligono de 8 lados?", {"Hexagono", "Heptagono", "Octagono", "Pentagono"}, 2},
    {"�Cuantas diagonales tiene un cuadrado?", {"1", "2", "3", "4"}, 1},
    {"Si un tren viaja a 60 km/h, �Cuantos km recorre en 3 horas?", {"160", "170", "145", "180"}, 3},
    {"�Cuantos kilometros hay en una milla?", {"2.347", "1.862", "1.604", "1.504"}, 2},
    {"Si un triangulo tiene un lado de 9 cm, �Cuanto mide su area?", {"82", "91", "100", "97"}, 1},
    {"�Cuantos minutos hay en una hora?", {"60", "100", "59", "70"}, 0},
    {"Si un rectangulo tiene lados de 7 cm y 10 cm, �Cuanto mide su area?", {"63", "77", "70", "73"}, 2},
    {"�Cuantas semanas hay en un a�o?", {"54", "47", "52", "55"}, 2},
    {"�Cuantos meses hay en una a�o", {"12", "13", "10", "11"}, 0},
    {"�Cual es el numero primo mas peque�o?", {"1", "3", "0", "2"}, 3},
    {"�Cuantos grados tiene un circulo completo?", {"180", "270", "360", "450"}, 2},
};

struct Pregunta preguntasHistoriaMexico[] = {
    {"�En qu� a�o comenz� la Independencia de M�xico?", {"1810", "1821", "1848", "1910"}, 0},
    {"�Qui�n fue el l�der de la lucha por la Independencia de M�xico?", {"Benito Ju�rez", "Miguel Hidalgo", "Emiliano Zapata", "Pancho Villa"}, 1},
    {"�En qu� ciudad se encuentra la pir�mide de Chich�n Itz�?", {"Oaxaca", "Canc�n", "M�rida", "M�xico, D.F."}, 2},
    {"�Qu� civilizaci�n construy� la ciudad de Teotihuac�n?", {"Aztecas", "Mayas", "Olmecas", "Toltecas"}, 0},
    {"�Cu�l fue la antigua capital de los aztecas?", {"Tenochtitl�n", "Tulum", "Chichen Itz�", "Palenque"}, 0},
    {"�Qu� evento ocurri� el 5 de mayo de 1862?", {"Independencia de M�xico", "Batalla de Puebla", "Revoluci�n Mexicana", "Tratado de Guadalupe Hidalgo"}, 1},
    {"�Qui�n fue el presidente de M�xico durante la Revoluci�n Mexicana?", {"Porfirio D�az", "Benito Ju�rez", "Francisco Madero", "Venustiano Carranza"}, 2},
    {"�En qu� a�o se promulg� la Constituci�n Mexicana?", {"1810", "1824", "1857", "1917"}, 3},
    {"�Qui�n fue conocido como 'El Libertador' en la Independencia de M�xico?", {"Jos� Mar�a Morelos", "Ignacio Allende", "Vicente Guerrero", "Miguel Hidalgo"}, 3},
    {"�Cu�l es el r�o m�s largo de M�xico?", {"R�o Bravo", "R�o Grijalva", "R�o Lerma", "R�o Balsas"}, 0},
    {"�Qu� pa�s invadi� M�xico en 1846, provocando la Guerra M�xico-Estados Unidos?", {"Espa�a", "Francia", "Estados Unidos", "Inglaterra"}, 2},
    {"�Qu� famosa pintora mexicana es conocida por sus retratos de la cultura ind�gena?", {"Frida Kahlo", "Diego Rivera", "David Alfaro Siqueiros", "Rufino Tamayo"}, 0},
    {"�Qui�n fue el �ltimo emperador azteca?", {"Moctezuma II", "Cuauht�moc", "Montezuma I", "Itzcoatl"}, 1},
    {"�En qu� a�o M�xico gan� su independencia de Espa�a?", {"1808", "1810", "1821", "1836"}, 2},
    {"�Qu� festividad mexicana conmemora a los muertos?", {"D�a de la Independencia", "D�a de Reyes", "D�a de los Muertos", "Cinco de Mayo"}, 2},
    {"�Cu�l es el plato t�pico mexicano hecho a base de ma�z?", {"Enchiladas", "Tacos", "Pozole", "Tamales"}, 2},
    {"�En qu� a�o se llev� a cabo la Revoluci�n Mexicana?", {"1810", "1857", "1910", "1920"}, 2},
    {"�Qu� ciudad fue la primera capital de M�xico despu�s de su independencia?", {"Guadalajara", "Puebla", "Veracruz", "M�xico, D.F."}, 3},
    {"�Qui�n es conocido como el 'Padre de la Patria' en M�xico?", {"Miguel Hidalgo", "Benito Ju�rez", "Emiliano Zapata", "Francisco Villa"}, 0},
    {"�En qu� a�o se llev� a cabo la conquista de M�xico por parte de los espa�oles?", {"1492", "1519", "1600", "1821"}, 1},
    {"�Qu� civilizaci�n construy� las pir�mides en la ciudad de Monte Alb�n?", {"Olmecas", "Zapotecas", "Toltecas", "Mixtecas"}, 1},
    {"�Qui�n fue el l�der militar que encabez� la resistencia contra la intervenci�n francesa en M�xico?", {"Benito Ju�rez", "Emiliano Zapata", "Ignacio Zaragoza", "Pancho Villa"}, 2},
    {"�Cu�l es el volc�n m�s alto de M�xico?", {"Popocat�petl", "Iztacc�huatl", "Nevado de Toluca", "Citlalt�petl"}, 0},
    {"�Qu� grupo ind�gena fund� la ciudad de Tenochtitl�n?", {"Aztecas", "Mayas", "Zapotecas", "Mixtecas"}, 0},
    {"�Qui�n fue el presidente de M�xico durante la Segunda Intervenci�n Francesa?", {"Porfirio D�az", "Benito Ju�rez", "Maximiliano de Habsburgo", "Ignacio Comonfort"}, 2},
    {"�En qu� a�o se proclam� la Independencia de M�xico?", {"1808", "1810", "1821", "1910"}, 1},
    {"�Cu�l es el desierto m�s grande de M�xico?", {"Desierto de Sonora", "Desierto de Chihuahua", "Desierto del Vizca�no", "Desierto de Altar"}, 0},
};

struct Pregunta obtenerPreguntaAleatoria(enum Categoria categoria, int tamano)
{
    switch (categoria)
    {
    case GEOGRAFIA:
        return preguntasGeografia[rand() % tamano];
    case CIENCIAS_NATURALES:
        return preguntasCienciasNaturales[rand() % tamano];
    case MATEMATICAS:
        return preguntasMatematicas[rand() % tamano];
    case HISTORIA_MEXICO:
        return preguntasHistoriaMexico[rand() % tamano];
    }
}



for (int i = 0; i < 4; ++i)
{
    int op_cat = rand() % 4;
    Categoria categoriaAleatoria = static_cast<Categoria>(op_cat);
    int tamano;

    switch (categoriaAleatoria)
    {
    case GEOGRAFIA:
        tamano = sizeof(preguntasGeografia) / sizeof(preguntasGeografia[0]);
        break;
    case CIENCIAS_NATURALES:
        tamano = sizeof(preguntasCienciasNaturales) / sizeof(preguntasCienciasNaturales[0]);
        break;
    case MATEMATICAS:
        tamano = sizeof(preguntasMatematicas) / sizeof(preguntasMatematicas[0]);
        break;
    case HISTORIA_MEXICO:
        tamano = sizeof(preguntasHistoriaMexico) / sizeof(preguntasHistoriaMexico[0]);
        break;
    }

    Pregunta preguntaActual = obtenerPreguntaAleatoria(categoriaAleatoria, tamano);

    // Imprime la pregunta y opciones
    std::cout << "\nCategoria: ";
    switch (categoriaAleatoria)
    {
    case GEOGRAFIA:
        std::cout << "Geografia\n";
        break;
    case CIENCIAS_NATURALES:
        std::cout << "Ciencias Naturales\n";
        break;
    case MATEMATICAS:
        std::cout << "Matematicas\n";
        break;
    case HISTORIA_MEXICO:
        std::cout << "Historia de Mexico\n";
        break;
    }

    std::cout << preguntaActual.enunciado << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        std::cout << i + 1 << ". " << preguntaActual.opciones[i] << std::endl;
    }

    // Resto del c�digo para manejar la respuesta del jugador

    // ...
}
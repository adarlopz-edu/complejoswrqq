#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Definicion de la clase para un numero complejo
class Numero {
private:
    int Real;        // Parte real del numero complejo
    int Complejo;    // Parte imaginaria del numero complejo

public:
    Numero(int, int);         // Constructor
    void suma(Numero);        // Metodo para la suma
    void resta(Numero);       // Metodo para la resta
    void multiplicacion(Numero);  // Metodo para la multiplicacion
    void division(Numero);        // Metodo para la division
};

// Constructor para la clase Numero
Numero::Numero(int real, int complejo) : Real(real), Complejo(complejo) {}

// Funcion para simplificar e imprimir el resultado complejo
void simplificarParteCompleja(int resultadoReal, int resultadoComplejo) {
    cout << endl << "El resultado es:   ";

    // Verifica si la parte real es cero
    if (resultadoReal == 0) {
        cout << resultadoComplejo << 'i' << endl;
    }
    // Verifica si la parte imaginaria es cero
    if (resultadoComplejo == 0) {
        cout << resultadoReal << endl;
    }
    // Verifica si la parte imaginaria es negativa
    else if (resultadoComplejo < 0) {
        cout << resultadoReal << resultadoComplejo << 'i' << endl;
    }
    // Verifica si la parte imaginaria es 1
    else if (resultadoComplejo == 1) {
        cout << resultadoReal << '+' << 'i' << endl;
    }
    // Verifica si la parte imaginaria es diferente de 0
    else {
        cout << resultadoReal << '+' << resultadoComplejo << 'i' << endl;
    }
}

// Metodo para realizar la suma de numeros complejos
void Numero::suma(Numero numero2) {
    int resultadoReal = Real + numero2.Real;
    int resultadoComplejo = Complejo + numero2.Complejo;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
}

// Metodo para realizar la resta de numeros complejos
void Numero::resta(Numero numero2) {
    int resultadoReal = Real - numero2.Real;
    int resultadoComplejo = Complejo - numero2.Complejo;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
}

// Metodo para realizar la multiplicacion de numeros complejos
void Numero::multiplicacion(Numero numero2) {
    int resultadoReal = Real * numero2.Real - Complejo * numero2.Complejo;
    int resultadoComplejo = Real * numero2.Complejo + Complejo * numero2.Real;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
}

// Metodo para realizar la division de numeros complejos
void Numero::division(Numero numero2) {
    int conjugadoReal = numero2.Real;
    int conjugadoComplejo = -numero2.Complejo;

    if (conjugadoReal == 0 && conjugadoComplejo == 0) {
        cout << "Error Matematico: Division por cero." << endl;
        return;
    }

    int resultadoReal = Real * conjugadoReal - Complejo * conjugadoComplejo;
    int resultadoComplejo = Real * conjugadoComplejo + Complejo * conjugadoReal;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
    cout << " / ";
    int resultadoReal2 = numero2.Real * conjugadoReal - numero2.Complejo * conjugadoComplejo;
    int resultadoComplejo2 = numero2.Real * conjugadoComplejo + numero2.Complejo * conjugadoReal;
    simplificarParteCompleja(resultadoReal2, resultadoComplejo2);
}

// Funcion para validar la expresion de entrada
bool validarInput(string expresion) {
    int posicionOperador = expresion.find_first_of("+-*/");

    if (posicionOperador == 0 || posicionOperador == expresion.length() - 1) {
        if (expresion[0] == '/') {
            cout << "Error: El operador '/' no puede estar al principio de la expresion." << endl;
            return false;
        }

        cout << "Error: La expresion no puede terminar con un operador." << endl;
        return false;
    }

    return true;
}

// Funcion para contar las ocurrencias de un caracter en una cadena
int countOccurrences(char c, string& str) {
    int count = 0;

    for (char i : str)
        if (i == c) count++;

    return count;
}

// Funcion para decodificar la expresion de entrada en partes reales e imaginarias
void Decodificador(string expresion, int numeros[], int realIndex, int complexIndex) {
    char operators[] = { '+', '-', '*', '/' };

    int totalOperators = 0;
    for (char c : operators) {
        totalOperators += countOccurrences(c, expresion);
    }

    if (totalOperators == 2) {
        int posicionOperador = expresion.find_first_of("+-");
        istringstream streamPrimerNumero(expresion.substr(0, posicionOperador - 1));
        streamPrimerNumero >> numeros[realIndex];

        int segundaPosicionOperador = expresion.find_first_of("+-", posicionOperador + 1);

        cout << endl << posicionOperador << endl;
        cout << endl << segundaPosicionOperador << endl;

        if (segundaPosicionOperador != string::npos) {
            istringstream streamSegundoNumero(expresion.substr(segundaPosicionOperador));
            streamSegundoNumero >> numeros[complexIndex];
        }
        else {
            istringstream streamSegundoNumero(expresion.substr(posicionOperador + 1));
            streamSegundoNumero >> numeros[complexIndex];
        }
    }
    else {
        int posicionOperador = expresion.find_first_of("+-");
        istringstream streamPrimerNumero(expresion.substr(0, posicionOperador));
        streamPrimerNumero >> numeros[realIndex];

        int segundaPosicionOperador = expresion.find_first_of("+-", posicionOperador + 1);

        if (segundaPosicionOperador != string::npos) {
            istringstream streamSegundoNumero(expresion.substr(segundaPosicionOperador));
            streamSegundoNumero >> numeros[complexIndex];
        }
        else {
            istringstream streamSegundoNumero(expresion.substr(posicionOperador + 1));
            streamSegundoNumero >> numeros[complexIndex];
        }

        if (posicionOperador != string::npos && expresion[posicionOperador] == '-') {
            numeros[complexIndex] = -numeros[complexIndex];
        }
    }
}

// Funcion para tomar expresiones de entrada y realizar operaciones con numeros complejos
void Input(string expresion1, string expresion2, int numeros1[2], int numeros2[2], int tipoOperacion) {
    cout << endl << "Ingrese la primera expresion (por ejemplo: 8+2i o 8-2i): ";
    cin >> expresion1;

    if (validarInput(expresion1)) {
        Decodificador(expresion1, numeros1, 0, 1);
        cout << endl << "Ingrese la segunda expresion (por ejemplo: 8+2i o 8-2i): ";
        cin >> expresion2;
        if (validarInput(expresion2)) {
            Decodificador(expresion2, numeros2, 0, 1);
            Numero numero1(numeros1[0], numeros1[1]);
            Numero numero2(numeros2[0], numeros2[1]);
            if (tipoOperacion == 1) {
                numero1.suma(numero2);
            }
            if (tipoOperacion == 2) {
                numero1.resta(numero2);
            }
            if (tipoOperacion == 3) {
                numero1.multiplicacion(numero2);
            }
            if (tipoOperacion == 4) {
                numero1.division(numero2);
            }
        }
    }
}

// Funcion principal
int main() {
    int tipoOperacion, numeros1[2], numeros2[2];
    string expresion1, expresion2;

    cout << "NUMEROS COMPLEJOS CON OBJETOS" << endl << endl;
    cout << "Seleccione una operacion" << endl;
    cout << "1. Suma" << endl << "2. Resta" << endl << "3. Multiplicacion" << endl << "4. Division" << endl;
    cin >> tipoOperacion;

    switch (tipoOperacion) {
    case 1:
        cout << endl << "Suma" << endl;
        Input(expresion1, expresion2, numeros1, numeros2, tipoOperacion);
        break;
    case 2:
        cout << endl << "Resta" << endl;
        Input(expresion1, expresion2, numeros1, numeros2, tipoOperacion);
        break;
    case 3:
        cout << endl << "Multiplicacion" << endl;
        Input(expresion1, expresion2, numeros1, numeros2, tipoOperacion);
        break;
    case 4:
        cout << endl << "Division" << endl;
        Input(expresion1, expresion2, numeros1, numeros2, tipoOperacion);
        break;
    default:
        cout << "Seleccione una operacion valida" << endl;
        break;
    }
    return 0;
}

#include<iostream>
#include <limits>
#include<string>
using namespace std;

struct datosAlumnos{
    int matricula;
    string nombre;
    float promedioG;
    string direccion;
    string telefono;
    struct datosAlumnos *sgtAlumno;
};

typedef struct datosAlumnos *Talumnos;
void imprimir(Talumnos &);
void agregarAlumno(Talumnos &);
int contarAlumnos(Talumnos );
void listaAArray(Talumnos , Talumnos* , int );
void arrayALista(Talumnos* , Talumnos& , int );
void quickSort(Talumnos* , int , int );
bool busquedaBinaria(Talumnos* , int , int );

int main(){
    int op;
    Talumnos alumnos=NULL;
    do{
        cout<<"----------MENU----------"<<endl;
        cout<<"1.Agregar alumno\n2.\n3.\n4.\n5.\n6.Mostrar(Temporal)\n7.Salir\n"<<endl;
        cout<<"\nIngresa una opcion: ";cin>>op;
        while(op<1 || op >7){
            cout<<"Error. Ingrese un valor entre 1 y 7"<<endl;
            system("pause"); system("cls");
            cout<<"----------MENU----------"<<endl;
            cout<<"1.Agregar alumno\n2.\n3.\n4.\n5.\n6.Mostrar(Temporal)\n7.Salir\n"<<endl;
            cout<<"\nIngresa una opcion: ";cin>>op;
        }
            switch(op){
                case 1:agregarAlumno(alumnos);
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                case 6:imprimir(alumnos);
                    break;
            }

        }while(op!=7);



    return 0;
}


void imprimir(Talumnos &alumnosT){
    Talumnos q;
    q=alumnosT;

    while(q!=NULL){
        cout<<q->matricula<<endl;
        q=q->sgtAlumno;
    }
}

// Funci�n para contar la cantidad de alumnos en la lista (�til para QuickSort)
int contarAlumnos(Talumnos alumnosT) {
    int count = 0;
    while (alumnosT != NULL) {
        count++;
        alumnosT = alumnosT->sgtAlumno;
    }
    return count;
}

// Funci�n para convertir la lista enlazada a un array
void listaAArray(Talumnos alumnosT, Talumnos* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = alumnosT;
        alumnosT = alumnosT->sgtAlumno;
    }
}

// Funci�n para convertir el array de vuelta a la lista enlazada
void arrayALista(Talumnos* array, Talumnos& alumnosT, int size) {
    alumnosT = array[0];
    Talumnos p = alumnosT;
    for (int i = 1; i < size; i++) {
        p->sgtAlumno = array[i];
        p = p->sgtAlumno;
    }
    p->sgtAlumno = NULL; // Terminar la lista
}

// Funci�n para la b�squeda binaria en un array de alumnos por matr�cula
bool busquedaBinaria(Talumnos* array, int size, int matricula) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (array[mid]->matricula == matricula) {
            return true; // Matr�cula ya existe
        } else if (array[mid]->matricula < matricula) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

// Funci�n para el QuickSort (ordenar por matr�cula)
void quickSort(Talumnos* array, int low, int high) {
    if (low < high) {
        int pivot = array[high]->matricula;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j]->matricula < pivot) {
                i++;
                swap(array[i], array[j]);
            }
        }
        swap(array[i + 1], array[high]);
        int pi = i + 1;

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// Funci�n para agregar un nuevo alumno con validaci�n de matr�cula duplicada
void agregarAlumno(Talumnos &alumnosT) {
    Talumnos aux = new(struct datosAlumnos);
    Talumnos p;
    int matricula;
    float promedioG;

    int cantidadAlumnos = contarAlumnos(alumnosT); // Cantidad de alumnos actuales
    Talumnos* alumnosArray = new Talumnos[cantidadAlumnos]; // Crear un array temporal
    listaAArray(alumnosT, alumnosArray, cantidadAlumnos); // Convertir la lista a array

    cout << "\n\t\t\tDATOS DEL ALUMNO\n";

    // Validaci�n de matr�cula �nica
    do {
        cout << "Ingrese el numero de matricula: ";
        cin >> matricula;

        // Verificar que la entrada sea num�rica y tenga exactamente 7 d�gitos
        if (cin.fail() || matricula < 1000000 || matricula > 9999999) {
            cout << "\nLa matricula debe ser un numero de 7 digitos y no puede contener letras." << endl;
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        } else if (busquedaBinaria(alumnosArray, cantidadAlumnos, matricula)) {
            cout << "\nLa matricula ya existe, ingrese una diferente." << endl;
        }

    } while (matricula < 1000000 || matricula > 9999999 || busquedaBinaria(alumnosArray, cantidadAlumnos, matricula));

    aux->matricula = matricula; // Asignar matr�cula
    cin.ignore();

    // Validaci�n para nombre
    do {
        cout << "Ingrese el nombre: ";
        getline(cin, aux->nombre);
        if (aux->nombre.length() == 0)
            cout << "\nEl campo no puede estar vacio" << endl;
    } while (aux->nombre.length() == 0);

    // Validaci�n para promedio general
    do {
        cout << "Ingrese el promedio general: ";
        cin >> promedioG;

        if (cin.fail() || promedioG < 0 || promedioG > 100) {
            cout << "\nEl promedio general debe ser un numero entre 0 y 100.\n";
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        }
    } while (cin.fail() || promedioG < 0 || promedioG > 100);

    aux->promedioG = promedioG;
    cin.ignore();

    // Validaci�n para direcci�n
    do {
        cout << "Ingrese la direccion: ";
        getline(cin, aux->direccion);

        if (aux->direccion.length() == 0) {
            cout << "\nEl campo no puede estar vacio" << endl;
        }
    } while (aux->direccion.length() == 0);

    // Validaci�n para n�mero de tel�fono
    do {
        cout << "Ingrese el numero de telefono: ";
        getline(cin, aux->telefono);

        if (aux->telefono.length() != 10) {
            cout << "\nEl telefono debe ser de 10 digitos" << endl;
        }
    } while (aux->telefono.length() != 10);

    // Agregar el nuevo alumno a la lista (como �ltimo elemento)
    aux->sgtAlumno = NULL;
    if (alumnosT == NULL) {
        alumnosT = aux;
    } else {
        p = alumnosT;
        while (p->sgtAlumno != NULL) {
            p = p->sgtAlumno;
        }
        p->sgtAlumno = aux;
    }

    // Ordenar la lista por matr�cula usando QuickSort
    cantidadAlumnos = contarAlumnos(alumnosT); // Recontar la cantidad de alumnos
    alumnosArray = new Talumnos[cantidadAlumnos]; // Crear nuevo array para QuickSort
    listaAArray(alumnosT, alumnosArray, cantidadAlumnos); // Convertir lista a array
    quickSort(alumnosArray, 0, cantidadAlumnos - 1); // Ordenar el array con QuickSort
    arrayALista(alumnosArray, alumnosT, cantidadAlumnos); // Convertir array de nuevo a lista
}

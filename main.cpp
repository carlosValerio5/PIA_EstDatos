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
int busquedaBinaria(Talumnos* , int , int );
void modifdatos(Talumnos &);

//Funciones de Baja y alta de estudiantes
int menuBaja();
void eliminar(Talumnos &, Talumnos&);
void eliminarPorMatricula(Talumnos&, int, Talumnos&);
void eliminarPorNombre(Talumnos&, Talumnos&, string);







int main(){
    int op;
    Talumnos alumnos=NULL;
    Talumnos PilaEliminados=NULL; 
    do{
        cout<<"----------MENU----------"<<endl;
        cout<<"1.Agregar alumno\n2.Baja de estudiantes\n3.\n4.\n5.Modificacion de Datos\n6.Mostrar(Temporal)\n7.Salir\n"<<endl;
        cout<<"\nIngresa una opcion: ";cin>>op;
        while(op<1 || op >7){
            cout<<"Error. Ingrese un valor entre 1 y 7"<<endl;
            system("pause"); system("cls");
            cout<<"\n\n\n----------MENU----------"<<endl;
            cout<<"1.Agregar alumno\n2.Baja de estudiantes\n3.\n4.\n5.Modificacion de Datos\n6.Mostrar(Temporal)\n7.Salir\n"<<endl;
            cout<<"\nIngresa una opcion: ";cin>>op;
        }
            switch(op){
                case 1:agregarAlumno(alumnos);
                    break;

                case 2:eliminar(alumnos, PilaEliminados);
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:modifdatos(alumnos);
                    break;

                case 6:imprimir(alumnos);
                    break;
            }

        }while(op!=7);



    return 0;
}

//-----------------------------------------------------------------------
int menuBaja(){
    int op;

    do
    {
        cout << "\n\n1.- Por matricula. \n2.- Por nombre.";
        cout << "\nSelecciona una opcion para dar de baja: ";
        cin >> op;
    } while (op != 1 && op != 2);
    
    return op;
}




void eliminarPorMatricula(Talumnos &listaAlumnos, int posE, Talumnos &Pila)
{
    Talumnos p, ant = NULL;
    int i =0;
    p = listaAlumnos;
    
    while(i <= posE)
    {
        if(i == posE)
        {
            if(p == listaAlumnos)
            {
                listaAlumnos = listaAlumnos->sgtAlumno;
            }else{
                ant->sgtAlumno = p->sgtAlumno;
            }
            cout << "\n\nSe elimina " << p->matricula;
            //Asignamos el nuevo elemento a la pila
            if(Pila == NULL)
            {
                Pila = p;
                Pila->sgtAlumno = NULL;
            }else{
                p->sgtAlumno = Pila;
                Pila = p;
            }
            return;
        }
        ant = p;
        p = p->sgtAlumno;
        i++;
    }
}


void eliminarPorNombre(Talumnos &listaAlumnos, Talumnos &Pila, string nombre)
{
    Talumnos p, ant = NULL;
    p=listaAlumnos;
    while(p!=NULL)
    {
        if (p->nombre == nombre)
        {
            if (p == listaAlumnos)
            {
                listaAlumnos = listaAlumnos->sgtAlumno;
            }else{
                ant->sgtAlumno = p->sgtAlumno;
            }
            //Asignamos el nuevo elemento a la pila
            cout << "\n\nSe elimina " << p->nombre;
            if(Pila == NULL)
            {
                Pila = p;
                Pila->sgtAlumno = NULL;
            }else{
                p->sgtAlumno = Pila;
                Pila = p;
            }
            return;
            
        }
        ant = p;
        p = p->sgtAlumno;
    }
}



void eliminar(Talumnos &alumnosT, Talumnos &Pila){ //Funcion para eliminar alumnos
    if(alumnosT != NULL)//Primero comprobamos si hay elemento para eliminar
    {

        if(menuBaja() == 1)//Eliminar alumno por matricula
        {
            int matricula, posE;
            int cantidad = contarAlumnos(alumnosT);//contamos la cantidad de alumnos
            Talumnos* alumnosArray = new Talumnos[cantidad]; // Crear un array temporal
            listaAArray(alumnosT, alumnosArray, cantidad); // Convertir la lista a array
            do
            {
                cout << "\n\nIngresa la matricula a eliminar: ";
                cin >> matricula;
                //Fragmento de codigo sacado de la funcion agregar funcion es para verificar la matricula
                if (cin.fail() || matricula < 1000000 || matricula > 9999999) {
                    cout << "\nLa matricula debe ser un numero de 7 digitos y no puede contener letras." << endl;
                    cin.clear(); // Limpiar el estado de error de cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                posE = busquedaBinaria(alumnosArray, cantidad, matricula); //posE sirvira para saber asta donde recorrer la lista para elimnar el alumno
            } while (matricula < 1000000 || matricula > 9999999 ||  busquedaBinaria(alumnosArray, cantidad, matricula)==-1);
            arrayALista(alumnosArray, alumnosT, cantidad);
            eliminarPorMatricula(alumnosT,posE, Pila);
        }else{
            string nombre;
            do {
                cin.ignore();
                cout << "\n\nIngrese el nombre: ";
                getline(cin, nombre);
                if (nombre.length() == 0)
                    cout << "\nEl campo no puede estar vacio" << endl;
            } while (nombre.length() == 0);
            eliminarPorNombre(alumnosT,Pila,nombre);
            cout << "\n\n" << Pila->nombre;
            
        }
    }else{
        cout << "\nNo se puede eliminar ningun elemento porque la lista esta vacia... ";
    }
}



//------------------------------------------------------------------------
void imprimir(Talumnos &alumnosT){
    Talumnos q;
    q=alumnosT;

    while(q!=NULL){
        cout<<q->matricula<<" "<<q->promedioG<<endl;
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
int busquedaBinaria(Talumnos* array, int size, int matricula) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (array[mid]->matricula == matricula) {
            return mid; // Matr�cula ya existe
        } else if (array[mid]->matricula < matricula) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
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
        } else if (busquedaBinaria(alumnosArray, cantidadAlumnos, matricula)!=-1) {
            cout << "\nLa matricula ya existe, ingrese una diferente." << endl;
        }

    } while (matricula < 1000000 || matricula > 9999999 || busquedaBinaria(alumnosArray, cantidadAlumnos, matricula)!=-1);

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
        if(cin.fail()){
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');} // Limpiar el buffer de entrada
        cout << "Ingrese el promedio general: ";
        cin >> promedioG;

        if (cin.fail() || promedioG < 0 || promedioG > 100) {
            cout << "\nEl promedio general debe ser un numero entre 0 y 100.\n";
        }
    } while (cin.fail()|| promedioG < 0 || promedioG > 100);

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

//Funcion para modificar datos de los alumnos
void modifdatos(Talumnos &p){

    int cantidad = contarAlumnos(p);//Cantidad de alumnos en la lista
    Talumnos *array = new Talumnos[cantidad];
    listaAArray(p, array, cantidad);//Convertir a array

    int op, matricula, ubicacion, opmod;
    do{
        cout<<"\n1. Busqueda por Matricula\n2. Busqueda por nombre\nIngrese una opcion:";
        cin>>op;
        if(cin.fail()||op<1||op>2){
            cout<<"\nOpcion invalida, intente de nuevo."<<endl;
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
        }
    }while(cin.fail()||op<1 || op>2);
    //Busqueda Binaria por matricula
    if(op==1){
        do{
            cout<<"\nIngrese una matricula:";
            cin>>matricula;
            if(cin.fail()||to_string(matricula).length()<7){
                cout<<"La matricula debe tener 7 digitos."<<endl;
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
            }

        }while(cin.fail()||to_string(matricula).length()<7);

        //Se busca la matricula ingresada con busqueda binaria
        ubicacion = busquedaBinaria(array, cantidad, matricula);//posicion de la matricula en array

        if(ubicacion == -1){//Caso matricula no encontrada
            cout<<"\nMatricula no encontrada. Regresando a menu.\n"<<endl;
            return;
        }
        do{
            cout << "\n1. Matricula\n2. Nombre\n3. Promedio General\n4. Direccion\n5. Telefono\nIngrese una opcion: ";
            cin>>opmod;
            if(cin.fail()||op<1||op>5){
                cout<<"Ingrese una opcion entre 1 y 5."<<endl;
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
            }
            switch (opmod)
            {
            case 1:
                do{
                    cout<<"\nIngrese la nueva matricula:";
                    cin>>matricula;
                    if(cin.fail()||to_string(matricula).length()<7){
                        cout<<"La matricula debe tener 7 digitos."<<endl;
                        cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
                    }

                }while(cin.fail()||to_string(matricula).length()<7);

                array[ubicacion]->matricula = matricula;

                quickSort(array, 0, cantidad-1);//volvemos a ordenar a los alumnos por matricula    
                break;
            
            default:
                break;
            }

        }while(cin.fail()||op<1||op>5);

    }
    arrayALista(array, p, cantidad);
}
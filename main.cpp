#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

// DEFINICIONES DECLARADAS
#define NUMBERCONJ 4 // Numero del conjunto en caso de Correspondencia Asociativa
#define BYTE 8 // Numero de bytes
#define SYSTEMBITS 32 // Este define el numero de bits del sistema, en este caso 32bits
#define s '\n' // Definimos el salto linea con la letra s

using namespace std;

// Creamos la estructura de la cache
// Usamos un struct para simplificar su representacion
typedef struct cache{
  bool valido;
}cache; // Esta estructura contendra una variable
        // logica que sera el Bit de validez de la cache

// PROTOTIPOS DE FUNCIONES Y PROCEDIMIENTOS
int division(int a, int b);
int modulo(int a, int b);
void esPotencia2(bool &k, int c, int &exp);
void obtdireccion(int d, int direccion[]);
void obtEtiqueta(int d[], int e[], int tame);


// PROGRAMA PRINCIpalabra
int main(){ 
  // Var
  int configuracion1, configuracion2, configuracion3, configuracion4, direccion, exp1, exp2, exp3;
  int tamL, tamP, tamE, tamC, i, j, nb, nl, conjL, val, max=0, nc;
  bool aux, aux2, aux3, flag, flag2;
  float na, nf, total, tasaAciertos, tasaFallos;
  ifstream archivo;

  archivo.open("configuracion.txt", ios::in); // Abrimos el archivo de configuración


  if(archivo.fail()){
    cout << "No se pudo abrir el archivo [configuracion.txt]" << s;
    exit(1);
  }

  // Pasamos los parametros para simular la cache
  archivo >> configuracion1;
  archivo >> configuracion2;
  archivo >> configuracion3;
  archivo >> configuracion4;
  archivo.close(); // Cerramos el archivo [configuracion.txt]

  esPotencia2(aux, configuracion1, exp1); // Se averigua las potencias de configuracion1, configuracion3, NUMBERCONJ
  esPotencia2(aux2, configuracion3, exp2);
  esPotencia2(aux3, NUMBERCONJ, exp3);
  aux = aux && aux2 && aux3; 

  if(!aux || configuracion1 < configuracion3){
    cout << "ERROR" <<  endl;
    exit(1);
  }

  tamL = configuracion1/configuracion3;

  tamP = (configuracion3*BYTE)/SYSTEMBITS;

  if(tamP <= 1){ // Si tamP es meno o igual que 1 entonces por default se trabaja con una palabra
    exp2 = 0;
    tamP = 1;
  }else{
    esPotencia2(aux, tamP, exp2); // Caso contrario se busca que potencia de dos corresponde la cantidad de palabras
  }

  // Formacion de la cache

  cache resultado[tamL];
  int palabra[tamL][tamP]; // Este es la estructura donde se guardan las palabras o palabraabra segun lo descrito en la configuracioniguracion
  esPotencia2(aux, tamL, exp1);
  tamE = SYSTEMBITS-(exp1+exp2); // Se declara un tamaño para los bits que contendra el campo etiqueta dependiendo de la correspondencia
  tamC = SYSTEMBITS-(exp2+exp3);

  // Etiquetas
  int etiqueta[tamL][tamE];
  int etiquetaAJ[tamL][tamC];

  conjL = tamL/NUMBERCONJ; // Esta variable es para saber cuantas entradas hay por conjunto
  if(conjL == 0 && configuracion2 == 1){
    cout << "ERROR de CONJUNTO" << s;
    exit(1);
  }

  // Cache formada
  int cont[tamL]; // Este arreglo es para el caso de operar el LRU

  // Inicializamos la cache
  for(i = 0; i < tamL; i++){
    resultado[i].valido = false;
    cont[i] =- 1;
    for(j=0; j < tamE; j++){
      etiqueta[i][j] =- 1;
    }
    for(j=0; j < tamC; j++){
      etiquetaAJ[i][j] =- 1;
    }

    for(j=0; j < tamP; j++){
      palabra[i][j] =- 1;
    }

  }

  
  int arregloDireccion[SYSTEMBITS];// Este va a ser el arreglo donde se guardara la arregloDireccion de bloque
  // que se transformara en un numero binario de SYSTEMBITS

  srand(time(NULL)); // Buscamos generar numeros aleatorios con srand() siempre y cuando se pida en
  // la configuracion

  tasaAciertos=0;
  tasaFallos=0;
  total=0;

  while(cin >> direccion){ // Verificamos que la entrada estandar de "entrada.txt" no ha llegado al final
    // Se ingresa la direccionección de bloque
    cout << direccion << " "; // La escribe en "salida.txt" 
    obtdireccion(direccion, arregloDireccion); // Se pasa a binario de SYSTEMBITS dicha direccionección
    nb = division(direccion, tamP); // Se busca a que bloque de la supuesta memoria principalabra pertenece la direccionección
    
    
    flag = true;

    if(configuracion2 == 0){ // Verificamos si es para correspondencia direccionecta
      int et2[tamE]; // Arreglo que será la etiqueta de la direccionección
      nl = modulo(nb, tamL);

      obtEtiqueta(arregloDireccion, et2, tamE);
      for(i = 0; i < tamE && flag; i++){
        if(etiqueta[nl][i] != et2[i]){
          flag = false;
        }
      }
      // ultimo cambio
      if(!flag || !resultado[nl].valido){ // Verificamos si las etiquetas son iguales o que el bit valido sea falso, así colocamos fallo
        cout << " Fallo" << s;
        tasaFallos++; // Tasa de fallos

        if(tamP == 1){ // Guardamos las arregloDireccions de datos en la matriz de palabras para aprovechar localidad espacial
          palabra[nl][0] = direccion; // Para una cache de una palabraabra solo se guarda la direccionección
        }else{
          for(i = 0; i < tamP; i++){ // Caso contrario, guardamos la direccionección ingreseda y ademas todas las adyacentes que pertenezcan al mismo
            palabra[nl][i] = i+(tamP*nb); // Bloque con el mismo tamaño de el numero de palabras por lineas
          }
        }

        for(i = 0; i < tamE; i++){ // Reemplazamos el valor de la etiqueta en la línea determinada
          etiqueta[nl][i] = et2[i];
        }

        resultado[nl].valido = true; // Se cambia a verdadero el bit de validez
      }else{
        cout << "Acierto" << s; // Verificamos si es un acierto, aumentamos la tasa de aciertos
        tasaAciertos++;
      }
        
  }else if(configuracion2 == 1){ // Verificamos si es una cache asociativa por conjunto

   
      flag2 = false;
      nc = modulo(nb, NUMBERCONJ); // Verificamos a que conjunto pertenece esa direccionección
      int etaj[tamC]; // Arreglo que sera la etiqueta de la direccionección
      obtEtiqueta(arregloDireccion, etaj, tamC);
      nl = nc*conjL; // Verficamos el margen para saber hasta que línea llegara el conjunto
      val = rand()%conjL; // Elejimos un numero al azar que sea menor al tamaño de entradas por conjunto

    if(configuracion4 == 1){ // Verificamos si la "politica de reemplazo es aleatoria"
       
        
        for(i = 0+nl; i < conjL+nl && !flag2; i++){

          for(j=0; j < tamC && flag; j++){
            if(etiquetaAJ[i][j] != etaj[j]){ // Verificamos si en el marco de entrada existe o no una etiqueta igual 
              flag = false;                  // a la etiqueta de la direccionección que ingresamos 
            }
          }

          if(flag){
            flag2 = true;
          }else{
            flag = true;
          }
        }
      



        if(!flag2){
          cout << "Fallo" << s;
          tasaFallos++;

          for(i = 0; i < tamC; i++){                  // Asignamos en la cache la etiqueta de la direccionección
            etiquetaAJ[val + (nc*conjL)][i] = etaj[i];// es una posición al azar dentro de su conjunto 
          }
          for(i = 0; i < tamP; i++){                 // LLenamos la matriz de las palabras en esa misma línea con las arregloDirecciones
            palabra[val+(nc*conjL)][i] = i + (nb*tamP);   // del bloque correspondiente a la direccionección
          }

        }else{
          cout << "Acierto" << s;
          tasaAciertos++;
        }

    }else if(configuracion4 == 0){ // Verificamos si la "politica" de reemplazo es LRU
        
    
        for(i = 0+nl; i < conjL+nl; i++){
          for(j = 0; j < tamC && flag; j++){
            if(etiquetaAJ[i][j] != etaj[j]){
              flag = false;
            }
          }
            if(!flag){
              flag = true;
            }else{
              flag2 = true;
              val = i;
            }
        }
      if(!flag2){ // Verificamos si se encuentra o no la etiqueta correspondiente

        cout << "Fallo" << s;
        tasaFallos++;
        int mayor;
        mayor=- 1;

          for(i = 0+nl; i < conjL+nl; i++){ // Verificamos con el arreglo de contadores que línea tiene más tiempo sin usarse
            if(cont[i] > mayor){
              mayor = cont[i];
              max = i;
              
            }
          }
        

         for(i = 0; i < tamC; i++){
            etiquetaAJ[max][i] = etaj[i]; // Ocupa la etiqueta de la direccionección en la línea de mayor tiempo sin usar
          }
        

          for(i = 0; i<tamP; i++){
            palabra[max][i] = i+(nb*tamP); // Guardamos las palabras
          }
         
          for(i = 0; i<tamL; i++){
            if(i != max){
              cont[i] = cont[i]+1;   // En todo el arreglo de contadores incrementamos un menos en la posición
                                    // donde se hizo el reemplazo
            }
          }
        
      }else{
        cout << "Acierto" << s;
        tasaAciertos++;
        cont[val] = 0;  // En caso de un acierto, devolvemos a cero la línea donde existió la igualdad de etiquetas

        for(i = 0; i < tamL; i++){ 
          if(i != val){
            cont[i] = cont[i]+1; // Incrementamos uno la posición donde se registro el acierto en el arreglo de contadores
          }
        }
      }
    }
  }

    for(i = 0; i < tamL; i++){ // Este ciclo nos sirve para imprimir en pantalla la memoria cache
      cout << i << " ";

      if(configuracion2 == 0){
        for(j = 0; j < tamE; j++){
          cout << etiqueta[i][j];
        }
      }else if(configuracion2 == 1){
        for(j = 0; j < tamC; j++){
          cout << etiquetaAJ[i][j];
        }
      }

      for(j = 0; j < tamP; j++){
        cout << " " << palabra[i][j];
      }

      cout << s;
    }

    cout << s;
    total++;

  }


  na = tasaAciertos/total;
  nf = tasaFallos/total;

  cout<<"ACIERTOS: "<<tasaAciertos<<s;
  cout<<"FALLOS: "<<tasaFallos<<s;
  cout << "TASA ACIERTOS: " << na << s;
  cout << "TASA FALLOS: " << nf << s;

  return 0;
}


//  IMPLEMENTACIÓN DE LOS PROCEDIMIENTOS Y FUNCIONES

// funcion que devuelve la division de dos numeros, pero devuelve solo un entero
// no devuelve decimales
int division(int a, int b){
  // Var

  // Inicio
  return (a/b);
}

// Función que devuelve el modulo 
int modulo(int a, int b){
  // Var

  // Inicio
  return a%b;
}

// Procedimiento que verifica si el entero c es potencia de 2 
// y obtiene su exponente(Algoritmo de logaritmo base 2, k indica si es pontencia o no)
void esPotencia2(bool &k, int c, int &exp){
  // Var
  int res;

  // Inicio
  k = true;
  exp = 0;

  while(c != 1 && k){
    res = c%2;

    if(res != 0){
      k = false;
    }

    c = c/2;
    exp++;
  }
}

// Procedimiento para obtener la direccionección 
void obtdireccion(int d, int direccion[]){
  
  // Var
  int res, tam;
  
  // Inicio
  tam = SYSTEMBITS-1;
   
  while(d != 0){
    res = d%2;
    direccion[tam] = res;
    d = d/2;
    tam--;
  }

  while(tam >= 0){
    direccion[tam] = 0;
    tam--;
  }

}

// Procedimiento para obtener la etiqueta
void obtEtiqueta(int d[], int e[], int tame){
  // Var
  int i;

  // Inicio
  for(i = 0; i < tame; i++){
    e[i] = d[i];
  }
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int read_split (int fin, char* buff, int maxlen, char* ch_end ){
 int i = 0, oneread = 1;
  char c = '.';
  while (c != ' ' && c != '\n' && oneread == 1 && i< maxlen){
    oneread = read(fin, &c, 1);
    if(c != ' ' && c != '\n' && oneread == 1){
      buff[i] = c;
      i++;
    }
  }
  *ch_end = c;
  if(i < maxlen) buff[i] = '\0';
  
  return i;
}


int main(int argc, char *argv[]) {
  

  /*1. Write a call to the sys-call ”read” and the variables you need to read one byte from the keyboard and store it in a variable of type char.

  char* resultat;
  int retorn= read(0,resultat,1);
  */

  /*2. Discuss how you can declare 100 integers and how you can know the size in bytes of the declared data.
  int numeros[100];
  int sizeByteArray=(100*sizeof(int));
  */

  /*3. Using the sys-call ”read” 100 integers from a binary file ”nums.dat” and store them in memory*/
  //int* int_pointer = malloc(100*sizeof(int));


  /*int int_array[100];
  for(int i = 0;i<100;i++ ){
    int_array[i]=i;
  }
  int f = open("nums.dat",  O_CREAT | O_RDWR, 0640);
	write(f, int_array, sizeof(int_array));
	close(f);*/

/*
  int f = open("nums.dat",O_RDWR, 0644);
  read(f, int_pointer, 100*sizeof(int));

  //4. In the previous program check if everything went correctly and all the information could be read.

  for(int i=0;i<100;i++) {
    printf("%d ", int_pointer[i]);
    }
	printf("\n");
  close(f);
  */

/*5. Do a sys-call ”read” that reads a string from the command line and checks if the length of the string
is greater than 0.*/

/*
char buff[100];
read(0,buff, 100);
if(strlen(buff)>0){
  printf("si, llargada %d", strlen(buff));
}*/

/*6. Write of a call to ”write” that writes a character ’a’ to the screen.*/
//write(1,"a",1);

/*7. Reads bytes one by one from the standard input and write them into the standard output*/


/*8. Imagine the previous program has been compiled into an executable named ”mycp”: how can you call
it from the command line to copy two files ”in.txt” to ”out.txt”?
*/
//mycp in.txt>out.txt

/*9. Read an integer from keyboard using scanf function and print the result of multiplying it by 2.*/
/*int var;
scanf("%d",&var);
printf("%d", var*2);*/


/*10. Read an integer of maximum 8 digits from keyboard (using sys-call read) and print the result of
multiplying it by 2. Its not possible to read binary data from keyboard (standard input), so first put it in a char buffer and then use sscanf for conversion.
*/

/*char* numero[8];
read(0,numero,8);
int resultat;
sscanf(numero, "%d",&resultat);
printf("%d",resultat);*/

/*11. Read a binary file named nums.dat containing 10 integers and print each integer multiplying it by 2.
*/
/*int f = open("nums.dat",O_RDWR, 0644);
int* int_pointer = malloc(10*sizeof(int));
read(f, int_pointer, 10*sizeof(int));
close(f);

for(int i=0;i<10;i++) {
    printf("%d ", int_pointer[i]*2);
}
	printf("\n");
  */

  /*12. Write a command shell program that counts the number of characters ’a’ in the standard input and
writes the result in the standard output.
*/
/*
int n = 4;
  int counter = 0;
  char ch[n];

  read(0,ch,n);

  for(int i = 0; i < n; i++){
    if('a'==ch[i]){
      counter ++;
    }
  }
  printf("Hi havien %d a's .\n", counter);*/

/*13. Discuss and explain what the following code does. Pay attention to the parameters: a file descriptor (or standard input 0), a pointer to an array of characters, the max length to be read, a pointer to the character that was encountered last (acts as an output parameter).*/


/*14. Read a text file (call it nums.txt) using read split (defined in ex.13) which has 10 integers written in it, separated by spaces and print each integer multiplying it by 2.*/
/*
 int f = open("nums.txt",O_RDWR, 0640);
 char* buff= malloc(50);
 int maxlen = 50;
 char ch_end ;
int a = 0;
int j=0;
for(int i=0; i<maxlen; i++){
  
  a=read_split(f, buff+j, maxlen, &ch_end); 
  buff[j+a]=' ';
  j=j+a+1;

}


  for(int i=0;i<maxlen;i++) {
    printf("%c", buff[i]);
}
	printf("\n");; 
 free(buff);

*/

//DELIVERY

//1
//DELIVERY - EXERCICI 1


  
// abrimos archivo que nos pasan por comanda, guardado en argv[1].
int f = open(argv[1],O_RDWR, 0640);

// Inicializamos variables :

 char* buff= malloc(300); // puntero char donde guardaremos texto.
 int maxlen = 300; // entero con máxima capacidad del puntero anterior.
 char ch_end; // char que recibe el ultimo valor leido por la funcion read_split
 
// inicializamos el advance (letras de palabra leida), cursor (indice de buffer) y contador de words y lines.
 int advance = 0, cursor =0, words =0, lines = 0;
 
for( int i=0; i<maxlen; i++){
  advance = read_split(f, buff+cursor, maxlen, &ch_end);
  
  // si recibimos 1 o mas letras --> contamos una palabra
  if(advance>0){
    words++;
  } else { // por el contrario, hemos acabado de leer
    lines++; // añadimos ultima linea
    buff[cursor+advance]='\n'; // finalizamos el buffer con un salto de linea

    //Forzamos salida del bucle
    i=maxlen;
  }

  //Detectamos que el read_split esta a final de linea
  if(ch_end == '\n'){
    lines++;
  }
  
  //Añadimos espacios entre las palabras del buff
  buff[cursor+advance]=' ';
  //Avanzamos el puntero tantas posiciones como caracteres leidos
  cursor = cursor + advance + 1;
}
// inicializamos el resumen de contadores de palabras y lineas
char review[30] = "";
//Guardamos en un solo array lo que queremos mostrar
sprintf(review,"\nWords: %d Lines: %d \n",words,lines);

//Mostramos el conjunto de palabras(en una sola linea) y la cantidad de palabras y lineas a traves del estandard output(1).
write(1,buff,cursor);
write(1,review, sizeof(review));


//2
/*
int f = open("words.txt",O_RDWR, 0640);
 char* buff= malloc(50);
 int maxlen = 50;
 char ch_end ;
 int a = 0;
 int j=0;
for(int i=0; i<maxlen; i++){
  a = read_split(f, buff+j, maxlen, &ch_end);
if( buff[j]  >='1' && buff[j]  <='9') {
   memcpy(buff, buff, j-1);
} else {
  buff[j+a]=' ';
  j=j+a+1;
}
  
  

}

for(int i=0;i<maxlen;i++) {
  if(!(buff[i]==' ' && buff[i+1]==' ')){
    printf("%c", buff[i]);
  }
    
}
printf("\n");
*/
  return 0;
}

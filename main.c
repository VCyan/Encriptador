/**
 * Copyright (c) 2018
 *
 * @file    Encriptador.c
 *
 * @authors
 * 
 *     Alberto
 *	   Brandon
 *     Victor
 *
 * @date    26.05.2018 14:58:05
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int SIZE = 6;

// Prototypes
void getMatrix(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[20]);
void displayMessage(int arr[SIZE][SIZE], char message[20]);
void displayMatrix(int arr[SIZE][SIZE]);
void encryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);
void encryptR(int matrix[SIZE][SIZE]);

void dencryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);

unsigned int reverseBits(unsigned int x);
//~ void initResultingMatrix(int **);
//~ void * matrixMultiplication(void *);


int main() {
    char message[20];
    char clave[10] = {'B','R','3','A','L','5','V','I','7','X'};
    int matrix[SIZE][SIZE]; // Multiplo de dos
    int copy[SIZE][SIZE];
    //~ int **ptrmatrix;

	// Set memory variables to 0...
	memset( message, 0, sizeof(message) );
	// Set memory matrices to 32 = [space] / ASCII Value.
	memset( matrix, 32, SIZE*SIZE*sizeof(int) );
	memset( copy, 32, SIZE*SIZE*sizeof(int) );
	
	printf("Ingresar mensaje a cifrar: ");
	//~ scanf("%s", message);
	fgets(message,21,stdin); // 21 = 20 + '\0'
	
	printf("Input: %s\n",message); // Note that message has a '\n'
	printf("Input length: %d\n\n",(int)strlen(message));
	
    getMatrix(matrix, copy, message);
	
	displayMessage(matrix, message);
	displayMatrix(matrix);
    
	// Encrypt Message - Rondas
	// Plus = Se podria agregar un switch que segun i = 0, 1, 2, ... se altere el orden de las funciones...
	for(unsigned int i = 0; i < SIZE; i++){
		// Encryption A
		// Encryption B
		// Encryption C
		// ...
	}
    encryptA(matrix, copy);
    
    encryptR(matrix);
    // Display encrypted Message
    displayMessage(matrix, message);
    displayMatrix(matrix);
        
    // Decrypt Message
    
	for(unsigned int i = 0; i < SIZE; i++){
		// Decryption C
		// Decryption B
		// Decryption A
		// ...
	}
	
	encryptR(matrix);
	dencryptA(matrix, copy);
	
	
    displayMessage(matrix, message);
    displayMatrix(matrix);

    return 0;
}

/* Fill up the matrix from message[20] to matrix[SIZE][SIZE], from ASCII to INT */
void getMatrix(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[20]){
    // Assign ASCII message to a Matrix
    // NOTE: 32 is the ASCII code for [space]
	int k = 0;
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
			if((int) message[k] < 32 || k > 20){
				matrix[i][j] = 32;
				copy[i][j] = 32;
			}
			else{
				matrix[i][j] = (int) message[k];
				copy[i][j] = (int) message[k];
			}
			k++;
		}
	}
}

/*    Show the message in console */
void displayMessage(int matrix[SIZE][SIZE], char message[20])
{
	int k = 0;
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
			message[k] = matrix[i][j];
			if(k > 20){
				i = j = SIZE;
				break;
			}
			k++;
		}
	}
	printf("Message: %s\n\n",message);
}

/*    Show the matrix in console */
void displayMatrix(int matrix[SIZE][SIZE]){
    //~ printf("\nMatrix:\n",name);
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            printf("%4c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeMatrix()
{
}

/* encryptA
 * 
 * La funcion encryptA realiza una trasposicion de matriz usando una matriz copia como auxiliar.
 * Mientras que la funcion decryptA devuelve la matriz original.
 * Cabe mencionar que esta operacion se reduce a una sola funcion... por lo que no es necesario decryptA. A arreglar luego.
 */

void encryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE])
{
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            matrix[i][j] = copy[j][i];
        }
    }
}

void dencryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE])
{
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            matrix[i][j] = copy[i][j];
        }
    }
}

/* encryptR
 * 
 * La funcion encryptR revierte los bits de de cada valor de la matriz, esto es:
 * Si se tiene el valor 10, en binario ( 1010 ) revertirá el orden de sus bits por ( 0101 ) = 5
 */
void encryptR(int matrix[SIZE][SIZE]){
	for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            matrix[i][j] = reverseBits((unsigned int)matrix[i][j]);
        }
    }
}

/* reverseBits()
 * 1010 => 0101
 * La funcion reverseBits es la función complementaria de encryptR, la cual realiza la operacion de revertir los bits.
 * Se recibe el valor a revertir (unsigned int x).
 * Se devuelve el nuevo numero revertido (unsigned int reverseX)
 */
unsigned int reverseBits(unsigned int x)
{
	// Como el valor recibido proviene de un char CHAR (1 byte / 8 bits) y un valor entero INT requiere ( 4 bytes / 32 bits )
	// 1. Necesitamos revertir los 32 bits, esto lo logramos recorriendo los 32 bits con un contador llamado SIZEINT de valor 32
    unsigned int SIZEINT = sizeof(x) * 8;
    // 1.1. Iniciamos nuestro nuevo numero revertido en 0 (0..0)
    unsigned int reverseX = 0; 
    unsigned int i;
    // 2. Iteramos sobre el valor x hasta SIZEINT (32) posiciones 
    for (i = 0; i < SIZEINT; i++)
    {
	// 3. Comparamos el valor x en la posicion i con el bit 0..1..0 en la posicion i con el operador bit AND (&)
	// If x AND 0..1..0 != 0, then...
	if((x & (1 << i))){
		// 4. Si el bit en la posicion i es 1, entonces en el nuevo numero en la posicion [(32 - 1) - i] establecemos el bit como 1
		// Note that bit # 32 is really bit # 31 as position bits start at 0
		// reverseX = reverseX OR bit # (( 0..1..0 ) - position i)
		reverseX |= 1 << ((SIZEINT - 1) - i);
	}
   }
   // 4. Transverse # of bits 24 positions.
   reverseX >>= 24; // Should be reverseX >>= (sizeof(x) * 8 - 8); // in case of 64 bits.
   return reverseX;
}


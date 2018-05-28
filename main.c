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
    //~ char clave[10] = {'B','R','3','A','L','5','V','I','7','X'};
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
 * Si se tiene el valor 10, en binario ( 1010 ) revertirá el orden de sus bits por ( 0101 )
 */

void encryptR(int matrix[SIZE][SIZE]){
	for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            matrix[i][j] = reverseBits((unsigned int)matrix[i][j]);
        }
    }
}
 
unsigned int reverseBits(unsigned int x)
{
	// https://stackoverflow.com/questions/6916974/change-a-bit-of-an-integer
	// As the integer value comes from a char (1 byte / 8 bits) and an integer value requires ( 4 bytes / 32 bits )
	// We multiply the value 
	// 1111 0000 => 0000 1111 or 1010 => 0101
    unsigned int NO_OF_BITS = sizeof(x) * 8;
    unsigned int reverse_num = 0;
    unsigned int i;
    for (i = 0; i < NO_OF_BITS; i++)
    {
		//~ printf("%u",(x & (1 << i))); 
		// If x AND 0..1..0 != 0, then...
		if((x & (1 << i))){
		//~ printf(" Si entro %u\n",(x & (1 << i)));
			// number = number OR bit # (( 0..1..0 ) - position i)
			// Note that bit # 32 is really bit # 31 as position bits start at 0...
			reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
		}
   }
   // Transverse # of bits 24 positions.
   reverse_num >>= 24;
   return reverse_num;
}


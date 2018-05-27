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

const int SIZE = 6;

// Prototypes
void getMatrix(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[20]);
void displayMessage(int arr[SIZE][SIZE], char message[20]);
void displayMatrix(int arr[SIZE][SIZE]);
void encryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);
void dencryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);

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
	printf("Input length: %ld\n\n",strlen(message));
	
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
    
    // Display encrypted Message
    displayMessage(matrix, message);
    displayMatrix(matrix);
        
    // Decrypt Message
    
	for(unsigned int i = 0; i < SIZE; i++){
		// Decryption A
		// Decryption B
		// Decryption C
		// ...
	}
	
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
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
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
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            matrix[i][j] = copy[j][i];
        }
    }
}

void dencryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            matrix[i][j] = copy[i][j];
        }
    }
}



    //~ for (int i = 0; i < SIZE; i++) {
        //~ for (int j = 0; j < SIZE; j++){
            //~ matrix[i][j] = matrix[i][j] >> 2;
        //~ }
    //~ }
    

    
    //~ for (int i = 0; i < SIZE; i++) {
        //~ for (int j = 0; j < SIZE; j++){
            //~ matrix[i][j] = matrix[i][j] << 2;
        //~ }
    //~ }

    //~ for (int i = index; i < (index + 1); i++) {
        //~ for (int j = 0; j < SIZE; j++) {
        //~ }
    //~ }

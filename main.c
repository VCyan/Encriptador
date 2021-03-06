/**
 * Copyright (c) 2018
 *
 * @file    Encriptador.c
 *
 * @authors
 * 
 * 	A00759273  Alberto
 *	A01611066  Brandon
 *	A01362306  Victor Eduardo Martin del Campo
 *
 * @date    26.05.2018 14:58:05
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const unsigned int SIZE = 5;

// Prototypes
void getMatrix(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[20]);
void getMatrix2(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[20]);
char* displayMessage(int arr[SIZE][SIZE], char message[20]);
char* dM(int arr[SIZE][SIZE], char* message);
void displayMatrix(int arr[SIZE][SIZE], char code[4]);

void createCopy(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);
	
void encryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);
void encryptR(int matrix[SIZE][SIZE]);
unsigned int reverseBits(unsigned int x);
void encryptXOR(int matrix[SIZE][SIZE], char clave[10]);
void encryptSUM(int matrix[SIZE][SIZE], char clave[10]);
void encryptMINUS(int matrix[SIZE][SIZE], char clave[10]);

void dencryptA(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]);

// Vigenere
char* getVigenereKey(char* key, int messageLength, int keyLength);
char* vigenereEncrypt(char* message, char* key);
char* vigenereDecrypt(char* message, char* key);

char* encrypt(char* message) {
    char clave[10] = {'B','R','A','L','S','V','I','J','X'};
    int matrix[SIZE][SIZE]; // Multiplo de dos
    int copy[SIZE][SIZE];

	// Set memory matrices to 32 = [space] / ASCII Value.
	memset( matrix, 0, SIZE*SIZE*sizeof(int) );
	memset( copy, 0, SIZE*SIZE*sizeof(int) );	

	strcpy(message,vigenereEncrypt(message, clave));

	getMatrix(matrix, copy, message);
	displayMatrix(matrix, "GETM");
 
	encryptA(matrix, copy);
	displayMatrix(matrix, "TRAS");
	
	encryptR(matrix);
	displayMatrix(matrix,"REVE");
	
	encryptXOR(matrix, clave);
	displayMatrix(matrix,"XOR");

	//encryptSUM(matrix, clave);
	//displayMatrix(matrix);

	displayMessage(matrix, message);

    return message;
}

char* decrypt(char* message){

    char clave[10] = {'B','R','A','L','S','V','I','J','X'};
    int matrix[SIZE][SIZE]; // Multiplo de dos
    int copy[SIZE][SIZE];
	
	// Set memory matrices to 32 = [space] / ASCII Value.
	memset( matrix, 0, SIZE*SIZE*sizeof(int) );
	memset( copy, 0, SIZE*SIZE*sizeof(int) );

    //encryptMINUS(matrix, clave);
	//displayMatrix(matrix);
	
	getMatrix2(matrix, copy, message);
	//displayMatrix(matrix);
	
	dM(matrix, message);
	displayMatrix(matrix, "MESS");
	
	encryptXOR(matrix, clave);
	displayMatrix(matrix,"XOR");
	
	encryptR(matrix);
	displayMatrix(matrix,"REVE");
	
	//getMatrix2(matrix, copy, message);
	//getMatrix(matrix, copy, "TRAS0");
	memset( copy, 0, SIZE*SIZE*sizeof(int) );
	createCopy(matrix, copy);
	encryptA(matrix, copy);
	displayMatrix(matrix,"TRAS");
	
	//displayMessage(matrix, message);
	strcpy(message,vigenereDecrypt(message, clave));
    //printf("Decrypted = %s\n",message);
    
    return message;
}


int main() {
    char message[20];
    char messageEncryted[36];
    // Set memory variables to 0...
	memset( message, 0, sizeof(message) );

    printf("INPUT TEXT: ");

    fgets(message,36,stdin); // 21 = 20 + '\0'
		size_t ln = strlen(message) - 1;
		if (*message && message[ln] == '\n'){message[ln] = '\0';}
    
	//printf("Input: %s\n",message);
	//printf("Input length: %d\n\n",(int)strlen(message));

    printf("%s\n", encrypt(message));
    
	printf("OUTPUT TEXT: ");
	fgets(messageEncryted,36,stdin); // 21 = 20 + '\0'
		ln = strlen(messageEncryted) - 1;
		if (*messageEncryted && messageEncryted[ln] == '\n'){messageEncryted[ln] = '\0';}
		
	//printf("%s\n", decrypt(messageEncryted));
    printf("%s\n", decrypt(messageEncryted));
    
    return 0;
}

/* Fill up the matrix from message[20] to matrix[SIZE][SIZE], from ASCII to INT */
void getMatrix(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[20]){
    // Assign ASCII message to a Matrix
    // NOTE: 32 is the ASCII code for [space]
	int k = 0;
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
			if((int) message[k] < 1 || k >= 20)
			{
				//printf("Roto k = %d",k);
				break;
				//copy[i][j] = 32;
			}
			else
			{
				matrix[i][j] = (int) message[k];
				copy[i][j] = (int) message[k];
			}
			k++;
		}
	}
}
void getMatrix2(int matrix[SIZE][SIZE], int copy[SIZE][SIZE], char message[36]){
    // Assign ASCII message to a Matrix
    // NOTE: 32 is the ASCII code for [space]
	int k = 0;
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
		{
			matrix[i][j] = (int) message[k];
			copy[i][j] = (int) message[k];
			//if(k > 20){
			//	i = j = SIZE;
			//	break;
			//}
		}
		k++;
		}
	}
}
void createCopy(int matrix[SIZE][SIZE], int copy[SIZE][SIZE]){
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
			copy[i][j] = matrix[i][j];
		}
	}
}
/*    Show the message in console */
char* displayMessage(int matrix[SIZE][SIZE], char message[20])
{
	int k = 0;
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
			if(matrix[i][j] == 0){
				matrix[i][j] = 33;
			}
			//if((char)matrix[i][j] == '\0')
			message[k] = (char)matrix[i][j];
			if(k > 20){
				i = j = SIZE;
				break;
			}
			k++;
		}
	}
	printf("Display Message 1: %s\n\n",message);
	return message;
}

char* dM(int matrix[SIZE][SIZE], char message[36])
{
	int k = 0;
	for(unsigned int i = 0; i < SIZE; i++){
		for(unsigned int j=0; j < SIZE; j++){
			if(matrix[i][j] == 33){
				matrix[i][j] = 0;
			}
			if(matrix[i][j] < 0){
				matrix[i][j] = 256 + matrix[i][j];
			}
			//if((char)matrix[i][j] == '\0')
			message[k] = (char)matrix[i][j];
			k++;
		}
	}
	printf("Display Message 2: %s\n\n",message);
	return message;
}

/*    Show the matrix in console */
void displayMatrix(int matrix[SIZE][SIZE], char code[3]){
    printf("\nDISPLAY MATRIX: %s\n", code);
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){
            printf("%4c", matrix[i][j]);
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
 * Si se tiene el valor 10, en binario ( 1010 ) revertirÃ¡ el orden de sus bits por ( 0101 ) = 5
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
 * La funcion reverseBits es la funciÃ³n complementaria de encryptR, la cual realiza la operacion de revertir los bits.
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

// Vigenere
// Por razones actualmente desconocidas en el caso del caracter ) se carcome en mensaje.
// Probar con este mensaje #$%&/()=?VAMOSvamosx 
// y con este otro  #$%&/(=?VAMOSvamosx 
char* getVigenereKey(char* key, int messageLength, int keyLength) {
    char* newKey = malloc(messageLength * sizeof(char*));
    int i, j;

    for(i = 0, j = 0; i < messageLength; ++i, ++j) {
        if(j == keyLength) {
            j = 0;
        }
        newKey[i] = key[j];
    }

    newKey[i] = '\0';

    return newKey;
}

char* vigenereEncrypt(char* message, char* key) {

    int messageLength = strlen(message);
    char* encryptedMessage = malloc(messageLength * sizeof(char*));
    char* newKey = getVigenereKey(key, messageLength, strlen(key));
    int i;
    
    for(i = 0; i < messageLength; ++i) {
        message[i] = toupper(message[i]);
        if(message[i] > 64 && message[i] < 91) {
            encryptedMessage[i] = ((message[i] + newKey[i]) % 26) + 'A';
        } else {
            encryptedMessage[i] = message[i];
        }
    }

    encryptedMessage[i] = '\0';
    return encryptedMessage;
}

char* vigenereDecrypt(char* message, char* key) {
    int messageLength = strlen(message);
    char* decryptedMessage = malloc(messageLength * sizeof(char*));
    char* newKey = getVigenereKey(key, messageLength, strlen(key));
    int i;

    for(i = 0; i < messageLength; ++i) {
        if(message[i] > 64 && message[i] < 91) {
            decryptedMessage[i] = ((message[i] - newKey[i]) % 26) + 'A';
        } else {
            decryptedMessage[i] = message[i];
        }
    }
    
    decryptedMessage[i] = '\0';
    return decryptedMessage;
}

void encryptSUM(int matrix[SIZE][SIZE], char clave[10])
{
    int pos = 0;

    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){

            matrix[i][j] = matrix[i][j] + clave[pos];
            pos = pos + 1;

            if (pos == 10){
                pos = 0;
            }

        }
    }
}

void encryptMINUS(int matrix[SIZE][SIZE], char clave[10])
{
    int pos = 0;

    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){

            matrix[i][j] = matrix[i][j] - clave[pos];
            pos = pos + 1;

            if (pos == 10){
                pos = 0;
            }

        }
    }
}

// encrypt and decrypt by XOR
void encryptXOR(int matrix[SIZE][SIZE], char clave[10])
{
    int pos = 0;

    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++){

            matrix[i][j] = matrix[i][j] ^ clave[pos];
            pos = pos + 1;

            if (pos == 10){
                pos = 0;
            }

        }
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void delete_word(char ** str){
	free(*str);
}

/* 
	Borra la letra especificada del string (la primer ocurrencia) , reduce el tamaño del string en 1
	 
*/
void delete_letter(char ** str, char letter) {

	char * new = NULL;
	
	if(*str != NULL){

		int i,j;
		
		new = malloc((strlen(*str)-1)*sizeof(char)); 
		
		for(i = 0; i < strlen(*str) && (*str)[i] != letter ; i++); //Buscamos donde esta la letra
		
		if(i == 0) { //La letra esta al principio
			for(j = 0 ; j < strlen(*str)-1 ; j++) {
				new[j] = (*str)[j+1];
			}
		}
		
		else if(i == strlen(*str)-1){ //La letra esta al final
			for(j = 0 ; j < strlen(*str)-1 ; j++) new[j] = (*str)[j]; 
			new[j] = '\0'; // J = strlen(*str)-2
		}
		
		else { //La letra esta en el medio
			for(j = 0 ; j < i ; j++) new[j] = (*str)[j]; //Copia las letras hasta el caracter en la pos i (no incluye el caracter en la pos i)
			for(j = i ; j < strlen(*str)-1 ; j++) new[j] = (*str)[j+1];
		}
		
	}
	
	free(*str);
	*str = new;

}

/*
	Busca una letra especificada del string
	Devuelve 1 si la encontro y 0 en caso contrario
*/
short search_letter(const char *str , char letter){

	int found = 0 , i ;
	
	for(i = 0; i < strlen(str) && str[i] != letter ; i++);
	
	if(str[i] == letter) found = 1;
	
	return found;

}

/* Agrega la letra especificada en la ultima posicion del string
	 Agrega ademas el \0
*/
void add_letter(char **str, char letter){

	if (*str == NULL){ // lugar para 2 pos 0 lettrt pos 1 '\0'
	  *str = malloc(sizeof(char)*2);
	  (*str)[0] = letter;
	  (*str)[1] = '\0';
	  
	}
	else{
		char * new = NULL;
		
		int i;
		//printf("new ahora ocupa %ld\n", strlen(str)*sizeof(char)+1);
		new = malloc(strlen(*str)*sizeof(char)+1);
	
 		int length = strlen(*str);
  
 		for(i = 0; i < length ; i++) new[i] = (*str)[i];
  
		new[i] = letter;
 		new[i+1] = '\0';
 		
 		free(*str);
 		*str = new;
  }
}

/* Agrega la letra especificada en la ultima posicion del string (utiliza realloc en vez de malloc)
	 Agrega ademas el \0
*/
void add_letterV2(char **str, char letter){

	if (*str == NULL){ // lugar para 2 pos 0 lettrt pos 1 '\0'
	  *str = malloc(sizeof(char)*2);
	  (*str)[0] = letter;
	  (*str)[1] = '\0';
	  
	}
	else{
		int i;
		//printf("new ahora ocupa %ld\n", strlen(str)*sizeof(char)+1);
		*str = realloc(*str,strlen(*str)*sizeof(char)+1);
	
 		int length = strlen(*str);
  
 		for(i = 0; i < length ; i++); //Se recorre el string
  
		(*str)[i] = letter;
 		(*str)[i+1] = '\0';
  }
}

/*
	Recibe dos strings (str y word) y verifica si word se encuentra dentro de str
	Devuelve 1 en caso de encontrar word y 0 en caso contrario
	Devuelve 2 si alguno de los strings era NULL
*/
short find_word(char * str , char * word){

	if((str != NULL)&&(word != NULL)){

		int i , j, count = 0;		
		char * str_act = NULL;
		
		i = 0;
		while(str[i] != '\0'){
				
			//Comienza verificacion
			j = 0;
			if(str[i] == word[j]) { 
				while((str[i] == word[j])&&(str[i] != '\0')){
					add_letter(&str_act,str[i]);
					i++; 
					j++;
				}
				if(strcmp(str_act,word) == 0) count++;
			}		
			
			free(str_act);
			str_act = NULL;	
			
			if(str[i] != '\0') i++;
			
		}//Se termino de leer STR
		
		if(count > 0) return 1;
		else return 0;				
	}
	else return 2; //Retorna 2 en caso de que alguno de los string fuera NULL
}


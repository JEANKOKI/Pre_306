#include <stdio.h>

int equal_STRINGS( char *first_String, char *second_String);



int equal_STRINGS( char *first_String, char *second_String){
    int i=0;

    while(first_String[i]!='\0'&& second_String[i]!='\0'){
        if(first_String[i]!=second_String[i]){
            return 0;
        }
        i++;
        }
    
    return (first_String[i] == '\0' && second_String[i] == '\0');
    
}

int main( int argc, char *argv[]){
    if(argc<2){
        printf("invalid amount of arguemets");
            return 1;
    }


    if( equal_STRINGS(argv[1],"-f")){
        printf("Display the number of fields in the first record of file  \n ");
                }

    else if(equal_STRINGS(argv[1],"-r")){
        printf("Display the number of data records in \n");
    }
    
    
    else if(equal_STRINGS(argv[1],"-min")||
            equal_STRINGS(argv[1],"-max")||
            equal_STRINGS(argv[1],"-mean")||
            equal_STRINGS(argv[1],"-h")){
                if(argc<3){
                      printf("Error another command is required \n");
        }
    }
        else if(equal_STRINGS(argv[1],"-records")){
            printf("Display records \n");
        }
        return 0;
       
}

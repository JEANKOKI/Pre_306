#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "program.h"

int main( int argc, char *argv[]){
    if(argc<3){
        printf("invalid amount of arguemets \n");
            return EXIT_FAILURE;
    }


    char *filename= argv[argc-1];  // since the filenam eis alwsy the end of arguement

    int header_flag=0;
    

    for( int i=1;i <argc-1;i++){
        if (strcmp(argv[i],"-h")==0){
            header_flag=1;
            break;
        }

        // check for -h first like said in git 
    }

    for( int i=1; i <argc-1;i++){
         if (strcmp(argv[i], "-f") == 0) {
            printf("Fields in first record: %d\n", count_fields(filename));
        }
         else if(strcmp(argv[i], "-r") == 0) {
             printf("Number of records: %d\n", count_records(filename, header_flag));
    }
         else if ((strcmp(argv[1], "-mean") == 0 || strcmp(argv[1], "-min") == 0 || strcmp(argv[1], "-max") == 0) && argc > 2) {
          int field_index = atoi(argv[2]);

        if (strcmp(argv[1], "-mean") == 0) {
            printf("The mean is: %.2f\n", calculate_mean(filename, field_index));
        } else if (strcmp(argv[1], "-min") == 0) {
            printf("The min is : %.2f\n", calculate_min(filename, field_index));
        } else if (strcmp(argv[1], "-max") == 0) {
            printf("The max is : %.2f\n", calculate_max(filename, field_index));
        }
         }
        else if (strcmp(argv[1], "-records") == 0 && argc > 3) {
            int field_index = atoi(argv[2]);
            char *value = argv[3];
            display_records(filename, field_index, value);
        }

        else {
            printf("Incorrect or incomplete command");
            return EXIT_FAILURE;
        }
         return EXIT_SUCCESS;
    } 
 
    
       
        

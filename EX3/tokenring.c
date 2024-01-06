#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdbool.h>


int main(int argc, char* argv[]){
int nfifos = atoi(argv[1]);
int prob =  atof(argv[2]) * 100;
int time = atoi(argv[3]);
char myfifo[50];
int token = 5; 

/*create fifos*/
for(int i = 1; i < nfifos; i++){
    sprintf(myfifo, "pipe%dto%d", i , i+1);
    mkfifo(myfifo, 0777);
}
sprintf(myfifo, "pipe%dto%d", nfifos, 1);
mkfifo(myfifo, 0777);


/*create processes*/
int pid;
for(int i = 1; i < nfifos; i++){
    /*criar 4 child processes*/
    if((pid = fork()) < 0){
        printf("Child process creation failure \n");
        exit(EXIT_FAILURE);
    }

/*child*/
    if(pid == 0){

        /*read - write*/

        if(i == 1) {
            /*if its reading from end-to-first pipe*/
            sprintf(myfifo, "pipe%dto%d", nfifos, i);
        }else{
            /*if its reading from anywhere else*/
            sprintf(myfifo, "pipe%dto%d", i - 1, i);
        }

        //opening writer
        int file_write;
        if((file_write = open(myfifo, O_RDONLY))<0){
            printf("Error opening writer child\n");
            exit(EXIT_FAILURE);

        } 

        close(file_write);

        sprintf(myfifo, "pipe%dto%d", i, i+1);


        //opening reader
        int file_read;
        if((file_read = open(myfifo, O_WRONLY))<0){
            printf("Error opening reader \n");

            exit(EXIT_FAILURE);
        }

        close(file_read);

        while(true){
        
            // read pipe
            read(file_read, &token, sizeof(token));

            /*lock*/
            int random = rand() % 100;
            
            if(random <= prob){
                printf( "\r[p%d] lock on token (val = %d)\n", (i % nfifos), token);
                sleep(time);
                printf( "\r[p%d] unlock token \n", i );
            } 
            token = token + 2;
            

            // write to pipe
            write(file_write, &token, sizeof(token));

            }
        
        }
    }
    
//main process


    /*read - write*/
    sprintf(myfifo, "pipe%dto%d", nfifos, 1);


    //opening reader
    int file_read;
    if((file_read = open(myfifo, O_WRONLY))<0){
        printf("Error opening reader \n");

        exit(EXIT_FAILURE);
    }  
    close(file_read);   


    sprintf(myfifo, "pipe%dto%d", nfifos - 1, nfifos);
    int file_write;

    //opening writer  
    if((file_write = open(myfifo, O_RDONLY))<0){
        printf("Error opening writer\n");
        exit(EXIT_FAILURE);

    }

    close(file_write);

    while(true){

        // read pipe
        read(file_read, &token, sizeof(token)); 

        /*lock*/
        int random = (rand() % 100);

        if(random <= prob){
            printf( "\r[p%d] lock on token (val = %d)\n", nfifos, token);
            sleep(time);
            printf( "\r[p%d] unlock token \n", nfifos );
        }
        token = token  + 2;


        // write to pipe
        write(file_write, &token, sizeof(token));
        
    
        } 
            
    return 0;
    }

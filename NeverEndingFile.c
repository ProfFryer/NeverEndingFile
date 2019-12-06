
// C program to implement one side of FIFO 
// initially from https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
// Modified by Sam Fryer, December 2019
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

// Should be a power of 2.
#define DATA_SIZE 4096

int main(int argc, char * argv[]) 
{ 
    int fd; 
    size_t written = 0;

    // Validate we have our arguments
    if (argc < 2) 
    {
        printf("usage: %s <filename>\n",argv[0]);
        return 1;
    }

    // FIFO file path 
    char * myfifo = argv[1]; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 
  
    unsigned char data[DATA_SIZE]; 
    unsigned char val = 0;
    for (int i = 0; i<DATA_SIZE; i++)
        data[i] = val++;


    // Open FIFO for write only 
    fd = open(myfifo, O_WRONLY); 
    if (fd < 1) 
        printf("Error opening %s\n",myfifo);
    else
    {

        while (1) 
        { 
            written = 0;

  
            // Write the input arr2ing on FIFO 
            // and close it 
            written = write(fd, data, DATA_SIZE); 

            if (written != DATA_SIZE) 
                printf("Error: wrote %ld of %d\n",written, DATA_SIZE);
        
            usleep(10);  
        }
        close(fd);
    } 
    return 0; 
} 



// C program for verifying that a file matches our expected bytes
// Sam Fryer, December 2019
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
    size_t bytesRead = 0;
    size_t ei = 0;
    unsigned long long byteCount = 0;

    // Validate we have our arguments
    if (argc < 2) 
    {
        printf("usage: %s <filename>\n",argv[0]);
        return 1;
    }

    // file path 
    char * filename = argv[1]; 
  
    unsigned char data[DATA_SIZE]; 

    // Set data we're expecting
    unsigned char expectedData[DATA_SIZE]; 
    unsigned char val = 0;
    for (int i = 0; i<DATA_SIZE; i++)
        expectedData[i] = val++;


    // Open for read only 
    fd = open(filename, O_RDONLY); 
    if (fd < 1) 
        printf("Error opening %s\n",filename);
    else
    {
	// Read the data
        while ((bytesRead = read(fd,data,DATA_SIZE))>0) 
        { 
            for(size_t i = 0; i<bytesRead; i++)
            {
                // make sure it matches what's expected.
                if (data[i] != expectedData[ei++])
                {
                    byteCount += i;
                    printf("ERROR FOUND AT BYTE 0x%08llX\n",byteCount);
                    return 1;
                }
                ei %= DATA_SIZE;
            }
            byteCount += DATA_SIZE;
        }
        close(fd);
    } 
    return 0; 
} 


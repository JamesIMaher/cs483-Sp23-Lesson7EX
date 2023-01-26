#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


int main() {
    const int _SIZE = 4096; //Size of the shared buffer. Same size as defined in the consumer.
    const char *name = "OSTest"; //Name of the shared buffer to reference the same buffer as the consumer. 
    const char *message1 = "Studying "; //Three strings that will be placed in the buffer for the consumer. 
    const char *message2 = "Operating Systems ";
    const char *message3 = "is fun!\n";
    int shm_fd; //Shared Memory File Descriptor
    void *ptr;

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); //O_CREAT and O_RDWR are bitmaps that are "or'd" together to select options.
    ftruncate(shm_fd, _SIZE); //Double check that the shared buffer is no larger than the buffer you just configured. 

    ptr = mmap(0, _SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); //Notice the producer can read and write. Consumer can only read. 

    if(ptr == MAP_FAILED){
        printf("Memory mapping failed\n");
        exit(-1);
    }

    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);
    sprintf(ptr, "%s", message2);
    ptr += strlen(message2);
    sprintf(ptr, "%s", message3);
    ptr += strlen(message3);

    /* //Use to show how unlinked shared memory cannot be accessed. 
    sleep(30);
    if(shm_unlink(name) == -1){
        printf("Error removing %s.\n",name);
        exit(-1);
    }
    */
    return 0;

}
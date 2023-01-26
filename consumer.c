#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

int main() {
    const int _SIZE = 4096; //Size of the shared memory buffer to allocate. 
    const char *name = "OSTest"; //String name of the shared memory buffer. Used by the producer to locate shared memory.
    int shm_fd; //Shared memory File Descriptor
    void *ptr;

    shm_fd = shm_open(name, O_RDWR, 0666); //shm_open instead of fopen. O_RDWR is read-write access defined in fcntl.h

    if(shm_fd == -1){
        printf("Shared Memory Initialization Failure.\n");
        exit(-1);
    }

    //Map the shared file descriptor into a region of the current process's virtual memory
    ptr = mmap(0, _SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    if(ptr == MAP_FAILED){
        printf("Memory mapping failed\n");
        exit(-1);
    }

    //Print data that is in the shared buffer
    printf("%s\n", (char*) ptr);

    if(shm_unlink(name) == -1){
        printf("Error removing %s.\n",name);
        exit(-1);
    }
    return 0;
}
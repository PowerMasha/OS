#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>

int main(int argc, char **argv){

    char semIn[] = "/semIn";
    int BUFFER_SIZE = 100;

    char* tmp_name = strdup("/tmp/tmp_file.XXXXXX");
    int tmp_fd = mkstemp(tmp_name);

    int file_size = BUFFER_SIZE + 1;
    char file_filler[file_size];
    for (int i = 0; i < file_size; ++i) {
        file_filler[i] = '\0';
    }
    write(tmp_fd, file_filler, file_size);
    char* map = (char*)mmap(NULL, BUFFER_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, tmp_fd, 0);

    sem_t* sem_in;
    sem_unlink(semIn);
    if ((sem_in = sem_open(semIn, O_CREAT, 0777, 0)) == SEM_FAILED ) {
        perror("sem_in");
        return 1;
    }

    int f;
  char buf[160];
  pid_t pid; // создание процесса
  if ((f = open(argv[1], O_RDWR | O_CREAT | O_APPEND)) == -1){
    printf("Cannot open file.\n");
    return -1;
  }
  pid = fork();
  if(pid == -1){
    printf("Can\'t fork\n"); // процесс не создался
    return -1;
  }//ребенок
  else if(pid == 0){
    sem_wait(sem_in);
    char c;
    while(read(f, &c, sizeof(char)) == sizeof(char)) {
        write(f, &c, sizeof(char));
    }
  }//родитель
  else{
      scanf("%s", map);
      if(dup2(f, 1) < 0) {
          printf("Error can't dup");
          exit(-1);
      }
      sem_post(sem_in);
      execlp(map, map, NULL); //выполнениe
  }
  return 0;
}

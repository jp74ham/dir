/*
opendir(const char *name) : returns a pointer to directory stream of name
readdir(DIR *dirp) : returns a pointer to a dirent structure representing the next directory entry
closedir(DIR *dirp) : returns 0 on success, -1 on failure
struct dirent {
    ino_t d_ino; 
    off_t d_off; //current location of dirp
    unsigned short d_reclen; //length of this record
    unsigned char d_type; //type of file
    char d_name[256]; //filename
    ...
};

output
d file_type_as_a_hex_number file_name file_size_as_a_decimal_number

*/

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    DIR *dirp; // create directory stream pointer object
    struct dirent *direntp; // create individual directory entry pointer object
    if (argc != 1 && argc != 2){
        printf("Incorrect number of arguments. Usage:\n\tdir\n\tdir DIRECTORY_NAME\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 2){  //no directory specified, list current directory

        if ((dirp = opendir(argv[1])) == NULL){
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }
    } else {
        if ((dirp = opendir(".")) == NULL){
            perror(".");
            exit(EXIT_FAILURE);
        }
    }
    while ((direntp = readdir(dirp)) != NULL){ //iterate through directory entries
        if (direntp->d_type == 4){
            printf("d ");
        } else{
            printf("  ");
        }
        printf("%d %s %d\n", direntp->d_type, direntp->d_name, direntp->d_reclen);
    }

    closedir(dirp);
    exit(EXIT_SUCCESS);
}
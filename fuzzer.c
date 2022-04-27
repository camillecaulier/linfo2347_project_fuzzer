//
// Created by Camil on 26/04/2022.
//
#include <stdio.h>
#include <string.h>

struct tar_t
{                              /* byte offset */
    char name[100];               /*   0 */
    char mode[8];                 /* 100 */
    char uid[8];                  /* 108 */
    char gid[8];                  /* 116 */
    char size[12];                /* 124 */
    char mtime[12];               /* 136 */
    char chksum[8];               /* 148 */
    char typeflag;                /* 156 */
    char linkname[100];           /* 157 */
    char magic[6];                /* 257 */
    char version[2];              /* 263 */
    char uname[32];               /* 265 */
    char gname[32];               /* 297 */
    char devmajor[8];             /* 329 */
    char devminor[8];             /* 337 */
    char prefix[155];             /* 345 */
    char padding[12];             /* 500 */
}mytar;


/**
 * Computes the checksum for a tar header and encode it on the header
 * @param entry: The tar header
 * @return the value of the checksum
 */
unsigned int calculate_checksum(struct tar_t* entry){
    // use spaces for the checksum bytes while calculating the checksum
    memset(entry->chksum, ' ', 8);

    // sum of entire metadata
    unsigned int check = 0;
    unsigned char* raw = (unsigned char*) entry;
    for(int i = 0; i < 512; i++){
        check += raw[i];
    }

    snprintf(entry->chksum, sizeof(entry->chksum), "%06o0", check);

    entry->chksum[6] = '\0';
    entry->chksum[7] = ' ';
    return check;
}
int main(int argc, char* argv[]){
    FILE *fptr;
    fptr = fopen("archive_test.tar","w");
    if(fptr == NULL)
        {
            printf("Error!");
//            exit(1);
        }
    int res = calculate_checksum(&mytar);
    printf("%d",res);
    fwrite (&mytar, sizeof(struct tar_t), 1, fptr);
    fclose(fptr);

    return 0;
}
int create_archive(){
    FILE *fptr;
    fptr = fopen("archive_test.tar","w");
    if(fptr == NULL){
        printf("Error!");
        return 0;
    }
    int res = calculate_checksum(&mytar);
    fwrite (&mytar, sizeof(struct tar_t), 1, fptr);
    fclose(fptr);
    return 1;
}
//char data_types = {"ascii", b};
//int create_data(){}






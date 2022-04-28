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
int run_extractor(int argc, char* argv[]){
    if (argc < 2)
        return -1;
    int rv = 0;
    char cmd[51];
    strncpy(cmd, argv[1], 25);
    cmd[26] = '\0';
    strncat(cmd, " archive.tar", 25); //path of executable
    char buf[33];
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    if(fgets(buf, 33, fp) == NULL) {
        printf("No output\n");
        goto finally;
    }
    if(strncmp(buf, "*** The program has crashed ***\n", 33)) {
        printf("Not the crash message\n");
        goto finally;
    } else {
        printf("Crash message\n");
        rv = 1;
        goto finally;
    }
    finally:
    if(pclose(fp) == -1) {
        printf("Command not found\n");
        rv = -1;
    }
    return rv;
}
int create_archive(FILE *fptr){
//    FILE *fptr;

    if(fptr == NULL){
        printf("Error!");
        return 0;
    }
    //    int res = calculate_checksum(&mytar);
    struct tar_t archive = {"fuck","fuck","fuck","fuck","fuck","fuck","fuck","1","fuck","fuck","fuck","fuck","fuck"};
    calculate_checksum(&archive);
    fwrite (&archive, sizeof(struct tar_t), 1, fptr);


    return 1;
}
//char *random_string(int size){
//    char all_char[] = "`1234567890-=¬!\"£$%^&*()_+¦qwertyuiop[]QWERTYUIOP{}asdfghjkl;'#ASDFGHJKL:@~\\zxcvbnm,./|ZXCVBNM<>?";
//
//}
char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {
            for (int n = 0;n < length;n++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}
int fuzzer(int argc, char argv[], FILE *fptr){
    int total_bugs = 0;
    for(int i = 0 ; i < 10; i++){
        int archive_check = create_archive(fptr);
        if (!archive_check){
            return 0;
        }
        int extractor_val = run_extractor(argc, argv);
        if (extractor_val > 0){
            total_bugs += 1;
        }
        if(extractor_val == -1){
            printf("error in the executable\n");
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]){
    int run = run_extractor(argc, argv);
    FILE *fptr;
    fptr = fopen("archive_test.tar","w");
    int run_fuzzer = fuzzer(argc, argv, fptr);
    fclose(fptr);
    if(!run_fuzzer){
        printf("error");
        return 0;
    }

    printf("extractor val : %d", run);
    return 0;
}


//char data_types = {"ascii", b};
//int create_data(){}






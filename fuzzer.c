//
// Created by Camil on 26/04/2022.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct tar_t{
    /* byte offset */
    char name[100];               /*   0 */ //nothing, something good, confusing random, big
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
    //17 fields
    //18 is for the
    //don't forget the file

};
/* Bits used in the mode field, values in octal.  */
//#define TSUID    04000          /* set UID on execution */
//#define TSGID    02000          /* set GID on execution */
//#define TSVTX    01000          /* reserved */
///* file permissions */
//#define TUREAD   00400          /* read by owner */
//#define TUWRITE  00200          /* write by owner */
//#define TUEXEC   00100          /* execute/search by owner */
//#define TGREAD   00040          /* read by group */
//#define TGWRITE  00020          /* write by group */
//#define TGEXEC   00010          /* execute/search by group */
//#define TOREAD   00004          /* read by other */
//#define TOWRITE  00002          /* write by other */
//#define TOEXEC   00001          /* execute/search by other */

unsigned  char modes[12] = {04000, 02000,01000, 00400, 00200, 00100, 00040, 00020, 00010,00004,00002,00001};


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

void fexpand(FILE* f, size_t amount, int value){
    while( amount-- ){
        fputc( value, f );
    }
}
void tar_add(FILE* tar_file, const char* file, const char* internal_name){
    //Get current position; round to a multiple of 512 if we aren't there already
    size_t index = ftell( tar_file );
    size_t offset = index % 512;
    if( offset != 0 ){
        fexpand( tar_file, 512 - offset, 0);
    }
    //Store the index for the header to return to later
    index = ftell( tar_file );
    //Write some space for our header
    fexpand( tar_file, sizeof(struct tar_t), 0 );
    //Write the input file to the tar file
    FILE* input = fopen( file, "rb" );
    if( input == NULL ){
        fprintf( stderr, "Failed to open %s for reading\n", file);
        return;
    }
    //Copy the file content to the tar file
    while( !feof(input) ){
        char buffer[2000];
        size_t read = fread( buffer, 1, 2000, input );
        fwrite( buffer, 1, read, tar_file);
    }
    //Get the end to calculate the size of the file
    size_t end = ftell( tar_file );
    //Round the file size to a multiple of 512 bytes
    offset = end % 512;
    if( end != 0 ){
        fexpand( tar_file, 512 - offset, 0);
    }
    //Fill out a new tar header
    struct tar_t header;
    //Calculate the checksum
    size_t checksum = 0;
    int i;
    const unsigned char* bytes = &header;
    //Save the new end to return to after writing the header
    end = ftell(tar_file);

    //Write the header
    fseek( tar_file, index, SEEK_SET );
    fwrite( bytes, 1, sizeof( struct tar_t ), tar_file );

    //Return to the end
    fseek( tar_file, end, SEEK_SET );
    fclose( input );
}

struct tar_t create_name(struct tar_t* archive, int modify_field, int modification_type){

}

char* random_string(int size){
    /*
     * creates a random string and returns the pointer
     */
    char all_char[] = "`1234567890-=¬!\"£$%^&*()_+¦qwertyuiop[]QWERTYUIOP{}asdfghjkl;'#ASDFGHJKL:@~\\zxcvbnm,./|ZXCVBNM<>?";
    char *random_string = NULL;
    if(size>0){
        random_string = malloc(sizeof(char)*(size + 1));
        if(random_string){
            for(int i = 0 ; i < size; i++){
                int random_letter = rand() % (int)(sizeof(all_char)-1);
                random_string[i] = all_char[random_letter];
            }
            random_string[size] = '\0';
        }
    }
    return random_string;

}

void create_archive_files(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification
//    struct tar_t archive;
//    char name[100]= "archive/file1";
//    printf("%s\n",name);
//    printf("%c\n", name[12]);
    FILE *fptr;
    fptr = fopen("archive.tar","w");
//    char name2[100] = "archive/file2";
    struct tar_t *archive = malloc(sizeof(struct tar_t));
    for(int i = 0 ; i < no_files;i++){


//        strcpy(archive->name, "archive/file");
        sprintf(archive->name,"file%o.txt",i );

//        printf(" archive name : %s\n", archive->name);
//        printf("archive/file%d\n",i );
        sprintf(archive->size, "%o",512);
        time_t rawtime;
        sprintf(archive->mode, "%o", modes[4]);

        sprintf(archive->mtime,"%o",localtime(&rawtime));
        printf(archive->mtime);
        printf("\n");
        sprintf(archive->chksum, "%o",calculate_checksum(archive));
        //two blocks of 512 null bytes
        fwrite(archive,512, 1, fptr);
        char *random_input = random_string(512);
        fwrite(random_input,512,1,fptr);
        free(random_input);
        char  *nullblock = calloc(512,1);
        fwrite(nullblock,512,2,fptr);
        free(nullblock);

//        free(name);
//        printf("%s",name);

    }
    if (modify_field == 0 && modification_type == 0){

    }
    fclose(fptr);
    return;
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
    printf(cmd);
    printf("\n");

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    if(fgets(buf, 33, fp) == NULL) {
        printf("No output\n");
        goto finally;
    }
    if(strncmp(buf, "*** The program has crashed ***\n", 33)) {
        printf(buf);
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



    if(fptr == NULL){
        printf("Error!");
        return 0;
    }
    struct tar_t archive;
    calculate_checksum(&archive);
    fwrite (&archive, sizeof(struct tar_t), 1, fptr);

    return 1;
}


int fuzzer(int argc, char argv[]){
    int total_bugs = 0;
    for(int i = 0 ; i < 10; i++){
//        int archive_check = create_archive(fptr);
//        if (!archive_check){
//            return 0;
//        }
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
//    printf(argv[1]);
    create_archive_files(0,0,1);
    int run = run_extractor(argc, argv);
//    FILE *fptr;
//    fptr = fopen("archive.tar","w");
    int run_fuzzer = fuzzer(argc, argv);
//    fclose(fptr);
    if(!run_fuzzer){
        printf("error");
        return 0;
    }

    printf("extractor val : %d", run);
    return 0;
}


//char data_types = {"ascii", b};
//int create_data(){}






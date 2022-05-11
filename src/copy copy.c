//
// Created by Camil on 26/04/2022.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>


static char extractor[100];
static int correct = 0;

struct tar_t {                              /* byte offset */
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
};

#define TMAGIC   "ustar\x00" 

//EXTRACTOR FUNCTION...
int run_extractor(){
    int rv = 0;
    char cmd[250];
    sprintf(cmd, "%s %s 2>&1", extractor, "archive.tar");
    char buf[250];
    FILE *fp;
    printf(cmd);
    printf("\n");

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }
    if(fgets(buf, 250, fp) == NULL) {
        printf("No output\n");
        goto finally;
    }
    if(strncmp(buf, "*** The program has crashed ***\n", 33)) {
        printf(buf);
        printf("Not the crash message\n");
        goto finally;
    } else {
        printf("Crash message\n");
        correct +=1;
        char new_name[100];
        sprintf(new_name,"success_%d.tar",correct);
        rename("archive.tar", new_name);
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


// CREATE CORRECT FILE FOR ARCHIVE
// void create_archive_files(){
   
//     struct tar_t *archive = calloc(1 , sizeof( tar_t));
//     tar_init(archive);
//     tar_write(archive,"bonjour",512);
//     run_extractor();
// }

// TEST #1 TRY WITH EMPTY TAR
// void test_empty(){
//     tar_t *archive;
//     FILE *fptr = fopen("archive.tar", "wb");
//     if (!fptr)
//   {
//     puts("Could not write to file");
//     return;
//   }
//     char * buffer = "";
//     calculate_checksum(archive);
//     fwrite(archive, sizeof(tar_t), 1, fptr);
//     fwrite(buffer, 0, 1, fptr);
//     char  *nullblock = calloc(512,2);
//     fwrite(nullblock,1024,1,fptr);
//     free(nullblock);
//     run_extractor();
// }

// TEST DIFFERENT SIZE + NULL BLOCK

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
void create_archive_files(){//the field to modify and which type of modification

    FILE *fptr;
    fptr = fopen("archive.tar","w");

//    char name2[100] = "archive/file2";
  
        struct tar_t *archive = calloc(1 , sizeof(struct tar_t));


        snprintf(archive->name,sizeof(archive->name),"archive_2.sh");
        snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
        snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);
        snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);
        snprintf(archive->size,sizeof(archive->size), "%06o",00000000554);
        memcpy(archive->magic,TMAGIC,sizeof(archive->magic));

        char version [2] = {'0','0'};
        memcpy(archive->version,"00",sizeof(version));

        calculate_checksum(archive);
        //two blocks of 512 null bytes
        fwrite(archive,512, 1, fptr);
        char * content = (char * )malloc(sizeof(char) *12);
        char mess[] = "bonjour\0";
        memcpy(content,mess,sizeof(mess));
        fwrite(content,1,12, fptr);
        free(content);
        char  *nullblock = calloc(512,2);

        fwrite(nullblock,1024,1,fptr);
        free(nullblock);
    
    
    fclose(fptr);
    run_extractor();
  

    return;
}



// void test_size(){
//     struct tar_t *archive = calloc(1 , sizeof( tar_t));
//     char buffer[] = "hello";
//     unsigned long len_buffer = strlen(buffer);

//     tar_init(archive);
//     tar_size(archive,"0000000000");
//     tar_write(archive,buffer,len_buffer);
//     run_extractor();

//     tar_init(archive);
//     tar_size(archive,"00000000001");
//     tar_write(archive,buffer,len_buffer);
//     run_extractor();

//     tar_init(archive);
//     tar_size(archive,"0000000054");
//     tar_write(archive,buffer,len_buffer);
//     run_extractor();

//     tar_init(archive);
//     tar_size(archive,"0000000554");
//     tar_write(archive,buffer,len_buffer);
//     run_extractor();

//     tar_init(archive);
//     tar_size(archive,"0000005554");
//     tar_write(archive,buffer,len_buffer);
//     run_extractor();

// }


int main(int argc, char* argv[]){
    strcpy(extractor, argv[1]);
//    printf(argv[1]);
    create_archive_files();
    // create_archive_files(0,0,1);
    // create_archive_files2(0,0,1);
    // create_archive_files3(0,0,1);
    // create_archive_files4(0,0,1);
    // create_archive_files5(0,0,1);
    // create_archive_files6(0,0,1);

    // int run = run_extractor(argc, argv);
//    FILE *fptr;
//    fptr = fopen("archive.tar","w");


    // printf("extractor val : %d", run);
    return 0;
}


//char data_types = {"ascii", b};
//int create_data(){}






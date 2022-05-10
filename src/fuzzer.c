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
int run_extractor(char* error){
    int rv = 0;
    char cmd[250];
    sprintf(cmd, "%s %s 2>&1", extractor, "archive.tar");
    char buf[250];
    FILE *fp;
    // printf(cmd);
    // printf("\n");

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }
    if(fgets(buf, 250, fp) == NULL) {
        // printf("No output\n");
        goto finally;
    }
    if(strncmp(buf, "*** The program has crashed ***\n", 33)) {
        printf(buf);
        printf("Not the crash message\n");
        goto finally;
    } else {
        printf("Crash message %s\n",error);
        correct +=1;
        char new_name[100];
        sprintf(new_name,"success_%s.tar",error);
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



void write_archive_file(struct tar_t * archive,char * buff){
    FILE *fptr;
    fptr = fopen("archive.tar","w");
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
}

void create_archive_files(struct tar_t* archive,size_t size){//the field to modify and which type of modification

        snprintf(archive->name,sizeof(archive->name),"archive.sh");
        snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
        snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);
        snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);
        snprintf(archive->size,sizeof(archive->size), "%0*lo",11,size);
        memcpy(archive->magic,TMAGIC,sizeof(archive->magic));
        char version [2] = {'0','0'};
        memcpy(archive->version,"00",sizeof(version));
        

}
 char* modify(int size){
        char * modify = (char * )malloc(size);
        for (int i = 0; i<size; i++){
            modify[i] = (char)(128+ rand()%128);
        }
        return modify;
}

// DIFFERENT SETS OF TESTS ON HEADER FIELDS
void tests(struct tar_t * archive,char * header,char*header_name){
    char error[100];
    // TEST1 : STRING
    strncpy(header,"aaaaaaa",sizeof(header));
    write_archive_file(archive,"bonjour\0");
    sprintf(error, "%s_string",header_name);
    run_extractor(error);

    //TEST2: NON ASCII
    char * field = (char *) modify(sizeof(header));
    snprintf(header,sizeof(header),field);
    write_archive_file(archive,"bonjour\0");
    sprintf(error, "%s_noascii",header_name);
    run_extractor(error);

    //TEST3:EMPTY
    snprintf(header,sizeof(header),"");
    write_archive_file(archive,"bonjour\0");
    sprintf(error, "%s_empty",header_name);
    run_extractor(error);

    //TEST4:HALF NULL
    memset(header, 0, sizeof(header) / 2);
    memset(header, '0', sizeof(header) / 2);
    sprintf(error, "%s_half_zero",header_name);
    run_extractor(error);

}


//NO NULL BLOCKS
void no_null(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    snprintf(archive->name,sizeof(archive->name),"archive_2.sh");
    snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
    snprintf(archive->uid,sizeof(archive-> uid),"0001750");
    snprintf(archive->gid,sizeof(archive->gid), "0001750");
    snprintf(archive->size,sizeof(archive->size), "%0*o",11,256);
    memcpy(archive->magic,TMAGIC,sizeof(archive->magic));
    char version [2] = {'0','0'};
    memcpy(archive->version,"00",sizeof(version));
    FILE *fptr;
    fptr = fopen("archive.tar","w");
    calculate_checksum(archive);
    //two blocks of 512 null bytes
    fwrite(archive,512, 1, fptr);
    char * content = (char * )malloc(sizeof(char) *12);
    char mess[] = "bonjour\0";
    memcpy(content,mess,sizeof(mess));
    fwrite(content,1,12, fptr);
    free(content);
    fclose(fptr);
    run_extractor("no_nullblocks");

        
}


// TESTING MODE
void mode(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->mode,"mode");
}


//TESTING ON UID 
void uid(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->uid,"uid");
    
}


// TESTING GID
void gid(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->gid,"gid");
}

// TESTING ON THE DIFFERENT SIZE 
void size(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    // create_archive_files(archive,512);
    // tests(archive,archive->size);
    create_archive_files(archive,0);
    write_archive_file(archive,"bonjour\0");
    run_extractor("null_size");
    create_archive_files(archive,1);
    write_archive_file(archive,"bonjour\0");
    run_extractor("1_size");
    create_archive_files(archive,600);
    write_archive_file(archive,"bonjour\0");
    run_extractor("600_size");
    create_archive_files(archive,2048);
    write_archive_file(archive,"bonjour\0");
    run_extractor("2048_size");
}

// TESTING MTIME VERS
void mtime(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->mtime,"mtime");
}

//TESTING ON TYPEFLAG
void typeflag()
{
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
     char error[30];
    for (int i = 0; i < 0x100; i++)
    {
        sprintf(error, "typeflag_0x%02x", i);
        archive->typeflag = (char)i;
        write_archive_file(archive,"bonjour\0");
        run_extractor(error);
    }
}

// TESTING MAGIC
void magic(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->magic,"magic");
}

// TESTING UNAME
void uname(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->uname,"uname");
}

// TESTING GNAME
void gname(){
    struct tar_t* archive = (struct tar_t*) calloc(1, sizeof(struct tar_t));
    create_archive_files(archive,512);
    tests(archive,archive->gname,"gname");
}



int main(int argc, char* argv[]){
    strcpy(extractor, argv[1]);
    no_null();
    uid();
    gid();
    size();
    mtime();
    typeflag();
    magic();
    uname();
    gname();
    return 0;
}





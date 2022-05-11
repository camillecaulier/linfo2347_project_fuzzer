
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "archive_creator.h"


/**
 * Computes the checksum for a tar header and encode it on the header
 * @param header: The tar header
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

char* random_string(int size){
    /*
     * creates a random string and returns the pointer
     */
    char all_char[] = "`1234567890-=¬!\"£$%^&*()_+¦qwertyuiop[]QWERTYUIOP{}asdfghjkl;'#ASDFGHJKL:@~\\zxcvbnm,./|ZXCVBNM<>?\n";
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

void tar_init(struct tar_t * archive){
    // char * name = (char *) random_string(sizeof(archive->name));
    snprintf(archive->name,sizeof(archive->name),"test");
    snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
    snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);
    snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);
    snprintf(archive->size,sizeof(archive->size), "%06o",00000000554);
    
    time_t mtime = time(NULL);
    snprintf(archive->mtime,sizeof(archive->mtime),"%o",mtime);
    archive->typeflag = '0';
    
    memcpy(archive->magic,TMAGIC,sizeof(archive->magic));
    memcpy(archive->version,"00",sizeof(archive->version));



}
void tar_write(struct tar_t* archive,char* buffer, size_t size){
    FILE *fptr;
    fptr = fopen("archive.tar","w");
    calculate_checksum(archive);
    fwrite(archive,size, 1, fptr);
    char  *nullblock = calloc(512,2);
    fwrite(nullblock,1024,1,fptr);
    free(nullblock);
    fclose(fptr);
}
void tar_size(struct tar_t * archive, char* size){
    sprintf(archive->size,"%s" ,size);
    printf(archive->size);
}
// void create_archive_files(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification

//         snprintf(archive->name,sizeof(archive->name),"archive_2.sh");
//         snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
//         snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);
//         snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);
//         snprintf(archive->size,sizeof(archive->size), "%06o","00000000554");
//         memcpy(archive->magic,TMAGIC,sizeof(archive->magic));

//         char version [2] = {'0','0'};
//         memcpy(archive->version,"00",sizeof(version));

//         calculate_checksum(archive);
//         //two blocks of 512 null bytes
//         fwrite(archive,512, 1, fptr);
//         char * content = (char * )malloc(sizeof(char) *12);
//         char mess[] = "bonjour\0";
//         memcpy(content,mess,sizeof(mess));
//         fwrite(content,1,12, fptr);
//         free(content);
//         // char  *nullblock = calloc(512,2);
//         // //        char *nullblock = malloc(512);
//         // //        memset(nullblock,' ',512);
//         // fwrite(nullblock,1024,1,fptr);
//         // free(nullblock);


//         //        free(name);
//         //        printf("%s",name);

//     }
//     if (modify_field == 0 && modification_type == 0){

//     }
//     fclose(fptr);
//     return;
// }
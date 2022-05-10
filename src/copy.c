// void create_archive_files(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification

//     FILE *fptr;
//     fptr = fopen("success_archive1.tar","w");

// //    char name2[100] = "archive/file2";
//     for(int i = 0 ; i < no_files;i++){
//         struct tar_t *archive = calloc(1 , sizeof(struct tar_t));


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

// void create_archive_files2(int modify_field, int modification_type,int no_files){
//        FILE *fptr;
//     fptr = fopen("success_archive2.tar","w");
// //    char name2[100] = "archive/file2";
//     for(int i = 0 ; i < no_files;i++){

//         struct tar_t *archive = malloc(sizeof(struct tar_t));
// //        struct tar_t *archive = malloc(512);
// //        memset(archive, ' ', 512);
// //        strcpy(archive->name, "archive/file");
//         // sprintf(archive->name,"file_%o.txt",i );
//         // memset(archive->name, ' ',100);
//         char name [100] = {'a','r','c','h','i','v','e','.','t','x','t'};
//         name[99] = '\0';
//         snprintf(archive->name,sizeof(archive->name),name);



//         snprintf(archive->mode,sizeof(archive->mode),"0%06o",0000777);

//         memset(archive->uid,' ',sizeof(archive->uid));
//         // snprintf(archive->uid,sizeof(archive->uid), "0%06o", 000000);
//         snprintf(archive->uid,sizeof(archive->uid),"%s","000000");

//         snprintf(archive->gid,sizeof(archive->gid), "0%06o", 0000000);


//         snprintf(archive->size,sizeof(archive->size), "%s","00000000066");



//         time_t now = time(NULL);
//         memset(archive->mtime, NULL, 12);
//         snprintf(archive->mtime,sizeof(archive->mtime),"%o",now);

//         archive->typeflag = '0';

//         memset(archive->magic, '\0', 8);
//         memcpy(archive->magic,TMAGIC,sizeof(archive->magic));

//         char version [2] = {'0','0'};
//         memcpy(archive->version,version,sizeof(archive->version));


//         memset(archive->uname, NULL,32);
//         snprintf(archive->uname,sizeof(archive->uname), "charles");

//         memset(archive->gname, NULL,32);
//         snprintf(archive->gname,sizeof(archive->gname), "charles");

//         memset(archive->devmajor, NULL ,8);
//         snprintf(archive->devmajor,sizeof(archive->devmajor), "0000000");

//         memset(archive->devminor, NULL ,8);
//         snprintf(archive->devminor,sizeof(archive->devminor), "0000000");

// //        fflush(stdout);
//         calculate_checksum(archive);
    
//         //two blocks of 512 null bytes
//         fwrite(archive,512, 1, fptr);
//         char *random_input = random_string(512);
//         fwrite(random_input,512,1,fptr);
//         free(random_input);
//     //    char  *nullblock = calloc(512,2);
//        char *nullblock = malloc(512);
//     //    memset(nullblock,' \0',512);
//        fwrite(nullblock,1024,1,fptr);
//        free(nullblock);


// }}

// void create_archive_files3(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification
// //    struct tar_t archive;
// //    char name[100]= "archive/file1";
// //    printf("%s\n",name);
// //    printf("%c\n", name[12]);
//     FILE *fptr;
//     fptr = fopen("success_archive3.tar","w");

// //    char name2[100] = "archive/file2";
//     for(int i = 0 ; i < no_files;i++){
//         struct tar_t *archive = calloc(1 , sizeof(struct tar_t));


//         snprintf(archive->name,sizeof(archive->name),"archive_2.sh.py");
//         snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
//         snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);
//         snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);
//         archive->typeflag = '1';
//         snprintf(archive->size,sizeof(archive->size), "%s","0000000554");
//         snprintf(archive->linkname,sizeof(archive->linkname), "%o",000000000);
//         memcpy(archive->magic,TMAGIC,sizeof(archive->magic));
//         memcpy(archive->version,"00",sizeof(archive->version));

//         calculate_checksum(archive);
//         //two blocks of 512 null bytes
//         fwrite(archive,512, 1, fptr);
//         char * content = (char * )malloc(sizeof(char) *12);
//         char mess[] = "exit\0";
//         memcpy(content,mess,sizeof(mess));
//         fwrite(content,1,12, fptr);
//         fwrite(content,1,12, fptr);
//         free(content);
//         char  *nullblock = calloc(512,2);
//         fwrite(nullblock,1024,1,fptr);
//         free(nullblock);

//     }
//     if (modify_field == 0 && modification_type == 0){

//     }
//     fclose(fptr);
//     return;
// }

// char* modify(int size){
//         char * modify = (char * )malloc(size);
//         for (int i = 0; i<size; i++){
//             modify[i] = (char)(128+ rand()%128);
//         }
//         return modify;
// }

// void create_archive_files4(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification

//     FILE *fptr;
//     fptr = fopen("success_archive4.tar","w");

//     for(int i = 0 ; i < 51;i++){
//         struct tar_t *archive = calloc(1, sizeof(struct tar_t));
//         char * name = (char *) modify(sizeof(archive->name));
//         snprintf(archive->name,sizeof(archive->name),name);

//         char * mode = (char *) modify(sizeof(archive->mode));
//         snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
//         // there is a crash boy
//         char * uid = (char *) modify(sizeof(archive->uid));
//         // snprintf(archive->uid,sizeof(archive-> uid),uid);
//         snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);

//         char * gid = (char *) modify(sizeof(archive->gid));
//         snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);

//         char *typeflag = (char *) modify(sizeof(archive->typeflag));
//         archive->typeflag = '0';
//         char * size = (char *) modify(sizeof(archive->size));
//         snprintf(archive->size,sizeof(archive->size), "00000%06o",00554);
       

//         // char * mtime = (char *) modify(sizeof(archive->mtime));
//         time_t mtime = time(NULL);
//         snprintf(archive->mtime,sizeof(archive->mtime),"00000%06o",st.st_mtime);
//         //marche pas
//         char * magic = (char *) modify(sizeof(archive->magic));
//         snprintf(archive->magic,sizeof(archive->magic),TMAGIC);

//         memcpy(archive->version,"00",sizeof(archive->version));

//         char * linkname = (char *) modify(sizeof(archive->linkname));
//         snprintf(archive->linkname,sizeof(archive->linkname),linkname);


//         memset(archive->uname, '4', sizeof(archive->uname));

//         char * gname = (char *) modify(sizeof(archive->gname));
//         snprintf(archive->gname,sizeof(archive->gname), gname);


//         calculate_checksum(archive);
//         //two blocks of 512 null bytes
//         fwrite(archive,512, 1, fptr);
//         char* mess = random_string(512);
//         fwrite(mess,1,512, fptr);
//         free(mess);

//     }
//     char  *nullblock = calloc(512,2);
//     fwrite(nullblock,1024,1,fptr);
//     free(nullblock);


//     if (modify_field == 0 && modification_type == 0){

//     }
//     fclose(fptr);
//     return;
// }

// void create_archive_files5(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification

//     FILE *fptr;
//     fptr = fopen("success_archive5.tar","wb");
//     if(fptr){
//         fclose(fptr);
//     }
    
//     return;
// }

// void create_archive_files6(int modify_field, int modification_type,int no_files){//the field to modify and which type of modification

//     FILE *fptr;
//     fptr = fopen("success_archive6.tar","w");

// //    char name2[100] = "archive/file2";
//     for(int i = 0 ; i < no_files;i++){
//         struct tar_t *archive = calloc(1 , sizeof(struct tar_t));


//         snprintf(archive->name,sizeof(archive->name),"archive_2.sh");
//         snprintf(archive->mode,sizeof(archive->mode), "0%06o", 0000777 );
//         snprintf(archive->uid,sizeof(archive-> uid),"0%06o", 0001750);
//         snprintf(archive->gid,sizeof(archive->gid), "0%06o",0001750);
//         memcpy(archive->magic,TMAGIC,sizeof(archive->magic));

//         memset(archive->size, 0, sizeof(archive->size));
//         memset(archive->size, '2', sizeof(archive->size) / 2);

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
//         char  *nullblock = calloc(512,2);
//         fwrite(nullblock,1024,1,fptr);
//         free(nullblock);


 

//     }
//     if (modify_field == 0 && modification_type == 0){

//     }
//     fclose(fptr);
//     return;
// }
#include <stdio.h>
#include <stdlib.h>

char *makeFileName(char *src){
    /* Get ext and path length */
    char *src_pos, *src_period;
    src_pos = src;
    src_period = 0;
    while(*src_pos != '\0'){
        if(*src_pos == '.') src_period = src_pos;
        src_pos++;
    }
    int src_len = src_pos - src;
    /* Make output file name string */
    char *dst = (char *)malloc(src_len + 2);
    char *dst_pos;
    src_pos = src;
    dst_pos = dst;
    if(src_period == 0){
        /* No ext -> add '_' at the end of the file name */
        while(*src_pos != '\0'){
            *dst_pos++ = *src_pos++;
        }
        *dst_pos++ = '_';
        *dst_pos = '\0';
    }else{
        /* With ext -> add '_' before the ext */
        while(src_pos != src_period){
            *dst_pos++ = *src_pos++;
        }
        *dst_pos++ = '_';
        while(*src_pos != '\0'){
            *dst_pos++ = *src_pos++;
        }
        *dst_pos = '\0';
    }
    return dst;
}

int main(int argc, char *argv[]){
    /* Check args */
    if(argc < 2){
        printf("Usage:\n");
        printf("utf8bom_changer file1, file2, ...\n");
        exit(0);
    }
    /* Process each file */
    int bom[3];
    bom[0] = 0xef;
    bom[1] = 0xbb;
    bom[2] = 0xbf;
    for(int f_count = 1; f_count < argc; f_count++){
        char *dst = makeFileName(argv[f_count]);
        printf("Src:%s\nDst:%s\n", argv[f_count], dst);
        FILE *f_src;
        f_src = fopen(argv[f_count], "r");
        if(f_src == NULL){
            printf("Can't open file: %s\n", argv[f_count]);
            free(dst);
            continue;
            /* exit(EXIT_FAILURE); */
        }
        FILE *f_dst;
        f_dst = fopen(dst, "w");
        if(f_dst == NULL){
            printf("Can't open file: %s\n", dst);
            fclose(f_src);
            free(dst);
            continue;
            /* exit(EXIT_FAILURE); */
        }
        /* Get first 3 chars */
        int head[3];
        head[0] = fgetc(f_src);
        if(head[0] == EOF){
            printf("Empty file: %s\n", argv[f_count]);
            fclose(f_src);
            fclose(f_dst);
            free(dst);
            continue;
        }
        /* if file size < 3, without bom */
        head[1] = fgetc(f_src);
        if(head[1] == EOF){
            for(int i = 0; i < 3; i++){
                fputc(bom[i], f_dst);
            }
            fputc(head[0], f_dst);
            fclose(f_src);
            fclose(f_dst);
            free(dst);
            continue;
        }
        head[2] = fgetc(f_src);
        if(head[2] == EOF){
            for(int i = 0; i < 3; i++){
                fputc(bom[i], f_dst);
            }
            fputc(head[0], f_dst);
            fputc(head[1], f_dst);
            fclose(f_src);
            fclose(f_dst);
            free(dst);
            continue;
        }
        /* with or without bom? */
        if(head[0] != bom[0] || head[1] != bom[1] || head[2] != bom[2]){
            /* without bom -> add bom before the fist 3 chars */
            fputc(bom[0], f_dst);
            fputc(bom[1], f_dst);
            fputc(bom[2], f_dst);
            fputc(head[0], f_dst);
            fputc(head[1], f_dst);
            fputc(head[2], f_dst);
        }
        /* rest of the file */
        int c = fgetc(f_src);
        while(c != EOF){
            fputc(c, f_dst);
            c = fgetc(f_src);
        }
        fclose(f_src);
        fclose(f_dst);
        free(dst);
    }
    return 0;
}
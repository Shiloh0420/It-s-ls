#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<ctype.h>
#include<stdbool.h>
#include<unistd.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<sys/ioctl.h>

#define MAX_FILES 114514

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_BGREEN  "\033[1;32m"
#define COLOR_RED     "\033[31m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_MAGENTA "\033[35m"


struct  all_information{
    char name[256];
    int inode;
    struct stat* stat_info;
};

void color_print(struct all_information** alllist,int index){

    struct stat* stat_info = alllist[index]->stat_info;
    if(S_ISDIR(stat_info->st_mode)) printf("%s",COLOR_BLUE);
    else if(S_ISLNK(stat_info->st_mode)) printf("%s",COLOR_MAGENTA);
    else if(S_ISFIFO(stat_info->st_mode)) printf("%s",COLOR_YELLOW);
    else if(S_ISBLK(stat_info->st_mode)) printf("\033[34;43m");
    else if(S_ISCHR(stat_info->st_mode)) printf("\033[30;43m");
    else if(stat_info->st_mode & (S_IXGRP | S_IXOTH | S_IXUSR)) printf("%s",COLOR_BGREEN);

}

int compare_by_name_string(const void*,const void*);    //sort
int compre_by_time(const void*,const void*);   //sort
void L_NULL_DETCET(void*);                          //检查NULL

/////////////////////////// about string //////////////////////////////
int get_input_string_number(char*);
char** get_input_string_segment(char*);
////////////////////////////////////////////  about parameter //////////
int count_dir_entry(DIR*);

int handle(char*,int,int,int,int,int,int,int);

void l_handle(struct all_information**,int,int,int,int,int,struct passwd*,struct group*);
void print_files_by_lines(struct all_information**,int,int,int,int,int);
int get_line(struct all_information**,int,int,int,int,int);

int main(int argc,char *argv[]){
   
    // DIR* dir;
    // struct dirent *entry;

    // char **filesname = (char**)malloc(MAX_FILES * sizeof(char*));
    // L_NULL_DETCET(filesname);

    // dir = opendir("/");
    // L_NULL_DETCET(dir);

    // int number_files=0;
    // for(;(entry = readdir(dir)) != NULL;){
    //     int len = strlen(entry->d_name)+1;
    //     filesname[number_files] = (char*)malloc(len * sizeof(char));
    //     L_NULL_DETCET(filesname[number_files]);
    //     if(filesname[number_files] != NULL){
    //     memmove(filesname[number_files],entry->d_name,len);
    //     number_files++;
    //     }
    // }

    // qsort(filesname,number_files,sizeof(char *),compare_string);

    //while(1){
    //char input[114514];

    // char exe_path[114514];
    // ssize_t count = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    
    // exe_path[count] = '\0';


    // printf("%s ",exe_path);
    // printf("\033[1;34m~\033[1;34m");
    // printf("\033[34m/学习这一块/\033[34m");
    // printf("\033[1;34mc语言这一块\033[1;34m ");
    // printf("\033[1;32m> ");
    //printf("\033[34m上善若水，水善利万物而不争 ——《道德经》 \033[1;32m❯\033[0m ");

    // if(fgets(input,114514,stdin)==NULL){
        
    //     size_t len=strlen(input);
    //     if(len>0 && input[len-1]=='\n'){
    //         input[len-1]='\0';
    //     }

    // }
    // for(int i=0;i<114514;i++){
    //     if(input[i]=='\n'){
    //         input[i]='\0';
    //         break;
    //     }
    // }
    //printf("kewu:%s\n",input);
    /////////////////////////////////////////////////////////////right//////////////////////////////////////////////////////



    int have_ls=0;
    int have_a=0;
    int have_l=0;
    int have_r=0;
    int have_t=0;
    int have_R=0;
    int have_i=0;
    int have_s=0;

///////////////////////////////////////////////////////////first//////////////////////////////////////////////////////////////
    

    //         }else{

    //             int errorlen=0;
    //             int j=i;

    //             while(input[j++]!=' '){
    //                 errorlen++;
    //             }

    //             char* errorinput=(char *)malloc(sizeof(char)*errorlen);
    //             memcpy(errorinput,input+i,errorlen);

    //             printf("zsh: command not found: %s\n",errorinput);
    //             return 0;

    //         }
    //     }    
    // }
//////////////////////////////////////////////////////////second/////////////////////////////////////////////////////////////////
    //     for(;lable1<114514;lable1++){

    //     if(input[lable1]!=' '){

    //         if(input[i]=='-'){

    //             if(input[i+1]==' '){


    //             }

    //         }

    //         if(input[i]!='-'){

    //             int errorlen=0;
    //             int j=i;

    //             while(input[j++]!=' '){
    //                 errorlen++;
    //             }

    //             char* errorinput=(char *)malloc(sizeof(char)*errorlen);
    //             memcpy(errorinput,input+i,errorlen);

    //             printf("ls: cannot access '%s': No such file ontry->d_namr directory\n",errorinput);
    //             i+=errorlen;
    //         }
    //     }
    // }

///////////////////////////////////////////////////////////获得输入的每个字符串/////////////////////////////////////////////////////////

    
    //int string_number = get_input_string_number(input);
    // printf("number:%d\n",string_number);

    //char** need=get_input_string_segment(input);
    int string_number =argc;
    char** need = malloc((argc + 1)*sizeof(char*));
    for(int i=0;i<argc;i++){
        need[i]=argv[i];
    }
    need[argc]=NULL;
    
    //printf("wtf\n");
    // for(int i=0;i<string_number;i++){
    //     printf("need[%d]:%s\n",i,need[i]);
    // }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ok//////////////////////////

/////////////////////////////////////////////////////////////检测参数//////////////////////////////////////////////////////////////////
    if(strcmp(need[0],"ls")==0){

        have_ls=1;

    }


    int argument_not_found=0;
    for(int i=1;i<string_number;i++){

        
        if(!(strcmp(need[i],"--help"))){
            
            printf("List directory contents.\n");
            printf("Ignore files and directories starting with a '.' by default\n");
            printf("\n");
            printf("Usage: ls [OPTION]... [FILE]...\n");
            printf("\n");
            printf("Arguments:\n");
            printf("  [paths]...\n");
            printf("\n");
            printf("Options:\n");
            printf("  --help                                     oh I get a little help from my friends\n");
            printf("  -a                                         applepen pinepple pen ppap .\n");
            printf("  -i                                         i want to break free\n");
            printf("  -l                                         lovelive good good\n");
            printf("  -R                                         RNB's king David Tao\n");
            printf("  -r                                         rip Kobe Bryant\n");
            printf("  -s                                         sb code sb life sb me sb everyone\n");
            printf("  -t                                         time and tide wait for no man\n");
            printf("\n");
            printf("The TIME_STYLE argument can be full-iso, long-iso, iso, locale or +FORMAT. FORMAT is interpreted like in date. Also the TIME_STYLE environment variable sets the default style to use.");
            printf("Let me take you down Cause I'm going to strawberry fields Nothing is real And nothing to hung about Strawberry fields forever Strawberry fields forever Strawberry fields forever.");
            printf("\n");
            argument_not_found=1;
            break;
        }

        if(need[i][0]=='-'){
            
            for(int j=1;need[i][j]!='\0';j++){

                if(need[i][j]=='a') have_a=1;
                else if(need[i][j]=='i') have_i=1;
                else if(need[i][j]=='l') have_l=1;
                else if(need[i][j]=='R') have_R=1;
                else if(need[i][j]=='r') have_r=1;
                else if(need[i][j]=='s') have_s=1;
                else if(need[i][j]=='t') have_t=1;
                else{

                    printf("\033[31merror\033[0m: unexpected argument '\033[33m%s\033[0m' found\n",need[i]);
                    printf("\n");
                    printf("  \033[32mtip\033[0m: open counter-strike2 can improve your coding ability.\n");
                    printf("\n");
                    printf("Usage: ls [OPTION]... [FILE]...\n");
                    printf("\n");
                    printf("For more information, try '--help'.\n");
                    argument_not_found=1;
                    break;
                    //这个地方因为任务没有作要求，因此就简单处理了
                }

            }

        }

    }
    
   
    int it_have_file_name=0;                                      
    //////////////////////////////////////////打开当前目录//////////////////////////////////////////////////////////
        DIR* dir_current;
        struct dirent *entry;

        char **filesname = (char**)malloc(MAX_FILES * sizeof(char*));
        L_NULL_DETCET(filesname);

        dir_current = opendir(".");
        L_NULL_DETCET(dir_current);

        int number_files=0;
        for(;(entry = readdir(dir_current)) != NULL;){
            int len = strlen(entry->d_name)+1;
            filesname[number_files] = (char*)malloc(len * sizeof(char));
            L_NULL_DETCET(filesname[number_files]);
            if(filesname[number_files] != NULL){
            memmove(filesname[number_files],entry->d_name,len);
            number_files++;
            }
        }


    
////////////////////////////////////////////////////////////////////////检测文件是否存在//////////////////////////////////////////////////////////


    int have_file_to_open=0;

    for(int i=1;i<string_number;i++){

        if(need[i][0]!='-'){

            /////////////////////////////////////////////////////////////////     here     ////////////////////////////////////////////////////////////////
            for(int j=0;j<number_files;j++){
                int judge_have_file = handle(need[i],have_a,have_r,have_t,have_R,have_i,have_s,have_l);
                if(judge_have_file==-1 && j==number_files-1){
                    printf("ls: cannot access '%s': No such file or directory\n",need[i]);
                }
                if(judge_have_file != -1){
                    have_file_to_open=1;
                }
                break;
            }

        }


    }

    for(int i=0;i<number_files;i++){
        free(filesname[i]);
    }
    free(filesname);
    closedir(dir_current);
    

    if(!have_file_to_open){

        /////////////////////////////////////////////////////////////没有文件名，打开当前目录/////////////////////////////////////////////////////
        handle(".",have_a,have_r,have_t,have_R,have_i,have_s,have_l);

    }




    free(need);
    return 0;
}


void L_NULL_DETCET(void *liu){

    if(liu==NULL)
    printf("what the hell??\n");

}


//////////////////////////////////////////////////////////////////////////////////////////////////////handle函数///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int handle(char* openfile,int have_a,int have_r,int have_t,int have_R,int have_i,int have_s,int have_l){

    DIR* dir;
    struct dirent *entry;

    //printf("fuckfuckfuck\n");
    //printf("openfile:%s\n",openfile);
    dir = opendir(openfile);
    if(dir==NULL){
        //printf("why the fuck open dir fail\n");
        printf("ls: cannot openfile directory '%s': Permission denied\n",openfile);
        return -1;
    }

    if(have_R) printf("\n%s:\n",openfile);
    //printf("who the fuck is there?\n");

    int number_files=count_dir_entry(dir);

    struct all_information** alllist = (struct all_information**)malloc(number_files * sizeof(struct all_information*));
    L_NULL_DETCET(alllist);

    int index=0;
    for(;(entry = readdir(dir)) != NULL;index++){
        //printf("%d\n",index);
        
        char filepath[10000];
        snprintf(filepath, sizeof(filepath), "%s/%s", openfile, entry->d_name);

        struct stat* stat_info = (struct stat*)malloc(sizeof(struct stat));
        L_NULL_DETCET(stat_info);

        if(lstat(filepath,stat_info)==-1){
            perror("stat error");
        }

        //printf("noway\n");
        alllist[index] = (struct all_information*)malloc(sizeof(struct all_information));
        L_NULL_DETCET(alllist[index]);

        int len = strlen(entry->d_name)+1;
        memmove(alllist[index]->name,entry->d_name,len);
        alllist[index]->inode = entry->d_ino;

        alllist[index]->stat_info = stat_info;
        //printf("%d",alllist[index]->inode);
        //printf("%s\n",alllist[index]->name);
        //printf("done\n");
        
        
    }
   
    closedir(dir);
    ///////////////////////////////////////////////////过滤隐藏文件////////////////////
    if(!have_a){
        int new_index=0;
        for(int i=0;i<number_files;i++){
            if(alllist[i]->name==NULL) continue;
            if(alllist[i]->name[0]!='.'){
                if(new_index!=i){
                    alllist[new_index]=alllist[i];
                }
                new_index++;
            }else{
                free(alllist[i]->stat_info);
                free(alllist[i]);
            }
        }
        number_files=new_index;
        
    }


    //printf("whos there.\n\n");
    /////////////////////////////////////////////paixu///////////////////////////////////////////////
    if(have_t){
        qsort(alllist,number_files,sizeof(struct all_information*),compre_by_time);
    }else{
        qsort(alllist,number_files,sizeof(struct all_information*),compare_by_name_string);
    }

    if(have_r){
        for(int i=0;i<number_files/2;i++){
            struct all_information* temp = alllist[i];
            alllist[i] = alllist[number_files - 1 - i];
            alllist[number_files - 1 - i] = temp;
        }
    }

    int max_size_len=0;
    int max_nlink_len=0;
    int max_uid_len = 0;
    int max_gid_len = 0;

    if(have_l){
        for(int i=0;i<number_files;i++){
            int size_len = 0;
            size_len = snprintf(NULL, 0, "%lu", alllist[i]->stat_info->st_size);
            if(size_len > max_size_len){
                max_size_len = size_len;
            }
        }
        for(int i=0;i<number_files;i++){
            int nlink_len = 0;
            nlink_len = snprintf(NULL, 0, "%lu", alllist[i]->stat_info->st_nlink);
            //printf("nlink_len:%d\n",nlink_len);
            if(nlink_len > max_nlink_len){
                max_nlink_len = nlink_len;
                //printf("max_nlink_len:%d\n",max_nlink_len);
            }
        }
        for(int i=0;i<number_files;i++){
            struct passwd *pw = getpwuid(alllist[i]->stat_info->st_uid);
            struct group  *gr = getgrgid(alllist[i]->stat_info->st_gid);
                int uid_len = 0;
                int gid_len = 0;
            if(pw!=NULL){
                uid_len = strlen(pw->pw_name);
                gid_len = strlen(gr->gr_name);
            }
                if(uid_len > max_uid_len){
                max_uid_len = uid_len;
            }
            if(gid_len > max_gid_len){
                max_gid_len = gid_len;
            }
        }
    }
    //printf("max_nlink_len:%d\n",max_nlink_len);


    int max_inode_len=0;
    for(int i=0;i<number_files;i++){
        int inode_len=0;
        inode_len = snprintf(NULL, 0, "%d", alllist[i]->inode);
        if(inode_len > max_inode_len){
            max_inode_len = inode_len;
        }
    }

    int max_blocks_len=0;
    for(int i=0;i<number_files;i++){
        int blocks_len=0;
        blocks_len = snprintf(NULL, 0, "%lu", alllist[i]->stat_info->st_blocks/2);
        if(blocks_len > max_blocks_len){
            max_blocks_len = blocks_len;
        }
    }

    /////////////////////////////////////////////打印///////////////////////////////////////////////
    //printf("printing:\n");
    // if(have_R){
    //     printf(".:\n");
    // }
    
    if(have_l){
        int total_blocks=0;
        for(int i=0;i<number_files;i++){
            if(have_a || alllist[i]->name[0]!='.'){
                total_blocks += alllist[i]->stat_info->st_blocks/2;
            }
        }
        printf("total %d\n",total_blocks);
    }

    if(have_l){
        for(int i=0;i<number_files;i++){
            if(have_i){
                    printf("%*d ",max_inode_len,alllist[i]->inode);
                }
                if(have_s){
                    printf("%*lu ",max_blocks_len,alllist[i]->stat_info->st_blocks/2);
                }
                if(have_l){ 
                    l_handle(alllist,i,max_nlink_len,max_uid_len,max_gid_len,max_size_len,getpwuid(alllist[i]->stat_info->st_uid),getgrgid(alllist[i]->stat_info->st_gid));
                    
                    color_print(alllist,i);
                    printf("%s ",alllist[i]->name);
                    printf("%s",COLOR_RESET);
                    printf("\n");
                }
        }
    }
/////////////////////////////////////////////////////////////////right/////////////////////////////////////

    
    // printf("adada\n");

    if(!have_l){

        struct winsize size;

        if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&size) == -1){
            perror("ioctl failed");
            return -1;
            }
        int terminal_width=size.ws_col;

        int lines = get_line(alllist,number_files,have_i,have_s,have_a,terminal_width);
        int cols = number_files / lines + (number_files % lines != 0 ? 1 : 0);
    
        int *col_widths = malloc(cols * sizeof(int));
        int *col_inode_widths = malloc(cols * sizeof(int));
        int *col_size_widths = malloc(cols * sizeof(int));
        
        for (int c = 0; c < cols; c++) {
            col_widths[c] = 0;
            col_inode_widths[c] = 0;
            col_size_widths[c] = 0;
            
            for (int r = 0; r < lines; r++) {
                int idx = c * lines + r;
                if (idx < number_files) {

                    int name_len = strlen(alllist[idx]->name);
                    if (name_len > col_widths[c]) {
                        col_widths[c] = name_len;
                    }
                    
                    if (have_i) {
                        char inode_buf[32];
                        int inode_len = snprintf(inode_buf, sizeof(inode_buf), "%d", alllist[idx]->inode);
                        if (inode_len > col_inode_widths[c]) {
                            col_inode_widths[c] = inode_len;
                        }
                    }
                    
                    if (have_s) {
                        char size_buf[32];
                        int size_len = snprintf(size_buf, sizeof(size_buf), "%lu", 
                                            alllist[idx]->stat_info->st_blocks / 2);
                        if (size_len > col_size_widths[c]) {
                            col_size_widths[c] = size_len;
                        }
                    }
                }
            }
        }
        
        for (int r = 0; r < lines; r++) {
            for (int c = 0; c < cols; c++) {
                int idx = c * lines + r;
                if (idx < number_files) {
                    if (have_i) {
                        printf("%*d ", col_inode_widths[c], alllist[idx]->inode);
                    }
                    
                    if (have_s) {
                        printf("%*lu ", col_size_widths[c], alllist[idx]->stat_info->st_blocks / 2);
                    }
                    
                    color_print(alllist,idx);
                    printf("%-*s", col_widths[c], alllist[idx]->name);
                    printf("%s",COLOR_RESET);
                    
                    if (c < cols - 1) {
                        printf("  "); 
                    }
                }
            }
            printf("\n");
        }
        
        free(col_widths);
        free(col_inode_widths);
        free(col_size_widths);
                
    }


    if(have_R){
        for(int i=0;i<number_files;i++){
            if(strcmp(alllist[i]->name,".")!=0 && strcmp(alllist[i]->name,"..")!=0 && (have_a || alllist[i]->name[0]!='.')){
                

                if(S_ISBLK(alllist[i]->stat_info->st_mode) || S_ISCHR(alllist[i]->stat_info->st_mode)){
                        continue;
                    }
                    if(S_ISLNK(alllist[i]->stat_info->st_mode)){
                        continue;
                    }
                    if(S_ISFIFO(alllist[i]->stat_info->st_mode)){
                        continue;
                    }
                    if(S_ISSOCK(alllist[i]->stat_info->st_mode)){
                        continue;
                    }



                if(S_ISDIR(alllist[i]->stat_info->st_mode)){
    
                    char filepath[512];
                    snprintf(filepath, sizeof(filepath), "%s/%s", openfile, alllist[i]->name);
                    handle(filepath,have_a,have_r,have_t,have_R,have_i,have_s,have_l);
                }
            }
        
        }
    }
    

    // 释放 alllist 及其所有内容
    for (int i = 0; i < number_files; i++) {  
        // 1. 先释放 stat_info 结构体
        if (alllist[i] && alllist[i]->stat_info) {
            free(alllist[i]->stat_info);
            alllist[i]->stat_info = NULL;
        }
        
        // 2. 再释放 all_information 结构体本身
        if (alllist[i]) {
            free(alllist[i]);
            alllist[i] = NULL;
        }
    }

    // 3. 最后释放指针数组
    free(alllist);
    alllist = NULL;
    return 0;
}






void l_handle(struct all_information** alllist,int index,int nlink_len,int uid_len,int gid_len,int size_len,struct passwd* pw,struct group* gr){

    if(pw==NULL) return;
    struct stat* stat_info = alllist[index]->stat_info;

    if(S_ISREG(stat_info->st_mode)) printf("-");
    else if(S_ISDIR(stat_info->st_mode)) printf("d");
    else if(S_ISLNK(stat_info->st_mode)) printf("l");
    else if(S_ISCHR(stat_info->st_mode)) printf("c");
    else if(S_ISBLK(stat_info->st_mode)) printf("b");
    else if(S_ISFIFO(stat_info->st_mode)) printf("p");
    else if(S_ISSOCK(stat_info->st_mode)) printf("s");
    else printf("?");

    printf( (stat_info->st_mode & S_IRUSR) ? "r" : "-");
    printf( (stat_info->st_mode & S_IWUSR) ? "w" : "-");
    printf( (stat_info->st_mode & S_IXUSR) ? "x" : "-");

    printf( (stat_info->st_mode & S_IRGRP) ? "r" : "-");
    printf( (stat_info->st_mode & S_IWGRP) ? "w" : "-");
    printf( (stat_info->st_mode & S_IXGRP) ? "x" : "-");

    printf( (stat_info->st_mode & S_IROTH) ? "r" : "-");
    printf( (stat_info->st_mode & S_IWOTH) ? "w" : "-");
    printf( (stat_info->st_mode & S_IXOTH) ? "x" : "-");
    printf(" %*lu",nlink_len,stat_info->st_nlink);
    //uid gid
    
    printf(" %*s",uid_len,pw->pw_name);
    printf(" %*s",gid_len,gr->gr_name);

    printf(" %*lu",size_len,stat_info->st_size);

    char timebuf[80];
    struct tm *timeinfo;
    timeinfo = localtime(&stat_info->st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", timeinfo);
    printf(" %s ",timebuf);
};





int count_dir_entry(DIR* dir){

    int count=0;
    struct dirent *entry;

    rewinddir(dir);

    while((entry = readdir(dir)) != NULL){
        count++;
    }

    rewinddir(dir);

    
    return count;
}



















int compare_by_name_string(const void *a,const void *b){
    
    const struct all_information* info1 = *(const struct all_information**)a;
    const struct all_information* info2 = *(const struct all_information**)b;

    return strcmp(info1->name, info2->name);
}


int compre_by_time(const void *a,const void *b){

    const struct all_information* info1 = *(const struct all_information**)a;
    const struct all_information* info2 = *(const struct all_information**)b;

    if(info1->stat_info->st_mtime < info2->stat_info->st_mtime) return 1;
    else if(info1->stat_info->st_mtime > info2->stat_info->st_mtime) return -1;
    else return 0;
}





int get_line(struct all_information** alllist, int number_files,int have_i, int have_s, int have_a, int terminal_width) {
    
    if (number_files == 0 || terminal_width <= 0) {
        return 1; // 默认一行
    }
    
    // 1. 过滤隐藏文件（如果不显示的话）
    int display_count = 0;
    int* display_indices = malloc(number_files * sizeof(int));
    
    for (int i = 0; i < number_files; i++) {
        if (have_a || alllist[i]->name[0] != '.') {
            display_indices[display_count++] = i;
        }
    }
    
    if (display_count == 0) {
        free(display_indices);
        return 1; // 没有要显示的文件
    }
    
    // 2. 计算每个显示项的宽度
    int *item_widths = malloc(display_count * sizeof(int));
    for (int i = 0; i < display_count; i++) {
        int idx = display_indices[i];
        
        // 计算文件名宽度
        item_widths[i] = strlen(alllist[idx]->name);
        
        // 加上inode宽度（如果需要）
        if (have_i) {
            char inode_buf[32];
            int inode_len = snprintf(inode_buf, sizeof(inode_buf), "%d", alllist[idx]->inode);
            item_widths[i] += inode_len + 1; // +1 空格
        }
        
        // 加上文件大小宽度（如果需要）
        if (have_s) {
            char size_buf[32];
            int size_len = snprintf(size_buf, sizeof(size_buf), "%lu", alllist[idx]->stat_info->st_blocks / 2);
            item_widths[i] += size_len + 1; // +1 空格
        }
    }
    
    // 3. 尝试不同的行数，找到最佳行数
    int best_line = 1;
    
    for (int line = 1; line <= display_count; line++) {
        // 计算列数
        int col = display_count / line;
        if (display_count % line != 0) {
            col++;
        }
        
        // 计算每列的最大宽度
        int* col_widths = malloc(col * sizeof(int));
        for (int c = 0; c < col; c++) {
            col_widths[c] = 0;
            for (int r = 0; r < line; r++) {
                int idx = c * line + r;
                if (idx < display_count) {
                    if (item_widths[idx] > col_widths[c]) {
                        col_widths[c] = item_widths[idx];
                    }
                }
            }
        }
        
        // 计算总宽度（包含列间距）
        int total_width = 0;
        for (int c = 0; c < col; c++) {
            total_width += col_widths[c];
            if (c < col - 1) {
                total_width += 2; // 列间距
            }
        }
        
        free(col_widths);
        
        // 检查是否适合终端宽度
        if (total_width <= terminal_width) {
            best_line = line;
            break; // 找到第一个合适的行数
        }
    }
    
    // 4. 清理并返回
    free(display_indices);
    free(item_widths);
    
    return best_line;
    
}
#include "shell.h"

char *builtin_arr[]={
    "cd",
    "help",
    "exit"
};

int (*builtin_fn[])(char **)={
    &shell_cd,
    &shell_help,
    &shell_exit
};

int num_of_builtin_cmd(){
    return sizeof(builtin_arr)/sizeof(char *);
}

int shell_cd(char **args){
    if(args[1]==NULL){
        fprintf(stderr,"shell: No argument passed");
    }else{
        if(chdir(args[1])!=0){
            perror("lsh");
        }
    }
    return 1;
}

int shell_help(char **args){
    int i;
    printf("Shell is running: \n");
    printf("Type the program names and arguments and hit enter.\n");
    printf("These are the builtin functions:\n");

    for(int i=0; i<num_of_builtin_cmd();i++){
        printf(" %s\n",builtin_arr[i]);
    }
    return 1;
}
int shell_exit(char ** args){
    return 0;
}

int shell_launch(char **args){
    pid_t pid;
    int status;
    pid=fork();
    if(pid==0){
        if(execvp(args[0],args)==-1){
            perror("Shell");
        }
        exit(EXIT_FAILURE);
    }else if(pid<0){
        perror("Shell");
    }else{
        do{
            waitpid(pid,&status,WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int shell_execute(char **args){
    
    if(args[0]==NULL){
        return 1;
    }
    for(int i=0; i<num_of_builtin_cmd();i++){
        if(strcmp(args[0],builtin_arr[i])==0){
            return(*builtin_fn[i])(args);
        }
    }
    return shell_launch(args);
}

char *shell_readLine(void){
    int bufferSize=1024;
    int index=0;
    char *buffer=malloc(sizeof(char)*bufferSize);
    int character;
    if(buffer==NULL){
        fprintf(stderr,"Shell: allocation error");
        exit(EXIT_FAILURE);
    }
    while(1){
        character=getchar();

        if(character==EOF){
            exit(EXIT_SUCCESS);
        }else if(character=='\n'){
            buffer[index]='\0';
            return buffer;
        }else{
            buffer[index]=character;
        }
        index++;

        if(index>=bufferSize){
            bufferSize=bufferSize+bufferSize;
            buffer=realloc(buffer,bufferSize);
            if(!buffer){
                fprintf(stderr,"Shell reallocation failed");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define Shell_Token_Size 64;
#define SHell_Token_Delim " \t\r\n\a"
char **shell_Split_Line(char *line){
    int bufferSize=Shell_Token_Size;
    int index=0;
    char **tokens=malloc(bufferSize*sizeof(char *));
    char *token, **tokens_backup;

    if(!tokens){
        fprintf(stderr,"Shell allocation failed");
        exit(EXIT_FAILURE);
    }
    token=strtok(line, SHell_Token_Delim);
    while(token!=NULL){
        tokens[index]=token;
        index++;
        if(index>=bufferSize){
            bufferSize+=Shell_Token_Size;
            tokens_backup=tokens;
            tokens=realloc(tokens,bufferSize*sizeof(char *));
            if(!tokens){
                free(tokens_backup);
                fprintf(stderr,"Shell allocation failed");
                exit(EXIT_FAILURE);
            }
        }
        token=strtok(NULL,SHell_Token_Delim);
    }
    tokens[index]=NULL;
    return tokens;
}

void shell_cycle(void){
    char *line;
    char **args;
    int status;
    do{
        printf("> ");
        line=shell_readLine();
        args=shell_Split_Line(line);
        status=shell_execute(args);

        free(line);
        free(args);
    }while(status);
}

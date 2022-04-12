#include <stdio.h>
#include <stdlib.h>

typedef struct horn{
    int noc; //number of horn clauses in the horn formula
    int p; //number of unique propositional atoms in the horn formula
    int* nt; //array representing the length of lhs of the implicants in each horn clause
    int** lhs; //array representing the lhs of the implicants in each horn clause
    int* rhs; //array representing the rhs of the implicants in each horn clause
}horn;

horn parse_input (){
    
    char str[20];
    printf("type input file name (e.g.: i2.txt): ");
    gets(str);
    horn formula;
    FILE *fptr;

   if ((fptr = fopen(str,"r")) == NULL){
       printf("Error! opening file");
       exit(1);
   }

    fscanf(fptr,"%d", &formula.p);
    fscanf(fptr,"%d", &formula.noc);
    char buffer;
    int j=0;
    int c=0;
    char rhsbuffer;
    formula.nt = (int *)malloc(formula.noc * sizeof(int));
    formula.rhs = (int *)malloc(formula.noc * sizeof(int));
    formula.lhs = (int **)malloc(1000*sizeof(int *));
	formula.lhs[0] = (int *)malloc(1000*sizeof(int *));
    while(fscanf(fptr,"%c", &buffer)==1){
        if(buffer=='>'){
            fscanf(fptr,"%c", &rhsbuffer);
            if(rhsbuffer=='T'){
                formula.rhs[c]=0;
            }
            else if(rhsbuffer=='F'){
                formula.rhs[c]=-1;
            }
            else{
                formula.rhs[c]=rhsbuffer-'0';
            }
            c++;
            j=0;
            formula.lhs[c] = (int *)malloc(1000*sizeof(int *));
        }
        else if(buffer=='^'||buffer=='\n'){

        }
        else{
            if(buffer=='T'){
                formula.lhs[c][j]=0;
            }
            else if(buffer=='F'){
                formula.lhs[c][j]=-1;
            }
            else{
                formula.lhs[c][j]=buffer-'0';
            }
            
            j++;
            formula.nt[c]=j;
        }
    }


    return formula;
}

int main(){
    
    horn hornformula=parse_input();
    for(int c=0; c<hornformula.noc; c++){
        printf("(");
        for(int t=0; t<hornformula.nt[c];t++){
            
            if(hornformula.lhs[c][t]==-1){
                printf("F");
            }
            else if(hornformula.lhs[c][t]==0){
                printf("T");
            }
            else{
                printf("p%d",hornformula.lhs[c][t]);
            }
            
            if(t!=hornformula.nt[c]-1)
            printf("^");
        }
        
        if(hornformula.rhs[c]==-1){
                printf(">F)");
            }
            else if(hornformula.rhs[c]==0){
                printf(">T)");
            }
            else{
                printf(">p%d)",hornformula.rhs[c]);
            }
        if(c!=hornformula.noc-1)
        printf("^");
    }
}
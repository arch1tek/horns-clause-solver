#include <stdio.h>
#include <stdlib.h>
int c[100]={0};
int a[9]={0};
int sat=1;

typedef struct horn{
    int noc; //number of horn clauses in the horn formula
    int p; //number of unique propositional atoms in the horn formula
    int* nt; //array representing the length of lhs of the implicants in each horn clause
    int** lhs; //array representing the lhs of the implicants in each horn clause
    int* rhs;
     //array representing the rhs of the implicants in each horn clause
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



int HORN_SAT(horn* h){
    
    horn formula=*h;
    int clauses=formula.noc;
    int atoms=formula.p;
    int checklhs[clauses];
    for (int i=0; i<clauses; i++){
        checklhs[i]=0;
    }
    sat=1;
    int flag=1;
    while(flag==1){
        for(int i=0; i<clauses;i++){
            if(c[i]==0){
                checklhs[i]=1;
                //check clause
                for(int j=0 ; j<formula.nt[i]; j++){
                    if(formula.lhs[i][j]==-1){
                        checklhs[i]=0; 
                        break;
                    }
                    else if(formula.lhs[i][j]==0){
                        checklhs[i]=1;
                        continue;
                    }
                    else{
                        if(a[formula.lhs[i][j]-1]==0){
                            checklhs[i]=0; 
                            break;
                        }
                    }

                }
                if(checklhs[i]==1){
                    c[i]=1;
                    int p=formula.rhs[i];
                    if(p==-1){
                        sat=0;
                        flag=0;
                        break;
                    }
                    else if (p==0){
                        continue;
                    }
                    else{
                        a[p-1]=1;
                    }
                }
            }

        }
        //check flag
        flag=0;
        for(int i=0; i<clauses;i++){
            if(c[i]==0){
                for(int j=0; j<formula.nt[i]; j++){
                    if(formula.lhs[i][j]!=-1&&formula.lhs[i][j]!=0)
                    if(a[formula.lhs[i][j]-1]==1){
                        flag=1;
                    }
                }
            }
        }
        
    }
    return sat;
}

void HORN_assignment(horn* h){
    horn formula=*h;
    if(sat==0){
        printf("The given horn formula is not satisfiable");
    }
    else {
        for(int i=0; i<formula.p;i++){
            if(a[i]==1){
                printf("T ");
            }
            else{
                printf("F ");
            }
        }}
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
    if(HORN_SAT(&hornformula)==1){
        printf("\nThe given horn formula is satisfiable\n");
    }
    else{
        printf("\nThe given horn formula is not satisfiable\n");
    }
    HORN_assignment(&hornformula);
}
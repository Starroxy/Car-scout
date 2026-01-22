// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#define ROW 30
#define COL 30
int a[ROW][COL],b[ROW][COL],c[ROW][COL]={0};
int r1,c1,r2,c2;
void scanArray();
void displayArray();
void add();
void mult();
void sub();
void menu();
void main() {
    int i,j,k;
    int choice;
    scanArray();
    displayArray();
    
    while(1){
            menu();
            printf("enter the choice:");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                       add();
                       break;
                case 2:
                       sub();
                       break;
                case 3: 
                       mult();
                       break;
                case 4:
                      exit(0);
                      break;
                default:
                      printf("\ninvalid choice");
            }
    }
    
    
}
void menu(){
    printf("\n1-------add;");
    printf("\n2-------sub;");
    printf("\n3-------mul;");
    printf("\n4-------exit;");
    // printf("\n5-------exit:");
    
}
void scanArray(){
    int i,j;
    printf("\n Entr the number of rows and colum  u need for the first array");
    scanf("%d %d",&r1,&c1);
    printf("\n Entr the number of rows and colum  u need for the second array");
    scanf("%d %d",&r2,&c2);
    if(r1>30 || c1>30 || r2>30 || c2>30){
        printf("size can not be above 30\n");
        exit(0);
        
    }else{
        printf("\n %d value for first matrix:\n",r1*c1);
        for (i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                printf("\n enter the value of a[%d][%d]",i,j);
                scanf("%d",&a[i][j]);
                }
        }
         printf("\n %d value for second matrix",r2*c2);
        for (i=0;i<r2;i++){
            for(j=0;j<c2;j++){
                printf("\n enter the value of a[%d][%d]",i,j);
                scanf("%d",&b[i][j]);
                }
        }
    }
}

void displayArray(){
    int i,j;
    printf("\nfirst matirx is as follow:");
    for (i=0;i<r1;i++){
        for (j=0;j<c1;j++){
            printf("%d\t",a[i][j]);
            }
        printf("\n");
    }
    printf("\n");
     printf("second matirx is as follow:");
    for (i=0;i<r2;i++){
        for (j=0;j<c2;j++){
            printf("%d\t",b[i][j]);
            }
        printf("\n");
    }
    printf("\n");
}

void add(){
    int i,j;
    if((r1==r2) && (c1==c2)){
        for (i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                c[i][j]=a[i][j]+b[i][j];
                
            }
        }
        printf("\n the addition is as follows\n");
        for (i=0;i<r1;i++){
            for (j=0;j<c1;j++)
            {
                printf("%d\n",c[i][j]);
            }
            printf("\n");
        }
    }else{
        printf("\n matrix are not comfortable");
    }
}

void sub() {
    int i,j;
    if((r1==c1) && (c1==c2)){
        for(i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                c[i][j]=a[i][j]-b[i][j];
            }
        }
          printf("\n the substraction is as follows\n");
        for (i=0;i<r1;i++){
            for (j=0;j<c1;j++)
            {
                printf("%d",c[i][j]);
            }
            printf("\n");
        }
    }else{
        printf("\n matrix are not comfortable");
    }
    }
  


void mult() {
    int i,j,k;
    if(c1==r2){
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                for(k=0;k<3;k++){
                    c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
                }
            }
        }
        printf("\n resultant matrix is\n");
        printf("%d",c[i][j]);
    }else{
        printf("not posible to multiply matrix");    
    }
    
}

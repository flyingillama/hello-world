#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
int main(int argc, char **argv){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int i,j;
//  int tab[a][b];
    char opt[]={'0','1','-'};
    srand((unsigned int)time(NULL));
    for(i=0;i<a;++i){
        printf("\n");
        for(j=0;j<b;++j)
            printf(" %c ",opt[rand()%3]);
    }
    printf("\n");
    return 0;
}
/*    for(i=0;i<a;++i)
        for(j=0;j<b;++j)
            tab[i][j]=(rand()%3);*/

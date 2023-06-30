#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int MAXR, MAXC;

struct kurzor{
    int x;
    int y;
    int pocRiadkov;
    int *r;
};

char ** vytvormaticuT(int r, int s){
    char **a;
    a = new char *[r];
    for(int i = 0; i < r; ++i){
        a[i] = new char[s];
        for(int j = 0; j < s; j++) a[i][j] = 0;
    }
    return a;
}
void zmazmaticuT(char **a, kurzor &k){
    for (int i = 0; i < MAXR; ++i) {
        delete[] a[i];
    }
    delete[] a;
    delete[] k.r;
}

void nacitajmaticuT(char **a, kurzor &k){
    for (int i = 0; i <= MAXR; ++i) {
        a[i][0] = '\n';
        a[i][1] = 0;
        k.r[i] = strlen(a[i]);
    }
    int r = 0;
    while(true){
        fgets(a[r], MAXC + 2, stdin);
        if (strcmp(a[r], "END\n") == 0){
            for (int i = 0; i < MAXC + 2; ++i) a[r][i] = 0;
            return;
        }
        k.r[r] = strlen(a[r]);
        k.pocRiadkov++;
        r++;
    }
}

void vypismaticuT(char **a, kurzor &k, FILE *f) {
    fputs("START\n", f);
    for(int r = 0; r < k.pocRiadkov; ++r){
        fprintf(f, "%s", a[r]);
    }
    fputs("END\n", f);
}

void deletechar(char **a, kurzor &k){
    if (k.x == k.r[k.y] -1) return;
    for (int i = k.x; i < k.r[k.y]; ++i) {
        a[k.y][i] = a[k.y][i+1];
    }
    k.r[k.y]--;
    if(k.r[k.pocRiadkov-1] == 1) k.pocRiadkov--;
}

void insertchar(char **a, kurzor &k, char c){
    if (k.r[k.y] == MAXC + 1) return;
    for (int i = k.r[k.y]+1; i >= k.x; --i) {
        a[k.y][i+1] = a[k.y][i];
    }
    a[k.y][k.x] = c;
    k.r[k.y] = strlen(a[k.y]);
}

void kright(kurzor &k){
    //if ((k.y == MAXR - 1 && k.x == MAXC) || (k.y == MAXR - 1 && k.x == k.r[k.y])) return;
    if (k.y == MAXR -1 && (k.x == MAXC || k.x == k.r[k.y]-1)) return;
    if (k.y != MAXR - 1 && k.x == k.r[k.y]-1){
        k.y++;
        k.x = 0;
    } else {
        k.x++;
    }
}

void kleft(kurzor &k){
    if (k.y == 0 && k.x == 0) return;
    if (k.x == 0){
        k.y--;
        k.x = k.r[k.y]-1;
    } else {
        k.x--;
    }
}

int main(){
    FILE *f;
    char **text;
    char s[20], p[20];
    kurzor k; k.x = 0; k.y = 0; k.pocRiadkov= 0; k.r = new int[MAXR];
    for (int i = 0; i < MAXR; ++i) k.r[i] = 0;
    scanf("MAXR %d MAXC %d\n", &MAXR, &MAXC);
    text = vytvormaticuT(MAXR+1, MAXC+2);
    scanf("START\n");
    nacitajmaticuT(text, k);


    while (true){
        scanf("%19s", s);
        switch (s[0]) {
            case 'L':
                kleft(k);
                printf("LEFT %d %d\n", k.y, k.x);
                break;
            case 'R':
                kright(k);
                printf("RIGHT %d %d\n", k.y, k.x);
                break;
            case 'I':
                p[0] = getc(stdin); p[1] = getc(stdin); p[2] = getc(stdin); p[3] = getc(stdin);
                cout << "INSERT " << k.y << " " << k.x << endl;
                insertchar(text, k, p[2]);
                break;
            case 'D':
                cout << "DELETE " << k.y << " " << k.x << endl;
                deletechar(text, k);
                break;
            case 'P':
                scanf("%s", p);
                if (p[0] == '-'){
                    f = stdout;
                    vypismaticuT(text, k, f);
                }
                else{
                    f = fopen(p,"a");
                    vypismaticuT(text, k, f);
                    fclose(f);
                }
                break;
            case 'E':
                zmazmaticuT(text, k);
                return 0;
            default:
                break;
        }
    }

}
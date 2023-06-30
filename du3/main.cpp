#include <cstdio>
#include <cstring>
using namespace std;

int MaxR, MaxC;
char key[7];
char **txt;

void start(){
    char c;
    scanf("%c", &c);
    txt = new char* [MaxR];
    for (int i = 0; i < MaxR; i++)
    {
        txt[i] = new char[MaxC+1];
        for (int j = 0; j < MaxC+1; j++)
        {
            scanf("%c", &c);
            if(c != '\n')
            {
                txt[i][j] = c;
                txt[i][j+1] = 0;
            }
            else
            {
                for(int u = j; u < MaxC+1; u++) txt[i][u] = 0;
                break;
            }
        }
        if(!strcmp(txt[i], "END"))
        {
            delete[] txt[i];
            MaxR = i;
            break;
        }
    }
}

void print(){
    char name[21];
    scanf("%s", name);

    FILE *f;
    if (!strcmp(name, "-")) f = stdout;
    else f = fopen(name, "a");

    fprintf(f, "START\n");
    for(int i = 0; i < MaxR; i++) fprintf(f, "%s\n", txt[i]);
    fprintf(f, "END\n");
}

int main()
{
    for(int i = 0; i < 2; i++)
    {
        scanf("%s", key);
        if(!strcmp(key, "MAXR")) scanf("%d", &MaxR);
        if(!strcmp(key, "MAXC")) scanf("%d", &MaxC);
    }


    while (true)
    {
        scanf("%s", key);
        if(!strcmp(key, "START"))
        {
            start();
            break;
        }
    }

     while (true)
    {
        scanf("%s", key);
        if(!strcmp(key, "PRINT")) print();
        // if(!strcmp(key, "LEFT")) left();
        // if(!strcmp(key, "RIGHT")) right();
        // if(!strcmp(key, "DELETE")) del();
        // if(!strcmp(key, "INSERT")) ins();
        if(!strcmp(key, "EXIT")) break;
    }

    //UVOLNENIE PAMETE
    for(int i = 0; i < MaxR; i++)
    {
        delete[] txt[i];
    }
    delete[] txt;
}
#include <iostream>
using namespace std;

// struct pre zavazia
struct zavazie
{
    int hmotnost, pocet;
};

// GLOBALNE PREMENNE
int n, m, pouzite;
bool a = false;
zavazie *zavazia;
int *naj;

// generovanie postupnosti zavazi
void generuj(int tmp[], int j, int vaha, int p){
    if(j < n)
    {
        for(int i = 0; i < zavazia[j].pocet; i++)
        {
            vaha += zavazia[j].hmotnost;

            if(vaha <= m)
            {
                tmp[j]++;
                if((tmp[j] + p) >= pouzite) return;
                if(vaha == m)
                {
                    pouzite = tmp[j] + p;
                    naj = tmp;
                    tmp = new int[n];
                    a = true;
                    return;
                }
            }
            else generuj(tmp, j+1, vaha-zavazia[j].hmotnost, p+tmp[j]);
        }
        generuj(tmp, j+1, vaha, p+tmp[j]);
    }
}

int main(){
    // nacitaj pocet druhov zavazi a pozadovanu hmotnost
    cin >> n >> m;
    pouzite = n*m;

    // vytvor a nacitaj pole zavazi
    zavazia = new zavazie[n];

    for(int i = 0; i < n; i++)
    {
        cin >> zavazia[i].hmotnost;
        cin >> zavazia[i].pocet;
    }

    // vytvor a vynuloj polia pre najlepsie a docasne rozlozenie zavazi
    int *tmp;
    //naj = new int[n];
    tmp = new int[n];

    for(int i = 0; i < n; i++) tmp[i] = 0;

    // generuj postupnosti zavazi
    generuj(tmp, 0, 0, 0);

    // vypis
    if(a)
    {
        cout << "Pocet pouzitych zavazi : " << pouzite << endl;
        for(int i = 0; i < n; i++) cout << "Zavazie " << zavazia[i].hmotnost << ": " << naj[i] << endl;
    }
    else cout << "Hmotnost sa neda vytvorit" << endl;

    // uvolnim pamet
    delete[] tmp;
}
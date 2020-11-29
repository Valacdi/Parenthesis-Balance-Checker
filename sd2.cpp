#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;

struct node
{
    char data;
    node* next;
};
class linkedList
{
private:
    node* head;
    vector<int> indeksas;
public:
    linkedList()  ///konstruktorius
    {
        head = NULL;
    }
    int ArTuscia();
    void push(char data);
    void pop();
    int ArSubalansuota(string reiksme, int kur);
    char top();
    void StekoValymas();
    void display();
};

void linkedList::push(char data) ///idejimas i gala
{
    node* temp = new node; ///iskiria vieta atmintyje naujam "node" tipo kintamajam ir sukuria rodykle "temp", rodancia i nauja elementa
    temp->data = data; ///priskiria reiksmes naujam elementui
    temp->next = NULL; ///rodykle i null
    if (ArTuscia()) ///jeigu tiesinis sarasas tuscias
    {
        head = temp; ///galvute rodys i sukurta elementa
        return; ///viskas kas po return bus ignoruojama, cia baigiasi funkcija jeigu suveikia ifas
    }
    temp->next = head;
    head = temp; ///temp tampa stacko top
}

void linkedList::pop()
{
    node* temp = head; ///sukuria pagalbine "temp" rodykle ir ji rodo i pirma elementa
    if (ArTuscia())
    {
        cout << "Tuscias stackas!!!!!";
        return;
    }
    head = head->next; ///priskiriam antra node head'ui
    delete temp; ///atminties salinimas
}

char linkedList::top()
{
    if (!ArTuscia())
        return head->data;
}

int linkedList::ArTuscia()
{
    if (head == NULL)
        return 1;
    else
        return 0;
}

void linkedList::StekoValymas()
{
    while (ArTuscia() == 0) ///tikriname ar tuscias stackas trinimui
    {
        pop(); ///jeigu taip, triname po viena elementa
    }
}

void linkedList::display()
{
    node* temp = head; ///sukuria pagalbine "temp" rodykle ir ji rodo i pirma elementa
    while (temp != NULL)
    {
        cout << temp->data << "\t";
        temp = temp->next; ///rodykle rodo i sekanti elementa
    }
}

int linkedList::ArSubalansuota(string reiksme, int kur)
{

    for (int i = 0; i < reiksme.length(); i++)
    {
        if (reiksme[i] == '(') ///suradome (
        {
            push(reiksme[i]); ///pushinam i stacka, ieskom jam poros
            indeksas.push_back(i);
        }
        else if (reiksme[i] == ')') ///suradome )
        {
            if (ArTuscia() || !((top() == '(' && reiksme[i] == ')'))) ///ar tuscias stackas? ar head'as turi (? (ar paskutinis stacko elementas)
            {
                cout << "Nr. " << kur+1 << "\t";
                for (int j = 0; j < reiksme.size(); j++)
                {
                    if (j != i)
                        cout << reiksme[j];
                    else
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0a);
                        cout << reiksme[i];
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                    }
                }
                cout << endl;
                return 0; ///jeigu kuris nors true tada baigiam, nesubalansuota
            }
            else
            {
                pop(); ///jeigu nesuveike if salygoje, tada triname ( ir ), ieskome toliau
                indeksas.pop_back();
            }
        }
    }
    if (ArTuscia() == 1) ///ar tuscias stackas?
    {
        return 1; ///jeigu taip tada subalansuota
    }
    else
    {
        cout << "Nr. " << kur+1 << "\t";
        for (int j = 0; j < reiksme.size(); j++)
        {
            if (j != indeksas[0])
                cout << reiksme[j];
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0a);
                cout << reiksme[indeksas[0]];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            }
        }
        cout << endl;
        indeksas.clear();
        StekoValymas();
        return 0; ///rodome kad nesubalansuota
    }
}

void skaityti(string failas, string reiksmes[], int& kiekis);

int main()
{
    int pasirinkimas, kiekis = 0, kur = 0, KuriEilute[10];
    string failas, reiksmes[10], KuriReiksme[10]; ///max 10 reiksmiu
    linkedList listas;

    cout << "NUOSTABUS REISKINIU TIKRINTUVAS\n";
    do
    {
        cout << "\n================================================\n";
        cout << "Meniu: \n";
        cout << "1. Nuskaityti dokumenta\n";
        cout << "2. Baigti programa\n";
        cout << "================================================\n";
        cout << "Pasirinkite: ";
        cin >> pasirinkimas;

        switch (pasirinkimas)
        {
        case 1:
            cout << "Iveskite dokumento pavadinima (dokumentas turi buti tame paciame kataloge kaip ir programa)\n";
            cin >> failas;
            skaityti(failas, reiksmes, kiekis);
            cout << "Dokumentas nuskaitytas\n";
            cout << "Pradedamas tikrinimas...\n";
            cout << "-------------------------------\n";
            cout << "-- Blogu reiskiniu suvestine --\n";
            cout << "-------------------------------\n";
            cout << "-- Eil. nr. | Reiskinys      --\n";
            cout << "-------------------------------\n";
            for (int i = 0; i < kiekis; i++)
            {
                if (listas.ArSubalansuota(reiksmes[i], i) == 0) ///jeigu reiksme grazina 0 tada jis nesubalansuotas
                {
                    kur++;
                }
                if (i + 1 == kiekis && kur != 0)
                {
                    cout << "\nDarbas baigtas.\n";
                }
            }
            if (kur == 0)
            {
                cout << "\n-------------------------------\n";
                cout << "-- Blogu reiskiniu nerasta!  --\n";
                cout << "-------------------------------\n";
                cout << "\nDarbas baigtas.\n";
            }
        case 2:
            break;
        default:
            cout << "Blogas pasirinkimas!!!\n";
        }
    } while (pasirinkimas != 2);

    return 0;
}

void skaityti(string failas, string reiksmes[], int& kiekis)
{
    ifstream fd(failas);

    while (!fd.eof())
    {
        fd >> reiksmes[kiekis];
        kiekis++;
    }
    fd.close();
}

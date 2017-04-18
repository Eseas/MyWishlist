#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* Global variables */
const char Data[] = "Data.txt";
const char BudgetData[] = "Budget.txt";
unsigned short q = 0;   /* Quantity of items */
float total = 0,
      budget = 0;
string Title;
bool NoDel,
     NoEdit;

struct TOne {
    unsigned int no;
    float priceTag;
    string name;
};

void Delete (TOne D[]),
     Edit (TOne D[]),
     New (TOne D[]),
     Refresh (TOne D[]),
     Total (TOne D[]),
     Budget (TOne D[]),
     Intro (TOne D[]);

int main(){
    setlocale (LC_ALL, "Lithuanian");

    TOne D[256];

    ifstream PB ("Budget.txt");
    PB >> budget;

    Refresh(D);

    ofstream RB ("Budget.txt");
    RB << budget;

    /* WRITING TO THE FILE: */
    ofstream R ("Data.txt");
    R << Title << endl;
    for (int i = 0; i < q; i++)
        R << D[i].no << ' ' << D[i].name << ' ' << D[i].priceTag;
    return 0;
}



void New (struct TOne D[]){
    char a;
    ofstream R (Data, ios::app);
    while(a != 'C'){
        cout << "\n(New) Enter name & price: ";
        q++;
        cin >> D[q].name >> D[q].priceTag;
        R << left << setw(7) << q << setw(25) << D[q].name << fixed
          << setprecision(2) << D[q].priceTag << endl;

        cout << "New [N] / Close [C] ";
        cin >> a;

        if (a == 'C') Refresh(D);
        }
}

void Delete (struct TOne D[]) {
    char b;
    if (D[0].no == 0) {cout << "Nothing to delete!" << endl; NoDel = true; Refresh(D);}
    while(b != 'X'){
        int noD;
        cout << "\n(Delete) Which one? ";
        cin >> noD;
        q--;

        // istrinimo algoritmas:
        D[noD - 1].name = D[noD].name;
        D[noD - 1].no = D[noD].no;
        D[noD - 1].priceTag = D[noD].priceTag;

        for (int j = noD; j < q; j++) {
            D[j].name = D[j + 1].name;
            D[j].no = D[j + 1].no;
            D[j].priceTag = D[j + 1].priceTag;

        }

        ofstream R (Data);
        R << Title << endl;
        for (int j = 0; j < q; j++){
            D[j].no = j + 1;
            R << left << setw(7) << D[j].no << setw(25) << D[j].name << D[j].priceTag << endl;
        }

        cout << "Delete [D] / Close [X] ";
        cin >> b;
        if (b == 'X') Refresh(D);
        }
}
void Edit (TOne D[]){
    int noE;    // Redagavimui numeris
    char what;
    char close;
    if (D[0].no == 0) {cout << "Nothing to edit!" << endl; NoEdit = true; Refresh(D);}

    while (close != 'C'){
    cout << endl << "(Edit) Which one? "; cin >> noE;
    cout << "What to edit?" << " Name [N] / Price [P] / Both [B] "; cin >> what;


    switch (what){
        case 'N':
            cout << "Enter new name: ";
            cin >> D[noE - 1].name;
            cout << "\nEdited." <<endl << "\nContinue editing [E] / Close [C] ";
            cin >> close;
            break;

        case 'P':
            cout << "Enter new price: ";
            cin >> D[noE - 1].priceTag;
            cout << "\nEdited." <<endl << "\nContinue editing [E] / Close [C] ";
            cin >> close;
            break;

        case 'B':
            cout << "Enter new name & price: ";
            cin >> D[noE - 1].name;
            cin >> D[noE - 1].priceTag;
            cout << "\nEdited." << endl << "\nContinue editing [E] / Close [C] ";
            cin >> close;
            break;
    }
        ofstream R (Data);
        R << Title << endl;
        for (int j = 0; j < q; j++){
            D[j].no = j + 1;
            R << left << setw(7) << D[j].no << setw(25) << D[j].name << D[j].priceTag << endl;
        }
        if (close == 'C') Refresh(D);
    }
}

void Intro () {
    ifstream PD (Data);
    cout << " Tips & Hints: \tUse Caps Lock! \n\t\tUse \".\" instead of \",\"!" << endl << endl;
    cout << "——————————————————————————————————————————————————" << endl;
}

void Refresh(struct TOne D[]){

    cout << "\n\n\n\n\n\n\n\n\n";
    Intro();

    ifstream PD (Data);

    PD >> Title;
    cout << "\t\t" << Title << endl;

    D[0].no = 0;

      /* Quantity of items */
    q = 0;
    PD >> D[q].no >> D[q].name >> D[q].priceTag;

    if (D[0].no == 0) cout << "\n\tThe list is empty!\n" << endl;
    else while(!PD.eof()){   /* DISPLAYING THE LIST */
        cout << " " << D[q].no << left << setw(2) << left << "."
             << setw(17) << D[q].name <<  setw(7) << left << fixed
             << setprecision(2) << setw(8) << right << D[q].priceTag << setw(5) << right << "Lt." << endl;
        q++;
        PD >> D[q].no >> D[q].name >> D[q].priceTag;
    }





    Total(D);  /* Displaying overview: */
    cout << "——————————————————————————————————————————————————" << endl;

    cout << endl << setw(17) << right << "Total amount:" << setw(11) << right << total
         << setw(5) << right <<"Lt.";
    cout << endl << setw(17) << right << "Your budget:" << setw(11) << right << budget
         << setw(5) << right <<"Lt.";

    if (total - budget >= 0)
        cout << endl << setw(17) << right << "Gap:" << setw(11) << right << total - budget
         << setw(5) << right <<"Lt." << endl << endl;
    else cout << endl << setw(17) << right << "Available:" << setw(11) << right << -1 * (total - budget)
         << setw(5) << right <<"Lt." << endl << endl;

    cout << "——————————————————————————————————————————————————" << endl;

    /* If the list is empty: */
    if (NoDel == true) {cout << "\n\tNothing to delete!\n" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    NoDel = false;}
    if (NoEdit == true) {cout << "\n\tNothing to edit!\n" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    NoEdit = false;}




    /* MENU */
    char choice;
    cout << setw(7) << left << " New" << setw(7) << "Edit" << setw(7) << "Delete" << setw(6) << right << "Exit"
             << setw(11) << right << "Refresh" << setw(9) << right << "Budget";
    cout << endl << setw(7) << left << " [N]" << setw(7) << "[E]" << setw(7) << " [D]" << setw(6) << right << "[X]"
             << setw(9) << right << "[R]" << setw(9) << right << "[B]" << endl << endl << "\t\tYour choice: ";

    cin >> choice;

    switch (choice){
        case 'X':
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nDone!\n\n"
                 << "Thank you for using this handy software.\n\nClose this window." << endl
                 << "\n2014© Kazimieras Senvaitis\n"
                 << "\nV1.003\n" << endl;
            cin >> choice;
            break;
        case 'N':
            New(D);
            break;
        case 'E':
            Edit(D);
            break;
        case 'D':
            Delete(D);
            break;
        case 'R':
            Refresh(D);
            break;
        case 'B':
            Budget(D);
            break;
        default: Refresh(D);
        }


    }


void Total (TOne D[]){
    total = 0;
    for (int i = 0; i < q; i++)
        total += D[i].priceTag;
}

void Budget (TOne D[]){

    cout << "\tEnter your budget: ";
    cin >> budget;


    Refresh(D);
}

#include <iostream>
#include <sstream>

using namespace std;

//Funktionen als Hilfe

void sort(int prozess[][5], int size, int n)
{
    for (int i = 0; i < size - 1; i++)
    {
        int  min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (prozess[n][j] < prozess[n][min])
            {
                int temp = prozess[0][j];
                int temp1 = prozess[1][j];
                int temp2 = prozess[2][j];
                int temp3 = prozess[3][j];

                prozess[0][j] = prozess[0][min];
                prozess[1][j] = prozess[1][min];
                prozess[2][j] = prozess[2][min];
                prozess[3][j] = prozess[3][min];

                prozess[0][min] = temp;
                prozess[1][min] = temp1;
                prozess[2][min] = temp2;
                prozess[3][min] = temp3;

            }
        }
    }
}

void sonderSort(int prozess[][5], int size, int n)
{
    for (int i = 0; i < size - 1; i++)
    {
        int  min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (prozess[1][j] == 0)
            {
                if (prozess[n][j] < prozess[n][min])
                {
                    int temp = prozess[0][j];
                    int temp1 = prozess[1][j];
                    int temp2 = prozess[2][j];
                    int temp3 = prozess[3][j];

                    prozess[0][j] = prozess[0][min];
                    prozess[1][j] = prozess[1][min];
                    prozess[2][j] = prozess[2][min];
                    prozess[3][j] = prozess[3][min];

                    prozess[0][min] = temp;
                    prozess[1][min] = temp1;
                    prozess[2][min] = temp2;
                    prozess[3][min] = temp3;

                }
            }
        }
    }
}

void shrink(int prozess[][5], int n, int reduce)
{
    for (int i = 0; i < 5; i++)
    {
        prozess[n][i] = prozess[n][i] - reduce;
        if (prozess[n][i] < 0)
        {
            prozess[n][i] = 0;
        }
    }
}

void sonderShrink(int prozess[][5], int n, int reduce, int ges[5], int waiter[5])
{
    if (prozess[2][n] > 0)
    {
        prozess[2][n] = prozess[2][n] - reduce;
        if (prozess[2][n] < 0)
        {
            int tempReduce = 0 - prozess[2][n];
            prozess[2][n] = 0;
            waiter[n] = waiter[n] + tempReduce;
            ges[n] = ges[n] + tempReduce;
            sonderShrink(prozess, n + 1, tempReduce, ges, waiter);
        }
    }
    else if (prozess[2][n] == 0)
    {
        sonderShrink(prozess, n + 1, reduce, ges, waiter);
    }
}

int check(int prozess[][5], int n)
{
    int counter = 0;
    for (int i = 0; i <= 4; i++)
    {
        if (prozess[n][i] == 0)
            counter++;
    }

    if (counter == 5)
    {
        return 1;
    }
    else
        return 0;
}


//Die verschieden Verfahren


//LEAST LAXITY FIRST

void llf(int prozess[][5], int size)
{
    cout << "Least Laxity First - Strategie: \n\n";
    int time_sum;
    for (int i = 0; i <= size; i++)
    {
        prozess[3][i] = (prozess[0][i] - prozess[1][i]) - prozess[2][i];        //Laxity brechnen
    }

    cout << "Prozesse unsortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    sort(prozess, size, 3);     //Prozesse sortieren

    cout << "\nProzesse sortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    time_sum = 0;
    int time_before = 0;
    int waiter = 0;
    for (int i = 1; i <= 4; i++)
    {
        time_before = time_sum;    //Ausgabe                                                     //Wartezeit berechnen
        time_sum = time_sum + prozess[2][i - 1];        //Rechung
        cout << "\n" << time_before << " + " << prozess[2][i - 1] << " = " << time_sum;     //Ausgabe
        cout << "\nProzess " << i << " wartet: " << time_sum << " Zeiteinheiten\n";         //Ausgabe
        waiter = waiter + time_sum;     //Rechnung
    }

    waiter = waiter + prozess[2][4] + time_sum;

    cout << "\n\nCPU wartet " << waiter << " Zeiteinheiten bis alle Prozesse erledigt sind.\n\n";

    double ausgabe = ((double)waiter) / ((double)size);
    cout << "\n" << waiter << " / " << size << " = " << ausgabe << "\n\n";        //Rechnung ausgeben

    cout << "Durchschnittliche Wartezeit der " << size << " Prozesse mit LLF-Strategie: " << ausgabe << " Zeiteinheiten\n\n\n";
}

//FIRST COME FIRST SERVED

void fcfs(int prozess[][5], int size)
{
    cout << "First Come First Served - Strategie: \n\n";
    cout << "Prozesse: \n";
    for (int i = 0; i <= size - 1; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    cout << "\n";

    int time_sum = 0;
    int time_before = 0;
    int waiter = 0;
    for (int i = 1; i <= 4; i++)
    {
        time_before = time_sum;     //Ausgabe                                                         //Wartezeit berechnen
        time_sum = time_sum + prozess[2][i - 1];       //Rechnung
        cout << "\n" << time_before << " + " << prozess[2][i - 1] << " = " << time_sum;     //Ausgabe
        cout << "\nProzess " << i << " wartet: " << time_sum << " Zeiteinheiten\n";         //Ausgabe
        waiter = waiter + time_sum;     //Rechnung
    }

    waiter = waiter + prozess[2][4] + time_sum;

    cout << "\n\nCPU wartet " << waiter << " Zeiteinheiten bis alle Prozesse erledigt sind.\n\n";

    double ausgabe = ((double)waiter) / ((double)size);
    cout << "\n" << waiter << " / " << size << " = " << ausgabe << "\n\n";        //Rechnung ausgeben

    cout << "Durchschnittliche Wartezeit der " << size << " Prozesse mit FCFS-Strategie: " << ausgabe << " Zeiteinheiten\n\n\n";
}

//SHORTEST-JOB-FIRST-PREEMPTIVE

void sjf_p(int prozess[][5], int size)
{
    int time_sum = 0;
    int reduce, startR;
    int ges = 0;
    int waiter = 0;       //Wartezeit bevor Readytime erreicht war
    int wait_Arr[5] = {}; //Wartezeit Array zum übergeben für Funktion
    int ges_Arr[5] = {};  //Wartezeit bevor Readytime erreicht war, Array zum übergeben
    bool calculate = false;
    int alltime = 0;
    for (int i = 0; i < 5; i++)
    {
        alltime = alltime + prozess[2][i];
    }
    cout << "Shortest Job First non-preemptive - Strategie: \n\n";

    cout << "Prozesse unsortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    sonderSort(prozess, size, 2);     //sortieren nach readytime
    cout << "\nProzesse sortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";
    }

    while (calculate != true)
    {
        for (int j = 0; j <= 4; j++)
        {
            reduce = prozess[1][j + 1];     //schaue wie lange die nächste readytime braucht um 0 zu werden
            shrink(prozess, 1, reduce); //Reduziere alle Readytimes um diesen Wert
            sonderShrink(prozess, 0, reduce, ges_Arr, wait_Arr);   //Reduziere die Bedienzeit des aktuellen Prozesses um diesen Wert, und bei Restwert die des nächsten, übernächsten usw... -> Erhöhe Wartezeit 
            sonderSort(prozess, size, 2);   //Sortiere Alle Prozesse die Ready sind nach ihrer Bedienzeit
            cout << "\nProzesse: \n";
            for (int i = 0; i <= 4; i++)
            {
                cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
            }
        }
        for (int i = 0; i < 5; i++)
        {
            waiter = waiter + wait_Arr[i];
        }
        for (int i = 0; i < 5; i++)
        {
            ges = ges + ges_Arr[i];
        }
        cout << "Gewartet: " << waiter << "\n";
        if (check(prozess, 1) == 1)        //checke ob alle Bedienzeiten auf 0 sind
            calculate = true;
    }

    for (int i = 1; i <= 4; i++)
    {
        if ((prozess[2][i - 1] == 0) && (prozess[2][i] > 0))    //Finde heraus bei welcher Bedienzeit wir beginnen müssen
        {
            startR = i;
        }
    }

    int time_before;
    for (int i = startR; i < 4; i++)
    {
        reduce = prozess[2][i];                                 //Reduziere die Restlichen Bedienzeiten und addiere es auf time_sum
        prozess[2][i] = 0;
        time_before = time_sum;
        time_sum = time_sum + reduce;
        waiter = waiter + time_sum;                             //Erhöhe die Gesamtwartezeit um time_sum
        cout << "\nProzesse: \n";
        for (int i = 0; i <= 4; i++)
        {
            cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";        //Prozesse ausgeben
        }
        cout << "Gewartet: " << time_sum << "\n";
    }
    waiter = waiter + alltime;     //Addiere die Wartezeit bevor alle Prozesse Ready waren dazu
    cout << "\nCPU wartet " << waiter << " Zeiteinheiten bis alle Prozesse erledigt sind.\n";
    double ausgabe = ((double)waiter) / ((double)size);
    cout << "\n" << waiter << " / " << size << " = " << ausgabe << "\n\n";        //Rechnung ausgeben

    cout << "Durchschnittliche Wartezeit der " << size << " Prozesse mit SJF-Preemptive-Strategie: " << ausgabe << " Zeiteinheiten\n\n\n";
}

//SHORTEST-JOB-FIRST-NON-PREEMPTIVE

void sjf_nonP(int prozess[][5], int size)
{
    cout << "Shortest Job First non-preemptive - Strategie: \n\n";

    cout << "Prozesse unsortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    sort(prozess, size, 2);     //Sortieren nach Bedienzeit

    cout << "\nProzesse sortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    cout << "\n";

    int time_sum = 0;
    int time_before = 0;
    int waiter = 0;
    for (int i = 1; i <= 4; i++)
    {
        time_before = time_sum;     //Ausgabe                                                         //Wartezeit berechnen
        time_sum = time_sum + prozess[2][i - 1];       //Rechnung
        cout << "\n" << time_before << " + " << prozess[2][i - 1] << " = " << time_sum;     //Ausgabe
        cout << "\nProzess " << i << " wartet: " << time_sum << " Zeiteinheiten\n";         //Ausgabe
        waiter = waiter + time_sum;     //Rechnung
    }

    waiter = waiter + prozess[2][4] + time_sum;

    cout << "\n\nCPU wartet " << waiter << " Zeiteinheiten bis alle Prozesse erledigt sind.\n\n";

    double ausgabe = ((double)waiter) / ((double)size);
    cout << "\n" << waiter << " / " << size << " = " << ausgabe << "\n\n";        //Rechnung ausgeben

    cout << "Durchschnittliche Wartezeit der " << size << " Prozesse mit FCFS-Strategie: " << ausgabe << " Zeiteinheiten\n\n\n";
}

//EARLIEST-DEADLINE-FIRST

void edf(int prozess[][5], int size)
{
    cout << "Earliest Deadline First - Strategie: \n\n";

    cout << "Prozesse unsortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    sort(prozess, size, 0);         //Sortieren nach Deadline

    cout << "\nProzesse sortiert: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    cout << "\n";

    int time_sum = 0;
    int time_before = 0;
    int waiter = 0;
    for (int i = 1; i <= 4; i++)
    {
        time_before = time_sum;     //Ausgabe                                                         //Wartezeit berechnen
        time_sum = time_sum + prozess[2][i - 1];       //Rechnung
        cout << "\n" << time_before << " + " << prozess[2][i - 1] << " = " << time_sum;     //Ausgabe
        cout << "\nProzess " << i << " wartet: " << time_sum << " Zeiteinheiten\n";         //Ausgabe
        waiter = waiter + time_sum;     //Rechnung
    }

    waiter = waiter + prozess[2][4] + time_sum;

    cout << "\n\nCPU wartet " << waiter << " Zeiteinheiten bis alle Prozesse erledigt sind.\n\n";

    double ausgabe = ((double)waiter) / ((double)size);
    cout << "\n" << waiter << " / " << size << " = " << ausgabe << "\n\n";        //Rechnung ausgeben

    cout << "Durchschnittliche Wartezeit der " << size << " Prozesse mit EDF-Strategie: " << ausgabe << " Zeiteinheiten\n\n\n";
}

//ROUND-ROBIN

void rr(int prozess[][5], int size)
{
    int time_sum = 0;
    cout << "Round Robin - Strategie: \n\n";

    cout << "Prozesse: \n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
    }

    int q = 3;
    bool calculate = false;

    int counter = 0;
    int waited = 0;
    int needed, before;
    int ausgabe;
    int add = 0;

    cout << "\n";

    while (calculate != true)       //Wiederhole das folgende alle Bedienzeiten auf 0 sind
    {
        for (int i = 0; i <= 4; i++)        //Wiederhole das folgende für jeden Prozess 
        {
            if (prozess[2][i] > 0)
            {
                before = prozess[2][i];
                cout << "Prozess: " << i << " ExecutionTime: " << prozess[2][i] << "\n";
                prozess[2][i] = prozess[2][i] - q;      //Ziehe das Quantum von der Bedienzeit des Prozesses ab
                if (prozess[2][i] < 0)                  //Falls die Bedienzeit weniger 0 ist, setze sie auf genau 0 und übergeb wieviel vom Quantum benutzt wurde
                {
                    prozess[2][i] = 0;
                }

                needed = before - prozess[2][i];
                cout << "needed: " << needed << "\n";   //Gebe aus wieviel vom Quantum benutzt wurde
                ausgabe = time_sum;
                time_sum = needed + waited;
                cout << "time_sum: " << waited << " + " << needed << " = " << time_sum << "\n";
                waited = time_sum;
                if (prozess[2][i] == 0)
                {
                    add = add + time_sum;
                }
                cout << "Prozesse: \n";
                for (int i = 0; i <= 4; i++)
                {
                    cout << "Deadline Prozess " << i + 1 << ": " << prozess[0][i] << "; Readytime Prozess " << i + 1 << ": " << prozess[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << prozess[2][i] << "; Laxity Prozess " << i + 1 << ": " << prozess[3][i] << "\n";     //Prozesse ausgeben
                }

                cout << "\n\n";
            }

            if (check(prozess, 2) == 1)        //checke ob alle Bedienzeiten auf 0 sind
                calculate = true;

            counter++;      //Zähle hoch wie oft wir das Quantum benutzt haben
        }
    };

    cout << "\n\nCPU wartet " << add << " Zeiteinheiten bis alle Prozesse erledigt sind.\n\n";

    double out = ((double)add) / ((double)size);
    cout << "\n" << add << " / " << size << " = " << out << "\n\n";        //Rechnung ausgeben

    cout << "Durchschnittliche Wartezeit der " << size << " Prozesse mit EDF-Strategie: " << out << " Zeiteinheiten\n\n\n";

}






int main()
{

    int Test_Arr_One[5][5] = { {30, 5, 20, 12, 18} //Deadline
                      , {10, 0, 6, 4, 8}     //Readytime
                      , {10, 5, 7, 6, 1}     //ExecutionTime
                      , {} };              //Laxity


    int Test_Arr_Second[5][5] = { {30, 5, 20, 12, 18} //Deadline
                      , {0, 0, 4, 4, 4}     //Readytime
                      , {22, 2, 3, 5, 8}     //ExecutionTime
                      , {} };              //Laxity

    int A_Size;
    int decisionOne, decisionTwo;
    cout << "Hallo ich begruesse sie zu meinem Programm des Schedulings!\n\nHier können sie die beiden Verfuegbaren Arrays sehen: \n\n";
    cout << "Testarray 1: \n\n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << Test_Arr_One[0][i] << "; Readytime Prozess " << i + 1 << ": " << Test_Arr_One[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << Test_Arr_One[2][i] << "; Laxity Prozess " << i + 1 << ": " << Test_Arr_One[3][i] << "\n";     //Prozesse ausgeben
    }
    cout << "\n\nTestarray 2: \n\n";
    for (int i = 0; i <= 4; i++)
    {
        cout << "Deadline Prozess " << i + 1 << ": " << Test_Arr_Second[0][i] << "; Readytime Prozess " << i + 1 << ": " << Test_Arr_Second[1][i] << "; Bedienzeit Prozess " << i + 1 << ": " << Test_Arr_Second[2][i] << "; Laxity Prozess " << i + 1 << ": " << Test_Arr_Second[3][i] << "\n";     //Prozesse ausgeben
    }

    cout << "\n\nWelches der beiden Arrays möchten sie benutzen? Fuer das erste bitte die 1 eingeben, und fuer das zweite die 2: ";
    cin >> decisionOne;
    switch (decisionOne)
    {
    case 1:
        cout << "\n\n\nWelches der Schdeulingverfahren möchten sie nun auf ihr gewähltes Array anwenden? Ihre Moeglichkeiten mit der jeweils benötigten Eingabe sind unten aufgelistet:\n\n-Least-Laxity-Fisrt: 1\n-First-Come-First-Served: 2\n-Shortest-Job-First-Preemptive: 3\n-Shortest-Job-First-Nonpreemptive: 4\n-Earliest-Deadline-First: 5\n-Round-Robin: 6\n\nBitte treffen sie nun ihre Wahl: ";
        cin >> decisionTwo;
        A_Size = (sizeof(Test_Arr_One) / sizeof(Test_Arr_One[0][0])) / 5;
        switch (decisionTwo)
        {
        case 1:
            llf(Test_Arr_One, A_Size);
            break;
        case 2:
            fcfs(Test_Arr_One, A_Size);
            break;
        case 3:
            sjf_p(Test_Arr_One, A_Size);
            break;
        case 4:
            sjf_nonP(Test_Arr_One, A_Size);
            break;
        case 5:
            edf(Test_Arr_One, A_Size);
            break;
        case 6:
            rr(Test_Arr_One, A_Size);
            break;
        default:
            cout << "\nBITTE TAETIGEN SIE EINE GUELTIGE EINGABE!!!\n";
            break;
        }
        break;

    case 2:
        cout << "\n\n\nWelches der Schdeulingverfahren möchten sie nun auf ihr gewähltes Array anwenden? Ihre Moeglichkeiten mit der jeweils benötigten Eingabe sind unten aufgelistet:\n\n-Least-Laxity-Fisrt: 1\n-First-Come-First-Served: 2\n-Shortest-Job-First-Preemptive: 3\n-Shortest-Job-First-Nonpreemptive: 4\n-Earliest-Deadline-First: 5\n-Round-Robin: 6\n\nBitte treffen sie nun ihre Wahl: ";
        cin >> decisionTwo;
        A_Size = (sizeof(Test_Arr_Second) / sizeof(Test_Arr_Second[0][0])) / 5;
        switch (decisionTwo)
        {
        case 1:
            llf(Test_Arr_Second, A_Size);
            break;
        case 2:
            fcfs(Test_Arr_Second, A_Size);
            break;
        case 3:
            sjf_p(Test_Arr_Second, A_Size);
            break;
        case 4:
            sjf_nonP(Test_Arr_Second, A_Size);
            break;
        case 5:
            edf(Test_Arr_Second, A_Size);
            break;
        case 6:
            rr(Test_Arr_Second, A_Size);
            break;
        default:
            cout << "\nBITTE TAETIGEN SIE EINE GUELTIGE EINGABE!!!\n";
            break;
        }
        break;
    default:
        cout << "\nBITTE TAETIGEN SIE EINE GUELTIGE EINGABE!!!\n";
        break;
    }

}
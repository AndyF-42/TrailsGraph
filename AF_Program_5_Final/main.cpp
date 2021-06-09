// main.cpp

#include "table.h"
using namespace std;

/* Andy Fleischer - CS163 - Program #5 - 6/4/2021
 * ----------------------------------------------
 * This sample client code handles a graph of
 * trails and pathways. Graph is undirected. */

void add_vertex(table* trails);
void add_edge(table* trails);
void display_all(table* trails);
void help();
void clean_input(char* destination, int size);

int main()
{
    table* trails = new table(); //my trails

    cout << "-------------------" << endl;
    cout << " Welcome to Trails " << endl;
    cout << "-------------------" << endl;
    help();
    
    char input[20] = "";
    while (strcmp(input, "quit") != 0) //main game loop
    {
        cout << ">> ";
        clean_input(input, 20);

        //check command
        if (strcmp(input, "addt") == 0)
            add_vertex(trails);
        else if (strcmp(input, "addp") == 0)
            add_edge(trails);
        else if (strcmp(input, "dall") == 0)
            display_all(trails);
        else if (strcmp(input, "help") == 0)
            help();
        else if (strcmp(input, "quit") != 0)
            cout << "Invalid command. Type \"help\" for list of valid commands." << endl;
    }

    delete trails;
    return 0;
}

//add_vertex - adds a vertex to the table
void add_vertex(table* trails)
{
    char to_add[20];
    cout << "Name: ";
    clean_input(to_add, 20);

    if (trails->insert_vertex(to_add)) //check return
        cout << "Added." << endl;
    else
        cout << "Could not add trail." << endl;
}

//add_edge - adds an edge to the table
void add_edge(table* trails)
{
    //inputs
    char start[20];
    cout << "Start: ";
    clean_input(start, 20);

    char end[20];
    cout << "End: ";
    clean_input(end, 20);

    char length_input[10];
    cout << "Length (miles): ";
    clean_input(length_input, 10);
    float length = (float)atof(length_input); //convert to float
    
    char difficulty_input[5];
    int difficulty = 0;
    while (difficulty < 1 || difficulty > 5) //get valid input (1-5)
    {
        cout << "Difficulty (1-5): ";
        clean_input(difficulty_input, 5);
        difficulty = atoi(difficulty_input);
    }

    if (trails->insert_edge(start, end, length, difficulty) &&
        trails->insert_edge(end, start, length, difficulty)) //add path both ways and check returns
        cout << "Added." << endl;
    else
        cout << "Could not add path." << endl;
}

//display_all - displays all vertices and their connections
void display_all(table* trails)
{
    if (!trails->display_all()) //error check
        cout << "No trails." << endl;
}

//help - prints out valid function
void help()
{
    cout << "Valid functions are:" << endl;
    cout << "  addt - Add a trail vertex to the graph" << endl;
    cout << "  addp - Add a path (edge) to the graph" << endl;
    cout << "  dall - Display all trails and connected paths" << endl;
    cout << "  help - Display these valid commands" << endl;
    cout << "  quit - Quit the program" << endl;
}

//clean_input - take in input of given size and clean the buffer
void clean_input(char* destination, int size)
{
    cin.get(destination, size);
    cin.clear();
    cin.ignore(1000, '\n');
}

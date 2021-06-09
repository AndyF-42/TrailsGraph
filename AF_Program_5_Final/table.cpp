// table.cpp

#include "table.h"

/* Andy Fleischer - CS163 - Program #5 - 6/4/2021
 * -----------------------------------------------
 * This class is a Table ADT implementing a graph
 * data structure with vertex and node structs to
 * graph out a trail map.
 * Functionalities include a constructor and
 * destructor, inserting edges and vertices,
 * displaying all adjacencies, and a depth-first
 * search for shortest path. */

//constructor - create the array, set the size, and initialize values to NULL
table::table(int size)
{
    list_size = size;
    adjacency_list = new vertex[list_size];
    
    for (int i = 0; i < list_size; ++i) //initialize all names and heads to NULL
    {
        adjacency_list[i].name = NULL;
        adjacency_list[i].head = NULL;
    }
}

//destructor - delete all memory
table::~table()
{
    for (int i = 0; i < list_size; ++i) //loop through full array
    {
        if (adjacency_list[i].name) { delete [] adjacency_list[i].name; } //delete the name

        node* current = adjacency_list[i].head;
        while (current) //loop through and delete each node
        {
            node* temp = current->next;
            delete current;
            current = temp;
        }
    }
    delete [] adjacency_list; //delete whole list
    list_size = 0;
}

//insert_vertex - inserts a vertex into the list
int table::insert_vertex(const char* to_add)
{
    if (!to_add)
        return 0; //error: no name

    for (int i = 0; i < list_size; ++i)
    {
        if (!adjacency_list[i].name) //if empty slot, copy in the name
        {
            adjacency_list[i].name = new char[strlen(to_add) + 1];
            strcpy(adjacency_list[i].name, to_add);
            return 1;
        }
    }
    return 0; //error: list is full
}

//insert_edge - insert an edge between vertices
int table::insert_edge(const char* curr, const char* to_attach, float length, int difficulty)
{
    if (!curr || !to_attach || !length || !difficulty)
        return 0; //error: bad inputs

    //find start and end
    int start = find_location(curr);
    int end = find_location(to_attach);

    if (start == -1 || end == -1)
        return 0; //error: could not find one of the vertices

    node* current = adjacency_list[start].head;
    node* previous = NULL;

    while (current) //loop through to the end of the LLL of edges
    {
        if (current->adjacent == &adjacency_list[end])
            return 0; //error: match already exists

        previous = current;
        current = current->next;
    }

    //create the node and all necessary data
    node* new_node = new node;
    new_node->next = NULL;
    new_node->adjacent = &adjacency_list[end];
    new_node->length = length;
    new_node->difficulty = difficulty;

    if (!previous) //add at head or previous->next
    {
        adjacency_list[start].head = new_node;
        return 1;
    }
    previous->next = new_node;
    return 1;
}

//display_all - display all vertices and their adjacent nodes
int table::display_all() const
{
    int has_path = 0; //tracks if has a path
    for (int i = 0; i < list_size; ++i) //loop through array
    {
        if (adjacency_list[i].name) //if the trail exists
        {
            has_path = 1;
            //print the trail and some dashes
            std::cout << adjacency_list[i].name << std::endl;
            for (int j = 0; adjacency_list[i].name[j] !='\0'; ++j)
                std::cout << "-";
            std::cout << std::endl; 
            
            //print what it is connected to
            std::cout << "Connected To:" << std::endl;
            node* current = adjacency_list[i].head;
            if (!current) //if no node, print that it has no connections
                std::cout << "  Nothing\n" << std::endl;
            while (current) //loop through and print all connections
            {
                std::cout << "  " << current->adjacent->name << std::endl;
                std::cout << "  Length: " << current->length << std::endl;
                std::cout << "  Difficulty: " << current->difficulty << "\n" << std::endl;
                current = current->next;
            } 
        }
    }
    return has_path;
}

//find_location - helper function to find the index of a given key (trail head name)
int table::find_location(const char* key) const
{
    for (int i = 0; i < list_size; ++i) //loop through and check if the name matches, otherwise return -1
        if (adjacency_list[i].name && strcmp(adjacency_list[i].name, key) == 0)
            return i;
    return -1;
}

// table.h

#include <iostream>
#include <cstring>

/* Andy Fleischer - CS163 - Program #5 - 6/4/2021
 * -----------------------------------------------
 * This class is a Table ADT implementing a
 * weighted graph data structure with vertex and
 * node structs to graph out a trail map.
 * Functionalities include a constructor and
 * destructor, inserting edges and vertices,
 * displaying all adjacencies.
 * NOTE: graph is by default directed, but user
 * can add edges both ways if undirected is
 * desired. */

struct vertex
{
    char* name; //NULL if vertex isn't set
    struct node* head; //edge list
};

struct node
{
    vertex* adjacent; //the vertex that is adjacent
    float length; //length in miles
    int difficulty; //1-5 difficulty rating
    node* next;
};


class table
{
    public:
        table(int size=5); //constructor (Task 1)
        ~table(); //destructor (Task 3)

        //following functions return 1 for success, or 0 for failure
        int insert_vertex(const char* to_add); //add vertex into graph (Task 1?)
        int insert_edge(const char* curr, const char* to_attach, float length, int difficulty); //add edge between vertices (Task 2)
        int display_adjacent(const char* name); //display all vertices adjacent to the one with given name (Task 4)
        int display_all() const; //display all vertices and edges (Task 4)
        
        //helper function, returns the index of a given key (vertex name)
        int find_location(const char* key) const;

    private:
        vertex* adjacency_list;
        int list_size;
};

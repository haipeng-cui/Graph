// Student Name:Haipeng Cui
// CPSC 2150, Assignment #8, specifications by Gladys Monagan
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

//type define
struct Node{
   int vertex;
   Node * next;
      };

class Graph {
   public:
      // build an empty graph with no vertices and no edges
      // the only way to add edges or vertices to the graph is with 
      // the >> operator which deletes the current graph
      // and reads and builds a new one
      Graph();

      // build a graph from the data read using the input stream iStream
      // Note: the previous graph is destroyed, before building a new one
      // read the number of vertices n
      // read pairs of integers corresponding to an edge in the graph
      // read until iStream fails (i.e. no more data or the data is not an integer)
      // reset iStream and clear the buffer of iStream
      // about the input expected
      //    => if any of the vertices of the edges (i, j) are not
      //       0 <= i < n and that 0 <= j < n, these 2 endpoints are ignored 
      //       and not added to the graph
      //    => every undirected edge may only be read ONCE
      //       if an undirected edge is read twice, it is ignored and not added
      //       to the graph
      // precondition: 
      //    iStream is an open stream not in a fail state
      Graph(std::istream& iStream);

      // read the number of vertices n
      // read pairs of integers corresponding to an edge in the graph
      // read until iStream fails (i.e. no more data or the data is not an integer)
      // reset iStream and clear the buffer of iStream
      // about the input expected
      //    => if any of the vertices of the edges (i, j) are not
      //       0 <= i < n and that 0 <= j < n, these 2 endpoints are ignored 
      //       and not added to the graph
      //    => every undirected edge may only be read ONCE
      //       if an undirected edge is read twice, it is ignored and not added
      //       to the graph
      // precondition: 
      //    iStream is an open stream not in a fail state
      friend std::istream& operator >> (std::istream& in, Graph&);

      // output the graph with a convenient format
      // a possibility is to output a vertex and then its neighbours 
      friend std::ostream& operator << (std::ostream&, const Graph&);

      // return true if the graph is connected, false otherwise
      // SOLUTION must be programmed with the STL std::stack
      bool isConnected() const;

      // return true if the graph has at least one cycle, false otherwise
      bool hasCycle() const;

      // list all the connected components using the output stream oStream
      // each connected component has its vertices in the same line
      // e.g. the output could look like this
      //    0 
      //    1 2 4 5 3 
      //    6 8 7
      // meaning that there is one connected component with only one vertex 0
      // there is another connected component with the vertices 1 2 4 5 3
      // there is another connected component with the vertices 6 8 7
      void listComponents(std::ostream& oStream) const;

      // overloaded assignment operator 
      Graph& operator = (const Graph&);

      // copy constructor
      Graph(const Graph&);

      // destructor
      ~Graph();
      
      //return number of sides;
      int numOfSide() const;
      
      //return number of Nodes;
      int numOfNode() const;
      
      //return number of component;
      int numOfcom() const;
      
      //G is an array of  vertex;
      Node** G;
      //n is number of Vertex;
      int n;
   private:
      static void insertEdge(int i,int j, Graph &graph);
      static Node* cons(int v,Node* List);
      static bool member(int v, Node* List);


};

#endif
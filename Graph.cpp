// Name:Haipeng Cui

#include <iostream>
#include <limits> // for declaration of 'numeric_limits' for in
#include <ios>    // for declaration of 'streamsize' for in
#include <queue>
#include <stack> 
#include "Graph.h"

//initial an empty graph
Graph::Graph() {
   G=nullptr;
   n=0;

}

Graph::Graph(std::istream& in) {
   //delete the old one
   for(int i=0;i<n;i++){
      Node* p=G[i];
      while(p!=nullptr){
         Node* discard=p;
         p=p->next;
      delete discard;
      }
   }
   delete [] G;
   n=0;
   //allcate space
   in>>n;
   G= new Node*[n];
   for(int i=0;i<n;i++){
      G[i] =nullptr;
      }
   //read edges;
   int i,j;
   while(in>>i>>j){
      Graph::insertEdge(i,j,*this);
      }
   

}


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
std::istream& operator >> (std::istream& in, Graph& graph) {
   //delete old one
   for(int i=0;i<graph.n;i++){
      Node* p=graph.G[i];
      while(p!=nullptr){
         Node* discard=p;
         p=p->next;
         delete discard;
         }
      }
   delete [] graph.G;
   graph.n=0;
    //read from file  
   in>>graph.n;
   graph.G= new Node*[graph.n];
   for(int i=0;i<graph.n;i++){
      graph.G[i] =nullptr;
      }
   int i,j;
   while(in>>i>>j){
      Graph::insertEdge(i,j,graph);
      }
   return in;
}
//insert edge
void Graph::insertEdge(int i,int j, Graph &graph){
   if(i!=j&& i>=0&&i<graph.n && j>=0 && j<graph.n){
      if(!member(i,graph.G[j]) && !member(j,graph.G[i])){
         graph.G[j] = cons(i,graph.G[j]);
         graph.G[i] = cons(j,graph.G[i]);
         }
      }
   }
//connect pair
 Node* Graph::cons(int v,Node* List){
    Node *p = new Node{v,List};
    return p;
    }
//check if v is a member of List
bool Graph::member(int v, Node* List){
   while(List!=nullptr){
      if(List->vertex==v){
         return true;
         }
      else
         List=List->next;
      }
   return false;
   }
//output
std::ostream& operator << (std::ostream& out, const Graph& graph) {
   for(int i=0;i<graph.n;i++){
      if(graph.G[i]!=nullptr){
         out<<"Vertex:"<<i<<" "<<"Pair:";
         Node *p = graph.G[i];
         while(p!=nullptr){
            out<<p->vertex<<" ";
            p=p->next;
            }
         out<<std::endl;   
         }
      
      }
   return out;
}

// postcondition:
//    deep copy of the rtSide was made      
Graph& Graph::operator = (const Graph& rtSide) {
      for(int i=0;i<n;i++){
         Node* p=G[i];
         while(p!=nullptr){
            Node* discard=p;
            p=p->next;
         delete discard;
         }
      }
      delete [] G;
      n=0;
      
      n=rtSide.n;
      G= new Node*[n];
      for(int i=0;i<n;i++){
         G[i] =nullptr;
         Node *p=rtSide.G[i];
         while(p!=nullptr){
            G[i]=cons(p->vertex,G[i]);
            p=p->next;
            }
      }
    return *this;  

}


Graph::Graph(const Graph& other) {
   n=0;
   G=nullptr;
   *this=other;
}

// destructor frees up the memory
Graph::~Graph() {
   for(int i=0;i<n;i++){
      Node* p=G[i];
      while(p!=nullptr){
         Node* discard=p;
         p=p->next;
         delete discard;
         }
      }
   delete [] G;
   n=0;
}

bool Graph::isConnected() const {//code from lecture
   
   if(n<2) return true;
   
   std::stack<int> s;
   
   bool *M = new bool[n];
   for(int i=0;i<n;i++){
      M[i] = false;
      }
   //start position;
   int v0=0;
   s.push(v0);
   Node*p;
   while(!s.empty()){
      int v=s.top();
      for(p=G[v];p!=nullptr&&M[p->vertex];p=p->next);
      if(p==nullptr)
         s.pop();
      else{
         s.push(p->vertex);
         M[p->vertex]=true;
         }
      }
      
   for(int i=0;i<n;i++){
      if(M[i] == false)
         return false;
      }
   return true;
}

bool Graph::hasCycle() const {
   //There is a  theorem: if there is a cycle in a graph, the total number of sides must be larger than the sum of nodes and the sum of linked componts(numOfSide >numOfNode -numOfcom)

   if(numOfSide() > numOfNode() -numOfcom())
      return true;
   else 
      return false;
}

int Graph::numOfNode() const{
   return n;
   }
 //return number of linked components;
   
int Graph::numOfcom() const{
   int sum=0;
      //create a stack
   std::stack<int> s;
   //create a boolean to mark if vetex are visited
   bool *M = new bool[n];
   for(int i=0;i<n;i++){
      M[i] = false;
      }
   //check every vertex
   for(int j=0;j<n;j++){
      //find the unvisted, connected sub-graph
      if(M[j] == false ){
         sum++;//once goes a new loop, mean there is a new component;
         if(G[j] == nullptr){
            M[j]=true;
            continue;
            }
         s.push(j);
         Node*p;
         while(!s.empty()){
            int v=s.top();
            for(p=G[v];p!=nullptr&&M[p->vertex];p=p->next);
            if(p==nullptr)
               s.pop();
            else{
               s.push(p->vertex);
               M[p->vertex]=true;
               }
            }
      }
      
   }
   
   return sum;
   }
   
//get the total number of sides
int Graph::numOfSide() const{
   int sum=0;
   for(int i=0;i<n;i++){
      Node *p=G[i];
      while(p!=nullptr){
         sum++;
         p = p->next;
         }
      }
   return sum/2;
   }
void Graph::listComponents(std::ostream& out) const {
   
   //create a stack
   std::stack<int> s;
   //create a boolean to mark if vetex are visited
   bool *M = new bool[n];
   for(int i=0;i<n;i++){
      M[i] = false;
      }
   //check every vertex
   for(int j=0;j<n;j++){
      //find the unvisted, connected sub-graph,and print it
      if(M[j] == false ){
         out<<"linked compoint:";
         if(G[j] == nullptr){
            out<<j<<std::endl;
            M[j]=true;
            continue;
            }
         s.push(j);
         Node*p;
         while(!s.empty()){
            int v=s.top();
            for(p=G[v];p!=nullptr&&M[p->vertex];p=p->next);
            if(p==nullptr)
               s.pop();
            else{
               s.push(p->vertex);
               M[p->vertex]=true;
               out<<p->vertex<<" ";
               }
            }
         out<<std::endl;
      }
      
   }  
}

#include<iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <chrono>
#include <unordered_map>
#ifndef LIST_H                //Used to avoid redefination of this header file when its included in other header files
#define LIST_H

using namespace std::chrono;
using namespace std;
using namespace filesystem;

class node{
    public:

        path adr;       //adress of the file in the folder
        int size;       //size of the file
        string date;    // creation date of the file
        int count;      //Number of times the file is accessed
        node* next;     //pointer to the next node

        node(path a, int b, string d, int e) : adr(a), size(b), date(d), count(e) {this->next = NULL;};

};

class m_node{
    public:

        path fdr;       //adress of the folder
        node* nextf;    //pointer to the linked list of the files in the folder
        node* tail;     
        m_node* link;   //pointer to the next folder

        m_node(path a) : fdr(a), nextf(nullptr), link(nullptr), tail(nullptr) {};
};

void append(path adr, int size, string date, node* &head, node* &tail, int count) /*To append node to the link it takes  Path of the file,size,date,
                                                                             count for number of times files is accessed,head and tail pointer of Linked list*/
{
    node* temp = new node(adr, size, date, count);

    if(head==NULL){
       
        head = temp;
        tail = temp;
        return;
    }

    tail->next = temp;
   
    tail = temp;
}

//function to store the entire data in the 2D linked list
void storef(path folder, path file, int size, m_node* &head, string date, int count)
{
    m_node* temp = new m_node(folder);      //To allocate memory for the node to store the path of the folder
    m_node* curr = head;

    //condition to handle empty list
    if(curr == nullptr)
    {
        
        node* t_head = new node(file, size, date, count);   
        head = temp;
        head->nextf = t_head;                   //Updating head Pointer
        head->tail=t_head;
   
        return;
    }

    while(curr->link != NULL)
    {
        if(curr->fdr == temp->fdr) break;
        curr = curr->link;
    }

    //condition to store the file at the current folder
    if(curr->fdr == temp->fdr){
      append(file, size, date, curr->nextf, curr->tail, count); 
    }
       
    else{
            node* t_head = new node(file, size, date, count);
            curr->link = temp;
          
            temp->nextf = t_head;
            temp->tail = t_head;
        }
    
    }



//Function for delete the node containing given file address
void delete_node(node* &head, node* curr, node* &prev)      //Function to delete node from linked list
{
    if(curr == head){           
        head = head->next;      //Update head node if current node is head node
        
        delete curr;
        return;
    }
    prev->next = curr->next;        //Else update the address stored in previous node 
    delete curr;
    return;
}

#endif

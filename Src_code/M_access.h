
#ifndef M_ACCESS_H
#define M_ACCESS_H
#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <chrono>
#include <unordered_map>
#include <vector>
#include "2D_list.h"
using namespace std::chrono;
using namespace std;
using namespace filesystem;

void delete_less_than_M_access_files(m_node* &main, int M, stack<path> &history, bool rut, vector<string> &store)   /*Function to delete the 
                                                                                            files whose access count is lesser than M times*/
{
     m_node* temp = main;               // main is the pointer to the first node of the  linked list

    while(temp != NULL){                // To traverse through the entire linked list
        node* curr = temp->nextf;      // Current points to the first node of the file linked list attached to the node of main linked list
        node* prev = NULL;

        while(curr != NULL){             // To traverse through the sub-linked list at each node of the main list
            if(curr->count < M){
                if(rut){                //rut is true when user goes for scheduled cleaning,false otherwise
                    store.push_back(curr->adr.string());    
                }else{
                    history.push(curr->adr);        // Push the path of the file to be deleted
                    if(!(remove(curr->adr.c_str()))){
                        cerr << "Error removing file: " << curr->adr << endl;
                    }
                }
                delete_node(temp->nextf, curr, prev);  // To update the Linked List
               
                if(prev==NULL)curr = temp->nextf;
                else curr = prev->next;         // To traverse the next node of sub linked lists
            }else{
                prev = curr;
                curr = curr->next;
            }
        }

        temp = temp->link;
    }
}
#endif

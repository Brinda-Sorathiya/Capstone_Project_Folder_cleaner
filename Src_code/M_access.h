
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
#include <chrono>
#include "2D_list.h"
using namespace std::chrono;
using namespace std;
using namespace filesystem;

void delete_less_than_M_access_files(m_node* &main, int M, stack<path> &history)
{
     m_node* temp = main;

    while(temp != NULL){
        node* curr = temp->nextf;
        node* prev = NULL;

        while(curr != NULL){
            if(curr->count < M){
                history.push(curr->adr);
                if(remove(curr->adr.c_str()) == 0)
                {
                   cout << "The empty file is successfully removed." << endl;
                } else {
                    cerr << "Error removing file: " << curr->adr << endl;
                }
                delete_node(temp->nextf, curr, prev);
               
                if(prev==NULL)curr = temp->nextf;
                else curr = prev->next;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }

        temp = temp->link;
    }
}
#endif
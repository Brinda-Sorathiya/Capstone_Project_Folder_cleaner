#ifndef REDUNDANT_H
#define REDUNDANT_H
#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <chrono>
#include <unordered_map>
#include <chrono>
#include"2D_list.h"
#include "N_months.h"



using namespace std::chrono;
using namespace std;
using namespace filesystem;

bool check_for_copy(path p1, path p2){
    ifstream file1(p1);
    ifstream file2(p2);
    if(!file1.is_open() ){
        std::cout << "Error to open the file" << endl;
        return false;
    }
     if(!file2.is_open() ){
       std:: cout << "Error to open the file" << endl;
        return false;
    }

    char c1, c2;
    while(file1.get(c1) && file2.get(c2)){
        if(c1 != c2) return false;
    }
   
    return true;
}

void check_for_empty_file(m_node* &main, stack<path> &history){
    m_node* temp = main;

    while(temp != NULL){
        node* curr = temp->nextf;
        node* prev = NULL;

        while(curr != NULL){
            if(std::filesystem::is_empty(curr->adr)){
                history.push(curr->adr);
                if(remove(curr->adr.c_str()) == 0){
                   std:: cout << "The empty file is successfully removed." << endl;
                } else {
                    cerr << "Error removing file: " << curr->adr << endl;
                }
                delete_node(temp->nextf, curr, prev);
                cout<<"Flag1\n";
                if(prev == NULL) prev = temp->nextf;
                else curr = prev->next;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }

        temp = temp->link;
    }
}

//Function to remove the redundant(copied) files
void check_for_redundant_file(m_node* &main, stack<path> &history)
{
    m_node* temp1 = main;

//Comparing each file with other files which lies in the same folder same as in the other folders
    while(temp1 != NULL){

        node* head1 = temp1->nextf;
        node* prev1 = NULL;
        
        while(head1 != NULL)
        {   
            m_node* temp2 = temp1;
             
            while(temp2 != NULL)
            {
                node* head2 = nullptr;
                node* prev2 = nullptr;

                if(temp1 == temp2){  
                    head2 = head1->next;
                    prev2 = head1;
                }else{
                    head2 = temp2->nextf;
                    prev2 = NULL;
                }
                
                while(head2 != NULL)
                {
                    bool key = true;
                    path pt;
                    if(head1->size == head2->size)
                    {
                        bool flag = check_for_copy(head1->adr, head2->adr);
                        
                        if(flag)
                        {
                            node* del = compare_diff(head1, head2);
                            history.push(del->adr);
                            remove(del->adr);

                            pt = del->adr;
                            if(del == head1){
                            delete_node(temp1->nextf, head1, prev1);
                            head1 = prev1;
                            }
                            else{
                            key = false;
                            delete_node(temp2->nextf, head2, prev2);
                            
                            head2 = prev2->next;
                            }    
                        }       
                    }
                    else if(key)
                    {
                        prev2 = head2; 
                        head2 = head2->next;
                    }
                }
                temp2 = temp2 -> link;
            }
            prev1 = head1;
            head1 = head1->next;
        }
        temp1 = temp1->link;
    }
}

#endif
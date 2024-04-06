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
#include <vector>
#include "2D_list.h"
#include "N_months.h"

using namespace std::chrono;
using namespace std;
using namespace filesystem;

bool check_for_copy(path p1, path p2) // Function to check if copy of file exists
{
    ifstream file1(p1); // To read contents of both the files
    ifstream file2(p2);
    if (!file1.is_open())
    {
        std::cout << "Error to open the file" << endl;
        return false;
    }
    if (!file2.is_open())
    {
        std::cout << "Error to open the file" << endl;
        return false;
    }

    char c1, c2;
    while (file1.get(c1) && file2.get(c2))
    {
        if (c1 != c2) // If contents are not equal, return false
            return false;
    }

    return true;
}

void check_for_empty_file(m_node *&main, stack<path> &history, bool rut, vector<string> &store) // TO check whether files are empty
{
    m_node *temp = main;

    while (temp != NULL) // To travere the main list
    {
        node *curr = temp->nextf;
        node *prev = NULL;

        while (curr != NULL) // To traverse the sub linked list attached at each node
        {
            if (std::filesystem::is_empty(curr->adr)) // If file is empty
            {
                if (rut)
                {
                    store.push_back(curr->adr.string());
                }
                else
                {
                    history.push(curr->adr);            // Push to stack
                    if (remove(curr->adr.c_str()) == 0) // Remove file from the folder
                    {
                        cerr << "Error removing file: " << curr->adr << endl;
                    }
                }
                delete_node(temp->nextf, curr, prev); // to delete the node which corresponds to the file to be deleted
                if (prev == NULL)
                    prev = temp->nextf;
                else
                    curr = prev->next;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }

        temp = temp->link;
    }
}

void check_for_redundant_file(m_node *&main, stack<path> &history, bool rut, vector<string> &store) // To check for redundant file
{
    m_node *temp1 = main;

    while (temp1 != NULL) // to traverse the main linked list
    {

        node *head1 = temp1->nextf;
        node *prev1 = NULL;

        while (head1 != NULL) // To traverse the linked lists of files at each node for main list
        {
            m_node *temp2 = temp1; /*Temp2 is maintained to check if the copy of file exists
                                   in another folder(whose path is in another node) or not*/

            while (temp2 != NULL) // Traversing main linked list to find copy of the current file in other folders
            {
                node *head2 = nullptr;
                node *prev2 = nullptr;

                if (temp1 == temp2)
                {
                    head2 = head1->next;
                    prev2 = head1;
                }
                else
                {
                    head2 = temp2->nextf;
                    prev2 = NULL;
                }

                while (head2 != NULL) // To traverse the sub linked lists
                {
                    bool key = true;
                    path pt;
                    if (head1->size == head2->size) // If size of two files is same
                    {
                        bool flag = check_for_copy(head1->adr, head2->adr); // To check whether the copy of file exists

                        if (flag)
                        {
                            node *del = compare_diff(head1, head2); // To get the older file if both files are same
                            if (rut)
                            {
                                store.push_back(del->adr.string());
                            }
                            history.push(del->adr);
                            remove(del->adr); // Delete the older file

                            pt = del->adr;
                            if (del == head1)
                            {
                                delete_node(temp1->nextf, head1, prev1); // updating the linked list
                                head1 = prev1;
                            }
                            else
                            {
                                key = false;
                                delete_node(temp2->nextf, head2, prev2);

                                head2 = prev2->next;
                            }
                        }
                    }
                    else if (key)
                    {
                        prev2 = head2;
                        head2 = head2->next;
                    }
                }
                temp2 = temp2->link;
            }
            prev1 = head1;
            head1 = head1->next; // To traverse the next node
        }
        temp1 = temp1->link; // To traverse the next node
    }
}

#endif

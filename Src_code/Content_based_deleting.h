#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "2D_list.h"
#include <tuple>
#include <thread>
using namespace std;
vector<tuple<string, node *&, node *, node *&>> vt;
void delete_file_through_content(m_node *&list, string key) //This function is to delete the files  which contain a specific word in their content

{
    m_node *temp = list;    

    while (temp != NULL)    //To traverse the main linked list
    {
        node *curr = temp->nextf;
        node *prev = NULL;

        while (curr != NULL)    //To traverse the file linked list at each node of main list
        {
            ifstream file(curr->adr.string());  //To read from the file
            if (!file.is_open())
            {
                cerr << "Error opening file." << std::endl;
                return;
            }
            string word;
            while (file >> word)
            {
                if (word == key)
                {
                    vt.push_back({curr->adr.string(), temp->nextf, curr, prev});    
                    break;
                }
            }
            prev = curr;
            curr = curr->next;
        }

        temp = temp->link;  //To traverse the next node
    }   

    if (!vt.empty())
    {
        cout << "Here is the list of the files containing this key-word" << endl;
        for (const auto &it : vt)       //All the files which contain that word will be displayed
        {
            cout << get<0>(it) << endl;
        }
    }
    else
    {
        cout<<endl<< "File with the entered word does not exist" << endl;
        return;
    }

    cout <<endl<<"Enter the Path of the file which you want to delete from above:" << endl;    //User has to choose which of the above displayed files he/she wants to delete
    string path;
    cin >> path;
    for (auto const it : vt)
    {
        if (get<0>(it) == path)
        {
            remove(path);
            delete_node(get<1>(it), get<2>(it), get<3>(it));    //To update the linked list
           cout<<"Successfully deleted\n";
            return;
        }
    }
   
}

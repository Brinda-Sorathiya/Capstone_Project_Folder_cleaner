#ifndef SORT_H
#define SORT_H
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
// Define a mapping between extensions and custom directory names
unordered_map<string, string> extension_to_name = {
    {".jpg", "photos"},
    {".pdf", "PDF_FILES"},
    {".jpeg", "photos"},
    {".mp4", "videos"},
    {".mov", "videos"},
    {".png", "photos"},
    {".cpp", "Programming Files"},

};
/*Here we have made an additional function which looks in the
 folder(containing different type of the files such as images, videos, files containing codes, pdfs) 
and sort the files according to the extensions and devides the folder into subfolder where each subfolder contains same type of the files*/
void sort_files(m_node *&list)
{
    m_node *trav = list;
    int count = 1;

    while (trav != NULL)
    {
        string path = trav->fdr.string(); //Taking directory path from the linked list as a string

        if (!exists(path) || !is_directory(path))   //Check whether the path exists
        {
            cout << "Directory does not exist or is not a directory." << endl;
            return;
        }

        for (const auto &entry : directory_iterator(path))    //Iterating through the  directory
        {
            if (is_regular_file(entry))         //Check whether its a regular file or some sub folder
            {

                string extension = entry.path().extension().string();       //stoeing extension of the current file as a string
                auto it = extension_to_name.find(extension);        //Check if the extension exists in the map defined

                if (it != extension_to_name.end())
                {                                                                 //to check whether that extension is there in Map or not,before creating subfol.
                    string subfolder_path = path + "/" + it->second; // it->second corresponds to Sub folder's Name
                    create_directory(subfolder_path);        //Predefined function in filesystem
                }
            }
        }

        for (const auto &entry : directory_iterator(path))    //iterating entire folder again to move the files to new sub folders
        {
            if (is_regular_file(entry))
            {
                string extension = entry.path().extension().string();
                auto it = extension_to_name.find(extension);

                if (it != extension_to_name.end())  
                {
                    string source_path = entry.path().string();
                    string final_path = path + "/" + it->second + "/" + entry.path().filename().string();
                    rename(source_path, final_path);      //Updating file path to move it to the desired sub foldr.
                }
            }
        }

        cout << "Files in this folder " << count << " are sorted based on extensions in the directory." << endl;
        count++;
        trav = trav->link;
    }
}
#endif

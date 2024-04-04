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
        {".png","photos"},
        {".cpp","Programming Files" },
       
};

//Here we have made an additional function which looks in the folder(containing different type of the files such as images, videos, files containing codes, pdfs) and sort the files according to the extensions and devides the folder into subfolder where each subfolder contains same type of the files
void sort_files(m_node* &list)
{    m_node* trav=list;
    int folder_count=1;

    while(trav!=NULL){
        string directory_path = trav->fdr.string(); // Replace this with the path to your directory

        if (!exists(directory_path) || !is_directory(directory_path)) 
        {
        cout<< "Directory does not exist or is not a directory." << endl;
        return ;
        }

        for (const auto& entry : directory_iterator(directory_path)) 
        {
            if (is_regular_file(entry)){

                string extension = entry.path().extension().string();
                auto it = extension_to_name.find(extension);

                if (it != extension_to_name.end()){    //This codition is used to check whether that extension is there in Map or not,befor creating subfol.
                string subdirectory_path = directory_path + "/" + it->second;   //it->second corresponds to Sub folder's Name
                create_directory(subdirectory_path);
                }

            }
        }

        for (const auto& entry : directory_iterator(directory_path)) 
        {    if (is_regular_file(entry))
             {
                string extension = entry.path().extension().string();
                auto it = extension_to_name.find(extension);

                if (it != extension_to_name.end()) {
                    string source_path = entry.path().string();
                    string destination_path = directory_path + "/" + it->second + "/" + entry.path().filename().string();
                    rename(source_path, destination_path);
                }

            }
        }

        cout << "Files in this folder "<<folder_count<<" are sorted based on extensions in the directory." << endl;
        folder_count++;
        trav=trav->link;

    }
}
#endif

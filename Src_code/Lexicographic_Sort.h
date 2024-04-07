#include <iostream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>
#include "2D_list.h"

namespace fs = std::filesystem;
using namespace std;
using namespace std::chrono;

void SortFileAlplabet(m_node *temp) //Function to sort the files based on lexicographical order
{

    while (temp != NULL)        //To traverse through the linked list
    {

        // check folder path exist or not
        if ((!fs::exists(temp->fdr)) || !fs::is_directory(temp->fdr))   
        {
            cout << "Error: Invalid folder path : temp->fdr" << endl;
            temp = temp->link;
            continue;
        }

        // Vector to store file paths
        vector<fs::path> filePaths;

        // push all file in vector
        for (const auto &a : fs::directory_iterator(temp->fdr))
        {
            if (a.is_regular_file())
            {
                filePaths.push_back(a.path()); // push filepath in vector
            }
        }

        // Sort file paths lexicographically
        sort(filePaths.begin(), filePaths.end());

        // Temporary folder to hold sorted files
        string tempFolder = temp->fdr.string() + "_temp";

        // Create temporary folder if it doesn't exist
        if (!fs::exists(tempFolder))
        {
            fs::create_directory(tempFolder);
        }

        // Move files to temporary folder
        for (const auto &b : filePaths)
        {
            string newPath = tempFolder + "/" + b.filename().string();
            fs::rename(b, newPath);
        }

        // Move files back to original folder
        for (const auto &c : fs::directory_iterator(tempFolder))
        {
            fs::rename(c.path(), temp->fdr.string() + "/" + c.path().filename().string());
        }

        // Remove temporary folder
        fs::remove_all(tempFolder);

        temp = temp->link;
    }

    return;
}

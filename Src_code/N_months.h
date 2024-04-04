#ifndef N_MONTH_H
#define N_MONTH_H
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

#ifndef FUN
#define FUN


// Function for converting a date string to time_t
void parseDateTime(time_t& timestamp, const char* datetimeString, const char* format) 
{
    std::istringstream ss(datetimeString);
    std::tm tmStruct = {};
    ss >> std::get_time(&tmStruct, format);
    timestamp = mktime(&tmStruct);
}

//Function to calculate the month difference between the current time and the creation time of the file
int Months_diff(string date2){  

    const char* datetimeString = date2.c_str();
    const char* format = "%d/%m/%Y";
    time_t createtime;
    parseDateTime(createtime, datetimeString, format);

    auto currentitme = system_clock::now();              // Getting the current time
    time_t cur = system_clock::to_time_t(currentitme);

    struct tm mentioned_time, curr_time;        // Convert time_t to tm structures
    mentioned_time = *localtime(&createtime);
    curr_time = *localtime(&cur);
    int diff = (curr_time.tm_mon + 12 * curr_time.tm_year) - (mentioned_time.tm_mon + 12 * mentioned_time.tm_year);

    return diff;

}

//Function to compare the month difference between two files
node* compare_diff(node* &curr1, node* &curr2)
{           string date1 = curr1->date;
            string date2 = curr2->date;
           
            int time1 = Months_diff(date1);
            int time2 = Months_diff(date2);

            if(time1 > time2) 
            return curr1;

            return curr2;
}
#endif
//Function to delete the files old more than N months
void Delete_files_older_than_N_months(m_node* &main, stack<path> history){

    m_node* temp = main;
    int folder_count = 1;
    while(temp != NULL)
    {
        node* curr = temp->nextf;
        node* prev = NULL;
        while(curr != NULL)
        {
            string date = curr->date;
            int curr_file_diff = Months_diff(date);

            if(curr_file_diff >= 24){
                history.push(curr->adr);
                if(remove(curr->adr.c_str()) == 0)
                {
                   std:: cout << "The empty file is successfully removed." << endl;
                } 
                else 
                {
                    cerr << "Error removing file: " << curr->adr << endl;
                }
                delete_node(temp->nextf, curr, prev);
               
                if(prev == NULL) curr = temp->nextf;
                else curr = prev->next;
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

#endif

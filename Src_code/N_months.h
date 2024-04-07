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
#include <vector>
#include "2D_list.h"

using namespace std::chrono;
using namespace std;
using namespace filesystem;

#ifndef FUN
#define FUN

// Function for converting a date string to time_t
void parseDateTime(time_t &stamp, const char *datetime, const char *format) 
{
    std::istringstream ss(datetime);
    std::tm tmStruct = {};                  // Declaring a object for struct tm
    ss >> std::get_time(&tmStruct, format); // parsing the string into tmstruct object
                                            // Time is parsed according to the format passed
    stamp = mktime(&tmStruct);          // to convert a tm object to an object of time_t type
}

// Function to calculate the month difference between the current time and the creation time of the file
int Months_diff(string date2) // To get the time diffrence in months
{

    const char *datetime = date2.c_str(); // To intialise pointer to array of characters with the date string
    const char *format = "%d/%m/%Y";            // Default format for date
    time_t createtime;
    parseDateTime(createtime, datetime, format); // Calling function to get the date in time_t object

    auto currentitme = system_clock::now();            // Getting the current time
    time_t cur = system_clock::to_time_t(currentitme); // Converting it to time_t

    struct tm m_time, curr_time; // Convert time_t to tm structures
    m_time = *localtime(&createtime);
    curr_time = *localtime(&cur);
    // To caculate the diffrence in months between current time and created date
    int diff = (curr_time.tm_mon + 12 * curr_time.tm_year) - (m_time.tm_mon + 12 * m_time.tm_year);

    return diff;
}
node *compare_diff(node *&curr1, node *&curr2) // Function to compare the month difference between two files

{
    string date1 = curr1->date; // Getting date from the first node
    string date2 = curr2->date; // Getting date from the next node

    int time1 = Months_diff(date1);
    int time2 = Months_diff(date2);

    if (time1 > time2)
        return curr1; // Return pointer to the node which stores the path of older file

    return curr2;
}
#endif
// Function to delete the files old more than N months
void Delete_files_older_than_N_months(m_node *&main, stack<path> history, bool rut, vector<string> &store) // Function to delete the files that are older than N months
{

    m_node *temp = main;
    int count = 1;
    while (temp != NULL) // Traversing the main linked list
    {
        node *curr = temp->nextf;
        node *prev = NULL;
        while (curr != NULL) // To traverse the file linked list of each folder
        {
            string date = curr->date;               // Get the date of the current file as a string
            int file_diff = Months_diff(date); // Calling the function to get month diffrence

            if (file_diff >= 24)
            {
                if (rut)
                {
                    store.push_back(curr->adr.string());
                }
                else
                {
                    history.push(curr->adr); // To push the path of the file to be deleted
                    if (remove(curr->adr.c_str()) == 0)
                    {
                        cerr << "Error removing file: " << curr->adr << endl;
                    }
                }
                delete_node(temp->nextf, curr, prev);

                if (prev == NULL)
                    curr = temp->nextf;
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

#endif

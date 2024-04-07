//included the header files that we defined 
#include "2D_list.h"    //The predefined headerfiles are already included in these files.
#include "scheduled.h"
#include "N_months.h"
#include "Redundant.h"
#include "M_access.h"
#include "Sort_files.h"
#include "Lexicograhic_Sort.h"
#include "Content_based_deleting.h"
#include <tuple>
#include <thread>
vector<tuple<string, node *&, node *, node *&>> vt;
vector<string> store;   
stack<path> history;    //A stack is defined globally which stores the paths of files to be deleted
int main()
{    
    cout << "Enter type of input file(enter c for csv and t for txt):"<<endl;      
    char c;
    cin >> c;
    m_node *list = nullptr;
    if (c == 't')
    {
        string str;
        cout << "Enter the address of the TextFile:- " << endl;    
        cin >> str;         //Taking path of text file as an input
        path s = str;       //Storing the path in the variable of path data type
        ifstream fin(s);    //To read the contents of text file

        if (!exists(s))     //If wrong path is entered
        {
            cout << "The entered path does not exist." << endl;
            return 1;       
        }

        string line;
        while (getline(fin, line))         //reading the input text file line by line 
        {
            if(line.empty())                //to tackle the condition for empty line
            continue; // to skip the successive lines and cheack for next line untill it's not an empty line.
            istringstream iss(line);    //istringstream is used to parse the string into diffrent variables
            string tfdr, name, date;
            int size, count;

            iss >> tfdr >> name >> date >> count;
            string temp = tfdr + "/" + name; 
            

            path file = temp;   
            size = file_size(file);     //To fnd the size of each file

            path folder = tfdr;
            storef(folder, file, size, list, date, count);  /Using storef func. defined in 2D_list header file to insert all data in Linked list/
        }
    }
    else
    {
        string str;
        cout << "Enter the address of the CSVFile:- " << endl;  
        cin >> str;
        path s = str;
        ifstream fin(s);

        if (!exists(s))
        {
            cout << "The entered path does not exist." << endl;
            return 1;
        }

        string line;
        while (getline(fin, line))
        {
            istringstream iss(line);
            if(line.empty())                 //to tackle the condition for empty line
            continue;
            string tfdr, name, date, n;
            int size;
            //As CSV is comma seperated file, we are storing folder path,file name,created date and access count in diffrent variables
            getline(iss, tfdr, ',');   
            getline(iss, name, ',');
            getline(iss, date, ',');
            getline(iss, n, ',');

            string temp = tfdr + "/" + name;    
            int count;
            if (std::all_of(n.begin(), n.end(), ::isdigit))
            {
                count = std::atoi(n.c_str());      //is used to convert count present in the text file as string into integer
            }
            else
            {
              cerr << "Invalid count value: " << n << std::endl;
                // Handle the error or skip this entry
            }
            path file = temp;
            size = file_size(file);

            path folder = tfdr;
            storef(folder, file, size, list, date, count);
        }
    }
    
    
    cout << "Do you want to perform normal cleaning of the file or the schedule cleaning(enter \"n\" for normal cleaning and \"s\" for schedulde cleaning)" << endl << endl;
    cout<<endl<<"NOTE: On choosing scheduled cleaning, you need to wait for the time that you would Enter\n ";
    char k;
    cin >> k;

    bool rut;   //A bool data type variable is maintained to save the choice of user

    if (k == 's')
        rut = true;     //rut is true for Scheduled cleaning,false otherwise
    else
        rut = false;     
    //The functions used later are all defined in our header files
    check_for_empty_file(list, history, rut, store);        
    check_for_redundant_file(list, history, rut, store);
    int m;
    cout<<endl << "What is the minimum number of times the file needs to be accessed to avoid deletion?"<<endl;
    cin>>m;
    delete_less_than_M_access_files(list, m, history, rut, store);
    
    Delete_files_older_than_N_months(list, history, rut, store);
    if (k == 's')
    {   int n;
        cout<<endl<<"Enter the time(in minutes) after which cleaning should be carried out:\n";
        cin>>n;
        cleanFilesAfterInterval(store, n);  //This function is used to delete files after a specific time interval
    }
    else
    {
    cout <<endl<< "Here is the list of files which are recently deleted." << endl;
        while (!history.empty())        //to prinf the stack which stores the paths of the files to be deleted
        {
            cout << history.top() << endl;
            history.pop();
        }
        cout << endl;
    }
    char ch;
  
    cout<<endl<<"Do you want to search for a file containing a specific word and then delete it?(y/n)\n";
      cin>>ch;
    if(ch=='y')
    {
     cout << "Enter the keyword:" << endl;
     string key;
      cin >> key;
    cout<<" Wait for some time till the code searches the word in all text files:"<<endl;
    delete_file_through_content(list,vt, key);   
    }

      char choice1;
      string choice2;
        cout<<endl<<"Do you want to sort the files:?(Enter 'y' for yes, 'n' for no)\n";
        cin>>choice1;
    if(choice1=='y')
    {  
        cout<<endl<<"Do you want both,Lexicographical and extension based sorting? or just the one based on lexicographic?(Enter 'both' for 1st choice)"<<endl;
      cin>>choice2;
      if(choice2=="both")
      {
         SortFileLexicographic(list);
         sort_files(list);
        cout << endl<<"Files sorted succesfully into the desired folders." << endl;
      }
      else            //By default, if user wants sorting, lexicographic sorting will be carried out
      {
         SortFileLexicographic(list);
         cout<<endl<<"Sorted Successfully in Lexicographical order";
      }
        
    }

    return 0;
}


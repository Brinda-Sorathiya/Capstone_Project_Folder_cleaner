# Capstone_Project_Folder_cleaner

## Contribution :

  Here is the list of the constrains on which each member has worked:
  
    -> Brinda Sorathiya : 2D_list.h, Redundunt.h,and their algorithms, Calculated Space and time complexity, code debugging
    -> Mahek Vaghera : M_access.h, Scheduled cleaning, and thier algorithms, additional comments 
    -> Nisarg Bhatia : Sort_files.h, N_Months.h, and their algorithms and maintained the main function
    -> Hardik Vala : Content_based_deletion.h, Lexicographical_Sort, and their algorithms and Maintained the main function


## Brief Information:
**Important Note** : TO enhance readability of the code, we have defined our own header files which are then included in our main code. All those extra header files are also uploaded.
             All those extra files must be downloaded on the system before running the code.
             
             Also, an existing header file -filesystem- is used which **requires C++17**. Older versions of Compiler might not support filesystem.

    Our C++ code works as a folder cleaner to remove the following kind of files:
    (1) Empty files
    (2) Files whose Copies exist
    (3) Files which haven't been accesssed for atleast some specific number of times.
    (4) Files older than a specific period of time
       - User enters a specific time as an input and based on that the above feature executes.

    In addition to this, we have added four additional features to make the folder cleaner more efficient. Following are the additional featurs:
    (1) Sorting the files based on the extension
    -Sub folders are created and files based on the extension are pushed to the desired sub folders
    (2) Sorting on the basis of lexicographical order
    (3) Scheduled cleaning
    The above feature provides the user with a choice of scheduling the cleaning process of a specific folder. Although the normal/Immediate 
    cleaning feature is also provided and user is asked to select either of them
    (4) Word finder
    It finds a specific text file having a word that the user enters deletes that file.

    *** The code takes a specific text file as an input(as given in the problem) which contains the folder's path and other details
     in the following format in each line:
     Folder_path       File_name    File_creation_Date(dd/mm/yyyy)    Access_count_of_file

     (NOTE:The above Information is space seperated in the txt file.)


    *** For the CSV Input file:
    The above input format should be there in CSV file as well with comma(,) seperation instead of space Seperation.
                
Data structures used in the code :
    Here mainly four kinds of data structures used in the code - 2D linked list, stacks, vectors, tuples

    2D linked list :
          Here, we have used 2D linked list. It formed by the combination of the 2 kinds of the node one kind of the node is m_node which it represents the folder and it contains adress of the current folder,head and tail pointer to the linked list of the files in the folder and link to the next pointer. 
          The other kind of the node represents the file and contains some information about the file.
          
          Here according to the constrains, two kind of the data structures can be applied - array or linked list. Because number of the files is not fixed so here 2D linked is used to reduce space complexity.Yes, a linked list has linear time direct access worse than an array but in any function of the code it's not needed to do direct access. Also deletion is used many times in the functions which can be easily handled through the 2D linked list in constant time complexity. Also by maintaining the tail pointer new node can be easily appended in constant time complexity.
          
          So as per the convenience in the time complexity and space complexity,2D linked list is the more optimum data structure so we have used a 2D linked list to store data.
          
          Also, here stack is used to store the history of recently deleted files.

        here is the list of the function in which 2D linked list is used,
            -> from 2D_list.h : append, storef, delete_node
            -> from Redundunt.h : check_for_empty_file, check_for_redundant_file
            -> from N_Months.h : Delete_files_older_than_N_months
            -> from M_access.h : delete_less_than_M_access_files
            -> from Lexicographical_Sort.h : SortedFileAlplabet
            -> from Content_based_deleting.h : delete_file_through_content

    Stacks :
            Here we have used stack to store the history of the deleted files so that list of the recently deleted files can be showed.

            Here is the list of the function in which stack is used,
            -> from Redundunt.h : check_for_empty_file, check_for_redundant_file
            -> from N_Months.h : Delete_files_older_than_N_months
            -> from M_access.h : delete_less_than_M_access_files

    Vector : 
            Here is the list of the function in which vector is used,
            -> from Redundunt.h : check_for_empty_file, check_for_redundant_file
            -> from N_Months.h : Delete_files_older_than_N_months
            -> from M_access.h : delete_less_than_M_access_files
            // In the above folder if user wants to do scheduled deletion than all the paths of the file is stored in vector
            -> from Scheduled.h : cleanFilesAfterInterval  //Used vector to fetch the paths of the files which needs to be deleted

    Tuples : 
            Here is the list of the function in which tuple is used,
            -> from Content_based_deleting.h : delete_file_through_content 
                // here vector of tuples is used because according to the functionality of the function delete_file_through_content here 4 kind of datas with defferent data types need to be stored so to handle a                       group of different data types tuple is only the optimum way.
                
    Unordered_map :
           Here is the list of the function in which tuple is used,
           -> from Sort_files.h : sort_files
           //The reason for using an unordered map is because it stores the file extensions as keys and sub folders' names as values, which is then 
    used to sort the files based on their extensions and create a sub folder for file of each extension. Unorderd map is preferred because it has a
    search time complexity O(1) in average case unlike an ordered map in which search has time complexity O(log n).
     

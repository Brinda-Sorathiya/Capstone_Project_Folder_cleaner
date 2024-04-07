# Capstone_Project_Folder_cleaner

Data structures used in the code :
    Here mainly for kind of data structures used in the code - 2D linked list, stacks, vectors, tuples

    2D linked list :
          Here, we have used 2D linked list. It formed by the combination of the 2 kinds of the node one kind of the node is m_node which it represents the folder and it contains adress of the current folder,            head and tail pointer to the linked list of the files in the folder and link to the next pointer.  The other kind of the node represents the file and contains some information about the file. 
          Here according to the constrains, two kind of the data structures can be applied - array or linked list. Because number of the files is not fixed so here 2D linked is used to reduce space complexity.           Yes, a linked list has linear time direct access worse than an array but in any function of the code it's not needed to do direct access, also deletion is used many times in the functions which can be             easily handled through the 2D linked list in constant time complexity. Also by maintaining the tail pointer new node can be easily appended in constant time complexity. So as per the convenience of the            time complexity and space complexity 2D linked list is the more optimum data structure so we have used a 2D linked list to store data.
          Also here stack is used to store the history of recently deleted files.

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

Contribution :

        Here is the list of the constrains on which each member is worked,

        -> Brinda Sorathiya : 2D_list.h, Redundunt.h, Calculated Space and time complexity
        -> Mahek Vaghera : M_access.h, Scheduled cleaning, Wrote the algorithms
        -> Nisarg Bhatia : Sort_files.h, N_Months.h, Wrote the algorithms
        -> Hardik Vala : Content_based_deletion.h, Lexicographical_Sort, Maintained the main function 

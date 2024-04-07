#include "2D_list.h"
#include<thread>
using namespace std;
namespace fs = std::filesystem;
using namespace std::chrono;
//Functiont to do a shedule cleaning of a file
void cleanFilesAfterInterval(const vector<string> &paths, int interval) /*A vector of filepath of the files to be deleted,
                                                                         interval in minutes after which file has to be deleted */                       
{   cout<<"wait for "<<interval<<" minutes for file deletion,then the code will run automatically:"<<endl<<endl; //takes input minutes from user 
    auto init_time = steady_clock::now(); //shows current time of system

    while (true)
    {
        auto time_diff =steady_clock::now() - init_time; //diffrence between system's current time and already stored time
        auto min_diff =duration_cast<minutes>(time_diff).count(); //convert elapsed time duration into minutes

        if (min_diff >= interval)
        {
            for (const auto &file_path : paths) //iterates through vector of file path 
            {
                if (fs::exists(file_path) && fs::is_regular_file(file_path))  // if file exists and a regular file
                {
                    fs::remove(file_path); //delete file
                    std::cout << "Deleted: " << file_path << std::endl;
                }
            }
            break; // Exit the loop after cleaning files
        }
        // Sleep for a short duration to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
      

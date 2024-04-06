#include "2D_list.h"
#include<thread>
using namespace std;
namespace fs = std::filesystem;
using namespace std::chrono;
void cleanFilesAfterInterval(const vector<string> &file_paths, int interval_minutes)                          
{   cout<<"wait for "<<interval_minutes<<" for file deletion:"<<endl;
    auto start_time = steady_clock::now();

    while (true)
    {
        auto elapsed_time =steady_clock::now() - start_time;
        auto elapsed_minutes =duration_cast<minutes>(elapsed_time).count();

        if (elapsed_minutes >= interval_minutes)
        {
            for (const auto &file_path : file_paths)
            {
                if (fs::exists(file_path) && fs::is_regular_file(file_path))
                {
                    fs::remove(file_path);
                    std::cout << "Deleted: " << file_path << std::endl;
                }
            }

            break; // Exit the loop after cleaning files
        }

        // Sleep for a short duration to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
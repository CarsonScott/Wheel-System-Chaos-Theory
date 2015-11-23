#include "SystemLog.hpp"

SystemLog::SystemLog()
{
    time = 0;
    goal = 0;
}

void SystemLog::record_system(float dt, float spin)
{
    time += dt;
    if(time >= goal)
    {
        points.push_back(Point(goal, spin));
        graph.plot(goal, spin);
        goal += .1;
    }
}

void SystemLog::save_to_file(std::string filename)
{
    std::ofstream file;
    file.open(filename.c_str());
    file << "<?xml version='1.0' encoding='UTF-8'?>\n";
    file << "<graph>\n";

    for(int i = 0; i < points.size(); i++)
    {
        file << "<point>\n";
        file << "<x>\n" << points[i].x << "\n</x>\n";
        file << "<y>\n" << points[i].y << "\n</y>\n";
        file << "</point>\n";
    }

    file << "</graph>\n";
    file.close();
}

float SystemLog::get_elapsed_time()
{
    return time;
}

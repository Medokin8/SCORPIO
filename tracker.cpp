#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>


using namespace std;

struct cpu_stat {
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
};




int main(){

    //Reading CPU
    while(1)
    {   
        string data_stat;
        
        ifstream reading_data;
        reading_data.open("/proc/stat");

        //skip all usage of CPU
        getline(reading_data, data_stat);

        struct cpu_stat cpu_sta_0, cpu_stat_1;
        
        sleep(1);


        

        //Save to file
        ofstream saving_data;
        saving_data.open ("system_data_readings.txt");
        saving_data << "Writing this to a file.\n";
        saving_data.close();
        sleep(5);
    }
}
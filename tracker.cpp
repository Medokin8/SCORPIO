#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <sys/statvfs.h>


using namespace std;

struct cpu_stat{
    string core;
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
    unsigned int steal;
    unsigned int guest;
    unsigned int guest_nice;
};

struct temp_stat{

};

void Reading_CPU(ofstream & saving_data)
{
    string data;
    cpu_stat cpu;

    ifstream reading_data;
    reading_data.open("/proc/stat");
    
    // ofstream saving_data;
    // saving_data.open ("system_data_readings.txt");

    getline(reading_data, data);

    stringstream iss(data);
    string cpu_label;
    iss >> cpu_label;

    cpu_label = cpu_label + " ";
    while(cpu_label != "intr")
    {
        iss >> cpu.user;
        iss >> cpu.nice;
        iss >> cpu.system;
        iss >> cpu.idle;
        iss >> cpu.iowait;
        iss >> cpu.irq;
        iss >> cpu.softirq;
        iss >> cpu.steal;
        iss >> cpu.guest;
        iss >> cpu.guest_nice;
        
        long long total_time = cpu.user + cpu.nice + cpu.system + cpu.idle + cpu.iowait + cpu.irq + cpu.softirq;
        //cout << "total_time:    " << total_time << endl;

        long long total_idle = cpu.idle - cpu.iowait;
        //cout << "total_idle:    " << total_idle << endl;

        double load_core = 100.0 * (total_time - total_idle) / total_time;
        //cout << cpu_label << ":          " << load_core <<" %" << endl;
        //cout << "diff:          " << (total_time - total_idle) << endl;

        //cout << cpu_label;
        saving_data << cpu_label;
        saving_data << "         " << load_core <<" % \n";

        //cout<<endl;

        getline(reading_data, data);

        stringstream iss(data);
        iss >> cpu_label;
    }
    
    reading_data.close();
}


void Reading_TEMP(ofstream & saving_data)
{
    string data;
    double numeric_data;

    ifstream reading_data;
    //string directory = "/sys/class/thermal/cooling_device";
    string directory = "/sys/class/thermal/thermal_zone";
    int i = 0;

    //string num_dir = directory + to_string(i) + "/type";
    string num_dir = directory + to_string(i) + "/temp";
    
    reading_data.open(num_dir);

    while(reading_data.is_open())
    {
        getline(reading_data, data);
        numeric_data = stod(data);

        //cout << num_dir << "   " << data << endl;

        string core = "Core" + to_string(i);
        saving_data << core ;
        //saving_data << "        " <<data <<" C \n";
        saving_data << "        " << numeric_data/1000.0 <<" C \n";

        reading_data.close();

        i++;

        //num_dir = directory + to_string(i) + "/type";
        num_dir = directory + to_string(i) + "/temp";

        reading_data.open(num_dir);
    }
    
}


void Reading_RAM(ofstream & saving_data)
{
    string data;

    ifstream reading_data;
    string directory = "/proc/meminfo";

    reading_data.open(directory);
    
    //MemTotal: 
    getline(reading_data, data);
    saving_data << data << "\n";

    //MemFree:
    getline(reading_data, data);
    saving_data << data << "\n";

    //MemAvailable:
    getline(reading_data, data);
    saving_data << data << "\n";

    reading_data.close();
}


void Reading_DISC(ofstream & saving_data)
{
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        cout << "Error: unable to retrieve file system statistics" << endl;
    }
    else
    {
        unsigned long long free_space = stat.f_bavail * stat.f_frsize;
        //cout << "FreeDiscSpace: " << free_space/1000.0 << " kb\n";
        saving_data << "FreeDiscSpace:    " << free_space/1000.0 << " kb\n";
    }
    
}


int main(){

    ofstream saving_data;
    saving_data.open ("system_data_readings.txt");

    Reading_CPU(saving_data);
    Reading_TEMP(saving_data);
    Reading_RAM(saving_data);
    Reading_DISC(saving_data);

    

    saving_data.close();

    return 0;
}
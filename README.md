# SCORPIO
Recruitment task for the Software department in SCORPIO

start_tracker.sh
  -  runs prebuild tracker.exe

tracker.exe
  - compiled tracker.cpp saved as tracker.exe


tracker.cpp
  - program in C++


steps_to_start_programm_with_start_of_system.txt
  - basic short instruction what to do to make program run when system starts and some notes about scripts and program


make_tracker.sh
  - script to make a new version of tracker.exe
  

NOTE:
  !!!  Befor running the program you should chage the directory of saving file, because the one after download is /home/nikodem/   !!!
  Saving values of Sended and Received bytes by network device is not working properly (always write 0).
  It is because of some problem with missing structure if_data and ifd->ifi_obytes, ifd->ifi_ibytes.

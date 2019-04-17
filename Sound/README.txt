#---------------------------------Sound Level Sensor-----------------------
Sound level meter project made by KHANH DO, Feb.2018.

This project uses a Raspberry PI 3 Mode B as a sound sensor. A USB sound card
with microphone and a RJ45 cable are needed as peripheral. The application runs
periodically every second and take record from microphone at a sample rate of
16000Hz. The sound is then calculated into 80 pieces of RMS value and displayed
as bar chart on terminal screen. If communication is enable ( conditional
complication), the sound will be re-calculated into 8 pieces of Fast Level data
and sent out to a PHP server program.

List of Contents:
1. Configuration instructions
2. Installation instructions
3. Operating instructions
4. File manifest
5. Copyright and license
6. Contact information

1. Configuration instructions

- Raspberry PI 3 Mode B
- USB sound card with microphone
- RJ45 straight-through cable
- SD card
- USB cable

2. Installation instructions

Firstly, insert SD card to Raspberry PI 3 . Secondly, connect RJ45 cable from
Raspberry to internet.Initialize Raspberry. Then connect sound card to Raspberry.
Connect microphone to sound card. Finally, connect USB cable from Raspberry to 5V
power supply (PC or laptop). Make sure that you could receive IP address via email.

3. Operating instructions

Open Putty, enter IP address that you received via email into Putty. Enter username
and password. Then go to file document of this application by using command "cd appdev"
. Make file to compile the application by using command "make" .List all the file by using
command "ls" to see file "sound.a". To run this application, use command "./sound.a", and 
you would see the bar which is illustrated for the sound. Speak to the micrphone to record
the sound. The duration of recording is 1 second. 8 pieces of data would be saved to file
sound_log.txt . Stop recording by pressing Ctrl + C.

4. File manifest
	4.1 main.c
		The file which is the main file containning the functions of other .c file to run the program.
	4.2 sound.c (included header files sound.h, comm.h, and screen.h)
		Display information of WAVE file format and display .wav file data.
	4.3 screen.c (included header files screen.h)
		Display .wav file data in bar-diagram.
	4.4 comm.c (included header file comm.h)
		Send data to server.
	4.5 makefile
		Compile all the file.

5. Copyright and license

6. Contact information

KHANH DO
Dept. of Information Technology
Vaasa University of Applied Sciences
Woffintie 30, 65100, Vaasa, Finland
Home: http://www.cc.puv.fi/~e1700699
email: e1700699(at)edu.vamk.fi


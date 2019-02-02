# Plotter
All the codes for the CNC Plotter machine

The following softwares are required for plotter
1. Arduino IDE
2. Processing 3.4
3. Inkscape (For creating Gcodes)

Running Instructions-
1. sudo chmod 777 /dev/tty*
2. Upload the arduino_CNC.ino file to the arduino UNO
3. Open the gcode_executor.pde file
4. Select port by pressing p
5. Make sure that the pen is at home position. If not use the plotter_test.ino to reset the plotter to home position
6. Press g to stream gcode and select the gcode which has to be drawn


Important resources-
1. Link to the tutorial - https://www.youtube.com/watch?v=szXNpI4GydA
2. Download Processing 3.4 - https://processing.org/download/
3. Download Inkscape - https://inkscape.org/release/inkscape-0.92.3/
4. Gcode extension for inkscape - https://github.com/martymcguire/inkscape-unicorn

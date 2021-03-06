Do not forget to add this folder and other subfolders if needed to MATLAB Path.
Check also ../ReadMe.txt.
Run main.m to test.

This sample is an example of robot localization in dead-reckoning when inside (below the line) and with GPS outside (above the line). Controls are z,s,q,d keys, zoom with +,- and stop with ESC.

In the main loop (see main.m), the state equations of a simple tank robot (see f.m, the state vector is composed of the x,y position of the robot, its heading and its speed) are integrated using Euler method to simulate the dynamics of the robot, taking into account keyboard inputs (see keycontrol.m, the inputs in the state equations corresponds to the rotating speed and the acceleration). Measurements with some bias and/or random noise are available depending on whether the robot is in the upper part of the environment (to simulate GPS availability when outside a building) or not. Heading measurement is supposed to be available at all time to simulate a compass on the robot (see g.m).

An interval observer is made to fuse the different sensors measurements and the approximate knowledge of the robot state equations (see f_hat.m). For that, interval arithmetic operations and contractors are used (+, -, *, cos, sin, intersection of intervals, etc.). This observer computes an estimate of the robot position, represented by a red box. This observer could be used almost directly to estimate the position of a real robot in similar conditions to the simulated one of this sample.

As expected, we see that the red box estimating the position of the robot is growing over time (dead-reckoning), unless GPS measurements are available.

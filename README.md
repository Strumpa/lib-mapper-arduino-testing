# lib-mapper-arduino-testing
testing libmapper arduino library on ESP32
please find the tester I tried using, Eduardo had suggested that I should start building on Mathias' Example_CppApi.ino in PlatformIO.
I thought that my code would work for creating float vectors of length SIG_SIZE and adding them to the signals. 

I guess the issue comes from my calls to add_signal but I can't tell why it breaks after values of SIG_SIZE>5.

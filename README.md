# jw-d2xx
Simple wrapper for an FTDI DLL to Java JNI

This library provide a simple wrapper for an FTDI DLL to be used in a Java application.
This wrapper is another DLL that has functions declarated as required by the Java Native Interface (JNI).
To avoid any licesing issue, the original DLL (input) and the resulting DLL to be loaded in the Java application (output) are not included. The repository includes only the C++ code that adjusts the interface, and a SConstructor file to build the DLL.
To finish building the project, download the D2XX DLL from FTDI website and add it to the same folder.
It is also necessary to have Python and Scons installed to build the project (yes, it is an aditional dependency, sorry. I just wanted to try scons to see how good it was.)

Thank you :blush:

Wolfgang

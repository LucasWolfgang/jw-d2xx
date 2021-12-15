# jw-d2xx
Simple wrapper for an FTDI DLL to Java JNI

This library provide a simple wrapper for an FTDI DLL to be used in a Java application. This wrapper is another DLL that has functions declarated as required by the Java Native Interface (JNI). To avoid any licesing issue, the original DLL (input) and the resulting DLL to be loaded in the Java application (output) are not included. The repository includes only the C++ code that adjusts the interface, and a SConstructor file to build the DLL.
- To finish building the project, download the D2XX DLL from FTDI website and add both the static library (.lib) and the header(.h) file to the same folder.
- It is necessary to have Python and Scons installed to build the project (yes, it is an aditional dependency, sorry. I just wanted to try scons to see how good it was.)
- It is currently building correctly using Microsoft Visual C++ (MSVC 19.30.30706 for x86), which is the default using by scons in a Windows environment. If you are able to do the same using CygWin, MSYS2 or MinGW directly please open an issue or a pull request, since I really want to know if these DLLs can only be used with MSVC, or it was me that was doing something wrong.

Thank you :blush:

Wolfgang

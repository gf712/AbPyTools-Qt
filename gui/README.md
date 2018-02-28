Frontend interface of AbPyTools-Qt in C/C++ using Qt library.

`main.cpp`
> Main routine that starts the GUI.

`mainwindow.cpp/h`
> MainWindow class\
This is the parent class that controls all the widgets and frames and connects the frontend to the backend.

`newsequencedialog.cpp/h`
> newSequenceDialog class\
This is a child of MainWindow. It allows the user to add a new antibody chain with a given sequence and numbering scheme.\
The corresponding window is opened from the main window: File -> New.

`chainGroups.cpp/h`
> ChainGroups class\
This is not directly involved in the GUI (at least for now). It acts as a container, similar to ChainCollectionCPP, but designed to interact with the frontend more directly.
This class also can point to several ChainCollectionCPP. \
This allows the user to work with several different groups of sequences at the same time, i.e.
one set of sequences but with different numbering schemes.
 
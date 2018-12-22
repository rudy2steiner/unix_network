# unix network programming(UNP)
* tcp socket bio
* nio(select)

# lib .a and .so
Static libraries (.a files)
Shared objects (.so files)
A static library(.a) is a library that can be linked directly into the final executable produced by the linker,
it is contained in it and there is no need to have the library into the system where the executable will be deployed.

A shared library(.so) is a library that is linked but not embedded in the final executable,
so will be loaded when the executable is launched and need to be present in the system where the executable is deployed.

A dynamic link library on windows(.dll) is like a shared library(.so) on linux but there are some differences between
the two implementations that are related to the OS (Windows vs Linux) :

A DLL can define two kinds of functions: exported and internal. The exported functions are intended to be called by other modules,
as well as from within the DLL where they are defined. Internal functions are typically intended to be called only from within the DLL where they are defined.

An SO library on Linux doesn't need special export statement to indicate exportable symbols, since all symbols are available to an interrogating process.

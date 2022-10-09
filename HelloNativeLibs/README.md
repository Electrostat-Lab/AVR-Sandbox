# Native Libraries development using GCC

<a name="TOPICS"></a>

## Contents of this tutorial: 
1) Static V.S. Dynamic Native libraries.
2) Simple project compilation using gcc for intel/arm processors V.S. avr-gcc.


## 1) Static V.S. Dynamic Native libraries:

| `Objective` | `Static Native libraries` | `Dynamic Native libraries` | 
|-------------|---------------------------|----------------------------|
| Definition | Are object files that includes all the sources for the target compiled project including the external included sources | Are object files that includes the project sources only 
| Other names | Compile-time libraries | Shared or Runtime libraries |
| Time of linking | At the compile time, the static object files are linked to the project and compiled with the project sources to an executable file | At the runtime, the loader loads the runtime library |

--------------------------------------------------------
## 2) Simple project compilation using intel gcc V.S. avr-gcc: 

- Quick Overview:

| `Compiling for intel/arm processors` | `Compiling for avr MCUs` | 
|--------------------------------------|--------------------------|
| For intel/arm processors, it's far direct to compile object files and the obejct files are compiled into shared or dynamic libs by default unless specified `-static` compiler option explicitly. | Object files are compiled into static object files by default and the compiler don't support dynamic compilation | 

1) Compiling the project into a dynamic/shared (or runtime) library for intel processors: 


2) Compiling the project into a static (or compile-time) library for intel processors:


3) Compiling the project into a dynamic/shared (or runtime) library for avr MCUs: 


4) Compiling the project into a dynamic/shared (or runtime) library: 



- Analysis of the compiler command and command options: 


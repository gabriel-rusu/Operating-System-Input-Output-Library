<p align="center">
  <a href="" rel="noopener">
 <img width="25%" height="25%" src="res/ubuntu-logo.png" alt="Project logo"></a>
</p>

<h1 align="center">Operating System Input Output Library</h1>

<p align="center"> The os_io.h header defines three variable types, several macros, and various functions for performing buffered input and output operations with files.
    <br> 
</p>

## 📝 Table of Contents
- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Built Using](#built_using)
- [Contributing](../CONTRIBUTING.md)
- [Authors](#authors)

## 🧐 About <a name = "about"></a>
 The following function signatures are exported by the os_io.h library:
```C
SO_FILE *so_fopen(const char *pathname, const char *mode);
int so_fclose(SO_FILE *stream);
int so_fileno(SO_FILE *stream);
int so_fflush(SO_FILE *stream);
int so_fputc(int c, SO_FILE *stream);
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream);
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream);
int so_fseek(SO_FILE *stream, long offset, int whence);
long so_ftell(SO_FILE *stream);
```
To use this functions you must add the os_io.h header in your source and specify at compile time where the library can be found
## 🏁 Getting Started <a name = "getting_started"></a>
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
To use the os_io.h library on your projects you must have:

* for UNIX based operating systems:
  * gcc - is a tool from the GNU Compiler Collection used to compile and link C programs

### Installing
This is a step by step series of examples that tell you how to get a development env running.

* Linux:
  * start by updating the packages list
    ```bash
    $sudo apt-get update
    ```
  * install the build-essential package(a package of new packages including gcc, g++ and make) by typing:
    ```bash
    $sudo apt-get install build-essential 
    ```
## 🔧 Running the tests <a name = "tests"></a>
If you want to run the automated tests for Linux system you must follow the following steps:
* clone the repository by copping the following command in your terminal:
  ```
  git clone https://github.com/gabriel-rusu/Operating-System-Input-Output-Library.git
  ```
* go into the project director and run the following command:
  ```bash
  make test
  ```
* the results of the tests will be in the newly created file result.out

## 🎈 Usage <a name="usage"></a>
If you want to use the ***os_io.so*** library in your projects then you must add the ***os_io.h*** header in the desired source file and specify at the compile time the path to the os_io.so library.

* running the following command in the project director will generate the os_io.so:
  ```bash
  make build
  ```


## ⛏️ Built Using <a name = "built_using"></a>
- [Visual Studio Code](https://code.visualstudio.com/) - code editor
- [GCC](https://gcc.gnu.org/) - used to compile the library on my Linux machine


## ✍️ Authors <a name = "authors"></a>
- [@gabriel-rusu](https://github.com/gabriel-rusu) - implementation


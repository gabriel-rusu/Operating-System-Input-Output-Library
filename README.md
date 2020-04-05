<p align="center">
  <a href="" rel="noopener">
 <img width="25%" height="25%" src="res/ubuntu-logo.png" alt="Project logo"></a>
</p>

<h3 align="center">Operating System Input Output Library</h3>

<div align="center">

  [![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> The os_io.h header defines three variable types, several macros, and various functions for performing buffered input and output operations with files.
    <br> 
</p>

## 📝 Table of Contents
- [About](#about)
- [Getting Started](#getting_started)
- [Deployment](#deployment)
- [Usage](#usage)
- [Built Using](#built_using)
- [TODO](../TODO.md)
- [Contributing](../CONTRIBUTING.md)
- [Authors](#authors)
- [Acknowledgments](#acknowledgement)

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
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites
To use the os_io.h library on your projects you must have:

* for UNIX based operating systems:
  * gcc - is a tool from the GNU Compiler Collection used to compile and link C programs

### Installing
This is a step by step series of examples that tell you how to get a development env running.

* Linux:
  * start by updating the packages list
    ```bash
    $sudo apt update
    ```
  * install the build-essential package(a package of new packages including gcc, g++ and make) by typing:
    ```bash
    $sudo apt install build-essential 
    ```
## 🔧 Running the tests <a name = "tests"></a>
Explain how to run the automated tests for this system.

### Break down into end to end tests
Explain what these tests test and why

```
Give an example
```

### And coding style tests
Explain what these tests test and why

```
Give an example
```

## 🎈 Usage <a name="usage"></a>
Add notes about how to use the system.

## 🚀 Deployment <a name = "deployment"></a>
Add additional notes about how to deploy this on a live system.

## ⛏️ Built Using <a name = "built_using"></a>
- [Visual Studio Code](https://code.visualstudio.com/) - code editor
- [GCC](https://gcc.gnu.org/) - used to compile the program on my Linux machine


## ✍️ Authors <a name = "authors"></a>
- [@RusuGabriel](https://github.com/RusuGabriel) - implementation


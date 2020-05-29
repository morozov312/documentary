# documentary (Alpha 1.0)
[![Build Status](https://travis-ci.org/morozov312/geometry.svg?branch=master)](https://travis-ci.org/github/morozov312/documentary)
# The Repository
This repository is a course project of discipline named "Software Development Technologies", during the development, we improved our skills of team-working using git, CI, code-style and unit-testing.
# Documentary
This program compiles documentation in html page format based on comments in source code. Here you can see  [supported programming languages](https://github.com/morozov312/documentary/wiki)
# How it works?
<p>
1)Installation </br>
  $ git clone https://github.com/morozov312/documentary.git && cd documentary && make install </br>
2)Running: </br>
  Running from local git repository: make run(default src and out dir)</br>
  Running from anywhere: documentary <args> </br>
  You can use "documentary --help" for details </br>
  Use "documentary -inpdir --help" or "documentary -outdir --help" for more information about arguments </br>
</p>
<b>!important</b></br>
<i>1) Don't use more than 30 file in a folder and don't try to process files which larger than 
50 000 lines or witch length of lines exceeds 500 characters. </br>
In this case, everything that is not included in the working range of the program will not be processed. </br>
2) For more correct display of documentation you can apply code style,such as Clang-format, to your document, but this is optional.</i>
<h1>Project build</h1>
<p>
This project uses Makefile to build. Command's which you can use: </br>
$ make </br>
Builds this project into executable files which will be located in bin folder </br>
$ make install </br>
Builds this project into executable files and replaces them to root folder </br>
$ make uninstall </br>
Deletes all installed files from root </br>
$ make reinstall </br>
Reinstall all installed files </br>
$ make run </br>
Runs program to generate documentation on this project surce files </br>
$ make check </br>
Tests existing functions using the library ctest.h </br>
$ make clean </br>
Removes assembly artifacts in folders ./bin and ./build and all html pages which you created in the folder ./docs </br>
$ make clean_html </br>
Removes generated html files in folder ./docs </br>
Compiler: gcc </br> OS you can use is Linux</br>
</p>
<h1>Example</h1>
Example of work and finished documentation developed by this program you can find in folder ./example </br></br> 
<p align="center">
  <img alt="example" src="./img/ex.png">
</p>


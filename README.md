# documentary (beta 1.0)
[![Build Status](https://travis-ci.org/morozov312/geometry.svg?branch=master)](https://travis-ci.org/github/morozov312/documentary)
# The Repository
This repository is a course project of discipline named "Software Development Technologies", during the development, we improved our skills of team-working using git, CI, code-style and unit-testing.
# Documentary
This program compiles documentation in html page format based on comments in source code. Here you can see  [supported programming languages](https://github.com/morozov312/documentary/wiki)
# How it works?
<p>
1) Download or clone this repository on your PC </br>
2) Use make to build project </br>
3) Use ./bin/documentary -inpdir "path" to run program and find all source files on path </br>
4) Enjoy your documentation which is located in folder ./docs </br>
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
$ make run </br>
runs program </br>
$ make check </br>
tests existing functions using the library ctest.h </br>
$ make clean </br>
removes assembly artifacts in folders ./bin and ./build and all html pages which you created in the folder ./docs </br>
$ make html_clean </br>
removes generated html files </br>
compiler: gcc </br> OS you can use is Linux and MacOS </br>
</p>
<h1>Example</h1>
Example of work and finished documentation developed by this program you can find in folder ./example </br></br> 
<p align="center">
  <img alt="example" src="./img/example.png">
</p>


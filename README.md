# documentary (beta 1.0)
[![Build Status](https://travis-ci.org/morozov312/geometry.svg?branch=master)](https://travis-ci.org/github/morozov312/documentary)
# The Repository
This repository is a course project in the discipline "Software Development Technologies", during the develop of which we improve our the skills of team-working on a github, CI, code-style, unit-testing and basic git commands.
# Documentary
This program compiles documentation on comments in source code one of the [supported programming languages](https://github.com/morozov312/documentary/wiki) in format html page.
# How it works?
<p>
1) Download or clone this repositoy on your PC </br>
2) Put the path to the file where you want to compile the documentation in the file ./path/path.txt </br>
3) From the project directory run in terminal command make && make run </br>
4) Enjoy your documentation which is located in folder ./docs </br>
</p>
<b>!important</b></br>
<i>1) Don't use more than 10 paths to a file at a time and don't try to process documents that are larger than 
50 000 lines or the length of lines in which exceeds 500 characters. </br>
In this case, everything that is not included in the working range of the program will not be processed. </br>
2) For more correct display of documentation you can apply code style,such as Clang-format, to your document, but this is optional.</i>
<h1>Project build</h1>
<p>
This project uses Makefile to build. Command's which you can use: </br>
$ make </br>
Build this project into executable files that will be located in the folder ./bin after this program will be ready to work.</br>
$ make run </br>
run program </br>
$ make check </br>
will test existing functions using the library ctest.h </br>
$ make clean </br>
remove assembly artifacts in folders ./bin and ./build and all html pages wich you created in the folder ./docs </br>
compiler: gcc   OS wich you can use by default Linux or MacOS </br>
</p>
<h1>Example</h1>
Example of work and finished documentation developed by this program you can find in folder ./example </br>
<p align="center">
  <img alt="example" src="./img/example.png">
</p>


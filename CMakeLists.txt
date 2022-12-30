cmake_minimum_required(VERSION 3.15) 

set(PROJECT_NAME test)				 		 
project("${PROJECT_NAME}")			 	


set(CMAKE_CXX_STANDARD 17)			 
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("Sounds/")
include_directories("Images/")

add_executable("${PROJECT_NAME}" bananacat.cpp
                                 banan.h
                                 Images/background.png
                                 Images/banan.png
                                 Images/bananacat.png
                                 Sounds/sad.ogg
                                 Sounds/meow.ogg)	
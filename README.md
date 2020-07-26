BStarTree
====================

This repository has a project with the implementation of a BStarTree.

It is written in C++.

The code of the BStarTree is independent of platform.

Is has two possible main files:

* [Codes](#markdown-header)
	* [A main that triggers unit test;](#markdown-header-emphasis)

	* [A Qt project to manage the BStarTree (With Gui).](#markdown-header-strikethrough)
	
The library used to make the Unit Test is the Catch v2.12.3. The code is already in this repository.

The Qt project generates images of the BStarTree, using the lib Graphviz.
Install this lib in your computer for you to be able to create such images.

The code was written containing the Doxygen documentation.

- - -

You have several options to build the project: 
====================

* [Build tools](#markdown-header)
	* [Makefile (using the file named MakefileGeneral);](#markdown-header-emphasis)
	* [CMake.](#markdown-header-emphasis)
	* [Qt Project (With QMake).](#markdown-header-emphasis)

The project has no leaks (Fully tested with Valgrind).

All the unit tests are ok.

- - -

The functionalities available are: 
====================

* [Functionalities](#markdown-header)
	* [Insert;](#markdown-header-emphasis)
	* [Search;](#markdown-header-emphasis)	
	* [Remove.](#markdown-header-emphasis)
	
- - -

Sample images: 
====================

![Alt text](images/sample.png)


Qt gui project: 
====================
The qt gui application gui is shown below:

![Alt text](images/guisample.png)



Insertion steps: 
====================

## Initial:

![Alt text](images/insertion/0.png)

## Inserting 50:

![Alt text](images/insertion/1.png)

## Inserting 40:

![Alt text](images/insertion/2.png)

## Inserting 60:

![Alt text](images/insertion/3.png)

## Inserting 70:

![Alt text](images/insertion/4.png)

## Inserting 80:

![Alt text](images/insertion/5.png)

## Inserting 90:

![Alt text](images/insertion/6.png)

## Inserting 100:

![Alt text](images/insertion/7.png)

## Inserting 110:

![Alt text](images/insertion/8.png)

## Inserting 120:

![Alt text](images/insertion/9.png)

## Inserting 130:

![Alt text](images/insertion/10.png)

## Inserting 101:

![Alt text](images/insertion/11.png)

## Inserting 105:

![Alt text](images/insertion/12.png)

## Inserting 104:

![Alt text](images/insertion/13.png)

## Inserting 103:

![Alt text](images/insertion/14.png)

## Inserting 102:

![Alt text](images/insertion/15.png)

## Inserting 140:

![Alt text](images/insertion/16.png)

## Inserting 150:

![Alt text](images/insertion/17.png)

## Inserting 160:

![Alt text](images/insertion/18.png)

## Inserting 170:

![Alt text](images/insertion/19.png)

## Inserting 180:

![Alt text](images/insertion/20.png)

## Inserting 190:

![Alt text](images/insertion/21.png)

## Inserting 200:

![Alt text](images/insertion/22.png)

## Inserting 210:

![Alt text](images/insertion/23.png)

Removing samples: 
====================

## Initial:

![Alt text](images/remove/0.png)

## Removing 180:

![Alt text](images/remove/1.png)

## Removing 170:

![Alt text](images/remove/2.png)

## Inserting 160:

![Alt text](images/remove/3.png)

## Removing 150:

![Alt text](images/remove/4.png)

## Inserting 140:

![Alt text](images/remove/5.png)

## Removing 190:

![Alt text](images/remove/6.png)

## Removing 130:

![Alt text](images/remove/7.png)

## Removing 210:

![Alt text](images/remove/8.png)

## Inserting 200:

![Alt text](images/remove/9.png)

## Removing 120:

![Alt text](images/remove/10.png)

## Inserting 70:

![Alt text](images/remove/11.png)

## Removing 60:

![Alt text](images/remove/12.png)

## Removing 50:

![Alt text](images/remove/13.png)

## Removing 40:

![Alt text](images/remove/14.png)

## Inserting 80:

![Alt text](images/remove/15.png)

## Removing 90:

![Alt text](images/remove/16.png)

## Inserting 100:

![Alt text](images/remove/17.png)

## Removing 101:

![Alt text](images/remove/18.png)

## Removing 102:

![Alt text](images/remove/19.png)

## Removing 110:

![Alt text](images/remove/20.png)

## Inserting 105:

![Alt text](images/remove/21.png)

## Removing 104:

![Alt text](images/remove/22.png)

## Inserting 103:

![Alt text](images/remove/23.png)

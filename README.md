libqtcerebellum
===============

Qt library for communication with Cerebellum daemon application


Requirements
============

For build, following packets are required:

* libzmq3-dev
* qt5-qmake


Installation
============

0. mkdir build && cd build
1. qmake ../
2. make


Using in the project
====================

In Qt Creator:

* Right-click on your project, select "Add library"
* Choose "External library"
* Library file -> build/libqtcerebellum.so
* Include path -> include/

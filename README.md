Server Stress
=====

A collection of stress tools

Dependencies
-----

**Ubuntu**

    $ sudo apt install gcc
    
    $ sudo apt-get install libcurl4-openssl-dev

**MacOS**

    $ brew install gcc

    $ brew install curl

    $ brew install openssl

Build
-----

    $ gcc -o stress_forest stress_forest.c -lcurl -lpthread

Running
----

    $ ./stress_forest 1 10 10 https://fcsbalancer.foresth11projects.com 

You can also run the following to see what the use options are for stress_forest
    
    $ ./stress_forest
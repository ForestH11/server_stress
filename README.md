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

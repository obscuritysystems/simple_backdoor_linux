To compile just run make from command line.

WARNING I AM NOT RESPONSIBLE FOR THE STUPID SHIT YOU DO WITH THIS.


This is meant for DC801 CTF, not for anything else !!!! 

Leaving this code running is dangerous.

To compile this code you will need gcc and make.

debian: apt-get install build-essential
centos: yum install make && yum install gcc

you@server:/folder/path/# make

To use run
you@server:/folder/path/# ./simple_backdoor portnumber &

use jobs to see what servers you are running

to test the server use telnet to the port number

telnet 127.0.0.1 portnumber

example: 

you@server:/file/path/simple_backdoor# ./simple_backdoor 21

you@server:/file/path/simple_backdoor# telnet 127.0.0.1 21
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
who
nemus  pts/3        2012-12-10 19:18 (10.x.x.x)
nemus  pts/4        2012-12-10 21:59 (10.x.x.x)
Connection closed by foreign host.

you@server:/file/path/simple_backdoor# telnet 127.0.0.1 21
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
df -h
Filesystem              Size  Used Avail Use% Mounted on
/dev/mapper/server-root   24G  6.2G   16G  28% /
udev                    236M  8.0K  236M   1% /dev
tmpfs                    99M  776K   98M   1% /run
none                    5.0M     0  5.0M   0% /run/lock
none                    246M     0  246M   0% /run/shm
/dev/sda1               228M   78M  139M  36% /boot
Connection closed by foreign host.


you@server:/folder/path# make clean



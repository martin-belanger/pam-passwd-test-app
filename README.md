# pam-passwd-test-app
Program to test pam_chauthtok()

Dependencies:

$ sudo apt-get install libpam-dev

Building:

$ make

Installing:

$ sudo cp clish /etc/pam.d/.

The edit /etc/pam.d/clish and replace [THE-PATH-TO-WHERE-THE-MODULE-IS-LOCATED]
to the corresponding path on your machine. Then copy clish as follows:

Running:

$ ./pwtst [username]

# pam-passwd-test-app
Program to test pam_chauthtok()

Dependencies:
$ sudo apt-get install libpam-dev

Building:
$ make

Installing:
$ sudo cp clish /etc/pam.d/.

Running:
$ ./pwtst [username]

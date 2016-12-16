# pam-passwd-test-app
Program to test pam_chauthtok()

# Dependencies:

`$ sudo apt-get install libpam-dev`

# Building:

`$ make`

# Installing:

`$ sudo cp clish /etc/pam.d/.`

Then edit `/etc/pam.d/clish` and replace `[THE-PATH-TO-WHERE-THE-MODULE-IS-LOCATED]`
to the corresponding path on your machine. For example, if you clone and build
the "dn-pam" repo in /tmp/dn-pam, then you would replace `[THE-PATH-TO-WHERE-THE-MODULE-IS-LOCATED]`
by `/tmp/dn-pam/modules/pam_hash-only/.libs/`, which is where `pam_hash-only.so`
is located.

# Running:

`$ ./pwtst [username]`

acdb_get
========

This binary dload the stock audio hal and dump the acdb table

WARNING: SOCs <=8974 aren't supported

0. Build and push this binary
0. Push stock 32bit audio HAL and dependencies to /vendor/lib
0. Run the binary
0. Enjoy your acdb table (kinda: it will print the IDs after the mixer paths string; use your brain and you'll be able to match whatever ACDB name you'll need)

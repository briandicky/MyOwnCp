# MyOwnCp
This is a implementation of my own cp, called lcp, which execute the same behavior as the cp function.
- The lcp only supports basic copy feature; copying a file to another file. (usage : lcp <source_file> <destination_file>).
- The output file is identical to the original input file (size, content), but the block usage on the disk is different.
- It will check how to create a file with holes.
- This won't handle all unusual exceptions.

##How to compile & run this program
This program is written in Linux environment, GUN make, and GCC(Gnu compiler collection.)
Just type the commands (in BASH shell),
```
make help
```

or

```
make clean dep all
```
It will automatically compile all the necessary files/codes, then generate the execution file.
Then type this,
```
./EXENAME
```

In the end, it will work successfully.

###2016 Advance UNIX Programmin HW3-1

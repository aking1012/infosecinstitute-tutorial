#!/usr/bin/env python

with open("./shellcode.txt", "r") as fa:
    text = fa.read()
    text = text.rstrip()
    this = text.decode("hex")
    with open("./shellcode.bin", "w") as fb:
        fb.write(this)


all: kompil.c
        gcc server.c -o server -lrt
        gcc klient.c -o klient -lrt
run:
        ./klient | ./server

gdb:
        gdb -q klient


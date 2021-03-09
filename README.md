# HilbertPrimes

Sources Used:

http://mech.math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html -- Most code for the X11 window interface is from here although there are some drastic changes in my program

https://codereview.stackexchange.com/questions/84052/checking-if-a-number-is-prime -- see the "isPrime()" function developed by stackexchange user nhgrif

-- Last but certainly not least the hilbert fucntion written for Windows (dos based systems). Quite a few tweaks had to be made, but the original conception of the code should be attributed to this person.


# Compiling on Linux/Unix based systems
`gcc -xc -lX11 hilbert.x -o hilbert.bin`

or

`gcc -xc hilbert.x -o hilbert.bin -lX11`

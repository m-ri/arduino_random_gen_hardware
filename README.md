# arduino_random_gen_hardware
Random hardware generator using only an arduino and a floating wire


# Material:
-Arduino Uno(I didn't tested other products)
-USB cable (connect Arduino to PC)
-PC
-one floating wire, connected to an analog pin

Summary;
Pairs of analog reads over a floating pin are performed (discarding values next to two endpoints,0 and 1023). The two readings are compared bit-to-bit, with a xor operation: bits which don't change across two reads are discarded, otherwise 
the first bit is kept  (Von Neumann procedure for extracting random bits). Due to this procedure, the output stream of random bits has not a fixed rate, but is related to how much often there is a variation over the floating pin. For instance, I've noticed an higher output rate when my notebook (which feeds the arduino) is connected to the electricity grid, instead of be powered only by battery.

Is possible to improve the speed by setting the flag fastADC, which increase the analog read's speed.

I don't assure any sort of true randomnsess. I've attached some statistical test performed over the output.

From a superficial benchmark, performed with fastADC set, I've got an output rate of 5320 random bits per second.

# Results
Look inside the "performance" folder, there you can find a random sample produced with my arduino UNO.
There are also results of statistical test,Ent and DieHard.

Below the result of Ent

Entropy = 1.000000 bits per bit.

Optimum compression would reduce the size
of this 371834040 bit file by 0 percent.

Chi square distribution for 371834040 samples is 28.13, and randomly
would exceed this value less than 0.01 percent of the times.

Arithmetic mean value of data bits is 0.4999 (0.5 = random).
Monte Carlo value for Pi is 3.148325537 (error 0.21 percent).
Serial correlation coefficient is -0.000895 (totally uncorrelated = 0.0).
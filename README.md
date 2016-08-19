# Arduino_random_gen_hardware
Random hardware generator using only an arduino and a floating wire

# Summary
Pairs of analog reads over a floating pin are performed (discarding values next to two endpoints,0 and 1023). The two readings are compared bit-to-bit, with a xor operation: bits which don't change across two reads are discarded, otherwise the first bit is kept  (Von Neumann procedure for extracting random bits). Due to this procedure, the output stream of random bits has not a fixed rate, but is related to how much often there is a variation over the floating pin. For instance, I've noticed an higher output rate when my notebook (which feeds the arduino) is connected to the electricity grid, instead of be powered only by battery.

I don't assure any sort of true randomnsess. Is mandatory to make some consideration about statistical independence inside a series of reads. I've performed some statistical tests over the output.

# Material
1. Arduino Uno (I didn't tested other products)
2. USB cable (connect Arduino to PC)
3. PC
5. one floating wire, connected to an analog pin

# Performance

Are available two flags, *fastADC* and *outputASCII*
* fastADC: it performs a faster read from analogRead, by changing the prescaler
* outputASCII: when set to 1, the Arduino produce a series of '0' and '1' ASCII characters. Otherwise, a pure binary stream is emitted.

With fastADC, my Arduino UNO produces about 9190bit/s with outputASCII cleared. Otherwise, with outputASCII are produced only 5320 bit/s of random values. 

# Results
Look inside the "performance" folder, there you can find a random sample produced with my arduino UNO, with both *fastADC* and *outputASCII* set to true.
There are also results of statistical test, *Ent* and *DieHard*.

Below the result of Ent

Entropy = 1.000000 bits per bit.

Optimum compression would reduce the size
of this 371834040 bit file by 0 percent.

Chi square distribution for 371834040 samples is 28.13, and randomly
would exceed this value less than 0.01 percent of the times.

Arithmetic mean value of data bits is 0.4999 (0.5 = random).
Monte Carlo value for Pi is 3.148325537 (error 0.21 percent).
Serial correlation coefficient is -0.000895 (totally uncorrelated = 0.0).
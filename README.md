# Basic SHA-256 implementation

This hashing algorithm will be used for implementing my blockchain based crypto coin


- initialize basic function
* ROTR = rotate right
* small sigma0 = rotr(x,7) ^ rotr(x,18) ^ shr(x, 3)
* small sigma1 = rotr(x,17) ^ rotr(x,19) ^ shr(x,10)
* ch = choice(x,y,z) = (x&y) ^ (!x&z) 
* maj = majority(x,y,z) = (x&y) ^ (x&z) ^ (y&z)
* big sigma0 = rotr(x,2) ^ rotr(x,13) ^ rotr(x, 22)
* big sigma1 = rotr(x,6) ^ rotr(x,11) ^ rotr(x, 25)


initialize first 64 cube roots of primary numbers into K array
initial hash values H0-H7 -> root of first 8 primary numbers
if message > 55 chars -> change h0-h7 value to be block 1 hash (64 bytes/8)


W array:

first 16 values W[0] - W[15] are the hash itself split into 8 byte values.

for every next value, the values are computed with this function:

w[i] = ssigma1(W[i-2]) + W[i-7] + ssigma0(W[i-15] + W[i-16]

after every computation limit to 32 bits
W[i] = W[i] & 0xFFFFFFFF

calculate temporary values for cycling a-h values:
for K reference start of file
temp1 = h + bsig1(E) + CH(e,f,g) + K[t] + W[t]
temp2 = bsig0(A) + MAJ(a,b,c)

cycling:
h = g
g = f
f = e
e = (d+temp1) & 0xFFFFFFFF (limit to 32 bits)
d = c
c = b
b = a
a =(temp1 + temp2) & 0xFFFFFFFF ( limit to 32 bits)

now add all values to the H variables

h0 = (h0 + a) & 0xFFFFFFFF
h1 = (h1 + b) & 0xFFFFFFFF
h2 = (h2 + c) & 0xFFFFFFFF
h3 = (h3 + d) & 0xFFFFFFFF
h4 = (h4 + e) & 0xFFFFFFFF
h5 = (h5 + f) & 0xFFFFFFFF
h6 = (h6 + g) & 0xFFFFFFFF
h7 = (h7 + h) & 0xFFFFFFFF


finished value is hex of all h's concatenated

return hex(h0) + hex(h1) + hex(h2) + hex(h3) + hex(h4) + hex(h5) + hex(h6) + hex(h7)



# Multi-block hashing
For multiblock hashing you use initial hash values equal to the last block hash values
*reference the H values for initial hash values*

# Basic SHA-256 implementation

This hashing algorithm will be used for implementing my blockchain based crypto coin


#### Initialize basic functions:
* Rotate right(word, amount) (ROTR) = (((word) >> (amount)) | ((word) << (32-(amount))))
* small sigma0 (SSIG0) = rotr(x,7) ^ rotr(x,18) ^ shr(x, 3)
* small sigma1 (SSIG1) = rotr(x,17) ^ rotr(x,19) ^ shr(x,10)
* choice(x,y,z) (CH) = (x&y) ^ (!x&z) 
* majority(x,y,z) (MAJ) = (x&y) ^ (x&z) ^ (y&z)
* big sigma0 (SSIG0) = rotr(x,2) ^ rotr(x,13) ^ rotr(x, 22)
* big sigma1 (SSIG1) = rotr(x,6) ^ rotr(x,11) ^ rotr(x, 25)


#### Initialization:
1. Initialize the first 64 cube roots of prime numbers into the `K` array.
2. Set initial hash values (`H0` to `H7`) to the square roots of the first 8 prime numbers.
3. If the message length exceeds 55 characters, change the values of `H0`-`H7` to be the hash of the first block (64 bytes/8).

#### W Array:
- The first 16 values, `W[0]` to `W[15]`, are the message itself split into 8-byte values.
- For each subsequent value, compute using the following function:
  \[
  W[i] = SSIG1(W[i-2]) + W[i-7] + SSIG0(W[i-15]) + W[i-16]
  \]
- After every computation, limit the value to 32 bits:
  \[
  W[i] = W[i] \& 0xFFFFFFFF
  \]

#### Temporary Values for Cycling A-H:
1. For `K[t]`, reference the start of the file.
2. Calculate:
   \[
   \temp1 = h + BSIG1(e) + CH(e, f, g) + K[t] + W[t]
   \]
   \[
   \temp2 = BSIG0(a) + MAJ(a, b, c)
   \]
3. Update the cycling values:
   [h = g]
   [g = f]
   [f = e]
   [e = (d + temp1) \& 0xFFFFFFFF]
   [d = c]
   [c = b]
   [b = a]
   [a = (temp1 + temp2) \& 0xFFFFFFFF]

#### Update H Variables:
After the cycling step, update the hash variables:
\[
H0 = H0 + a
\]

\[
H1 = H1 + b
\]

\[
H2 = H2 + c
\]

\[
H3 = H3 + d
\]

\[
H4 = H4 + e
\]

\[
H5 = H5 + f
\]

\[
H6 = H6 + g
\]

\[
H7 = H7 + h
\]

#### Final Hash:
The final hash is the concatenation of the hexadecimal values of `H0` to `H7`:

hash = hex(H0) + hex(H1) + hex(H2) + hex(H3) + hex(H4) + hex(H5) + hex(H6) + hex(H7)

Return this concatenated hexadecimal string as the hash.

---

### Multi-Block Hashing:
For multi-block hashing, use the hash values from the previous block as the initial hash values for the next block. Specifically, reference the `H` values to initialize the hash for subsequent blocks.

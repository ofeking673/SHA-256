#include "SHA256.h"

std::string SHA256::compute_hash(std::string value)
{
	std::vector<unsigned long> Block;
	for (int i = 0; i < 512; i += 32)
	{
		Block.push_back(std::strtoul(value.substr(i, 32).c_str(), NULL, 2));
	} //initialize the first 16 words as a unsigned long instead of the string it is

	unsigned long H[8];
	H[0] = 0x6a09e667;
	H[1] = 0xbb67ae85;
	H[2] = 0x3c6ef372;
	H[3] = 0xa54ff53a;
	H[4] = 0x510e527f;
	H[5] = 0x9b05688c;
	H[6] = 0x1f83d9ab;
	H[7] = 0x5be0cd19;

	unsigned long W[64];

	for (int t = 0; t < 16; t++)
	{
		W[t] = Block[t] & 0xFFFFFFFF; //input 32 bit long words
	}

	for (int t = 16; t < 64; t++)
	{
		//calculate the next 48 words with this formula
		//σ1(t-2) + (t-7) + σ0(t-15) + (t-16) -> 32 bits
		W[t] = (SSIG1(W[t - 2]) + W[t - 7] + SSIG0(W[t - 15]) + W[t - 16]) & 0xFFFFFFFF; 
	}

	unsigned long temp1;
	unsigned long temp2;
	unsigned long a = H[0];
	unsigned long b = H[1];
	unsigned long c = H[2];
	unsigned long d = H[3];
	unsigned long e = H[4];
	unsigned long f = H[5];
	unsigned long g = H[6];
	unsigned long h = H[7];

	for (int i = 0; i < 64; i++) // cycle 64 times
	{
		//calculate the temporary values for compression
		temp1 = h + BSIG1(e) + CH(e, f, g) + k[i] + W[i];
		temp2 = BSIG0(a) + MAJ(a, b, c);

		//cycle through the compression values
		h = g; g = f; f = e;
		e = (d + temp1) & 0xFFFFFFFF;
		d = c; c = b; b = a;
		a = (temp1 + temp2) & 0xFFFFFFFF;
	}

	H[0] = (H[0] + a) & 0xFFFFFFFF;
	H[1] = (H[1] + b) & 0xFFFFFFFF;
	H[2] = (H[2] + c) & 0xFFFFFFFF;
	H[3] = (H[3] + d) & 0xFFFFFFFF;
	H[4] = (H[4] + e) & 0xFFFFFFFF;
	H[5] = (H[5] + f) & 0xFFFFFFFF;
	H[6] = (H[6] + g) & 0xFFFFFFFF;
	H[7] = (H[7] + h) & 0xFFFFFFFF;

	std::string temp = "";
	for (int i = 0; i < 8; i++) // concatenate all values
	{
		temp.append(hex(H[i]));
	}
	return temp;
}

/*
* > Input: unsigned long number
* > Output: string containing the hexadecimal value of the input
*/
std::string SHA256::hex(unsigned long inp)
{
	std::stringstream ss;
	ss << std::hex << std::setw(8) << std::setfill('0') << inp;
	return ss.str();
}

std::string SHA256::pad512bits(std::string value)
{
	int original_length = value.size();  // length in bytes
	int bit_length = original_length * 8;  // length in bits
	int padding_length = 447 - bit_length;  // how many 0's to add

	std::string binary_message = convertBinary(value);
	binary_message += "1";

	binary_message += std::string(padding_length, '0');

	std::string length_bits = std::bitset<64>(bit_length).to_string(); //transfer bit length to binary
	binary_message += length_bits;

	std::cout << binary_message << std::endl;
	return binary_message;
}


std::string SHA256::convertBinary(std::string value)
{
	std::string temp = "";

	for (int i = 0; i < value.length(); i++)
	{
		std::bitset<8> b(value[i]);
		temp += b.to_string();
	}

	return temp;
}

std::string SHA256::digest(std::string value)
{
	value = pad512bits(value);
	return compute_hash(value);;
}

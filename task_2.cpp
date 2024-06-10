#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
class Bit_Vector
{
	private:
		int depth;
		unsigned char *bits;
	public:
		Bit_Vector(int _depth, unsigned char *_bits) : depth(_depth)
		{
			int x = sizeof(_bits);
			bits = new unsigned char [depth];
			std::copy(_bits, _bits + _depth, bits);
			for (int i = x; i < depth; i++)
				bits[i] = 0;
		}
		~Bit_Vector()
		{
			delete bits;
		}
		int operator () () const
		{
			return depth;
		}

		Bit_Vector get_bit_field(int offset, int field_depth)
		{
            if (field_depth + offset > depth)
            {
                    throw(std::range_error("index is out of range"));
            }
			unsigned char buf[field_depth];
			std::copy(bits + offset, bits + offset + field_depth, buf);
			return Bit_Vector(field_depth, buf);
		}

		uint64_t get_bit_field_in_long(int offset, int field_depth)
		{
			uint64_t res = 0;
			if (field_depth + offset > depth)
			{
				throw(std::range_error("index is out of range"));
			}
			else if (field_depth > 64)
			{
				throw(std::overflow_error("bit depth is too big for writing in long variable"));
			}
			for (int i = offset; i < offset + field_depth; i++)
			{
				res = res << 1 + bits[i];
			}
			return res;
		}

		void set_bit_field(int offset, Bit_Vector &vector)
		{
            if (vector.depth + offset > depth)
            {
                    throw(std::range_error("index is out of range"));
            }
			std::copy(vector.bits + offset, vector.bits + offset + vector.depth, bits);
		}

		std::string to_string()
		{
			std::string res;
			int hex = 0;
			for (int i = 0; i < depth; i++)
			{
				std::cout << (int) bits[i] << "\n";
				hex += bits[i]*pow(256, i);
			}
			std::cout << hex << "\n";
			while (hex > 0)
			{
				if (hex%16 == 10)
				{
					 res.push_back('A');
				}
				else if (hex%16 == 11)
				{
					res.push_back('B');
				}
                                else if (hex%16 == 12)
                                {
                                        res.push_back('C');
                                }
                                else if (hex%16 == 13)
                                {
                                        res.push_back('D');
				}
                                else if (hex%16 == 14)
                                {
                                        res.push_back('E');
                                }
                                else if (hex%16 == 15)
                                {
                                        res.push_back('F');
                                }
				else
				{
					res.push_back(std::to_string(hex%16)[0]);
				}
				hex /= 16;
			}
			std::reverse(res.begin(), res.end());
			return res;
		}
};

int main()
{
	uint64_t tmp = 0x1234567;
	Bit_Vector v (20, reinterpret_cast <unsigned char*> (&tmp));
	std::cout << v.to_string () << std::endl;
}

#include <iostream>
#include <vector>

class Bit_Vector
{
	private:
		int depth;
		int *bits;
	public:
		Bit_Vector(int _depth, int *_bits) : depth(_depth)
		{
			bits = new int [depth];
			std::copy(_bits, _bits + _depth, bits);
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
			int buf[field_depth];
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
			int i = 0, num = 0;
			while ((i + 3) < depth)
			{
				num += bits[i]*8 + bits[i+1]*4 + bits[i+2]*2 + bits[i+3];
				std::cout << num << "\n";
				if (num < 10)
				{
					res += std::to_string(num);
				}
				else
				{
					res.push_back(char(65 + num - 10));
				}
				i += 4;
				num = 0;
			}
			return res;
		}
};

int main()
{
	int *arr = new int[12]{1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1};
	Bit_Vector v(12, arr);
	std::cout << v.to_string() << "\n";
}

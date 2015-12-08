define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;


void cut(vector<vector<int>>&, int, int, int, int, int);
bool check(vector<vector<int>>, int, int, int, int);
bool Most(vector<vector<int>>&, vector<vector<int>>&, vector<int>, int);
int ReadFile(string, vector<int> &, vector<vector<int>>&, vector<vector<int>>&);

//#define DEBUG //debugging mode

int ReadFile(
	string _name_file,
	vector<int> &_WH,
	vector<vector<int>>& _array_wall,
	vector<vector<int>>& _array_block
	)
{
	ifstream File(_name_file);
	if (File.bad())
	{
		return 1;
	}
	int TEMPINT;
	File >> TEMPINT;
	_WH.push_back(TEMPINT);
	File >> TEMPINT;
	_WH.push_back(TEMPINT);
	if (_WH[0] == 0 && _WH[1] == 0)
		return 2;
	//
	for (size_t i = 0; i < _WH[0]; ++i)
	{
		vector<int> temp;
		_array_wall.push_back(temp);
	}
	//
	bool TEMPBOOL = 0;
	//
	string bits;
	for (int i = 0; i < _WH[1]; ++i)
	{
		File >> bits;
		char* char_bit = new char[bits.length()];
		strcpy(char_bit, bits.c_str());
		for (int j = 0; j < _WH[0]; ++j)
		{
			_array_wall[j].push_back(char_bit[j] - '0');
		}

	}

	//
	int tmp;
	File >> TEMPINT;
	//
	for (size_t i = 0; i < TEMPINT; ++i)
	{
		vector<int> temp;
		_array_block.push_back(temp);
	}
	//
	for (int i = 0; i < TEMPINT; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			File >> tmp;
			_array_block[i].push_back(tmp);
		}
	}
}

bool Most(
	vector<vector<int>>& _stena,
	vector<vector<int>>& _blocks, 
	vector<int> _WH, int count/*counter (1) in wall*/
	)
{
	bool result = 0;
	for (int j = 0; j < _blocks.size(); j++)
		if (_blocks[j][2]>0 && count >= (_blocks[j][0] * _blocks[j][1]))
			for (int z = 0; z < 2; z++)//two options string & stolb
				for (int x = 0; x < _WH[0] - _blocks[j][1 - z]; x++)
					for (int y = 0; y < _WH[1] - _blocks[j][z]; y++)
						if (check(_stena, x, y, +_blocks[j][1 - z], _blocks[j][z])) 
						{
							cut(_stena, x, y, _blocks[j][1-z], _blocks[j][z], 0);
							count -= _blocks[j][0] * _blocks[j][1];
							_blocks[j][2]--;
							if (count == 0)
								return 1;
							result = Most(_stena, _blocks, _WH, count);
							//------------------- many iter--------------
							if (result) return result;
							_blocks[j][2]++;
							count += _blocks[j][0] * _blocks[j][1];
							cut(_stena, x, y, _blocks[j][1 - z], _blocks[j][z], 1);
						}
	return result;
}

void cut(
	vector<vector<int>>& _wall,
	int x, 
	int y,
	int w,
	int h,
	int v
	) 
{

	for (int i = 0; i < w - x; i++)
		for (int j = 0; j < h - y; j++)
			_wall[x + i][y + j] = v;
}

bool check(
	vector<vector<int>> _wall,
	int x,
	int y,
	int w,
	int h
	)
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (_wall[x + i][y + j] == 0) return false;
		}
	}
	return true;
}

int main()
{

	vector<int> test_WH(0);
	vector<vector<int>> test_array_wall;
	vector<vector<int>> test_array_block;
	string test_string = "task.txt";

	ReadFile(test_string, test_WH, test_array_wall, test_array_block);//read data
	int count = 0;
	for (int i = 0; i < test_array_wall.size(); i++) {
		for (int j = 0; j < test_array_wall[i].size(); j++) {
			if (test_array_wall[i][j] == 1) count++;
		}
	}
	
	if (Most(test_array_wall, test_array_block, test_WH, count))
		cout << "yes";
	else
		cout << "No";
	cin.get();
	return 0;
}
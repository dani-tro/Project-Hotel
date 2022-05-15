#include <iostream>
#include <fstream>

using namespace std;

void create_file1()
{
	fstream file;
	file.open("hotel_example1.bin", ios::out | ios::binary);
	uint32_t room_number, number_of_beds;
	if (file.is_open() == false)cout << "Error\n";
	for(int i = 0; i < 8; i++)
	{
		room_number = rand() % 100;
		number_of_beds = rand() % 5 + 1;
		cout << room_number << " " << number_of_beds << endl;
		file.write(reinterpret_cast<const char*>(&room_number), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&number_of_beds), sizeof(uint32_t));
	}
	room_number = 0;
	file.write(reinterpret_cast<const char*>(&room_number), sizeof(uint32_t));
	file.write(reinterpret_cast<const char*>(&room_number), sizeof(uint32_t));
	file.close();
}

void create_file2()
{
	fstream file;
	file.open("hotel_example2.bin", ios::out | ios::binary);
	uint32_t room_number, number_of_beds;
	if (file.is_open() == false)cout << "Error\n";
	for(int i = 0; i < 10; i++)
	{
		room_number = (i + 1);
		number_of_beds = (2 * i + 1) % 3 + 1;
		cout << room_number << " " << number_of_beds << endl;
		file.write(reinterpret_cast<const char*>(&room_number), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&number_of_beds), sizeof(uint32_t));
	}
	room_number = 0;
	file.write(reinterpret_cast<const char*>(&room_number), sizeof(uint32_t));
	file.write(reinterpret_cast<const char*>(&room_number), sizeof(uint32_t));
	file.close();
}

int main()
{
	create_file1();
	create_file2();
	return 0;
}

/*

hotel_example1.bin
41 3
34 1
69 5
78 4
62 5
5 1
81 3
61 2
-1 -1

hotel_example2.bin
1 2
2 1
3 3
4 2
5 1
6 3
7 2
8 1
9 3
10 2
-1 -1

*/


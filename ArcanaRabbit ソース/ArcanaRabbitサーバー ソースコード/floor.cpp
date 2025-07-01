#include "pch.h"
#include "floor.h"

void Floor::LoadFloor(const char* MapFilePath)
{
	std::ifstream inputFile(MapFilePath);
	std::string line;
	if (inputFile.is_open())
	{
		while (std::getline(inputFile, line))
		{

		}
		inputFile.close();

	}

	std::string loadlen[512];
	for (int i = 0; i < 512; i++)
	{
		loadlen[i] = line.substr(86 * i, 86);
		float ind = 0;
		for (char a : loadlen[i])
		{
			//“ª‚Ü‚Åˆø‚­
			int num = a;
			num = num - 0x30;
			if ((int)ind < 85)
			{
				if (num > 31)
				{
					num -= 32;
					SetFloor({ ind * 6.0f + 5 ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f + 5 ,(float)i }, false);
				}

				if (num > 15)
				{
					num -= 16;
					SetFloor({ ind * 6.0f + 4 ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f + 4 ,(float)i }, false);
				}

				if (num > 7)
				{
					num -= 8;
					SetFloor({ ind * 6.0f + 3 ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f + 3 ,(float)i }, false);
				}

				if (num > 3)
				{
					num -= 4;
					SetFloor({ ind * 6.0f + 2 ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f + 2 ,(float)i }, false);
				}

				if (num > 1)
				{
					num -= 2;
					SetFloor({ ind * 6.0f + 1 ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f + 1 ,(float)i }, false);
				}

				if (num > 0)
				{
					num -= 1;
					SetFloor({ ind * 6.0f ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f ,(float)i }, false);
				}
			}
			else
			{
				if (num > 1)
				{
					num -= 2;
					SetFloor({ ind * 6.0f + 1 ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f + 1 ,(float)i }, false);
				}

				if (num > 0)
				{
					num -= 1;
					SetFloor({ ind * 6.0f ,(float)i }, true);
				}
				else
				{
					SetFloor({ ind * 6.0f ,(float)i }, false);
				}
			}
			ind++;
		}
	}
}

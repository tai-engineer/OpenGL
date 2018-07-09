#include "ObjMng.hpp"

void ObjMng::print()
{
	for (itmDict = mDict.begin(); itmDict != mDict.end(); ++itmDict)
	{
		printf("key:%s\t\t value:", itmDict->first);
		for (itvID = itmDict->second.begin(); itvID != itmDict->second.end(); ++itvID)
		{
			printf("%d ", *itvID);
		}
		printf("\r\n");
	}
}
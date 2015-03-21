#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include "BrowserPic.h"

int CBrowserPic::BrowserPic( string path, string postfix, vector<string>& pic_list, bool subFilter )
{
	WIN32_FIND_DATA findData;
	HANDLE hHandle = NULL;
	string filePathName; // 查找文件名类型
	string fullPathName; // 查找到的文件
 
	filePathName = path;
	filePathName += "\\*.";
	filePathName += postfix;
 
	hHandle = FindFirstFile( ( LPCWSTR )filePathName.data(), &findData );
 
	if( hHandle == INVALID_HANDLE_VALUE )
	return 1;
 
	do 
	{
		if( "." == (string)(char*)findData.cFileName ||
		".." == (string)(char*)findData.cFileName )
		continue;
 
		fullPathName = path;
		fullPathName += "\\";
		fullPathName += (string)(char*)findData.cFileName;
 
		if( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && subFilter )
			BrowserPic( fullPathName.data(), postfix, pic_list, subFilter );
		else
		{
			string str = fullPathName.substr( fullPathName.length() - 3 );
			if( str == "jpg" || str == "bmp" )
			{
				pic_list.push_back( fullPathName );
			}
		}
	} while ( FindNextFile( hHandle, &findData) );
	FindClose( hHandle );
	return pic_list.size();
}
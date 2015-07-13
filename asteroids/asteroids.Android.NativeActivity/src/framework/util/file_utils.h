#pragma once
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
// file utilities to handle files inside the apk
//	Part of my public game framework available at:
//		http://github.com/arajar/android_file_utils
//////////////////////////////////////////////////////////////////////////

namespace util
{

	//////////////////////////////////////////////////////////////////////////

	namespace fs
	{
		static AAssetManager* assetMgr;
	}

	//////////////////////////////////////////////////////////////////////////

	void setAssetMgr(AAssetManager* mgr);

	int android_read(void* cookie, char* buf, int size);
	int android_write(void* cookie, const char* buf, int size);
	fpos_t android_seek(void* cookie, fpos_t offset, int whence);
	int android_close(void* cookie);

	FILE* android_fopen(const char* fname, const char* mode);

#define fopen(name, mode) util::android_fopen(name, mode)

	//////////////////////////////////////////////////////////////////////////
}
#include "file_utils.h"

namespace util
{
	//////////////////////////////////////////////////////////////////////////
	
	void setAssetMgr(AAssetManager * mgr)
	{
		fs::assetMgr = mgr;
	}

	//////////////////////////////////////////////////////////////////////////
	
	int android_read(void* cookie, char* buf, int size)
	{
		return AAsset_read((AAsset*)cookie, buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	int android_write(void* cookie, const char* buf, int size)
	{
		return EACCES; // can't provide write access to the apk
	}

	//////////////////////////////////////////////////////////////////////////

	fpos_t android_seek(void* cookie, fpos_t offset, int whence)
	{
		return AAsset_seek((AAsset*)cookie, offset, whence);
	}

	//////////////////////////////////////////////////////////////////////////

	int android_close(void* cookie)
	{
		AAsset_close((AAsset*)cookie);
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	FILE* android_fopen(const char* fname, const char* mode)
	{
		// we don't support writting to files... yet
		if (mode[0] == 'w') return nullptr;

		AAsset* asset = AAssetManager_open(fs::assetMgr, fname, 0);
		if (!asset)
		{
			return nullptr;
		}

		// Override fread, fwrite, fseek and fclose with our own functions to be able to 
		// read files from the assets folder inside the APK
		return funopen(asset, android_read, android_write, android_seek, android_close);
	}

}
#include "UIlib.h"
#include "UIMemLooker.h"

namespace DuiLib
{
	std::string FileNameFromPath(const char* lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return ("");

		std::string strPath(lpszPath);

		std::string::iterator iter;
		for (iter = strPath.begin(); iter < strPath.end(); iter++)
		{
			if (('\\') == *iter)
				*iter = ('/');
		}

		std::string::size_type nPos = strPath.rfind(('/'));
		if (nPos != std::string::npos)
			strPath = strPath.substr(nPos + 1);

		return strPath;
	}

	DuiMemeryLooker::DuiMemeryLooker()
		: m_pcs(NULL)
		, mTotalAllocations(0)
		, mAllocated(0)
		, mFreeBytes(0)
	{
		if(NULL==m_pcs)
		{
			m_pcs = LockHelper::newLock<critical_session>();
		}
	}
	
	DuiMemeryLooker::~DuiMemeryLooker()
	{
		LockHelper::delLock(m_pcs);

		MemoryTrace();
	}

	void DuiMemeryLooker::_recordAlloc(void* ptr, size_t sz, const char* file, size_t ln, const char* func)
	{
		if (file && func)
		{
			LockHelper lock(m_pcs);
			{
				const char* msg = ("Double allocation with same address - this probably means you have a mismatched allocation / deallocation style.");
				DuiAssertX(mAllocations.find(ptr) == mAllocations.end(), msg);

				//if (file && func)
				mAllocations[ptr] = Alloc(sz, ln, FileNameFromPath(file).c_str(), func);
				//else
					//mAllocations[ptr] = Alloc(sz, ln);
				mTotalAllocations += sz;
				mAllocated += sz;
			}
		}
	}
	void DuiMemeryLooker::_recordDealloc(void* ptr)
	{
		// deal cleanly with null pointers
		if (!ptr)
			return;
		LockHelper lock(m_pcs);
		{
			AllocationMap::iterator i = mAllocations.find(ptr);
			const char* msg = ("Unable to locate allocation unit - this probably means you have a mismatched allocation / deallocation style.");
			//DuiAssertX(i != mAllocations.end(), msg);
			if (i != mAllocations.end())
			{
				// global stats
				mTotalAllocations -= i->second._bytes;
				mFreeBytes += i->second._bytes;
				mAllocations.erase(i);
			}
		}
	}

	CDuiString DuiMemeryLooker::GetCurMemoryFile()
	{
		CDuiString curApp = PathUtil::GetCurAppName(FALSE);
		curApp  += _T(".mry");
		return curApp;
	}

	void DuiMemeryLooker::MemoryTrace()
	{
#ifndef _UNICODE
		FILE * fp = fopen(GetCurMemoryFile().GetData(),"w+");
#else
		FILE*  fp = _wfopen(GetCurMemoryFile().GetData(), _T("w+"));
#endif

		if(!fp)
			return ;
		fprintf(fp,"\n");
		fprintf(fp,"-----------------------\n");
		fprintf(fp,"Memory Usage Statistics\n");
		fprintf(fp,"-----------------------\n");
		fprintf(fp,"\n");
		fprintf(fp,"Alloced %d,Dealloc %d Bytes\n",mAllocated,mFreeBytes);
		fprintf(fp,"Leaker %d Bytes\n",mTotalAllocations);
		fprintf(fp, "-----------------------\n");
		fprintf(fp, "Memory Leaker Detail\n");
		fprintf(fp, "-----------------------\n");
		for (AllocationMap::iterator it=mAllocations.begin();it!=mAllocations.end();++it)
		{
			fprintf(fp,"File=%s,Func=%s,Line=%d, Alloc: %d\n", 
				it->second._file,it->second._function,it->second._line,it->second._bytes);
		}
		fflush(fp);
		fclose(fp);
	}
}
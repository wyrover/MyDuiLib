#ifndef _MemTrack_h
#define _MemTrack_h

#ifdef _MSC_VER
#pragma once
#endif

#include <map>

namespace DuiLib
{
	class UILIB_API DuiMemeryLooker : public Singleton<DuiMemeryLooker>
	{
		DECLARE_SINGLETON_CLASS(DuiMemeryLooker)
	protected:
		struct Alloc
		{
			char          _file[256];
			unsigned int  _line;
			char 		  _function[256];
			size_t        _bytes;
			Alloc()
				: _bytes(0)
				, _line(0)
			{
			}
			Alloc(size_t bytes, unsigned int line = 0, const char* file = "<UnKnow Source>", const char* function = "<UnKnow Function>")
			{
				memset(_file, 0, sizeof(_file));
				if (file)
					memcpy(_file, file, strlen(file));
				_line = line;
				memset(_function, 0, sizeof(_function));
				if (function)
					memcpy(_function, function, strlen(function));
				_bytes = bytes;
			}
		 };
	public:   		
		DuiMemeryLooker();
		virtual ~DuiMemeryLooker();


		/** Record an allocation that has been made. Only to be called by
		the memory management subsystem.
		@param ptr The pointer to the memory
		@param sz The size of the memory in bytes
		@param pool The memory pool this allocation is occurring from
		@param file The file in which the allocation is being made
		@param ln The line on which the allocation is being made
		@param func The function in which the allocation is being made
		*/
		void _recordAlloc(void* ptr, size_t sz, 
			const char* file = NULL, size_t ln = 0, const char* func = NULL);
		// Record the deallocation of memory.
		void _recordDealloc(void* ptr);
	
		void MemoryTrace();

		CDuiString GetCurMemoryFile();
	private:
		ILock* m_pcs;
		size_t mTotalAllocations;
		size_t mFreeBytes;
		size_t mAllocated;
#pragma warning(push)
#pragma warning(disable:4251)
		typedef std::map<void*, Alloc> AllocationMap;
		AllocationMap mAllocations;
#pragma warning(pop) 
	};

}









#endif//_MemTrack_h
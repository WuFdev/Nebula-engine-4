#pragma once

#ifdef MEM_TRACK

#include "core/lux.h"
#include "core/hash_map.h"
#include "core/map.h"
#include "core/spin_mutex.h"

#include <crtdbg.h>
#include <stdlib.h>

namespace Lux
{
	template<>
	struct HashFunc<void*>
	{
		static size_t get(const void* key)
		{
			size_t x = ((int32_t(key) >> 16) ^ int32_t(key)) * 0x45d9f3b;
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = ((x >> 16) ^ x);
			return x;
		}
	};

	class MemTrackAllocator
	{
	public:
		void* allocate(size_t n) { return malloc(n); }
		void deallocate(void* p) { free(p); }
		void* reallocate(void* p, size_t n) { return realloc(p, n); }
	};

	class LUX_CORE_API MemoryTracker
	{
	public:
		class Entry
		{
		public:
			Entry()
				: m_file(NULL), m_line(0), m_alloc_id(0), m_size(0), m_mark(0)
			{}

			// copy constructor
			Entry(const Entry& src)
				: m_file(src.m_file), m_line(src.m_line), m_alloc_id(src.m_alloc_id), m_size(src.m_size), m_mark(src.m_mark)
			{}

			Entry(const char* file, int line, size_t size)
				: m_file(file), m_line(line), m_alloc_id(MemoryTracker::getAllocID()), m_size(size), m_mark(0)
			{}

			const char* file() const { return m_file; }
			const int line() const { return m_line; }
			const uint32_t allocID() const { return m_alloc_id; }
			const size_t size() const { return m_size; }

			void mark() { ++m_mark; }
			const uint8_t getMark() const { return m_mark; }

		private:
			const char* m_file;
			uint32_t m_line;
			uint32_t m_alloc_id;
			size_t m_size;
			uint8_t m_mark;
		};

	public:
		static MemoryTracker& getInstance();
		static void destruct();

		void add(void* p, const size_t size, const char* file, const int line);
		void remove(void* p);

		void dumpDetailed();
		void dumpSortedByAllocationOrder();
		void dumpTruncatedPerFileLine();
		void dumpTruncatedPerFile();

		void markAll();
		void dumpUnmarked();

		static uint32_t getAllocID() { return s_alloc_counter++; }

	private:
		// struct FILE_LINE_REPORT
		struct FileLineReport
		{
			const char *file;
			int32_t line;

			LUX_FORCE_INLINE bool operator == (const FileLineReport &other) const { return file == other.file && line == other.line; }
			LUX_FORCE_INLINE bool operator != (const FileLineReport &other) const { return !(*this == other); }

			LUX_FORCE_INLINE bool operator < (const FileLineReport &other) const
			{
				if(file == NULL)
					return other.file != NULL;
				if(other.file == NULL)
					return false;
				int cmp = strcmp(file, other.file);
				if(cmp != 0)
					return cmp < 0;
				return line < other.line;
			}

			LUX_FORCE_INLINE bool operator > (const FileLineReport &other) const
			{
				if(file == NULL)
					return other.file != NULL;
				if(other.file == NULL)
					return false;
				int cmp = strcmp(file, other.file);
				if(cmp != 0)
					return cmp > 0;
				return line > other.line;
			}
		};

		typedef HashMap<void*, Entry, HashFunc<void*>, MemTrackAllocator> EntryTable;
		typedef map<uint32_t, Entry*, MemTrackAllocator> map_alloc_order;

		typedef map<FileLineReport, int32_t, MemTrackAllocator> file_line_map;
		typedef map<const char *, int32_t, MemTrackAllocator> file_map;

		typedef map<FileLineReport, uint32_t, MemTrackAllocator> alloc_count_map;

		MemoryTracker();
		~MemoryTracker();

		void dumpEntry(const Entry& entry) const;

		EntryTable m_map;

		MT::SpinMutex* m_lock;
		uint32_t m_allocated_memory;
		uint8_t m_mark;

		static MemoryTracker* s_instance;
		static uint32_t s_alloc_counter;
	};
} //~namespace Lux

#endif // MEM_TRACK

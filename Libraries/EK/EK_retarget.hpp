#ifndef __EK_RETARGET_HPP
#define __EK_RETARGET_HPP

#include <EK_config.h>
#include <new>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <vector>

#define HEAP_INFO_BLOCKS 100

class Heap {
  private:
		uint32_t Size;
#ifdef HEAP_DEBUG
		bool Analyzing, DetailedAnalysis;
	  uint32_t Used;
	  uint32_t Peak;
	  const char* Message;
	  size_t TypeSize;
	  struct InfoBlock {
		  void* Pointer;
			size_t Size;
		} InfoBlocks[HEAP_INFO_BLOCKS];
		int GetUsedInfoBlocks();
#endif
		
	public:
		Heap(uint32_t size): Size(size) {}
		
		void StartAnalysis(bool = false);
		void StopAnalysis(void);
		void ReportHeapUsage(bool = false);
		bool GetAnalyzing(void);
		void Debug(const char*);
		
#ifdef HEAP_DEBUG
		template<typename T>
		void Debug(const char* message, T obj) {
			if (Analyzing) {
				Message = message;
				TypeSize = sizeof(obj);
			}
		}
		
		template<typename T>
		void Debug(const char* message) {
			if (Analyzing) {
				Message = message;
				TypeSize = sizeof(T);
			}
		}
#else
		template<typename T>
		void Debug(const char* message, T obj) {}
		template<typename T>
		void Debug(const char* message) {}
#endif
		
		void MarkAlloc(void* p, size_t size, const char* prefix);
		void MarkFree(void* p, const char* prefix);
		friend void* operator new(size_t) throw(std::bad_alloc);
		friend void* operator new[](size_t) throw(std::bad_alloc);
		friend void operator delete(void*) throw();
		friend void operator delete[](void*) throw();
};

extern Heap Heap;

#ifdef HEAP_DEBUG
extern const char* __file__;
extern size_t __line__;

#define new (__file__=__FILE__,__line__=__LINE__) && 0 ? NULL : new	
#define delete __file__=__FILE__,__line__=__LINE__, delete
#endif

#endif

#include "EK_retarget.hpp"
#include <tasks.hpp>

// change heap size also in startup.s!
// only reports C++ heap, no direct calls to malloc! (apart from fopen/fclose)
class Heap Heap(HeapSize);

#ifdef HEAP_DEBUG

const char* __file__ = "";
size_t __line__ = 0;

void Heap::StartAnalysis(bool detailed) {	
	Analyzing = true;
	DetailedAnalysis = detailed;
}

void Heap::StopAnalysis(void) {
	Analyzing = false;
	ReportHeapUsage(true);
}

void Heap::ReportHeapUsage(bool detailed) {
	int peakPercentage = Peak * 100 / Size;
  if (detailed)
		printf(
			"Heap size:\t%d bytes\r\n"
			"Currently used:\t%d bytes (%d%%)\r\n"
			"Max usage:\t%d bytes (%d%%)\r\n"
			"(Using %d of %d available heap info blocks)\r\n",
			Size, Used, Used * 100 / Size, Peak, peakPercentage, GetUsedInfoBlocks(), HEAP_INFO_BLOCKS
		);
	else {
		printf("Heap:  %*d / %*d bytes (%*d%%) Heap is ", 5, Peak, 5, Size, 3, peakPercentage);
		if (peakPercentage >= 100)
			printf("exhausted!");
		else if (peakPercentage >= 90)
			printf("almost exhausted!");
		else
			printf("fine.");
		printf("\r\n");
	}
}

bool Heap::GetAnalyzing(void) {
  return Analyzing;
}

void Heap::Debug(const char* message) {
	if (Analyzing)
		Message = message;
}

void Heap::MarkAlloc(void* p, size_t size, const char* prefix) {
	if (p == NULL) {
		if (DetailedAnalysis) printf("%s\tbad_alloc\r\n", prefix);
	} else {
		Used += size;
		if (Used > Peak)
			Peak = Used;
		for (int i = 0; i < HEAP_INFO_BLOCKS; i++)
			if (i == HEAP_INFO_BLOCKS - 1 && InfoBlocks[i].Pointer != NULL)
				printf("Exceeded heap info blocks, increase HEAP_INFO_BLOCKS!\r\n");
			else if (InfoBlocks[i].Pointer == NULL) {
				InfoBlocks[i].Pointer = p;
				InfoBlocks[i].Size = size;
				break;
			}
		if (DetailedAnalysis) {
			printf("%s\t%04x\t+%*d\t%*d", prefix, (int) p & 0xFFFF, 5, size, 5, Used);
			if (__file__[0] == '\0') {
				if (Message != NULL)
					printf("\t%s", Message);
				if (TypeSize)
					printf(" (%d bytes)", TypeSize);
			} else
				printf("\t%s(%d)", __file__, __line__);
			printf("\r\n");
		}
	}
	Message = NULL;
	TypeSize = 0;
	__file__ = "";
	__line__ = 0;
}

void Heap::MarkFree(void* p, const char* prefix) {
	if (p != NULL) {
		size_t size = 0;
		for (int i = 0; i < HEAP_INFO_BLOCKS; i++)
			if (InfoBlocks[i].Pointer == p) {
				InfoBlocks[i].Pointer = NULL;
				size = InfoBlocks[i].Size;
				break;
			}
		Used -= size;
		if (DetailedAnalysis) {
			printf("%s\t%04x\t-%*d\t%*d", prefix, (int) p & 0xFFFF, 5, size, 5, Used);
			if (__file__[0] == '\0') {
				if (Message != NULL)
					printf("\t%s", Message);
				if (TypeSize)
					printf(" (%d bytes)", TypeSize);
			} else
				printf("\t%s(%d)", __file__, __line__);
			printf("\r\n");
		}
	}
	TypeSize = 0;
	Message = NULL;
	__file__ = "";
	__line__ = 0;
}

int Heap::GetUsedInfoBlocks() {
	int usedInfoBlocks = 0;
	for (int i = 0; i < HEAP_INFO_BLOCKS; i++)
		if (InfoBlocks[i].Pointer != NULL)
			usedInfoBlocks++;
	return usedInfoBlocks;
}

#undef new
#undef delete

void* operator new(size_t size) throw(std::bad_alloc) {
  void* p = malloc(size);
	if (Heap.Analyzing)
	  Heap.MarkAlloc(p, size, "new");
	return p;
}

void* operator new[](size_t size) throw(std::bad_alloc) {
  void* p = malloc(size);
	if (Heap.Analyzing)
    Heap.MarkAlloc(p, size, "new[]");
	return p;
}

void operator delete(void *p) throw() {
	if (Heap.Analyzing)
	  Heap.MarkFree(p, "delete");
  free(p);
}

void operator delete[](void *p) throw() {
	if (Heap.Analyzing)
	  Heap.MarkFree(p, "delete[]");
  free(p);
}

extern "C" void HeapMarkAlloc(void* p, size_t size, const char* prefix, const char* file, int line) {
	if (Heap.GetAnalyzing()) {
		__file__ = file;
		__line__ = line;
		Heap.MarkAlloc(p, size, prefix);
	}
}

extern "C" void HeapMarkFree(void* p, const char* prefix, const char* file, int line) {
  if (Heap.GetAnalyzing()) {
  	__file__ = file;
		__line__ = line;
		Heap.MarkFree(p, prefix);
	}
}

#else

void Heap::StartAnalysis(void) {}
void Heap::StopAnalysis(void) {}
bool Heap::GetAnalyzing(void) { return false; }
void Heap::Debug(const char* message) {}
void Heap::MarkAlloc(void* p, size_t size, const char* prefix) {}
void Heap::MarkFree(void* p, const char* prefix) {}
extern "C" void HeapMarkAlloc(void* p, size_t size, const char* prefix, const char* file, int line) {}
extern "C" void HeapMarkFree(void* p, const char* prefix, const char* file, int line) {}

#endif

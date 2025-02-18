/**
 * @file      main.cpp
 * @brief     Stream compaction test program
 * @authors   Kai Ninomiya
 * @date      2015
 * @copyright University of Pennsylvania
 */

#include <cstdio>
#include <stream_compaction/cpu.h>
#include <stream_compaction/naive.h>
#include <stream_compaction/efficient.h>
#include <stream_compaction/thrust.h>
#include <stream_compaction/radixsort.h>
#include "testing_helpers.hpp"

const int TSIZE = 1 << 27; // feel free to change the TSIZE of array
const int NPOT = TSIZE - 3; // Non-Power-Of-Two
int *a = new int[TSIZE];
int *b = new int[TSIZE];
int *c = new int[TSIZE];

int main(int argc, char* argv[]) {
    // Scan tests

    printf("\n");
    printf("****************\n");
    printf("** SCAN TESTS **\n");
    printf("****************\n");

    genArray(TSIZE - 1, a, 10);  // Leave a 0 at the end to test that edge case
    //onesArray(TSIZE, a);
    a[TSIZE - 1] = 0;
    printArray(TSIZE, a, true);

     //initialize b using StreamCompaction::CPU::scan you implement
     //We use b for further comparison. Make sure your StreamCompaction::CPU::scan is correct.
     //At first all cases passed because b && c are all zeroes.
    zeroArray(TSIZE, b);
    printDesc("cpu scan, power-of-two");
    StreamCompaction::CPU::scan(TSIZE, b, a);
    printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    printArray(TSIZE, b, true);

    zeroArray(TSIZE, c);
    printDesc("cpu scan, non-power-of-two");
    StreamCompaction::CPU::scan(NPOT, c, a);
    printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    printArray(NPOT, b, true);
    printCmpResult(NPOT, b, c);

    zeroArray(TSIZE, c);
    printDesc("naive scan, power-of-two");
    StreamCompaction::Naive::scan(TSIZE, c, a);
    printElapsedTime(StreamCompaction::Naive::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(TSIZE, c, true);
    printCmpResult(TSIZE, b, c);

    /* For bug-finding only: Array of 1s to help find bugs in stream compaction or scan
    onesArray(TSIZE, c);
    printDesc("1s array for finding bugs");
    StreamCompaction::Naive::scan(TSIZE, c, a);
    printArray(TSIZE, c, true); */

    zeroArray(TSIZE, c);
    printDesc("naive scan, non-power-of-two");
    StreamCompaction::Naive::scan(NPOT, c, a);
    printElapsedTime(StreamCompaction::Naive::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(TSIZE, c, true);
    printCmpResult(NPOT, b, c);

    zeroArray(TSIZE, c);
    printDesc("work-efficient scan, power-of-two");
    StreamCompaction::Efficient::scan(TSIZE, c, a);
    printElapsedTime(StreamCompaction::Efficient::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(TSIZE, c, true);
    printCmpResult(TSIZE, b, c);

    zeroArray(TSIZE, c);
    printDesc("work-efficient scan, non-power-of-two");
    StreamCompaction::Efficient::scan(NPOT, c, a);
    printElapsedTime(StreamCompaction::Efficient::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(NPOT, c, true);
    printCmpResult(NPOT, b, c);

    zeroArray(TSIZE, c);
    printDesc("work-efficient scanShared, power-of-two");
    StreamCompaction::Efficient::scanShared(TSIZE, c, a);
    printElapsedTime(StreamCompaction::Efficient::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    printArray(TSIZE, c, true);
    printCmpResult(TSIZE, b, c);

    zeroArray(TSIZE, c);
    printDesc("work-efficient scanShared, non-power-of-two");
    StreamCompaction::Efficient::scanShared(NPOT, c, a);
    printElapsedTime(StreamCompaction::Efficient::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    printArray(NPOT, c, true);
    printCmpResult(NPOT, b, c);

    zeroArray(TSIZE, c);
    printDesc("thrust scan, power-of-two");
    StreamCompaction::Thrust::scan(TSIZE, c, a);
    printElapsedTime(StreamCompaction::Thrust::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(TSIZE, c, true);
    printCmpResult(TSIZE, b, c);

    zeroArray(TSIZE, c);
    printDesc("thrust scan, non-power-of-two");
    StreamCompaction::Thrust::scan(NPOT, c, a);
    printElapsedTime(StreamCompaction::Thrust::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(NPOT, c, true);
    printCmpResult(NPOT, b, c);

    //printf("\n");
    //printf("*****************************\n");
    //printf("** STREAM COMPACTION TESTS **\n");
    //printf("*****************************\n");

    //// Compaction tests

    //genArray(TSIZE - 1, a, 4);  // Leave a 0 at the end to test that edge case
    //a[TSIZE - 1] = 0;
    //printArray(TSIZE, a, true);

    //int count, expectedCount, expectedNPOT;

    // initialize b using StreamCompaction::CPU::compactWithoutScan you implement
    // We use b for further comparison. Make sure your StreamCompaction::CPU::compactWithoutScan is correct.
    //zeroArray(TSIZE, b);
    //printDesc("cpu compact without scan, power-of-two");
    //count = StreamCompaction::CPU::compactWithoutScan(TSIZE, b, a);
    //printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    //expectedCount = count;
    //printArray(count, b, true);
    //printCmpLenResult(count, expectedCount, b, b);

    //zeroArray(TSIZE, c);
    //printDesc("cpu compact without scan, non-power-of-two");
    //count = StreamCompaction::CPU::compactWithoutScan(NPOT, c, a);
    //printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    //expectedNPOT = count;
    //printArray(count, c, true);
    //printCmpLenResult(count, expectedNPOT, b, c);

    //zeroArray(TSIZE, c);
    //printDesc("cpu compact with scan");
    //count = StreamCompaction::CPU::compactWithScan(TSIZE, c, a);
    //printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    //printArray(count, c, true);
    //printCmpLenResult(count, expectedCount, b, c);

    //zeroArray(TSIZE, c);
    //printDesc("work-efficient compact, power-of-two");
    //count = StreamCompaction::Efficient::compact(TSIZE, c, a);
    //printElapsedTime(StreamCompaction::Efficient::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(count, c, true);
    //printCmpLenResult(count, expectedCount, b, c);

    //zeroArray(TSIZE, c);
    //printDesc("work-efficient compact, non-power-of-two");
    //count = StreamCompaction::Efficient::compact(NPOT, c, a);
    //printElapsedTime(StreamCompaction::Efficient::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    ////printArray(count, c, true);
    //printCmpLenResult(count, expectedNPOT, b, c);

    //printf("\n");
    //printf("*****************************\n");
    //printf("** Radix Sort TESTS **\n");
    //printf("*****************************\n");

    //genArray(TSIZE - 1, a, 100000);
    //printArray(TSIZE, a, true);

    //zeroArray(TSIZE, b);
    //printDesc("cpu sort power-of-two");
    //StreamCompaction::CPU::sort(TSIZE, b, a);
    //printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    //printArray(TSIZE, b, true);

    //zeroArray(TSIZE, c);
    //printDesc("my radixsort power-of-two");
    //StreamCompaction::RadixSort::radixsort(TSIZE, c, a);
    //printElapsedTime(StreamCompaction::RadixSort::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(TSIZE, c, true);
    //printCmpResult(TSIZE, b, c);

    //zeroArray(TSIZE, b);
    //printDesc("cpu sort non-power-of-two");
    //StreamCompaction::CPU::sort(NPOT, b, a);
    //printElapsedTime(StreamCompaction::CPU::timer().getCpuElapsedTimeForPreviousOperation(), "(std::chrono Measured)");
    //printArray(NPOT, b, true);

    //zeroArray(TSIZE, c);
    //printDesc("my radixsort non-power-of-two");
    //StreamCompaction::RadixSort::radixsort(NPOT, c, a);
    //printElapsedTime(StreamCompaction::RadixSort::timer().getGpuElapsedTimeForPreviousOperation(), "(CUDA Measured)");
    //printArray(NPOT, c, true);
    //printCmpResult(NPOT, b, c);


    //system("pause"); // stop Win32 console from closing on exit
    delete[] a;
    delete[] b;
    delete[] c;
}

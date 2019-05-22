//University of Washington Bothell - CSSE
// CSS342C : Proffesor Munehiro Fukuda
// Created by Eyas Rashid on 2/21/2019
//
// Program 4: Sorting - semi-in-place merge sort
// Purpose: implementing a non-recursive  semi-in-place
// version of merge sort to increase  practical performance
// of merge sort.

#include <vector>
#include <math.h>
#include <algorithm> // used for swap and min functions

using namespace std;

// compares elements and sorts into array for the current layer of merger
template<class Comparable>
void merge(vector<Comparable> &currentArray, vector<Comparable> &swapArray, int left, int right, int end) {

    int curLeft = left; // first index of left segment
    int curRight = right; // first index of right segment

    for (int i = left; i < end; i++) {
        // if curLeft index is < than the left segment AND
        // (curRight index is >= end of the right segment OR
        // value of curLeft is <= value of curRight)
        // place curLeft value into swapArray and increment curLeft
        if (curLeft < right && (curRight >= end || currentArray[curLeft] <= currentArray[curRight])) {
            swapArray[i] = currentArray[curLeft];
            curLeft++;
        } else {
            swapArray[i] = currentArray[curRight];
            curRight++;
        }
    }
}

//splits the array into smaller portions and sorts the array
template<class Comparable>
void mergesort(vector<Comparable> &originalArray) {

    // tracks current iteration to handle swapping back and forth
    // between original array and temp array
    int iterator = 0;
    int size = originalArray.size();

    // temporary Array used for semi-in-place sort
    vector<Comparable> tempArray(size);

    // divides array into segments that are multiples of 2 and increments iterator to keep track
    // of which array is holding the values
    // iterator tracks the switch between temporary Array and Original Array
    for (int segment = 1; segment < size; segment *= 2, iterator++) {

        for (int counter = 0; counter < size; counter += 2 * segment) {

            // if iterator is even then merges to temp array
            if (iterator % 2 == 0) {
                merge(originalArray, tempArray, counter, (counter + segment),
                      min(counter + (2 * segment), size));
            } else {
                merge(tempArray, originalArray, counter, (counter + segment),
                      min(counter + (2 * segment), size));
            }
        }
    }
    // if the last iteration of mergers is in the temporary array swap back to original array
    if (iterator % 2 != 0)
        originalArray.swap(tempArray);
}
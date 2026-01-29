package main

import (
	"fmt"
)

// HeapSortService provides OOP-style heap sort
type HeapSortService struct{}

// siftDown maintains the heap property for subtree rooted at start up to end (inclusive)
func (s *HeapSortService) siftDown(data []int, start, end int) {
	root := start
	for {
		child := root*2 + 1
		if child > end {
			break
		}
		swapIdx := root
		if data[swapIdx] < data[child] {
			swapIdx = child
		}
		if child+1 <= end && data[swapIdx] < data[child+1] {
			swapIdx = child + 1
		}
		if swapIdx == root {
			return
		}
		data[root], data[swapIdx] = data[swapIdx], data[root]
		root = swapIdx
	}
}

// HeapSortInt sorts the int slice in-place using heap sort (ascending).
// Modifies the input slice.
func (s *HeapSortService) HeapSortInt(data []int) {
	n := len(data)
	if n < 2 {
		return
	}

	// Build max heap
	for start := n/2 - 1; start >= 0; start-- {
		s.siftDown(data, start, n-1)
	}

	// Extract elements from heap one by one
	for end := n - 1; end > 0; end-- {
		data[0], data[end] = data[end], data[0]
		s.siftDown(data, 0, end-1)
	}
}

func main() {
	service := &HeapSortService{}

	// Test cases
	testCases := [][]int{
		{64, 34, 25, 12, 22, 11, 90}, // Standard
		{3, 1, 4, 1, 5},              // Duplicates/small
		{},                           // Empty
		{1},                          // Single
	}

	for i, data := range testCases {
		original := make([]int, len(data))
		copy(original, data)
		fmt.Printf("Test %d: original %v -> ", i+1, original)
		service.HeapSortInt(data)
		fmt.Printf("sorted %v\n", data)
	}
}

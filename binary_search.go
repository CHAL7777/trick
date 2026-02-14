package main

import (
	"fmt"
)

// BinarySearchService provides OOP-style binary search
type BinarySearchService struct{}

// BinarySearchInt performs binary search on sorted int slice.
// Returns index if found, -1 if not.
func (s *BinarySearchService) BinarySearchInt(data []int, target int) int {
	low, high := 0, len(data)-1
	for low <= high {
		mid := low + (high-low)/2
		if data[mid] == target {
			return mid
		}
		if data[mid] < target {
			low = mid + 1
		} else {
			high = mid - 1
		}
	}
	return -1
}

// FindAllInt returns all indices matching target (for duplicates)
func (s *BinarySearchService) FindAllInt(data []int, target int) []int {
	idx := s.BinarySearchInt(data, target)
	if idx == -1 {
		return nil
	}
	low, high := idx, idx
	for low > 0 && data[low-1] == target {
		low--
	}
	for high < len(data)-1 && data[high+1] == target {
		high++
	}
	result := make([]int, 0, high-low+1)
	for i := low; i <= high; i++ {
		result = append(result, i)
	}
	return result
}

func main() {
	service := &BinarySearchService{}

	data := []int{1, 3, 5, 5, 7, 9, 11}
	target := 5
	idx := service.BinarySearchInt(data, target)
	fmt.Printf("BinarySearchInt(%v, %d) = %d\n", data, target, idx)

	allIdx := service.FindAllInt(data, target)
	fmt.Printf("FindAllInt(%v, %d) = %v\n", data, target, allIdx)

	targetNotFound := 6
	fmt.Printf("BinarySearchInt(%v, %d) = %d\n", data, targetNotFound, service.BinarySearchInt(data, targetNotFound))

	// Note: For strings/floats, add BinarySearchString/BinarySearchFloat64 methods similarly
}

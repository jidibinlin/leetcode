package main

import (
	"fmt"
	"math"
)

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	k := int(math.Ceil((float64(len(nums1)) + float64(len(nums2))) / 2))

	if (len(nums1)+len(nums2))%2 == 0 {
		foo1 := getKthElement(nums1, nums2, k)
		foo2 := getKthElement(nums1, nums2, k+1)
		return float64(foo1+foo2) / 2
	} else {
		return float64(getKthElement(nums1, nums2, k))
	}

}

func getKthElement(nums1 []int, nums2 []int, k int) int {
	if len(nums1) == 0 {
		return nums2[k-1]
	}

	if len(nums2) == 0 {
		return nums1[k-1]
	}

	compareIdx := k / 2

	if compareIdx == 0 {
		return min(nums1[0], nums2[0])
	}

	nums1Idx := min(len(nums1)-1, compareIdx-1)
	nums2Idx := min(len(nums2)-1, compareIdx-1)

	if nums1[nums1Idx] >= nums2[nums2Idx] {
		if len(nums2) <= compareIdx {
			return getKthElement(nums1, []int{}, k-(nums2Idx+1))
		}
		return getKthElement(nums1, nums2[compareIdx:], k-(nums2Idx+1))
	} else {
		if len(nums1) <= compareIdx {
			return getKthElement([]int{}, nums2, k-(nums1Idx+1))
		}
		return getKthElement(nums1[compareIdx:], nums2, k-(nums1Idx+1))
	}
}

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func main() {
	nums1 := []int{1, 2}
	nums2 := []int{3, 4}
	fmt.Println(findMedianSortedArrays(nums1, nums2))
	//fmt.Println(getKthElement(nums1, nums2, 4))
}

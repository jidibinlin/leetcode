package main

import (
	"sort"
)

func threeSum(nums []int) [][]int {

	if len(nums) < 3 {
		return [][]int{}
	}

	result := [][]int{}
	sort.Ints(nums)

	for i := 0; i <= len(nums)-3; i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}

		k := len(nums) - 1
		target := -1 * nums[i]

		for j := i + 1; j <= len(nums)-2; j++ {
			if j > i+1 && nums[j] == nums[j-1] {
				continue
			}

			for j < k && nums[j]+nums[k] > target {
				k--
			}

			if j == k {
				break
			}

			if nums[j]+nums[k] == target {
				result = append(result, []int{nums[i], nums[j], nums[k]})
			}

		}
	}
	return result
}

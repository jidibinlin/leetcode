package main

import (
	"fmt"
	"math"
	"sort"
)

func threeSumClosest(nums []int, target int) int {
	result := math.MaxInt64

	distance := math.MaxFloat64
	sort.Ints(nums)
	for i := 0; i < len(nums); i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}
		third := len(nums) - 1
		for j := i + 1; j < len(nums); j++ {

			if j > i+1 && nums[j] == nums[j-1] {
				continue
			}

			for nums[i]+nums[j]+nums[third] > target && third > j {
				if third < len(nums)-1 && nums[third] == nums[third+1] {
					third--
					continue
				}
				sum := nums[i] + nums[j] + nums[third]
				tmpDistance := math.Abs(float64(sum - target))
				if tmpDistance <= distance {
					distance = tmpDistance
					result = sum
				}
				third--
			}

			if third == j {
				break
			}

			if nums[i]+nums[j]+nums[third] <= target {
				sum := nums[i] + nums[j] + nums[third]
				tmpDistance := math.Abs(float64(sum - target))
				if tmpDistance <= distance {
					distance = tmpDistance
					result = sum
				}
			}
		}
	}
	return result
}

func main() {
	nums := []int{1, 1, -1, -1, 3}
	fmt.Println(threeSumClosest(nums, -1))
}

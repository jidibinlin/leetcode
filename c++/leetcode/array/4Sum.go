func fourSum(nums []int, target int) [][]int {
	result := [][]int{}
	if len(nums) < 4 {
		return result
	}
	sort.Ints(nums)
	for i := 0; i < len(nums)-3; i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}
		ntarget := target - nums[i]
		tmp := threeSum(nums[i+1:], nums[i], ntarget)
		for _, value := range tmp {
			result = append(result, value)
		}
	}
	return result
}

func threeSum(nums []int, first int, target int) [][]int {
	result := [][]int{}
	if len(nums) < 3 {
		return result
	}

	for i := 0; i < len(nums); i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}

		k := len(nums) - 1
		ntarget := target - nums[i]

		for j := i + 1; j < len(nums); j++ {
			if j > i+1 && nums[j] == nums[j-1] {
				continue
			}

			for j < k && nums[j]+nums[k] > ntarget {
				k--
			}

			if j == k {
				break
			}

			if nums[j]+nums[k] == ntarget {
				result = append(result, []int{first, nums[i], nums[j], nums[k]})
			}
		}
	}
	return result
}

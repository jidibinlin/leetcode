package main

// quickSort ...
func quickSort(nums []int, left int, right int) {
	if left >= right {
		return
	}

	temp := nums[left]
	start := left
	stop := right

	for right != left {
		for right > left && nums[right] >= temp {
			right--
		}
		for left < right && nums[left] <= temp {
			left++
		}
		if right > left {
			nums[right], nums[left] = nums[left], nums[right]
		}
	}

	nums[right], nums[start] = temp, nums[right]
	quickSort(nums, start, left)
	quickSort(nums, right+1, stop)
}

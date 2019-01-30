package Array

import (
	"fmt"
	"sort"
)

// 1. Two Sum
// topics: array, hash table
func twoSumDFS(nums []int, target int) []int {
	if len(nums) <= 0 {
		return []int{}
	}

	for i := range nums {
		for j := i + 1; j < len(nums); j++ {
			if nums[i]+nums[j] == target {
				res := make([]int, 2)
				res[0] = i
				res[1] = j
				return res
			}
		}
	}

	return []int{}
}

func twoSumHashMap(nums []int, target int) []int {
	if len(nums) < 1 {
		return []int{}
	}

	numMap := make(map[int]int)
	for key, value := range nums {
		if _, ok := numMap[target-value]; ok {
			return []int{numMap[target-value], key}
		}
		numMap[value] = key
	}

	return []int{}
}

func twoSumTest() {
	fmt.Println("1. Two Sum")
	nums := []int{3, 2, 4}
	target := 6
	res := twoSumDFS(nums, target)
	fmt.Println("twoSumDFS: ", res)

	res = twoSumHashMap(nums, target)
	fmt.Println("twoSumHashMap: ", res)
	fmt.Println()
}

// 39. Combination Sum
// topics: array, backtracking
func combinationSum(candidates []int, target int) [][]int {
	var res [][]int
	var path []int
	sort.Ints(candidates)
	combination(&res, path, candidates, target, 0)
	return res
}

func combination(res *[][]int, path []int, candidates []int, target int, begin int) {
	if 0 == target {
		/*
		// func2
		new_path := make([]int, len(path))
		copy(new_path, path, )
		*res = append(*res, new_path)
		*/
		// func1
		*res = append(*res, path)
		return
	}

	for key, value := range candidates[begin:] {
		if target-value >= 0 {
			path = append(path, value)
			combination(res, path, candidates, target-value, key+begin)
			// here path is slice, res append path, just append a reference, so when path change(append, slice again), it can change result in res
			// func1
			path = path[: len(path)-1 : len(path)-1]
			/*
			// func2
			path = path[:len(path)-1]
			*/
		}
	}
}

func combinationSumTest() {
	fmt.Println("39. Combination Sum")
	candidates := []int{2, 3, 5}
	result := combinationSum(candidates, 8)
	fmt.Println("combinationSum: ", "candidates: ", candidates, "result: ", result)
	fmt.Println()
}

func TestLeetCodeArray() {
	twoSumTest()
	combinationSumTest()
}

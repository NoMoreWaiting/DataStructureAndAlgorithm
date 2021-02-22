class TwoSum:
    """
    1. Two Sum
    topics: array, hash table
    """

    def two_sum_hash_map(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        if len(nums) < 1:
            return []

        nums_dict = {}

        for i in range(len(nums)):
            if (target - nums[i]) in nums_dict:
                return [nums_dict[target - nums[i]], i]
            nums_dict[nums[i]] = i

        return []

    def test(self):
        print("1. Two Sum")
        nums = [3, 2, 4]
        target = 6
        res = self.two_sum_hash_map(nums, target)
        print("twoSumHashMap: ", res)
        print()


class CombinationSum:
    """
    39. CombinationSum
    topics: array, backtracking
    """

    def combination_sum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        res = []
        list.sort(candidates)
        self.combination(res, [], candidates, target, 0)
        return res

    def combination(self, res, path, candidates, target, begin):
        if target == 0:
            res.append(path)
            return

        for key in range(begin, len(candidates)):
            if target - candidates[key] >= 0:
                self.combination(res, path + [candidates[key]], candidates, target - candidates[key], key)
            else:
                break

    def test(self):
        print("39. CombinationSum")
        candidates = [2, 3, 5]
        result = self.combination_sum(candidates, 8)
        print("combinationSum: ", "candidates: ", candidates, "result: ", result)
        print()


def test_leet_code_array():
    two_sum = TwoSum()
    two_sum.test()

    combination = CombinationSum()
    combination.test()

class TwoSum:
	"""
	1. Two Sum
	topics: array, hash table
	"""
	def twoSumHashMap(self, nums, target):
		"""
		:type nums: List[int]
		:type target: int
		:rtype: List[int]
		"""
		if len(nums) < 1:
			return []

		numsDict = {}

		for i in range(len(nums)):
			if (target - nums[i]) in numsDict:
				return [numsDict[target - nums[i]], i]
			numsDict[nums[i]] = i

		return []

	def test(self):
		print("1. Two Sum")
		nums = [3, 2, 4]
		target = 6
		res = self.twoSumHashMap(nums, target)
		print("twoSumHashMap: ", res)
		print()


class CombinationSum:
	"""
	39. CombinationSum
	topics: array, backtracking
	"""
	def combinationSum(self, candidates, target):
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
		result = self.combinationSum(candidates, 8)
		print("combinationSum: ", "candidates: ", candidates, "result: ", result)
		print()


def TestLeetCodeArray():
	twoSum = TwoSum()
	twoSum.test()

	combination = CombinationSum()
	combination.test()
class Solution:
    nums = []
    value = []

    def calcRobber(self, house: int):
        myValue = self.nums[house]

        # Get the max last possible robbery value
        # We can pick either house 0 or 1, if we arrive at this step
        if house == 1:
            return max(myValue, self.nums[0])

        if house == 0:
            return myValue

        # Stop if value of house has already been calculated
        if self.value[house] != -1:
            return self.value[house]

        # Calculate value of robbery
        # if we pick current house
        val1 = self.calcRobber(house - 2) + myValue
        # if we pick the previous house
        val2 = self.calcRobber(house - 1)

        # Pick max value and store it in precalc value array
        myValue = max(val1, val2)
        self.value[house] = myValue
        return myValue

    def rob(self, nums: List[int]) -> int:
        self.nums = nums
        # Init array of calculated house values
        # -1 means value not calculated yet
        self.value = [-1] * len(nums)

        return self.calcRobber(len(nums) - 1)

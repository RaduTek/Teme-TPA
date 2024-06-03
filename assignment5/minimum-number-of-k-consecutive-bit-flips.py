class Solution:
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        n = len(nums)

        # Count of k-bits that need to be flipped
        count = 0
        # Flag that indicates whether a flip should be done
        # at the current pos
        current = 0
        # Array of positions we start flipping bits from
        flips = [0] * n

        for i in range(n):
            # Toggle current flip state flag
            # if index is after the first flip group
            if i >= k:
                current ^= flips[i - k]

            # Flip current bit if necessary
            if nums[i] == current:
                if i > n - k:
                    # We can't start a flip at a position
                    # too close to the end of the array
                    return -1
                if i < n - k:
                    # Start flip at position i
                    flips[i] = 1
                count += 1
                current ^= 1

        return count

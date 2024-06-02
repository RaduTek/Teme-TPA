class Solution:
    def countFromIndex(self, left: int, right: int, s: str) -> int:
        count = 0

        # Increase substring start and finish positions as long
        # as subsstring is a palindrome
        while 0 <= left and right < len(s) and s[left] == s[right]:
            left -= 1
            right += 1
            count += 1
        
        return count
    
    def countSubstrings(self, s: str) -> int:
        count = 0

        for i in range(len(s)):
            # count odd length palindromes
            count += self.countFromIndex(i, i, s)
            # count even length palindromes
            count += self.countFromIndex(i, i+1, s)

        return count
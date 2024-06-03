# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class TreeNodeEx(TreeNode):
    def __init__(self, val=0, left=None, right=None):
        super().__init__(val, left, right)
        self.total = -1


def cast_treenodeex(node: Optional[TreeNode]) -> Optional[TreeNodeEx]:
    if not node:
        return None

    left_ex = cast_treenodeex(node.left)
    right_ex = cast_treenodeex(node.right)

    return TreeNodeEx(node.val, left_ex, right_ex)


class Solution:

    def calcRobber(self, house: Optional[TreeNodeEx]) -> int:
        # Not a node
        if not house:
            return 0

        # Leaf node
        if not house.left and not house.right:
            return house.val

        # Return total value if present
        if house.total != -1:
            return house.total

        # Calculate value of next depth
        val1 = self.calcRobber(house.left)
        val1 += self.calcRobber(house.right)

        # Calculate value of current node and
        val2 = house.val
        if house.left:
            val2 += self.calcRobber(house.left.left)
            val2 += self.calcRobber(house.left.right)
        if house.right:
            val2 += self.calcRobber(house.right.left)
            val2 += self.calcRobber(house.right.right)

        house.total = max(val1, val2)
        return house.total

    def rob(self, root: Optional[TreeNode]) -> int:
        return self.calcRobber(cast_treenodeex(root))

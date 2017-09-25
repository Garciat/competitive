// https://leetcode.com/problems/sum-root-to-leaf-numbers/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func sumNumbers(root *TreeNode) int {
    return work(root, 0)
}

func work(node *TreeNode, val int) int {
    if node == nil {
        return 0
    }
    next := 10 * val + node.Val
    if node.Left == nil && node.Right == nil {
        return next
    }
    return work(node.Left, next) + work(node.Right, next)
}

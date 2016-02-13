/*
 * Problem 4.45
 * Noah Weiner
 *
 * Running time: O(n)
 */

template<typename T>
struct BinaryTreeNode {
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	T element;
};

template<typename T>
bool similar(const BinaryTreeNode<T>* n1, const BinaryTreeNode<T>* n2) {
	if (n1 == NULL && n2 == NULL)
		return true;
	else if (n1 != NULL && n2 != NULL)
		return (n1->element == n2->element
				&& similar(n1->left, n1->right)
				&& similar(n2->left, n2->right));
	else
		return false;
}

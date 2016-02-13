/*
 * Problem 4.31
 * Noah Weiner
 */

template<typename T>
struct BinaryNode {
	BinaryNode* left;
	BinaryNode* right;
	T element;
};

/*
 * a) O(n)
 */

int num_nodes(const BinaryNode* n) {
	int count = 1;
	if (n->left != NULL) count += num_nodes(n->left);
	if (n->right != NULL) count += num_nodes(n->right);
	return count;
}

/*
 * b) O(n)
 */

int num_leaves(const BinaryNode* n) {
	if (n->left == NULL && n->right == NULL)
		return 1;
	else {
		int count = 0;
		if (n->left != NULL) count += num_leaves(n->left);
		if (n->right != NULL) count += num_leaves(n->right);
		return count;
	}
}

/*
 * c) O(n)
 */

int num_fullnodes(const BinaryNode* n) {
	int count = (n->left == NULL && n->right == NULL) ? 1 : 0;
	if (n->left != NULL) count += num_fullnodes(n->left);
	if (n->right != NULL) count += num_fullnodes(n->right);
	return count;
}

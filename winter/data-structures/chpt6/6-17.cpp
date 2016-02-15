/* Problem 6.17
 * Noah Weiner
 *
 * Suppose that binary heaps are represented using explicit links. Consider the problem
 * of merging binary heap lhs with rhs. Assume both heaps are perfect binary trees,
 * containing 2l − 1 and 2r − 1 nodes, respectively.
 */

/* Sample node structure */
template< typename Comparable >
struct HeapNode {
	Comparable value;
	HeapNode* left, right;
	HeapNode(Comparable value, HeapNode* left = nullptr,
		HeapNode* right = nullptr) : value(value), left(left), right(right) { }
}

/* helper functions */

/* returns new root node */
HeapNode* percolateDown(HeapNode* node) {
	HeapNode* tmp, root;
	root = tmp = node;
	while (node->left != nullptr || root->value < tmp->value) {
		if (node->right == nullptr)
			tmp = node->left;
		else
			tmp = node->left->value < node->right->value ? node->left : node->right;

		if (tmp->value < node->value) {
			/* swap nodes */
			std::swap(node->left, tmp->left);
			std::swap(node->right, tmp->right);

			/* keep track of root */
			if (node == root)
				root = tmp;
		}
	}

	return root;
}

/*
 * a. Give an O(log N) algorithm to merge the two heaps if l = r.
 */

HeapNode* merge(HeapNode* lhs, HeapNode* rhs) {
	HeapNode* tmp, brm, root;	/* brm = bottom-right-most node */

	/* delete bottom-right-most value in rhs tree */
	brm = rhs;
	tmp = nullptr;	/* chase pointer */
	while (brm->right != nullptr) {
		tmp = brm;
		brm = brm->right;
	}
	if (tmp != nullptr)
		tmp->right = nullptr;

	/* make brm root */
	brm->left = lhs;
	brm->right = rhs;
	return percolateDown(brm);
}

/*
 * b. Give an O(log N) algorithm to merge the two heaps if |l − r| = 1.
 */

HeapNode* merge(HeapNode* lhs, HeapNode* rhs) {
	HeapNode* tmpL, tmpR, brmL, brmR, brm, root;

	/* smaller tree should go on the right */
	brmL = lhs;
	brmR = rhs;
	tmpL = tmpR = nullptr;	/* chase pointers */

	while (brm == nullptr) {
		if (brmL->right == nullptr) {
			brm = brmR->right;

			if (tmpR != nullptr)
				tmpR->right = nullptr;	/* remove brm from tree */

			if (brmR->right != nullptr) {
				/* right tree is larger */
				std::swap(lhs, rhs);
			}
		} else if (tmpR->right == nullptr) {
			/* left tree is larger */
			brm = tmpL->right;

			if (tmpL != nullptr)
				tmpL->right = nullptr;	/* remove brm from tree */
		} else {
			tmpL = brmL;
			tmpR = brmR;
			brmL = brmL->right;
			brmR = brmR->right;
		}
	}

	/* make brm root */
	brm->left = lhs;
	brm->right = rhs;
	return percolateDown(brm);
}

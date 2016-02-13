/*
 * Problem 4.26
 * Noah Weiner
 */

template<typename T>
struct node {
	node* left;
	node* right;
	T val;
};

/*
 * k1, k2, and k3 are the three nodes involved in the rotation, as defined
 * in the text (p. 150).
 *
 * Returns the new parent node (k2).
 */
node* double_rotation(node* k1, node* k2, node* k3) {
	k1->right = k2->left;
	k3->left = k2->right;
	k2->left = k1;
	k2->right = k3;
	return k2;
}

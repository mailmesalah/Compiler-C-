#include "TreeNode.h"


void TreeNode::registerChildForSearch(TreeNode* node) {
	elementsIndex.push_back(node);
	if (parent != NULL) {
		parent->registerChildForSearch(node);
	}
}

TreeNode::TreeNode() {
	children = {};
}

TreeNode::TreeNode(const string pdata) {
	data = pdata;
	children = {};
	//this.children = new LinkedList<TreeNode<T>>();
	//this.elementsIndex = new LinkedList<TreeNode<T>>();
	this->elementsIndex.push_back(this);
}

TreeNode* TreeNode::addChild(string data) {
	TreeNode* childNode = new TreeNode(data);	
	childNode->parent = this;
	children.push_back(childNode);
	registerChildForSearch(childNode);
	return childNode;
}

bool TreeNode::isRoot() {
	return this->parent == NULL;
}

bool TreeNode::isLeaf() {
	return this->children.size() == 0;
}

int TreeNode::getLevel() {
	if (isRoot()) {
		return 0;
	}
	else {
		this->parent->getLevel() + 1;
	}
}

TreeNode* TreeNode::findTreeNode(const string cmp) {
	for (std::list<TreeNode*>::iterator it = elementsIndex.begin(); it != elementsIndex.end(); ++it) {
		TreeNode *temp = (*it);
		string elData = temp->data;

		if (strcmp(cmp.c_str(), elData.c_str()) == 0) {
			return temp;
		}
	}

	return NULL;
}


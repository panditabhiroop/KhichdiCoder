    #include <iostream>
    #include <conio.h>
    using namespace std;
     
    struct RBNode {
    	int val;
    	int col;
    	struct RBNode* left;
    	struct RBNode* right;
    	struct RBNode* parent;
    };
    typedef struct RBNode node;
     
    void rightRotation(node* temp) {
     
    	if (temp->left == NULL) {
    		cout << "Invalid move can't Right rotate along a node having no left child\n";
    		return;
    	}
     
    	if (temp->parent != NULL) {
    		if (temp->parent->left == temp) {
    			temp->parent->left = temp->left;
    		//	cout << "one\n";
    		}
    		else {
    			temp->parent->right = temp->left;
    		//	cout << "two\n";
    		}
     
    	}
     
    	temp->left->parent = temp->parent;
    	temp->parent = temp->left;
    	temp->left = temp->parent->right;
    	temp->parent->right = temp;
    	if (temp->left != NULL)
    	temp->left->parent = temp;
    }
     
    void leftRotation(node* temp) {
     
    	if (temp->right == NULL) {
    		cout << "Can't apply left rotation on this node as it doesn't have a right child\n";
    		return;
    	}
     
    	if (temp->parent != NULL) {
    		if (temp->parent->left == temp) {
    			temp->parent->left = temp->right;
    		}
    		else {
    			temp->parent->right = temp->right;
    		}
     
    	}
     
    	temp->right->parent = temp->parent;
    	temp->parent = temp->right;
    	temp->right = temp->right->left;
    	temp->parent->left = temp;
    	if (temp->right != NULL)
    	temp->right->parent = temp;
    }
     
    int checkRBTree(node* root) {
     
    	if (root == NULL)
    		return 1;
     
    	if (root->col == 2) {
    		if (root->parent == NULL || root->parent->col == 2)
    			return -1;
    	}
     
    	int temp = checkRBTree(root->left);
    	int temp1 = checkRBTree(root->right);
     
    	if (temp == temp1) {
    		return root->col == 1 ? temp + 1 : temp;
    	}
    		return -1;
     
     
    }
     
    void printNode(node* temp) {
    	cout << "Printing the node:\n";
    	cout << "val is: " << temp->val << endl;
    	cout << "col is: " << temp->col << endl;
    	if (temp->left == NULL) {
    		cout << "left node: NULL\n";
    	}
    	else {
    		cout << "left node: " << temp->left->val << endl;
    	}
     
    	if (temp->right == NULL) {
    		cout << "Right node: NULL\n";
    	}
    	else {
    		cout << "Right node: " << temp->right->val << endl;
    	}
     
    	if (temp->parent == NULL) {
    		cout << "parent node: NULL\n";
    	}
    	else {
    		cout << "parent node: " << temp->parent->val << endl;
    	}
    }
     
    node* insert(node* root, int val) {
     
    	node *temp = root;
    	node *temp1 = temp->val > val ? temp->left : temp->right;
    	while (temp1 != NULL) {
    		temp = temp1;
    		temp1 = temp->val > val ? temp->left : temp->right;
    	}
    	temp1 = new node();
    	temp1->val = val;
    	temp1->left = NULL;
    	temp1->right = NULL;
    	temp1->parent = temp;
    	temp1->col = 2;
    	if (temp->val > val) {
    		temp->left = temp1;
    	}
    	else {
    		temp->right = temp1;
    	}
    		
    		while (temp1 != root && temp1->col == 2 && temp1->parent->col == 2) {
     
    			if (temp1->parent->parent == NULL) {
    				temp1->parent->col = 1;
    				break;
    			}
    			
    			if (temp1->parent == temp1->parent->parent->left) {
    			//	cout << "five\n";
    				temp = temp1->parent->parent->right;
    				if (temp != NULL && temp->col == 2) {
    					//CASE1
    				//	cout << "six\n";
    					temp1->parent->col = 1;
    					temp1->parent->parent->col = 2;
    					temp->col = 1;
    					temp1 = temp1->parent->parent;
    					continue;
    				}
    				else {
    					if (temp1 == temp1->parent->right) {
    						//CASE2
    						leftRotation(temp1->parent);
    						temp1 = temp1->left;
    					//	cout << "seven\n";
    					}
    				}
    				//CASE3
    				rightRotation(temp1->parent->parent);
    				temp1->parent->col = 1;
    				temp1->parent->right->col = 2;
    				break;
    			}
    			else {
    			//	cout << "eight\n";
    				temp = temp1->parent->parent->left;
    				if (temp != NULL && temp->col == 2) {
    					//CASE4
    					//cout << "nine\n";
    					temp1->parent->col = 1;
    					temp1->parent->parent->col = 2;
    					temp->col = 1;
    					temp1 = temp1->parent->parent;
    					continue;
    				}
    				else {
    					if (temp1 == temp1->parent->left) {
    						//CASE5
    						rightRotation(temp1->parent);
    						temp1 = temp1->right;
    					//	cout << "ten\n";
    					}
    				}
    				//CASE6
    				leftRotation(temp1->parent->parent);
    				temp1->parent->col = 1;
    				temp1->parent->left->col = 2;
    				break;
    			}
    		}
    		while (root->parent != NULL) {
    			root = root->parent;
    		}
    		root->col = 1;
    	return root;
    	
    }
     
    int balanceHeight(node* vnode, node* prnt, node* root) {
     
    	node* temp = vnode;
    	if (vnode == root)
    		return 1;
     
    	// Now different cases will be covered
    	// Case 1.1: 
    	if (temp == prnt->right) {
     
    		// Temp is the right child of it's father
     
    		if (prnt->col == 2) {
    			//Temp's parent color is red
     
    			if (prnt->left->left != NULL && prnt->left->left->col == 2) {
     
    				//Case 1.1.1:
    				//Temp's left sibling has a left child which is red in color
     
    				rightRotation(prnt);
    				prnt->col = 1;
    				prnt->parent->col = 2;
    				prnt->parent->left->col = 1;
    				return 1;
    			}
     
    			if (prnt->left->right != NULL && prnt->left->right->col == 2) {
     
    				//Case 1.1.2:
    				//Temp's left sibling has a right child whose color is red
    				leftRotation(prnt->left);
    				rightRotation(prnt);
    				prnt->col = 1;
    				return 1;
    			}
     
    			if ((prnt->left->left == NULL || prnt->left->left->col == 1) && (prnt->left->right == NULL || prnt->left->right->col == 1)) {
     
    				//Case 1.2:
    				//Temp's left sibling either have no child or having only black  child
    				prnt->col = 1;
    				prnt->left->col = 2;
    				return 1;
    			}
    		}
    		else {
    			
    			//Temp's parent color is black
     
    			if (prnt->left->col == 2) {
     
    				//Temp's left sibling is red in color
     
    				if (prnt->left->right != NULL) {
     
    					//Temp's left sibling has a right child
     
    					if (prnt->left->right->left != NULL && prnt->left->right->left->col == 2) {
     
    						//Case 2.1.1.1:
    						//Temp's left sibling's right child has a left child which is red
     
    						prnt->left->right->left->col = 1;
    						leftRotation(prnt->left);
    						rightRotation(prnt);
    						return 1;
    					}
     
    					if (prnt->left->right->right != NULL && prnt->left->right->right->col == 2) {
     
    						//Case 2.1.1.2:
    						//Temp's left sibling's right child has a right child which is red
    						prnt->left->right->right->col = 1;
    						leftRotation(prnt->left->right);
    						leftRotation(prnt->left);
    						rightRotation(prnt);
    						return 1;
    					}
     
    						//Case 2.1.2:
    						prnt->left->col = 1;
    						prnt->left->right->col = 2;
    						rightRotation(prnt);
    						return 1;
    					}
     
    				} else {
     
    				//Temp's left sibling is black in color
     
    				if (prnt->left->left != NULL && prnt->left->left->col == 2) {
     
    					//Case 2.2.1.1
    					//Temp's left sibling has a left child which is red in color
    					prnt->left->left->col = 1;
    					rightRotation(prnt);
    					return 1;
    				}
     
    				if (prnt->left->right != NULL && prnt->left->right->col == 2) {
     
    					//Case 2.2.1.2:
    					//Temp's left sibling has a right child which is red in color
    					prnt->left->right->col = 1;
    					leftRotation(prnt->left);
    					rightRotation(prnt);
    					return 1;
    				}
     
    				//Case 2.2.2 need to work
    				prnt->left->col = 2;
    				balanceHeight(prnt, prnt->parent, root);
    				return 1;
     
    			}
     
    		}
    	}
     else {
     
    	 //Temp is the left child of it's parent
     
    	 if (prnt->col == 2) {
    		 //Temp's parent color is red
     
    		 if (prnt->right->right != NULL && prnt->right->right->col == 2) {
     
    			 //Case 1.1.1:
    			 //Temp's Right sibling has a right child which is red in color
     
    			 leftRotation(prnt);
    			 prnt->col = 1;
    			 prnt->parent->col = 2;
    			 prnt->parent->right->col = 1;
    			 return 1;
    		 }
     
    		 if (prnt->right->left != NULL && prnt->right->left->col == 2) {
     
    			 //Case 1.1.2:
    			 //Temp's right sibling has a left child whose color is red
    			 rightRotation(prnt->right);
    			 leftRotation(prnt);
    			 prnt->col = 1;
    			// prnt->parent->col = 1;
    			 return 1;
    		 }
     
    		 if ((prnt->right->left == NULL || prnt->right->left->col == 1) && (prnt->right->right == NULL || prnt->right->right->col == 1)) {
     
    			 //Case 1.2:
    			 //Temp's Right sibling either have no child or having only black  child
    			 prnt->col = 1;
    			 prnt->right->col = 2;
    			 return 1;
    		 }
    	 }
    	 else {
     
    		 //Temp's parent color is black
     
    		 if (prnt->right->col == 2) {
     
    			 //Temp's Right sibling is red in color
     
    			 if (prnt->right->left != NULL) {
     
    				 //Temp's Right sibling has a left child
     
    				 if (prnt->right->left->right != NULL && prnt->right->left->right->col == 2) {
     
    					 //Case 2.1.1.1:
    					 //Temp's Right sibling's left child has a Right child which is red
     
    					 prnt->right->left->right->col = 1;
    					 rightRotation(prnt->right);
    					 leftRotation(prnt);
    					 return 1;
    				 }
     
    				 if (prnt->right->left->left != NULL && prnt->right->left->left->col == 2) {
     
    					 //Case 2.1.1.2:
    					 //Temp's Right sibling's left child has a left child which is red
    					 prnt->right->left->left->col = 1;
    					 rightRotation(prnt->right->left);
    					 rightRotation(prnt->right);
    					 leftRotation(prnt);
    					 return 1;
    				 }
     
    				 //Case 2.1.2:
    				 prnt->right->col = 1;
    				 prnt->right->left->col = 2;
    				 leftRotation(prnt);
    				 return 1;
    			 }
     
    		 }
    		 else {
     
    			 //Temp's Right sibling is black in color
     
    			 if (prnt->right->right != NULL && prnt->right->right->col == 2) {
     
    				 //Case 2.2.1.1
    				 //Temp's Right sibling has a right child which is red in color
    				 prnt->right->right->col = 1;
    				 leftRotation(prnt);
    				 return 1;
    			 }
     
    			 if (prnt->right->left != NULL && prnt->right->left->col == 2) {
     
    				 //Case 2.2.1.2:
    				 //Temp's Right sibling has a left child which is red in color
    				 prnt->right->left->col = 1;
    				 rightRotation(prnt->right);
    				 leftRotation(prnt);
    				 return 1;
    			 }
     
    			 //Case 2.2.2 need to work
    			 prnt->right->col = 2;
    			 balanceHeight(prnt, prnt->parent, root);
    			 return 1;
     
    		 }
     
    	 }
     
     }
    	
     
    	if (vnode->col == 2) {
    		if (vnode == vnode->parent->left) {
    			vnode->parent->left = temp;
    		}
    		else {
    			vnode->parent->right = temp;
    		}
     
    		if (temp != NULL) {
    			temp->parent = vnode->parent;
    		}
    		return 1;
    	}
    	else {
    		if (temp != NULL && temp->col == 2) {
    			if (vnode == vnode->parent->left) {
    				vnode->parent->left = temp;
    			}
    			else {
    				vnode->parent->right = temp;
    			}
     
    			temp->parent = vnode->parent;
    			temp->col = 1;
    			return 1;
    		}
    	}
    }
     
    int deleteNode(node* root, int val) {
     
    	cout << "Came to delete node whose value is: " << val << endl;
     
    	if (root == NULL) {
    		cout << "Can't delete from an empty tree\n";
    		return 0;
    	}
     
    	node* temp = root;
    	node* temp1 = temp;
    	//node* temp1;
    	while (temp != NULL && temp->val != val) {
    		cout << "temp val is: " << temp->val << endl;
    		if (temp->val > val) {
    			temp = temp->left;
    		}
    		else {
    			temp = temp->right;
    		}
    	}
     
    	cout << "came out of while loop\n";
     
    	if (temp == NULL) {
    		cout << "The value is not found in the tree. So can't delete\n";
    		return 0;
    	}
     
    	if (temp->right != NULL) {
     
    		//Getting the right successor of the node
    		cout << "coming to find the right successor\n";
    		temp1 = temp->right;
     
    		while (temp1->left != NULL) {
    			temp1 = temp1->left;
    		}
     
    		//Exchanging the values
    		temp->val = temp1->val;
    	}
    	else if (temp->left != NULL) {
     
    		//Getting the left successor of the node
    		cout << "coming to find the left successor of the node\n";
    		temp1 = temp->left;
    		while (temp1->right != NULL) {
    			temp1 = temp1->right;
    		}
     
    		//Exchanging the values
    		temp->val = temp1->val;
    	}
    	else {
    		cout << "it's a leaf node\n";
    		temp1 = temp;
    	}
     
    	//Actual deleting the Successor node
     
    	temp = temp1->left == NULL ? temp1->right : temp1->left;
     
    	//Changing parent pointer here as it is common for all
     
    	if (temp1->parent->right == temp1) { 
     
    		temp1->parent->right = temp;
    	}
    	else {
     
    		temp1->parent->left = temp;
    	}
     
    	//Now classification will happen
    	if (temp1->col == 2) {
    		
    		//The node to be deleted is a red Node
    		if (temp != NULL) {
    			temp->parent = temp1->parent;
    		}
    		
    		return 1;
    		
    	}
    	else {
     
    		//The node to be deleted is a black node
     
    		if (temp != NULL) {
     
    			//If it has a non null child
     
    			if (temp->col == 2) {
     
    				//The color of the non null child is red
    				temp->parent = temp1->parent;
    				temp->col = 1;
    				return 1;
    			}
    			else {
     
    				//This case is not possible
     
    				//The color of the non null child is Black
    				temp->parent = temp1->parent;
     
    				//########################################################## Adjust the height of the tree with node temp ################################################################# 
    				balanceHeight(temp, temp->parent, root);
    			}
    		}
    		else {
     
    			//it has no child
    			//############################################################## Adjust the height of the tree with node temp1 #################################################################
    			balanceHeight(temp, temp1->parent, root);
    		}
     
    	}
    		
    }
     
    void inorder(node *root) {
    	if (root == NULL)
    		return;
    	inorder(root->left);
    	//cout << root->val << " ";
    	printNode(root);
    	cout << endl;
    	inorder(root->right);
    }
     
    int main()
    {
    	int n, val, t;
    	node* root = new node();
    	cin >> val;
    	root->val = val;
    	root->parent = NULL;
    	root->left = NULL;
    	root->right = NULL;
    	root->col = 1;
     
    	while (true) {
    		cin >> t;
    		if (t == 0) {
    			inorder(root);
    			break;
    		}
    		else if (t == 1) {
    			cin >> val;
    			root = insert(root, val);
    		}
    		else {
    			cin >> val;
    			deleteNode(root, val);
    		}
     
    			while (root->parent != NULL) {
    				root = root->parent;
    			}
    	}
     
    
    	cout << "tree height is: \n";
    	cout<<checkRBTree(root)<<"\n";
    	char ch;
    	cin >> ch;
    	return 0;
    }



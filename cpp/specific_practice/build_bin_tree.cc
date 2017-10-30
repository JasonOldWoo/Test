#include <vector>
#include <iostream>
using namespace std;
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
	public:
		typedef unsigned int uint;
		TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
			return reConstructBinaryTree_recusively(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
		}

		TreeNode* reConstructBinaryTree_recusively(vector<int>& pre, uint pl, uint pr, vector<int>& vin, uint vl, uint vr) {
			if (pl >= pre.size()) {
				return NULL;
			}
			if (pr >= pre.size()) {
				return NULL;
			}
			if (pl >  pr) {
				return NULL;
			}
			if (pl == pr) {
				std::cout << "leaf: " << pre[pl] << std::endl;
				return NodeAccess::Assign(pre[pl]);
			}

			TreeNode* p_subl = NULL;	// 左子树
			TreeNode* p_subr = NULL;	// 右子树

			/* **
			 * 找中根数组的根位置
			 * **/
			uint vroot = vl;
			while (!(pre[pl] == vin[vroot]) && vroot < vin.size()) {
				vroot ++;
			}

			uint leftsub_pl = pl + 1;
			uint leftsub_pr = pl + vroot - vl;
			uint leftsub_vl = vl;
			uint leftsub_vr = vroot - 1;

			if (vroot  != vl) {
				p_subl = reConstructBinaryTree_recusively(pre, leftsub_pl, leftsub_pr, vin, leftsub_vl, leftsub_vr);
			}

			uint rightsub_pl = leftsub_pr + 1;
			uint rightsub_pr = pr;
			uint rightsub_vl = vroot + 1;
			uint rightsub_vr = vr;
			if (vroot < vin.size()) {
				p_subr = reConstructBinaryTree_recusively(pre, rightsub_pl, rightsub_pr, vin, rightsub_vl, rightsub_vr);
			}

			TreeNode* root = NodeAccess::Assign(pre[pl]);
			NodeAccess::Left(root) = p_subl;
			NodeAccess::Right(root) = p_subr;
			std::cout << pre[pl] << std::endl;
			return root;
		}

		class NodeAccess {
			public:
				static TreeNode* Assign(int val) {
					return new TreeNode(val);
				}

				static TreeNode*& Left(TreeNode* p_node) {
					return p_node->left;
				}

				static TreeNode*& Right(TreeNode* p_node) {
					return p_node->right;
				}

				static int& Val(TreeNode* p_node) {
					return p_node->val;
				}
		};
};

int main()
{
	int preint[] = {1,2,4,7,3,5,6,8};
	int vinint[] = {4,7,2,1,5,3,8,6};
	vector<int> pre(preint, preint + sizeof (preint) / sizeof (int));
	vector<int> vin(vinint, vinint + sizeof (vinint) / sizeof (int));
	Solution s;
	s.reConstructBinaryTree(pre, vin);
	return 0;
}

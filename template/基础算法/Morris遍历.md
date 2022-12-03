## Morris遍历

一般的二叉树的递归遍历或者非递归遍历`时间复杂度`为`O(n)`,`空间复杂度`为`O(n)`

**但是Morris遍历能够使得`时间复杂度`保持为`O(n)`的情况下空间复杂度为`O(1)`**



`Morris`遍历核心操作：

> 当前指针为`cur`

```cpp
1)cur无左子树,cur = cur -> right;
2)cur有左子树，先找到左子树的最右边结点 right_most
    2)right_most 右指针为空，将该节点右指针指向cur，cur左移
    3)right_most 右指针指向cur，回复其右指针为空，cur向右移动
3)cur为null，停止
```

此时得到的遍历序列(`cur`的遍历序列)称为`Morris`序列



`Morris`序列的有趣性质：

> 1) 节点无左子树，节点只出现一次
> 2) 节点有左子树，节点出现两次
> 3) 两次的中间正好将此节点的左子树完全遍历



核心：由于二叉树没有向上的指针，因此需要借助栈/系统栈来帮助遍历，而`Morris遍历`之所以能够到达`O(1)`的空间复杂度就是因为他创建了向上的指针





代码：

先序遍历

```cpp
class Solution{
public:
    vector<int> preorderTraversal(TreeNode* root){
        vector<int> res;
        if(root==nullptr)
        return res;
        TreeNode* cur=root, *pre=nullptr;
        while(cur!=nullptr){
            if(cur->left==nullptr){//当前节点左子树为空则遍历右子树
                res.push_back(cur->val);
                cur=cur->right;
            }//当到达最左节点时，也是用此回退。
            else{
                pre=cur->left;//前驱节点
                while(pre->right!=nullptr && pre->right!=cur){
                    pre=pre->right;
                }//找到前驱节点的最右节点，为什么这里要pre->right!=cur呢？因为当你遍历到左子树最后一个节点后会回退到上一个节点，这事pre->right=cur,会造成死循环
                if(pre->right==nullptr){
                    pre->right=cur;
                    res.push_back(cur->val);
                    cur=cur->left;
                }//遍历左节点
                if(pre->right==cur){
                    pre->right=nullptr;
                    cur=cur->right;
                }//遍历右节点
            }
        }
        return res;
    }
};

```

中序遍历

```cpp
class Solution{
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> res;
        if(root==nullptr)
        return res;
        TreeNode* cur=root, *pre=nullptr;
        while(cur!=nullptr){
            if(cur->left==nullptr){
                res.push_back(cur->val);
                cur=cur->right;
            }
            else{
                pre=cur->left;
                while(pre->right!=nullptr && pre->right!=cur){
                    pre=pre->right;
                }
                if(pre->right==nullptr){
                    pre->right=cur;
                    cur=cur->left;
                }
                if(pre->right==cur){
                    pre->right=nullptr;
                    res.push_back(cur->val);
                    cur=cur->right;
                }
            }
        }
        return res;
    }
};

```

后序遍历

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root==nullptr)
        return res;
        TreeNode* cur=root,*pre=nullptr;//这上面是Morris模板
        while(cur!=nullptr){
            if(cur->left==nullptr){
                cur=cur->right;
            }
            else{
                pre=cur->left;
                while(pre->right!=nullptr && pre->right!=cur){
                    pre=pre->right;
                }
                if(pre->right==nullptr){
                    pre->right=cur;
                    cur=cur->left;
                }
                if(pre->right==cur){
                    pre->right=nullptr;
                    rightBrunch(cur->left,res);//回退倒上一层把下一个左节点的右边节点一次全遍历过去再将结果翻转
                    cur=cur->right;
                }
            }
        }
        rightBrunch(root,res);//还剩头结点的右边节点没处理
        return res;
    }
    void rightBrunch(TreeNode* root , vector<int>& res){
        TreeNode* cur=root;
        int count=0;
        while(cur!=nullptr){
            ++count;
            res.push_back(cur->val);//把右边节点值装入数组
            cur=cur->right;
        }
        reverse(res.end()-count,res.end());//翻转
    }
};

```



```

```
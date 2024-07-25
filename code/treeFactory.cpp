/* --------------------------------------- 
 * Description: Print tree branches horizontally in console for better view of data with treewise structure.
 * Author: Linghuei Guo
 * Affiliation: Henu, Kaifeng, China
 * MailTo: guolh2013@hotmail.com 
 * PGP: 6819D81B0971C2C4
 * Copyright: All Rights Reserved
--------------------------------------- */

#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include<iostream>
#include <sstream>
#include <vector>
using namespace std;


template <typename T, typename DType>
class TreePrinter {
public:
  static int dataWidth;
  virtual string dataStringify(T* node) {
    ostringstream sout;
    sout.setf(ios::left);
    sout.width(dataWidth);
    sout.fill(' ');
    sout.precision(dataWidth / 3);
    sout << *(node);
    return sout.str();
  }
    
  virtual T* getLeft(T* parent) ;
  virtual T* getRight(T* parent);
  virtual DType* getData(T* node) = 0; 
      
  virtual bool isLeaf(T* node);

  void print(T* root, ostream& o = cout, string prefix = ">", bool isLeft = false) {


    if (!isLeft) {
      o<<prefix.substr(0, prefix.length() - 1)<<"└";
    }
    else {
      o<<"┬";
    }


    string output = dataStringify(root);
    o<<"─ "<<output<<"";

    if (isLeaf(root)) {
      o<<""<<endl;
      return ;
    }
    else {
      cout<<"─";
    }

    string preLeft = "";
    string preRight= "";
    for (int i = 0; i < output.length() + 3; i++) {
      preLeft += " ";
      preRight += " ";
    }
    preRight+= " ";
    preLeft += "│";
    print(getLeft(root), o, prefix + preLeft, true);
    print(getRight(root), o, prefix + preRight, false);
  }
};

class WordPrinter : public TreePrinter<string, string> {
public:
  vector<string *> nodes;
  WordPrinter() : TreePrinter() {
    //    this-> dataWidth = 8;
  }

  int* wordDivider(string s) {
    static int ans[3];

    int len = s.length();

    // for for
    int &b0 = ans[0], &b1 = ans[1], &b2= ans[2], c;
    b0 = b1 = b2 = c = 0;

    for (b1 = 0; b1 < len; b1++) {
      char si = s[b1];
      
      b2 = b1 + 1;
      if (si == ')' && c > 0) 
	--c;
      else if (si == '(')
	b2 = b1;

      if (si == ' ' || si == ')' || si == '(')  {
	if (c == 0) {
	  if (b0 < b1) {
	    break;
	  }
	  else {
	    ++b0;
	  }
	}
      }

      if (si == '(') {
	++c;
      }
    }
    return ans;
  }

  static int wordCount(string s) {
    int words = 0, isWord = 0;
    for (int i = 0; i < s.length(); i++) {
      char ci = s[i];
      if (ci == '(' || ci == ')' || ci == ' ')  {
	isWord = 0;
      }
      else if (!isWord){
	++words;
	isWord = 1;
      }
    }
    return words;
  }

  static void wordDividerTester() {
    using namespace std;
    WordPrinter wp;
    string s = "((de)f(g)h)) (def(g(h))i) j j(abc)((de)f(g)h) j(abc)((de)f(g)h) j(abc)((de)f(g)h) j(abc)((de)f(g)h) j(abc)((de)f(g)h) j(abc)((de)f(g)h) j(abc)((de)f(g)h) j(abc)((de)f(g)h) j";
    while (s.length() > 0){
      int *dvs = wp.wordDivider(s);
      cout<<dvs[0]<<" .. "<<dvs[1]<<" : "<<dvs[2]<<endl;
      cout<<s.substr(dvs[0], dvs[1] - dvs[0])<<endl;
      s = s.substr(dvs[1], s.length());
      cout<<s<<endl;
      cout<<"  -- "<<endl;
    }

  }

  string* getLeft(string *s) {
    int len = s->length();
    string *ans = new string;

    int *divides = wordDivider(*s);
    *ans = s->substr(divides[0], divides[1] - divides[0]);

    nodes.push_back(ans);
    return ans;
  }

  string* getRight(string *s) {
    int len = s->length();
    string *ans = new string;


    int *divides = wordDivider(*s);
    *ans = s->substr(divides[2], len);
    
    
    nodes.push_back(ans);
    return ans;
  }

  string* getData(string *s) {
    string *ans = new string;
    *ans = *s + " :{" + std::to_string(wordCount(*s)) + "}"; 
    nodes.push_back(ans);
    return ans;
  }

  bool isLeaf(string *s) {
    int layers = wordCount(*s);
    return layers <= 1;
  }

  
  
  void flush() {
    while (nodes.size()) {
      delete *(nodes.end() - 1);
      nodes.pop_back();
    }
    cout<<"Cache flushed!"<<endl;
  }
  ~WordPrinter() {
    flush();
  }
} streePrinter;

template<> int TreePrinter<string, string>::dataWidth = 8;


template <typename DType> class TreeNode;
template <typename DType> class TreeFactory;
template <typename DType> class BalancedTree;

template<class DType> ostream& operator<<(ostream &o, TreeNode<DType>& n);
/*
 * @require: operator<=(DType, DType);
 */
template <typename DType> 
class TreeNode {
public:
  TreeNode() {
    isNull = true;
    depth = 0;
    left = right = NULL;
    data = -1;
  }

protected:
  bool isNull;
  DType data;
  TreeNode *left, *right;
  int depth;
  friend ostream& operator<<<DType>(ostream &o, TreeNode<DType>& n);
  template<typename D> friend class TreeFactory;
  template<typename D> friend class BalancedTree;
};

template<typename DType>
ostream& operator<<(ostream &o, TreeNode<DType>& n) {
  if (n.isNull) {
    o<<"[ ]";
  }
  else {
    o<<n.data;
  }
  return o;
}

template <typename DType>
class TreeFactory : virtual public TreePrinter<TreeNode<DType>, DType> {
  typedef TreeNode<DType> Nd;
public:
  TreeNode<DType> *root;

  TreeFactory() {
    root = new TreeNode<DType>();
  }

  static int setDepth(Nd *root) {
    if (root -> isNull)
      root->depth = 0;
    else {
      int dl = root->left->depth;
      int dr = root->right->depth;
      root->depth = dl >= dr ? dl + 1 : dr + 1;
    }
    return root->depth;
  }
  virtual Nd* insert(Nd *root, DType& data);
  virtual Nd* insert(DType& data);
  virtual Nd* getLeft(Nd *r);
  virtual Nd* getRight(Nd *r);
  virtual bool isLeaf(Nd *r);
  virtual DType *getData(Nd *r) {
    return &(r->data);
  }
  static void test() {
    TreeFactory<DType> tf;
    srand(23);
    for (int i = 0; i < 64; i++) {
      int rdm = (i + rand() % 15);
      tf.insert(rdm);
    }
    cout<<"Binary Search Tree Constructed..."<<endl;
    tf.print(tf.root);
  }
};

template<typename DType>
TreeNode<DType>  * TreeFactory<DType>::insert(TreeNode<DType> *root, DType &data) {
  if (root->isNull) {
    root->isNull = false;
    root->data = data;
    root->depth = 1;
    root->left = new TreeNode<DType>();
    root->right = new TreeNode<DType>();
  }
  else if (data  <= root->data) {
    root->left = insert(root->left, data);
  }
  else {
    root->right = insert(root->right, data);
  }
  return root;
}


template<typename DType>
TreeNode<DType>  * TreeFactory<DType>::insert(DType &data) {
  return insert(root, data);
}

template<typename DType>
bool TreeFactory<DType>::isLeaf(TreeNode<DType> *root) {
  return ! root || root->isNull || (!root->left || root->left->isNull) && (!root->right || root->right->isNull);
}

template<typename DType>
TreeNode<DType>* TreeFactory<DType>::getLeft(TreeNode<DType> *root) {
  return root->left;
}

template<typename DType>
TreeNode<DType>* TreeFactory<DType>::getRight(TreeNode<DType> *root) {
  return root->right;
}


template <typename DType>
class BalancedTree : public TreeFactory<DType> {
public:
  typedef TreeNode<DType> Nd;
  int getBalance(Nd* r) {
    if (r->isNull) {
      return 0;
    }
    else
      return r->left->depth - r->right->depth;
  }

  //@assert: ! r->right->isNull;
  Nd* rotateLeft(Nd* r) {
    Nd *r1 = r->right, *sub1 = r->right->left;
    r1->left = r;
    r->right = sub1;
    this->setDepth(r);
    this->setDepth(r1);
    return r1;
  }

  //@assert: ! r->left->isNull;
  Nd* rotateRight(Nd* r) {
    Nd *r1 = r->left, *sub1 = r->left->right;
    r1->right= r;
    r->left= sub1;
    this->setDepth(r);
    this->setDepth(r1);
    return r1;
  }

  Nd* rebalance(Nd* r) {
    int b = getBalance(r);
    if (b >= 2) {
      int bLeft = getBalance(r->left); 
      if (bLeft < 0) {
	r->left = rotateLeft(r->left);
      }
      r = rotateRight(r);
    }
    else if (b <= -2) {
      int bRight = getBalance(r->right);
      if (bRight > 0) {
	r->right = rotateRight(r->right);
      }
      r = rotateLeft(r);
    }
    return r;
  }
 
  Nd* insert(DType &data) {
    this->root = insert(this->root, data);
    return this->root;
  }

  Nd* insert(Nd* r, DType &data) {
    if (r->isNull) {
      r->isNull = false;
      r->depth = 1;
      r->data = data;
      r->left = new TreeNode<DType>;
      r->right = new TreeNode<DType>;
      return r;
    }
    else if (data < r->data) {
      r->left = insert(r->left, data);
      this->setDepth(r);
      return rebalance(r);
    }
    else {
      r->right = insert(r->right, data);
      this->setDepth(r);
      return rebalance(r);
    }
  }

  void print(){
    TreePrinter<TreeNode<DType>, DType>::print(this->root);
  }

  static void test() {
    BalancedTree<DType> t;
    srand(23);
    for (int i = 0; i < 64; ++i) {
      DType r = i + rand() % 15; 
      t.insert(r);
    }
    cout<<"Balanced Tree Constructed..."<<endl;
    t.print();
  }
};

template<> int TreePrinter<TreeNode<int>, int>::dataWidth = 6;
template<> int TreePrinter<TreeNode<double>, double>::dataWidth = 10;



#ifndef INCLUDE_AS_HEAD

int main() {
  string sentence= "(((ab) c ) (def(g(h))i)) (j h (i j))";
  cout<<"The sentence is :     "<<sentence<<endl;
  cout<<"The sentence is divided among the tree branches:"<<endl;
  streePrinter.print(&sentence);
  //WordPrinter::wordDividerTester();
  TreeFactory<int>::test();
  BalancedTree<int>::test();
  return 0;
}

#endif

#endif

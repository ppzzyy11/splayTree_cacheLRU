#ifndef splayTree_H_
#define splayTree_H_

#include "rotateBST.h"


using namespace std;

template<typename Key,typename Value>
class rotateBST;

template<typename Key,typename Value>
class SplayTree:public rotateBST<Key,Value>
{
    public:
        SplayTree()
        {
            time_left_rotation=0;
            time_right_rotation=0;
        }
        typename SplayTree<Key,Value>::iterator find(const Key& key)
        {
            Node<Key,Value>* pre=NULL;
            Node<Key,Value>* cur=this->mRoot;
            if(cur==NULL)
            {
                typename SplayTree<Key,Value>::iterator it(NULL);
                return it;
            }
            if(cur->getKey()==key)
            {
                typename SplayTree<Key,Value>::iterator it(cur);
                return it;
            }
            pre=cur;
            while(cur!=NULL)
            {
                pre=cur;
                if(cur->getKey()<key)//key is bigger ,go to right
                {
                    cur=cur->getRight();
                }else if(cur->getKey()>key)//key is smaller,go to left
                {
                    cur=cur->getLeft();
                }else {
                    splay(cur);
                    typename SplayTree<Key,Value>::iterator it(cur);
                    return it;
                }
            }
            splay(pre);
            typename SplayTree<Key,Value>::iterator it(NULL);
            return it;
        }
        typename SplayTree<Key,Value>::iterator findMin()
        {
            Node<Key,Value>* cur=this->mRoot;
            if(cur==NULL)
            {
                typename SplayTree<Key,Value>::iterator it(NULL);
                return it;
            }
            while(cur->getLeft()!=NULL)
            {
                cur=cur->getLeft();
            }
            splay(cur);
            typename SplayTree<Key,Value>::iterator it(cur);
            return it;
        }
        typename SplayTree<Key,Value>::iterator findMax()
        {
            Node<Key,Value>* cur=this->mRoot;
            if(cur==NULL)
            {
                typename SplayTree<Key,Value>::iterator it(NULL);
                return it;
            }
            while(cur->getRight()!=NULL)
            {
                cur=cur->getRight();
            }
            splay(cur);
            typename SplayTree<Key,Value>::iterator it(cur);
            return it;
        }
        void deleteMinLeaf()
        {
            Node<Key,Value>* cur=this->mRoot;
            if(cur==NULL) return ;

            while(cur->getLeft()!=NULL||cur->getRight()!=NULL)
            {
                if(cur->getLeft()!=NULL)
                {
                    cur=cur->getLeft();
                }else if(cur->getRight()!=NULL)
                {
                    cur=cur->getRight();
                }
            }
            remove(cur->getKey());
        }
        void deleteMaxLeaf()
        {
            Node<Key,Value>* cur=this->mRoot;
            if(cur==NULL) return;

            while(cur->getLeft()!=NULL||cur->getRight()!=NULL)
            {
                if(cur->getLeft()!=NULL)
                {
                    cur=cur->getLeft();
                }else if(cur->getRight()!=NULL)
                {
                    cur=cur->getRight();
                }
            }
            remove(cur->getKey());
        }
        void insert(const std::pair<const Key,Value>& keyValuePair)
        {
            BinarySearchTree<Key,Value>::insert(keyValuePair);
            find(keyValuePair.first);
        }
        void remove(const Key& key)
        {
            Node<Key,Value>* pre=NULL;
            Node<Key,Value>* cur=this->mRoot;
            if(cur==NULL) return ;
            while(cur)
            {
                if(cur->getKey()<key)//key is bigger ,go to right to find
                {
                    pre=cur;
                    cur=cur->getRight();
                }else if(cur->getKey()>key)//key is smaller, go to left
                {
                    pre=cur;
                    cur=cur->getLeft();
                }else
                {
                    BinarySearchTree<Key,Value>::remove(key);
                    break;//splay pre
                }
            }//cur is NULL,pre is last visited node OR cur is node to be delete , pre is parent
            splay(pre);
        }
        int getTimesLeftRotation(){return time_left_rotation;}
        int getTimesRightRotation(){return time_right_rotation;}
    private:
        Node<Key,Value>* splay(Node<Key,Value>* nod,Key k);//stand splay
        typename SplayTree<Key,Value>::iterator findHelper(Node<Key,Value>* nod,const Key& key);
        Node<Key,Value>* getp(const Key& k)
        {

        }
        int time_left_rotation;
        int time_right_rotation;
    protected:
        void splay(Node<Key,Value>* x)//splay the given node to the root//the r is existed
        {
            if(x==NULL) return ;
            Node<Key,Value>* p=x->getParent();
            if(p==NULL) return ;
            Node<Key,Value>* g=p->getParent();
            if(g==NULL)//p is root
            {
                if(p->getLeft()==x)
                {
                    rotateBST<Key,Value>::rightRotate(p);
                    return ;
                }else if(p->getRight()==x)
                {
                    rotateBST<Key,Value>::leftRotate(p);
                    return ;
                }
            }
            if(g->getLeft()==p&&p->getLeft()==x)//left left
            {
                rotateBST<Key,Value>::rightRotate(g);
            }else if(g->getLeft()==p&&p->getRight()==x)
            {
                rotateBST<Key,Value>::leftRotate(p);
                rotateBST<Key,Value>::rightRotate(g);
            }else if(g->getRight()==p&&p->getRight()==x)
            {
                rotateBST<Key,Value>::leftRotate(g);
            }else if(g->getRight()==p&&p->getLeft()==x)
            {
                rotateBST<Key,Value>::rightRotate(p);
                rotateBST<Key,Value>::leftRotate(g);
            }
            splay(x);
        }
};



template<typename Key,typename Value>
typename SplayTree<Key,Value>::iterator SplayTree<Key,Value>:: findHelper(Node<Key,Value>* nod,const Key& k)
{
    if(nod==NULL)
    {
        typename SplayTree<Key,Value>::iterator end(NULL);
        return end;
    }
    if(nod->getKey()<k)//k is on the right subtree
    {
        return findHelper(nod->getRight(),k);
    }else if(nod->getKey()>k)// k is on the left subtree
    {
        return findHelper(nod->getLeft(),k);
    }else {
        typename SplayTree<Key,Value>::iterator it(nod);
        return it;
    }
}


#endif

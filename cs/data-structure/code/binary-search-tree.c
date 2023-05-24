#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int key;
  struct node *leftChild;
  struct node *rightChild;
} node;
typedef node *nodePointer;

nodePointer new()
{
  nodePointer temp = (nodePointer)malloc(sizeof(node));
  temp->leftChild = temp->rightChild = NULL;
  return temp;
}

nodePointer modifiedSearch(nodePointer root, int key)
{ // get a parent node for inserting
  if (root->key == key || !root->key)
    return NULL;
  if (root->key > key && !root->leftChild || root->key < key && !root->rightChild)
    return root;
  if (root->key > key)
    return modifiedSearch(root->leftChild, key);
  if (root->key < key)
    return modifiedSearch(root->rightChild, key);
}

void insert(nodePointer *root, int key)
{
  nodePointer temp = modifiedSearch(*root, key);
  nodePointer newNode = new ();
  newNode->key = key;
  if (temp)
  {
    if (temp->key > key)
      temp->leftChild = newNode;
    else
      temp->rightChild = newNode;
  }
  else
  {
    *root = newNode;
  }
}

nodePointer search(nodePointer root, int key)
{
  if (!root)
    return NULL;
  if (root->key == key)
    return root;
  if (root->key > key)
  {
    return search(root->leftChild, key);
  }
  else
    return search(root->rightChild, key);
}

nodePointer parent(nodePointer root, int key)
{ // get a node that is a parent node has child that has a given key.
  if (!root)
    return NULL;
  if (root->leftChild && root->leftChild->key == key || root->rightChild && root->rightChild->key == key)
    return root;
  if (root->key > key)
  {
    return parent(root->leftChild, key);
  }
  else
    return parent(root->rightChild, key);
}

int max(nodePointer root)
{
  nodePointer temp = root;
  while (temp->rightChild)
    temp = temp->rightChild;
  return temp->key;
}

void delete(nodePointer root, int key)
{
  nodePointer target = search(root, key);
  nodePointer parentNode = parent(root, key);
  if (target && parentNode)
  {
    if (!target->leftChild && !target->rightChild)
    { // target is a leaf node;
      if (parentNode->leftChild->key == key)
      {
        free(parentNode->leftChild);
        parentNode->leftChild = NULL;
      }
      else
      {
        free(parentNode->rightChild);
        parentNode->rightChild = NULL;
      }
    }
    else if (!target->leftChild || !target->rightChild)
    { // target has a child node;
      nodePointer targetChild = target->leftChild ? target->leftChild : target->rightChild;
      if (parentNode->leftChild->key == key)
      {
        parentNode->leftChild = targetChild;
        free(target);
      }
      else
      {
        parentNode->rightChild = targetChild;
        free(target);
      }
    }
    else
    { // target has 2 child nodes
      int m = max(target->leftChild);
      delete (root, m);
      target->key = m;
    }
  }
}

void inorder(nodePointer root)
{
  if (root)
  {
    if (root->leftChild)
      inorder(root->leftChild);
    if (root->key)
      printf("%d ", root->key);
    if (root->rightChild)
      inorder(root->rightChild);
  }
}

int main(void)
{
  nodePointer root = new ();
  int arr[10] = {15, 10, 2, 20, 17, 26, 16, 24, 28, 25};
  for (int i = 0; i < 10; i++)
  {
    insert(&root, arr[i]);
  }
  delete (root, 20);
  inorder(root);
  return 0;
}

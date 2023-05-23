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
  return (nodePointer)malloc(sizeof(node));
}

nodePointer modifiedSearch(nodePointer root, int key)
{
  if (root->key == key || !root)
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
  if (temp)
  {
    nodePointer newNode = new ();
    newNode->key = key;
    if (temp->key > key)
      temp->leftChild = newNode;
    else
      temp->rightChild = newNode;
  }
}

nodePointer search(nodePointer root, int key)
{
  if (!root)
    return NULL;
  if (root->key == key)
    return root;
  if (root->key > key)
    return search(root->leftChild, key);
  else
    return search(root->rightChild, key);
}

void print(nodePointer root)
{
  if (root)
  {
    print(root->leftChild);
    printf("%d ", root->key);
    print(root->rightChild);
  }
}

int main(void)
{
  nodePointer root = new ();
  root->key = 15;
  insert(&root, 10);
  insert(&root, 18);
  insert(&root, 2);
  print(root);
  printf("%d", search(root, 3));
  return 0;
}

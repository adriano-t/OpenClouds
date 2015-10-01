#include "includes.h"
/*
ffeq, TreeNode, leaves, GetFDiffRec are private and only used within this file

*/
inline bool ffeq(FileReader& fr, int pos, FileReader& fr2, int pos2, int num)
{
	for (int i = 0; i < num; i++)
	if (fr[pos + i] != fr2[pos2 + i])
		return(false);
	return(true);
}

static std::list<void*> leaves;
struct TreeNode
{
	int weight; // weight as number of information required for storage of diffs
	int realWeight;
	enum TreeNodeType { Root, Insertion, Deletion, Replacement } type;
	uint64_t where, howMuch;
	uint64_t oldIndex, oldLength;
	uint8_t* data;
	/*
	Insertion:
		Where is the position in B of the first byte inserted
		howMuch is the number of bytes inserted
		data contains the bytes inserted
	Deletion:
		Where is the position in B of the first byte deleted.
		howMuch is the number of bytes deleted
	*/
	
	int leaveCount = 0;
	const int leaveCountMax = 10;
	TreeNode** children;
	TreeNode* parent; // Automatically set by addChild

	TreeNode()
	{
		// preload 10 leaves
		children = new TreeNode*[leaveCountMax];
		for (int i = 0; i < leaveCountMax; i++)
			children[i] = nullptr;
		parent = nullptr;
		// Apon creation, a node is also a leave inside the whole Tree
		::leaves.push_back(this);
		realWeight = 0;
		weight = 0;
	}

	TreeNode* addChild(TreeNode* tn)
	{
		if (leaveCount == 10)
			return nullptr;
		if (leaveCount == 0)
			// First time addLeave is called
			::leaves.remove(this);
			// If a node gets a child, it is no longer a leave
		assert(tn->weight); // weight of child must be set before adding it
		tn->parent = this;
		tn->realWeight = weight + tn->weight;
		children[leaveCount++] = tn;
		return tn;
	}
};


void GetFDiffRec(FileReader* newFile, FileReader* oldFile, int64_t p1, int64_t p2, TreeNode& root);
void GetFDiff(FileReader* newFile, FileReader* oldFile)
{
	TreeNode root;
	root.type = TreeNode::TreeNodeType::Root;

	GetFDiffRec(newFile, oldFile, 0, 0, root);

	int a = 3;
	// Traverse the structure and list the leaves

}
void GetFDiffRec(FileReader* _newFile, FileReader* _oldFile, int64_t p1, int64_t p2, TreeNode& root)
{
	FileReader& newFile = *_newFile;
	FileReader& oldFile = *_oldFile;
	int64_t newPtr = p1;
	int64_t oldPtr = p2;
	int64_t newLength = newFile.length();
	int64_t oldLength = oldFile.length();
	while (newFile[newPtr] == oldFile[oldPtr])
	{
		newPtr++;
		oldPtr++;

		if (newPtr >= newLength - 1 || oldPtr >= oldLength - 1)
			// Either new or old file was completely read
			// todo: if one file reached eof and the other did not
			// commit change as last node.
			return;
	}

	// ******************************************************************************
	// ****************** INSERTION *************************************************
	// ******************************************************************************
	// New = Old + inserted data
	int numBytes = 5;
	int newIndex = newPtr + 1;

	if (newIndex + numBytes - 1 < newLength)
	while (!ffeq(newFile, newIndex, oldFile, oldPtr, numBytes))
	{
		newIndex++;
		if (newIndex + numBytes - 1 >= newLength)
		{
			// Reached eof without finding insertion end.
			// => deletion of oldFile data from oldPtr to end
			// => insertion of newFile data from newPtr to end
			TreeNode* tn = new TreeNode;
			tn->oldIndex = oldPtr;
			tn->oldLength = oldLength - oldPtr;
			tn->type = TreeNode::TreeNodeType::Deletion;
			tn->weight = 3; // type, oldIndex, oldLength, parent
			root.addChild(tn); // manages leaves and real weights
			
			TreeNode* tn2 = new TreeNode;
			tn2->type = TreeNode::TreeNodeType::Insertion;
			tn2->where = newPtr;
			tn2->howMuch = newLength - newPtr;
			tn2->weight = 3;
			//todo: setup data
			tn->addChild(tn2);


			// The file ended! no more recursion needed
			return;
		}
	}
	else
		newIndex = 0;

	if (newIndex != 0)
	{
		TreeNode* tn = new TreeNode;
		tn->where = newPtr;
		tn->howMuch = newIndex - newPtr; // todo: check this out
		tn->weight = tn->howMuch + 3;  // where, howMuch, type, data
		tn->type = TreeNode::TreeNodeType::Insertion;
		tn->data = new uint8_t[tn->howMuch]; // todo: setup data
		root.addChild(tn);
		GetFDiffRec(_newFile, _oldFile, newIndex + numBytes, oldPtr + numBytes, *tn);
	}

	// ******************************************************************************
	// ****************** DELETION **************************************************
	// ******************************************************************************
	// Some data of oldFile were deleted and are not present in newFile
	// So the first 5 bytes of newFile should be present somewhere
	// after this point in oldFile
	int oldIndex = oldPtr + 1;
	if (oldIndex + numBytes - 1 < oldLength)
	while (!ffeq(newFile, newPtr, oldFile, oldIndex, numBytes))
	{
		oldIndex++;
		if (oldIndex + numBytes - 1 >= oldLength)
		{
			oldIndex = 0;
			break;
		}
	}
	else
		oldIndex = 0;

	if (oldIndex != 0)
	{
		TreeNode* tn = new TreeNode;
		tn->where = oldPtr;
		tn->howMuch = newIndex - oldPtr; // todo: check this out
		tn->weight = 3; // where, howMuch, type
		tn->type = TreeNode::TreeNodeType::Deletion;
		root.addChild(tn);
		GetFDiffRec(_newFile, _oldFile, newPtr + numBytes, oldIndex + numBytes, *tn);
	}
}

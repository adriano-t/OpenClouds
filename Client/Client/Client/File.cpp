#include "includes.h"
unsigned char FileReader::operator[](uint64_t pos)
{
	static const int32_t buffSize = 1000000;
	static uint8_t  buffer[buffSize]; // 1 MB buffer
	static uint64_t start_pos = 0;
	static uint64_t end_pos = 0;

	if (src == NULL) // Not initialized
		return(0);
	
	// If pos belongs to preloaded data, retrieve it
	if (pos >= start_pos && pos < end_pos)
		return(buffer[pos - start_pos]);

	// otherwise, reload
	fseek(src, pos, SEEK_SET);
	end_pos = (uint64_t)fread(buffer, 1, buffSize, src) + start_pos;
	start_pos = pos;
	return(buffer[0]);
}


FileReader::FileReader(const std::string& fname)
{
	FileReader(fname.c_str());
}
FileReader::FileReader(const char* fname)
{
	fopen_s(&src, fname, "rb");
	if (src == NULL)
		return;
	fseek(src, 0, SEEK_END);
	fpos_t a;
	fgetpos(src, &a);
	len = a;
}

inline bool ffeq(FileReader& fr, int pos, FileReader& fr2, int pos2, int num)
{
	for (int i = 0; i < num; i++)
	if (fr[pos + i] != fr2[pos2 + i])
		return(false);
	return(true);
}
struct TreeNode
{
	int weight; // weight as number of information required for storage of diffs
	enum TreeNodeType { Root, Insertion, Deletion, Appending, Replacement } type;
	uint64_t where, howMuch;
	uint8_t* data;
	/*
	Insertion:
		Where is the position in A of the first byte inserted
		howMuch is the number of bytes inserted
		data contains the bytes inserted
	Deletion:
		Where is the position in B of the first byte deleted.
		howMuch is the number of bytes deleted
	*/

	TreeNode** leaves;

	TreeNode()
	{
		leaves = new TreeNode*[6];
		for (int i = 0; i < 6; i++)
			leaves[i] = nullptr;
	}

};

void GetFDiffRec(FileReader& newFile, FileReader& oldFile, int64_t p1, int64_t p2, TreeNode& root);
void GetFDiff(FileReader& newFile, FileReader& oldFile)
{
	TreeNode root;
	root.type = TreeNode::TreeNodeType::Root;

	GetFDiffRec(newFile, oldFile, 0, 0, root);

	int a = 3;
}

void GetFDiffRec(FileReader& newFile, FileReader& oldFile, int64_t p1, int64_t p2, TreeNode& root)
{
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
	// A contains data inserted
	int numBytes = 5;
	int newIndex = newPtr + 1;

	if (newIndex + numBytes - 1 < newLength)
	while (!ffeq(newFile, newIndex, oldFile, oldPtr, numBytes))
	{
		newIndex++;
		if (newIndex + numBytes - 1 >= newLength)
		{
			// Reached eof without finding insertion end: it was not insertion
			newIndex = 0;
			break;
		}
	}
	else
		newIndex = 0;

	if (newIndex != 0)
	{
		TreeNode* tn = new TreeNode;
		root.leaves[0] = tn;
		tn->where = newPtr;
		tn->howMuch = newIndex - newPtr; // todo: check this out
		tn->weight = tn->howMuch + 3;  // where, howMuch, type, data
		tn->type = TreeNode::TreeNodeType::Insertion;
		GetFDiffRec(newFile, oldFile, newIndex + numBytes, oldPtr + numBytes, *root.leaves[0]);
	}

	// ******************************************************************************
	// ****************** DELETION **************************************************
	// ******************************************************************************
	// Some data of B were deleted and are not present in A
	// So the first 5 bytes of A should be present somewhere
	// after that point in B
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
		root.leaves[1] = tn;
		tn->where = oldPtr;
		tn->howMuch = newIndex - oldPtr; // todo: check this out
		tn->weight = 3; // where, howMuch, type
		tn->type = TreeNode::TreeNodeType::Deletion;
		GetFDiffRec(newFile, oldFile, newPtr + numBytes, oldIndex + numBytes, *root.leaves[1]);
	}
}


const char* getTypeName(TreeNode::TreeNodeType type)
{
	switch (type)
	{
	case(TreeNode::TreeNodeType::Root):
			return("Root");
	case(TreeNode::TreeNodeType::Appending) :
		return("Appending");
	case(TreeNode::TreeNodeType::Deletion) :
		return("Deletion");
	case(TreeNode::TreeNodeType::Insertion) :
		return("Insertion");
	default:
		return("UnknownType");
	}
}
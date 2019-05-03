#pragma once
namespace eleno
{
	template <class T>
	struct LinkNode
	{
		T data;
		LinkNode* next;
	};

	template <class T>
	struct DLinkNode
	{
		T data;
		DLinkNode* prev;
		DLinkNode* next;
	};
}

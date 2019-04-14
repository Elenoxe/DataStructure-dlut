#pragma once
namespace eleno
{
	template <class T>
	struct LinkNode
	{
		T data;
		LinkNode<T>* next;
	};

	template <class T>
	struct DLinkNode
	{
		T data;
		DLinkNode<T>* prev;
		DLinkNode<T>* next;
	};
}

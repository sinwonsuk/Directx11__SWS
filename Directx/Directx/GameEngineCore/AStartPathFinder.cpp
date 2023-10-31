#include "PreCompile.h"
#include "AStartPathFinder.h"

AStartPathFinder::AStartPathFinder() 
{
}

AStartPathFinder::~AStartPathFinder() 
{
}


std::shared_ptr<PathFindNode> AStartPathFinder::CreateNode(PathFindNode* _Parent, PathPoint _Start, PathPoint _End)
{
	if (true == OpenIndex.contains(_Start.Key))
	{
		return nullptr;
	}

	std::shared_ptr<PathFindNode> NewNode = std::make_shared<PathFindNode>();

	// �������������� �Ÿ� ���
	NewNode->H = _Start.Distance(_End);
	NewNode->G = 0.0f;

	if (nullptr != _Parent)
	{
		NewNode->G = NewNode->Index.Distance(_Parent->Index);
		NewNode->Parent = _Parent;
	}

	NewNode->CalF();
	NewNode->Index = _Start;
	OpenIndex.insert(NewNode->Index.Key);

	OpenList.insert(std::make_pair(NewNode->F,NewNode));
	return NewNode;
}

std::vector<PathPoint> AStartPathFinder::PathFind(PathPoint _Start, PathPoint _End)
{
	return std::vector<PathPoint>();
	// ���� ����Ʈ�� ä������.
	CreateNode(nullptr, _Start, _End);

	// ã�� Ƚ���� �����Ұų�.
	int Count = 0;

	PathPoint ArrDir[8] = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0},
		{-1, 1},
		{1, -1},
		{1, 1},
		{-1, -1},
	};

	while (OpenList.size())
	{
		std::multimap<float, std::shared_ptr<PathFindNode>>::iterator FindNodeIter;
		FindNodeIter = OpenList.begin();
		std::shared_ptr<PathFindNode> FindNode = FindNodeIter->second;
		OpenList.erase(FindNodeIter);
		OpenIndex.erase(FindNode->Index.Key);
		CloseList.push_back(FindNode);
		CloseIndex.insert(FindNode->Index.Key);

		for (size_t i = 0; i < 8; i++)
		{
			PathPoint FindIndex = FindNode->Index + ArrDir[i];

			if (nullptr == IsBlockCallBack)
			{
				MsgBoxAssert("��ã�� �Ǵܿ� �ݹ��� �־����� �ʾҽ��ϴ�");
			}

			if (true == IsBlockCallBack(FindIndex))
			{
				continue;
			}

			if (true == CloseIndex.contains(FindIndex.Key) || true == OpenList.contains(FindIndex.Key))
			{
				continue;
			}

			std::shared_ptr<PathFindNode> Node = CreateNode(FindNode.get(), FindIndex, _End);

			if (FindIndex.Key == _End.Key)
			{
				break;
			}
		}
	}


	return std::vector<PathPoint>();
}
#include "PathSearch.h"

namespace fullsail_ai {
	namespace algorithms {

		PathSearch::PathSearch()
		{

		}

		PathSearch::~PathSearch()
		{
		}

		void PathSearch::initialize(TileMap* _tileMap)
		{
			tileMap = _tileMap;

			int row = tileMap->getRowCount();
			int column = tileMap->getColumnCount();

			for (int x = 0; x < row; x++)
			{
				for (int y = 0; y < column; y++)
				{
					SearchNode* node = new SearchNode();
					Tile* temp = tileMap->getTile(x, y);
					node->tile = temp;
					if (temp->getWeight() != 0)
					{
						nodes[temp] = node;
					}
				}
			}

			for (auto& node : nodes)
			{
				int row = node.second->tile->getRow();
				int column = node.second->tile->getColumn();
				Tile* temp;

				if (row % 2 == 0)
				{
					temp = tileMap->getTile(row - 1, column - 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row - 1, column);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row, column - 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row, column + 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row + 1, column - 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row + 1, column);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}
				}
				else
				{

					temp = tileMap->getTile(row - 1, column);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row - 1, column + 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row, column - 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row, column + 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row + 1, column);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}

					temp = tileMap->getTile(row + 1, column + 1);

					if (temp && temp->getWeight() != 0)
					{
						node.second->neighbors.push_back(nodes[temp]);
					}
				}

			}
		}

		void PathSearch::enter(int startRow, int startColumn, int goalRow, int goalColumn)
		{
			PlannerNode* start = new PlannerNode();
			start->parent = nullptr;
			start->searchNode = nodes[tileMap->getTile(startRow, startColumn)];
			visited[start->searchNode] = start;
			queue.push(start);
			this->begin = start;


			PlannerNode* end = new PlannerNode();
			end->parent = nullptr;
			end->searchNode = nodes[tileMap->getTile(goalRow, goalColumn)];
			this->goal = end;
		}

		void PathSearch::update(long timeslice)
		{ 
			while (!queue.empty())
			{
				PlannerNode* curr = queue.front();
				queue.pop();

				curr->searchNode->tile->setFill(0xff0000ff);

			/*	if (timeslice == 0)
				{
					for (auto& node : nodes)
					{
						node.second->tile->clearLines();
					}

					PlannerNode* temp = curr;
					PlannerNode* par = temp->parent;

					while (par != nullptr && temp->searchNode != nullptr)
					{
						temp->searchNode->tile->addLineTo(temp->parent->searchNode->tile, 0xffff0000);


						temp = par;
						par = par->parent;
					}
				}*/

				if (curr->searchNode == goal->searchNode)
				{
					queue.clear();
					delete goal;
					goal = curr;
					break;
				}

				for (int i = 0; i < curr->searchNode->neighbors.size(); i++)
				{
					SearchNode* succ = curr->searchNode->neighbors[i];

					float distance = sqrt(
						pow(succ->tile->getXCoordinate() - curr->searchNode->tile->getXCoordinate(), 2) +
						pow(succ->tile->getYCoordinate() - curr->searchNode->tile->getYCoordinate(), 2) * 1.0);

					float tempGivenCost = curr->giveCost + ((distance * succ->tile->getWeight()));

					if (visited[succ] != NULL)
					{
						if (tempGivenCost < visited[succ]->giveCost)
						{
							PlannerNode* succNode = visited[succ];
							queue.remove(succNode);
							
							succNode->giveCost = tempGivenCost;
							succNode->finalCost = succNode->giveCost + succNode->heuristicCost * 1.2f;
							succNode->parent = curr;

							queue.push(succNode);
						}
					}
					else
					{
						PlannerNode* succNode = new PlannerNode({ succ });

						succNode->heuristicCost = sqrt(
							pow(goal->searchNode->tile->getXCoordinate() - succ->tile->getXCoordinate(), 2) +
							pow(goal->searchNode->tile->getYCoordinate() - succ->tile->getYCoordinate(), 2) * 1.0);
						
						succNode->giveCost = tempGivenCost;
						succNode->finalCost = succNode->giveCost + succNode->heuristicCost * 1.2f;
						succNode->parent = curr;
						visited[succ] = succNode;
						queue.push(succNode);
					}
				}

				if (timeslice == 0)
				{
					break;
				}
			}
		}


		void PathSearch::exit()
		{
			for (auto& visit : visited)
			{
				delete visit.second;
			}
			visited.clear();
			queue.clear();
		}

		void PathSearch::shutdown()
		{
			for (auto& node : nodes)
			{
				delete node.second;
			}
			nodes.clear();
		}

		bool PathSearch::isDone() const
		{
			return queue.empty();
		}

		std::vector<Tile const*> const PathSearch::getSolution() const
		{
			std::vector<Tile const*> temp;

			for (PlannerNode* curr = goal; curr != nullptr; curr = curr->parent)
			{
				temp.push_back(curr->searchNode->tile);
			}

			return temp;
		}
	}
}  // namespace fullsail_ai::algorithms

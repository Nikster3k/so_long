#include "Enemy.h"
#include <algorithm>
#include <unordered_map>
#include <queue>
#include "Utils.h"

void CEnemy::UpdateEnemyPos(CMap& a_map, CPlayer& a_player)
{
	std::vector<Vector2> path = AStar(m_pos, a_player.m_pos, a_map);
	if (path.size() > 0)
		path.erase(path.begin());
	auto nextStep = Vector2::Zero();
	if (path.size() > 0)
		nextStep = path.front();
	m_moveDir = nextStep - m_pos;
}

bool CEnemy::IsOnMap(Vector2 a_pos)
{
	return (a_pos.x >= 0) && (a_pos.x < CMap::s_mapWidth) && (a_pos.y >= 0) && (a_pos.y <= CMap::s_mapHeight);
}

bool CEnemy::IsWall(Vector2 a_pos, CMap& a_map)
{
	if (a_map.GetMapTileAt(a_pos).m_tileType == CTile::TileType::WALL)
		return true;
	else
		return false;
}

//erstellt hash für vector2 um vector2 als key in der map(dictionary) zu verwenden.
template <>
struct std::hash<Vector2>
{
	size_t operator()(const Vector2& p) const
	{
		return hash<int>()(p.x) ^ hash<int>()(p.y);
	}
};

//habe diese operator überladung HIER gebraucht sonst gab es error
bool operator==(const Vector2& lhs, const Vector2& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

//A* nicht von mir ausgedacht zusammen gewürfelt aus einigen internet resourcen
std::vector<Vector2> CEnemy::AStar(Vector2 a_start, Vector2 a_goal, CMap& a_map)
{
	std::unordered_map<Vector2, Vector2> cameFrom;
	std::unordered_map<Vector2, int> gScore;
	std::unordered_map<Vector2, int> fScore;

	auto compare = [&fScore](const Vector2& a, const Vector2& b)
	{
		return fScore[a] > fScore[b];
	};

	std::priority_queue<Vector2, std::vector<Vector2>, decltype(compare)> openSet(compare);

	openSet.push(a_start);
	gScore[a_start] = 0;
	fScore[a_start] = ManhattanDistance(a_start, a_goal);

	std::vector<Vector2> directions = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}  // Possible moves: right, left, down, up
	};

	while (!openSet.empty())
	{
		Vector2 current = openSet.top();
		openSet.pop();

		if (current.IsEqualInt(a_goal))
		{
			std::vector<Vector2> path;
			while (!current.IsEqualInt(a_start))
			{
				path.push_back(current);
				current = cameFrom[current];
			}
			path.push_back(a_start);
			std::reverse(path.begin(), path.end());
			return path;
		}

		for (const Vector2& dir : directions)
		{
			Vector2 neighbor = { current + dir };
			if (!IsOnMap(neighbor) || IsWall(neighbor, a_map))
				continue;
			int tentative_gScore = gScore[current] + 1;
			if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor])
			{
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentative_gScore;
				fScore[neighbor] = tentative_gScore + ManhattanDistance(neighbor, a_goal);
				openSet.push(neighbor);
			}
		}
	}

	return {};
}


int CEnemy::ManhattanDistance(Vector2& a_lhs, Vector2& a_rhs)
{
	return abs(a_lhs.x - a_rhs.x) + abs(a_lhs.y - a_rhs.y);
}

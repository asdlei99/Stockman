#include <AI\Behavior\NavigationMesh.h>
#include <Misc\FileLoader.h>
using namespace Logic;

NavigationMesh::NavigationMesh()
{
}

NavigationMesh::~NavigationMesh()
{
}

void NavigationMesh::createTestMesh()
{
	Triangle one = { 0 };
	one.vertices[0] = DirectX::SimpleMath::Vector3({ 5.f, 5.f, 5.f });
	one.vertices[1] = DirectX::SimpleMath::Vector3({ 10.f, 5.f, 5.f });
	one.vertices[2] = DirectX::SimpleMath::Vector3({ 10.f, 5.f, 10.f });

	Triangle two = { 1 };
	one.vertices[0] = DirectX::SimpleMath::Vector3({ 5.f, 5.f, 5.f });
	one.vertices[1] = DirectX::SimpleMath::Vector3({ 5.f, 5.f, 10.f });
	one.vertices[2] = DirectX::SimpleMath::Vector3({ 10.f, 5.f, 10.f });

	triangleList.push_back(one);
	triangleList.push_back(two);
}

void NavigationMesh::addTriangle(Triangle const & triangle)
{
	triangleList.push_back(triangle);
}

const std::vector<NavigationMesh::Triangle>& NavigationMesh::getList() const
{
	return triangleList;
}
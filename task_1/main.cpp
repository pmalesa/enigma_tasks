#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::string;

class Tree
{
private:
	class Trunk
	{
	public:
		Trunk() : _thickness(0.1), _height(1.0) {}
		~Trunk() = default;
		float get_thickness() const { return _thickness; }
		float get_height() const { return _height; }
		void grow()
		{
			_thickness += 0.1;
			_height += 0.5;
			if (_thickness > MAX_THICKNESS)
				_thickness = MAX_THICKNESS;
			if (_height > MAX_HEIGHT)
				_height = MAX_HEIGHT;
		}

	private:
		float _thickness;
		float _height;
		
		static constexpr float MAX_THICKNESS = 1.0;
		static constexpr float MAX_HEIGHT = 10.0;
	};

	class Branch
	{
	public:
		Branch() = default;
		~Branch() = default;
		float get_thickness() const { return _thickness; }
		float get_length() const { return _length; }
		void grow()
		{
			_thickness += 0.02;
			_length += 0.5;
			if (_thickness > MAX_THICKNESS)
				_thickness = MAX_THICKNESS;
			if (_length > MAX_LENGTH)
				_length = MAX_LENGTH;
		}

	private:
		float _thickness;
		float _length;

		static constexpr float MAX_THICKNESS = 0.2;
		static constexpr float MAX_LENGTH = 4.0;
	};

/* ----------------------------------------------------------------- */
public:
	Tree() 
	{
		_trunk = make_unique<Trunk>();
	}
	virtual ~Tree() {};
	virtual void grow()
	{
		std::cout << "The tree is growing...\n";
		_trunk->grow();
		if (_branches.size() < MAX_BRANCHES)
		{
			_branches.push_back(make_unique<Branch>());
			for (auto& branch : _branches)
				branch->grow();
		} 
	}

	virtual void print_parameters() const = 0;
	
	const unique_ptr<Trunk>& get_trunk() const { return _trunk; }
	const vector<unique_ptr<Branch>>& get_branches() const { return _branches; }

	static constexpr int MAX_BRANCHES = 10;

private:
	unique_ptr<Trunk> _trunk;
	vector<unique_ptr<Branch>> _branches = {};

};

class LeafyTree : public Tree
{
public:
	LeafyTree() = default;

	void grow() override
	{
		Tree::grow();
		for (size_t i = 0; i < 5; ++i)
		{
			if (_leaves.size() >= MAX_LEAVES)
				break;
			_leaves.push_back(make_unique<string>("LEAF_" + std::to_string(_leaves.size() + 1)));
		}
		std::cout << "The leafy tree has grown!\n";
	}

	void print_parameters() const override
	{
		std::cout <<
			"Leafy tree's parameters:\n" <<
			"	- trunk height: " + std::to_string(get_trunk()->get_height()) << "\n" <<
			"	- trunk thickness: " + std::to_string(get_trunk()->get_thickness()) << "\n" <<
			"	- branches: " + std::to_string(get_branches().size()) << "\n" <<
			"	- leaves: " + std::to_string(_leaves.size()) << "\n";
	}
	
private:
	vector<unique_ptr<string>> _leaves;
	static constexpr int MAX_LEAVES = 100;
	
};

class ConiferTree : public Tree
{
public:
	ConiferTree() = default;

	void grow() override
	{
		Tree::grow();
		for (size_t i = 0; i < 10; ++i)
		{
			if (_needles.size() >= MAX_NEEDLES)
				break;
			_needles.push_back(make_unique<string>("NEEDLE_" + std::to_string(_needles.size() + 1)));
		}
		std::cout << "The conifer tree has grown!\n";
	}

	void print_parameters() const override
	{
		std::cout <<
			"Conifer tree's parameters:\n" <<
			"	- trunk height: " + std::to_string(get_trunk()->get_height()) << "\n" <<
			"	- trunk thickness: " + std::to_string(get_trunk()->get_thickness()) << "\n" <<
			"	- branches: " + std::to_string(get_branches().size()) << "\n" <<
			"	- needles: " + std::to_string(_needles.size()) << "\n";
	}

private:
	vector<unique_ptr<string>> _needles;
	static constexpr int MAX_NEEDLES = 200;

};

int main()
{
	vector<unique_ptr<Tree>> trees = {};
	for (size_t i = 0; i < 5; ++i)
		trees.push_back(make_unique<LeafyTree>());
	for (size_t i = 0; i < 5; ++i)
		trees.push_back(make_unique<ConiferTree>());
	
	for (auto& tree : trees)
		tree->grow();

	trees[5]->print_parameters();
	trees[5]->grow();
	trees[5]->grow();
	trees[5]->print_parameters();

	return 0;
}

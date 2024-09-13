#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Structure to represent a location or node
struct Node
{
    string name;
    Node(string n) : name(n) {}
};

// Structure to represent an edge or path between nodes
struct Edge
{
    string from;
    string to;
    int distance;
    int time;
    Edge(string f, string t, int d, int ti) : from(f), to(t), distance(d), time(ti) {}
};

// Function to check if a node exists in the list of nodes
bool nodeExists(const vector<Node> &nodes, const string &name)
{
    return find_if(nodes.begin(), nodes.end(), [&](const Node &node)
                   { return node.name == name; }) != nodes.end();
}

// Function to check if an edge exists between two nodes
bool edgeExists(const vector<Edge> &edges, const string &from, const string &to)
{
    return find_if(edges.begin(), edges.end(), [&](const Edge &edge)
                   { return edge.from == from && edge.to == to; }) != edges.end();
}

// Function to add a new node to the list of nodes
void addNode(vector<Node> &nodes, const string &name)
{
    if (!nodeExists(nodes, name))
    {
        nodes.push_back(Node(name));
        cout << "Node '" << name << "' added successfully." << endl;
    }
    else
    {
        cout << "Node '" << name << "' already exists." << endl;
    }
}

// Function to add a new edge between two nodes
void addEdge(vector<Edge> &edges, const vector<Node> &nodes, const string &from, const string &to, int distance, int time)
{
    if (!edgeExists(edges, from, to) && nodeExists(nodes, from) && nodeExists(nodes, to))
    {
        edges.push_back(Edge(from, to, distance, time));
        cout << "Edge from '" << from << "' to '" << to << "' added successfully." << endl;
    }
    else
    {
        cout << "Edge already exists or invalid nodes specified." << endl;
    }
}

// Function to find the shortest distance between two nodes using Dijkstra's algorithm
void findShortestDistance(const vector<Node> &nodes, const vector<Edge> &edges, const string &from, const string &to)
{
    // Implementation of Dijkstra's algorithm for distance calculation
    vector<int> distance(nodes.size(), numeric_limits<int>::max());
    vector<int> previous(nodes.size(), -1);
    int fromIndex = -1;
    int toIndex = -1;

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].name == from)
        {
            fromIndex = i;
        }
        else if (nodes[i].name == to)
        {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1)
    {
        cout << "Invalid nodes specified." << endl;
        return;
    }

    distance[fromIndex] = 0;

    for (int i = 0; i < nodes.size() - 1; i++)
    {
        for (const Edge &edge : edges)
        {
            int u = distance[fromIndex] + edge.distance;
            if (u < distance[toIndex] && edge.from == nodes[fromIndex].name)
            {
                distance[toIndex] = u;
                previous[toIndex] = fromIndex;
            }
        }
    }

    // Reconstruct the path
    string shortestPath = nodes[toIndex].name;
    int currentIndex = toIndex;
    while (currentIndex != fromIndex)
    {
        currentIndex = previous[currentIndex];
        shortestPath = nodes[currentIndex].name + " -> " + shortestPath;
    }

    cout << "Shortest path from " << from << " to " << to << ": " << shortestPath << endl;
    cout << "Total distance: " << distance[toIndex] << " km" << endl;
}

// Function to find the shortest time between two nodes using Dijkstra's algorithm
void findShortestTime(const vector<Node> &nodes, const vector<Edge> &edges, const string &from, const string &to)
{
    vector<int> time(nodes.size(), numeric_limits<int>::max());
    vector<int> previous(nodes.size(), -1);
    int fromIndex = -1;
    int toIndex = -1;

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].name == from)
        {
            fromIndex = i;
        }
        else if (nodes[i].name == to)
        {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1)
    {
        cout << "Invalid nodes specified." << endl;
        return;
    }

    time[fromIndex] = 0;

    for (int i = 0; i < nodes.size() - 1; i++)
    {
        for (const Edge &edge : edges)
        {
            int u = time[fromIndex] + edge.time;
            if (u < time[toIndex] && edge.from == nodes[fromIndex].name)
            {
                time[toIndex] = u;
                previous[toIndex] = fromIndex;
            }
        }
    }

    // Reconstruct the path
    string shortestPath = nodes[toIndex].name;
    int currentIndex = toIndex;
    while (currentIndex != fromIndex)
    {
        currentIndex = previous[currentIndex];
        shortestPath = nodes[currentIndex].name + " -> " + shortestPath;
    }

    cout << "Shortest time path from " << from << " to " << to << ": " << shortestPath << endl;
    cout << "Total time: " << time[toIndex] << " minutes" << endl;
}

// Function to display the map (nodes and edges)
void displayMap(const vector<Node> &nodes, const vector<Edge> &edges)
{
    vector<Node> sortedNodes = nodes; // Create a copy of nodes to sort
    sort(sortedNodes.begin(), sortedNodes.end(), [](const Node &a, const Node &b)
         { return a.name < b.name; });

    cout << "Nodes and their edges :" << endl;
    for (const Node &node : sortedNodes)
    {
        cout << "Node: " << node.name << endl;
        cout << "Edges:" << endl;
        for (const Edge &edge : edges)
        {
            if (edge.from == node.name)
            {
                cout << "  To: " << edge.to << ", Distance: " << edge.distance << ", Time: " << edge.time << endl;
            }
        }
        cout << endl;
    }
}

int main()
{
    vector<Node> nodes;
    vector<Edge> edges;

    nodes.push_back(Node("Baner"));
    nodes.push_back(Node("Kothrud"));
    nodes.push_back(Node("Warje"));
    nodes.push_back(Node("Katraj"));
    nodes.push_back(Node("Bibewadi"));
    nodes.push_back(Node("Swargate"));
    nodes.push_back(Node("Shivajinagar"));
    nodes.push_back(Node("Aundh"));
    nodes.push_back(Node("Pashan"));
    nodes.push_back(Node("Khadki"));

    edges.push_back(Edge("Kothrud", "Warje", 5, 25));
    edges.push_back(Edge("Warje", "Katraj", 10, 30));
    edges.push_back(Edge("Katraj", "Bibewadi", 15, 35));
    edges.push_back(Edge("Bibewadi", "Swargate", 5, 20));
    edges.push_back(Edge("Swargate", "Shivajinagar", 10, 25));
    edges.push_back(Edge("Shivajinagar", "Aundh", 15, 30));
    edges.push_back(Edge("Aundh", "Pashan", 5, 20));
    edges.push_back(Edge("Pashan", "Khadki", 10, 25));
    edges.push_back(Edge("Khadki", "Baner", 15, 30));
    edges.push_back(Edge("Baner", "Kothrud", 5, 20));
    edges.push_back(Edge("Kothrud", "Bibewadi", 10, 25));
    edges.push_back(Edge("Bibewadi", "Swargate", 15, 30));
    edges.push_back(Edge("Swargate", "Aundh", 5, 20));
    edges.push_back(Edge("Aundh", "Khadki", 10, 25));
    edges.push_back(Edge("Khadki", "Baner", 15, 30));
    edges.push_back(Edge("Baner", "Warje", 5, 20));

    int choice;
    while (true)
    {
        cout << "Main Menu:" << endl;
        cout << "1. Add a node" << endl;
        cout << "2. Add an edge" << endl;
        cout << "3. Find Shortest Distance" << endl;
        cout << "4. Find Shortest Time" << endl;
        cout << "5. Display Map" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string nodeName;
            cout << "Enter node name: ";
            cin >> nodeName;
            addNode(nodes, nodeName);
            break;
        }
        case 2:
        {
            string from, to;
            int distance, time;
            cout << "Enter source node: ";
            cin >> from;
            cout << "Enter destination node: ";
            cin >> to;
            cout << "Enter distance in km: ";
            cin >> distance;
            cout << "Enter time in minutes: ";
            cin >> time;
            addEdge(edges, nodes, from, to, distance, time);
            break;
        }
        case 3:
        {
            string from, to;
            cout << "Enter source node: ";
            cin >> from;
            cout << "Enter destination node: ";
            cin >> to;
            findShortestDistance(nodes, edges, from, to);
            break;
        }
        case 4:
        {
            string from, to;
            cout << "Enter source node: ";
            cin >> from;
            cout << "Enter destination node: ";
            cin >> to;
            findShortestTime(nodes, edges, from, to);
            break;
        }
        case 5:
        {
            displayMap(nodes, edges);
            break;
        }
        case 6:
        {
            cout << "Exiting the program." << endl;
            return 0;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    }

    return 0;
}

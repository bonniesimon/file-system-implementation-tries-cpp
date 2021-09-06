#include <bits/stdc++.h>
using namespace std;

class FileSystem{
public:
	FileSystem(){
		root = new TrieNode();
	}

	void mkdir(string path){
		auto curr = putNode(path);
		curr->isFile = false;
	}

	void ls(string path){
		auto curr = getNode(path);

		for(auto child : curr->children){
			cout << child.first << endl;
		}
	}
	void rmdir(string path){
		auto prev_folder = getPrevNode(path);
		string folder_name = split(path, '/').back();

		prev_folder->children.erase(folder_name);
	}
	void move(string sourcePath, string destPath){
		auto sourceNode = getNode(sourcePath);
		string sourceNodeName = split(sourcePath, '/').back();
		auto destNode = getNode(destPath);

		destNode->children[sourceNodeName] = destNode;
		
		rmdir(sourcePath);
	}

	void symlink(string sourcePath, string destPath){
		auto sourcePrevNode = getPrevNode(sourcePath);
		string sourceNodeName = split(sourcePath, '/').back();
		auto destPrevNode = getPrevNode(destPath);
		string destNodeName = split(destPath, '/').back();

		sourcePrevNode->children[sourceNodeName] = destPrevNode->children[destNodeName];
	}
private:
	struct TrieNode{
		unordered_map<string, TrieNode*> children;
		bool isFile;
		string content;
	};

	TrieNode* root;

	TrieNode* getPrevNode(string path){
		vector<string> folders_in_path = split(path, '/');
		auto curr = root;
		auto prev = curr;
		for(string folder : folders_in_path){
			prev = curr;
			curr = curr->children[folder];
		}

		return prev;
	}

	TrieNode* getNode(string path){
		auto curr = root;
		vector<string> folders_in_path = split(path, '/');

		for(string folder : folders_in_path){
			curr = curr->children[folder];
		}
		
		return curr;
	}

	TrieNode* putNode(string path){
		auto curr = root;
		vector<string> folders_in_path = split(path, '/');

		for(string folder : folders_in_path){
			if(!curr->children.count(folder)){
				curr->children[folder] = new TrieNode();
			}
			curr = curr->children[folder];
		}

		return curr;
	}

	vector<string> split(string str, char delim){
		vector<string> tokens;

		stringstream ss(str);
		string token;

		while(getline(ss, token, delim)){
			if(!token.empty()){
				tokens.emplace_back(token);
			}
		}

		return tokens;
	}
};

int main(){
	FileSystem fs;
	fs.mkdir("/bonnie");
	fs.mkdir("/bonnie/new/cake");
	fs.mkdir("/bonnie/newest");
	fs.mkdir("/bonnie/newest/cake1/sheesh");
	fs.symlink("/bonnie/new/cake", "/bonnie/newest/cake1");
	fs.ls("/bonnie/new/cake");
	// cout << "Before moving : \n";
	// fs.ls("/bonnie/new");
	// fs.move("/bonnie/new/cake", "/bonnie/newest");
	// cout << "After moving : \n";
	// fs.ls("/bonnie/new");
	// fs.ls("/bonnie/newest");
	// fs.ls("/bonnie");
	// fs.rmdir("/bonnie/new");
	// fs.ls("/bonnie");
	return 0;
}
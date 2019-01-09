#include <bits/stdc++.h> 
#define MAX_TREE_HT 256 
using namespace std;

map<char, string> codes;


map<char, int> freq;

struct MinHeapNode 
{ 
    char data;             
    int freq;            
    MinHeapNode *left, *right; 
  
    MinHeapNode(char data, int freq) 
    { 
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 
  

struct compare 
{ 
    bool operator()(MinHeapNode* l, MinHeapNode* r) 
    { 
        return (l->freq > r->freq); 
    } 
}; 
  

void printCodes(struct MinHeapNode* root, string str) 
{ 
    if (!root) 
        return; 
    if (root->data != '$') 
        cout << root->data << ": " << str << "\n"; 
    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
} 
  

void storeCodes(struct MinHeapNode* root, string str) 
{ 
    if (root==NULL) 
        return; 
    if (root->data != '$') 
        codes[root->data]=str; 
    storeCodes(root->left, str + "0"); 
    storeCodes(root->right, str + "1"); 
} 

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 
  

void HuffmanCodes(int size) 
{ 
    struct MinHeapNode *left, *right, *top; 
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++) 
        minHeap.push(new MinHeapNode(v->first, v->second)); 
    while (minHeap.size() != 1) 
    { 
        left = minHeap.top(); 
        minHeap.pop(); 
        right = minHeap.top(); 
        minHeap.pop(); 
        top = new MinHeapNode('$', left->freq + right->freq); 
        top->left = left; 
        top->right = right; 
        minHeap.push(top); 
    } 
    storeCodes(minHeap.top(), ""); 
} 
  

void calcFreq(string str, int n) 
{ 
    for (int i=0; i<str.size(); i++) 
        freq[str[i]]++; 
} 




string decode_file(struct MinHeapNode* root, string s) 
{ 
    string ans = ""; 
    struct MinHeapNode* curr = root; 
    for (int i=0;i<s.size();i++) 
    { 
        if (s[i] == '0') 
           curr = curr->left; 
        else
           curr = curr->right; 
  
        
        if (curr->left==NULL and curr->right==NULL) 
        { 
            ans += curr->data; 
            curr = root; 
        } 
    } 

    return ans+'\0'; 
} 

int main() 
{ 
    string str;
	std::ofstream out("output.txt");
	std::ifstream t("input.txt");
	std::ifstream dt("decode.txt");
	std::ofstream dout("decoded.txt");
	int operation;
	std::stringstream buffer;
	string encodedString, decodedString;
	cout << "encode(1) or decode(2)?";
	cin >> operation;
	switch(operation){
		case(1):
			
		    
		    buffer << t.rdbuf();
		    str=buffer.str();
		    for ( auto it = str.begin() ; it < str.end(); it++ )
		 		{
    				if(*it==' ') *it='_';
					else if (*it=='\n') *it='#';
				}
		
			calcFreq(str, str.length());
		    HuffmanCodes(str.length());
		    out << "Number of key elements: " << codes.size() << "\n\n";   
			out << "Character With their codes:\n";
		    for (auto v=codes.begin(); v!=codes.end(); v++) {
		        
		  		out << v->first <<' ' << v->second << endl;
		  	}
		    for (auto i: str)
		        encodedString+=codes[i];
			  
			
			out << "\nEncoded Huffman data:\n" << encodedString << endl;   
			    
		    
		    out.close();
			  
			
			cout << "\nData has been encoded in output.txt\n";
			break;
		case(2):
			int keys;
			char key;
			string val;
			string ans="";
			cout << "Enter the number of keys:";
			cin >> keys;
			cout << "Enter the key value pair:";
			
			for(int i=0;i<keys;i++){
				cin >> key;
				cin >> val;
				codes.insert({ key, val });
			}
			buffer << dt.rdbuf();
		    str=buffer.str();
		    int i=0,j=0, length=str.length();
		    while(i+j<=length){
		    	string tmp= str.substr(i,j);
		    	for (auto it=codes.begin();it!=codes.end();it++){
		    		if(tmp==it->second){
		    			ans+=it->first;
		    			i=i+j;
		    			j=0;
					}
				
				}
				j++;
			}
			for ( auto it = ans.begin() ; it < ans.end(); it++ )
		 		{
    				if(*it=='_') *it=' ';
					else if (*it=='#') *it='\n';
				}
			cout << ans;
			dout << ans;
		    
			
			
			
			
	}

    return 0; 
} 

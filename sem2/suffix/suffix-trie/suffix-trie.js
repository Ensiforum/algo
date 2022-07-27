<script>
let MAX_CHAR = 256;

class SuffixTrieNode
{
	
	// Constructor
	constructor()
	{
		this.indexes = [];
		this.children = new Array(MAX_CHAR);

		for(let i = 0; i < MAX_CHAR; i++)
		{
			this.children[i] = 0;
		}
	}
	
// A recursive function to insert a suffix of
// the text in subtree rooted with this node
insertSuffix(s,index)
{
	
	// Store index in linked list
	this.indexes.push(index);

	// If string has more characters
	if (s.length > 0)
	{
		
		// Find the first character
		let cIndex = s[0];

		// If there is no edge for this character,
		// add a new edge
		if (this.children[cIndex] == null)
			this.children[cIndex] = new SuffixTrieNode();

		// Recur for next suffix
		this.children[cIndex].insertSuffix(s.substring(1),
										index + 1);
	}
}

// A function to search a pattern in subtree rooted
// with this node.The function returns pointer to a
// linked list containing all indexes where pattern
// is present. The returned indexes are indexes of
// last characters of matched text.
search(s)
{
	
	// If all characters of pattern have been
	// processed,
	if (s.length == 0)
		return this.indexes;

	// If there is an edge from the current node of
	// suffix tree, follow the edge.
	if (this.children[s[0]] != null)
		return(this.children[s[0]].search(
				s.substring(1)));

	// If there is no edge, pattern doesnt exist in
	// text
	else
		return null;
}
}

let root = new SuffixTrieNode();

// Constructor (Builds a trie of suffixes of the
// given text)
function Suffix_tree(txt)
{
	
	// Consider all suffixes of given string and
	// insert them into the Suffix Trie using
	// recursive function insertSuffix() in
	// SuffixTrieNode class
	for(let i = 0; i < txt.length; i++)
		root.insertSuffix(txt.substring(i), i);
}

/* Prints all occurrences of pat in the Suffix
Trie S (built for text) */
function search_tree(pat)
{
	
	// Let us call recursive search function for
	// root of Trie.
	// We get a list of all indexes (where pat is
	// present in text) in variable 'result'
	let result = root.search(pat);

	// Check if the list of indexes is empty or not
	if (result == null)
		document.write("Pattern not found<br>");
	else
	{
		let patLen = pat.length;

		for(let i of result.values())
			document.write("Pattern found at position " +
						(i - patLen)+"<br>");
	}
}

// Driver code

// Let us build a suffix trie for text
// "geeksforgeeks.org"
let txt = "geeksforgeeks.org";
Suffix_tree(txt);

document.write("Search for 'ee'<br>");
search_tree("ee");

document.write("<br>Search for 'geek'<br>");
search_tree("geek");

document.write("<br>Search for 'quiz'<br>");
search_tree("quiz");

document.write("<br>Search for 'forgeeks'<br>");
search_tree("forgeeks");

// This code is contributed by unknown2108

</script>

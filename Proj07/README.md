# Document Similarity

In this assignment we will do various manipulations of maps, sets and vectors.

## Description

Pattern recognition, related in many ways to machine learning, is of course a big deal these days. We are going to look at a relatively simple and straight forward approach to pattern recognition, document similarity. If I give you two documents, can you tell how “similar” they are to each other.

We will look at two measures: Jaccard Similarity and Cosine Similarity using term frequencies.

# Jaccard Similarity

Jaccard similarity is a measure that uses only the unique words found in the documents. The count of the number of times a word occurs in a document is not used. Based on the unique words found in each of two documents A and B, we measure the Jaccard Similarity as:

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj07/Proj07-1.png)

Where the |A| indicates the count of the number of unique elements in A. This similarity results in a real number between 0 and 1, where 1 indicates the documents are identical and 0 indicates the documents are completely dissimilar. For example given the two short documents.

1. “This is a test.”
2. “This test bothers me. This test bothers you.”

We process the words to remove non alphabetic chars and lowercase everything to create:

|A| == 4 (this, is, a, test)

|B| == 5 (this, test, bothers, me, you)

|A∩B| == 2 (this, test)

2 / (4 + 5 - 2) == 2 / 7

# Cosine Similarity

Cosine similarity depends not only on the words themselves but their frequency as well. The frequencies that are used in the calculation can vary, but a common one is called the normalized term frequency. If we used just straight frequencies, then documents with many repeated words would tend to dominate the process. To counter this we measure the term frequency by normalizing their values. We do so by first calculating the norm factor for the frequencies of each term in the document.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj07/Proj07-2.png)

which is the square root of the frequencies of each word squared. The normalized term frequency is then the term / NF for each term in that document.

Using the same two sentences from above now with frequencies, we calculate the normalized frequency for each term.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj07/Proj07-3.png)

The cosine similarity formula is

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj07/Proj07-4.png)

What’s nice about that is that because the A and B values are normalized, the denominator square roots are both 1, meaning they fall away. What is left is to calculate the product of the normalized value pairs and add them all up. Skipping any term with a 0 (which under multiplication makes it 0) we use the normalized pairs for “this” and “test”

(0.5 * 0.535) + (0.5 * 0.535) = 0.535

a different value then found with Jaccard

# Program Specifications

**`ostream& print_vector (ostream &out, const vector<string> &v);`**

print the contents of the vector `<string>` to the parameter ostream. Return the ostream used.

**`string clean_word (const string&);`**

Take in a string. Create a new string where you remove any non-alphabetic characters and lower case everything. Return that new string.

**`vector<string> split (const string &s, char delim = ' ');`**

Take in the string, return a vector where the string is split by the parameter character **delim**. Note the default is only provided in the header, not the definitions.

**`bool process_words (map_type&, string);`**

Takes in an empty map and a string representing a file name. The function opens the file, reads the file one line at a time, splits the line, cleans each word and then records it in the map where the key of the map is the string and the value of the map is how many times that string occurred.

**Error**: if the file represented by the string cannot be opened, the function returns false and makes no changes to the map. Otherwise the map is updated as indicated and the function returns true.

**`ostream& print_map (ostream& out, const map_type& m);`**

Like print_vector above, print the contents of the map to the parameter ostream. Return the ostream used.

**`double jaccard_similarity (const map_type &m1, const map_type &m2);`**

Takes in two maps (representing the result of **process_words** on two documents). Using **only the keys** it calculates the jaccard similarity as described. Returns the similarity.

**`double calc_norm_factor (const map_type &m1);`**

For a map created by **process_words**, calculate the norm factor of the map / document as shown above (the square root of the frequencies squared). Return the norm factor.

**`double cosine_similarity_tf (const map_type &m1, const map_type &m2);`**

Calculate the term frequency cosine similarity for two maps created by **process_words** as described above. Return the similarity.

# Notes

1. For jaccard, you only need to work with the keys. You can calculate set intersection yourself, but much easier to use the algorithm set_intersection, perhaps on two vectors that have the keys of the two dictionaries. Beware that set_intersection requires sorted elements (if you extract the keys into a vector, would they already be sorted or not?). Furthermore, beware of integer division here. Perhaps `static_cast<double>` is your friend?
2. For cosine, you need to make a new map / vector where the element frequencies are normalized. Then wherever both documents have the same key, you need to multiply the two normalized frequencies and add those products up. Here set_intersection probably does not do what you want.

-----

## Feedback and suggestions

- E-mail：<liutia20@msu.edu>

---------

Thanks for reading this help document

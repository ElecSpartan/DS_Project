# XML Parser and Network Analyzer
This project is for our Data structures and algorithms course. It aims at understanding and parsing XML and JSON files. Then, we get the XML of a users and their posts and followers. We have to analyze this network using graph algorithms and to extract certain metrics. The output has to be shown on a GUI application for better visualization.

This project is divided into 3 parts:
1. XML Parsing.
2. Users network analysis.
3. GUI.

## XML Parsing:
In this part we have certain operations that we want to perform on an XML input file, which are:

|XML Operation| Explanation|
|----|---|
|Verify| To determine whether the file is a valid XML file or not and determine the location of the errors.|
|Correct| To try and solve the problems in the invalid file.|
|Minify| To make the XML file smaller by removing all redundant whitespaces and newlines without altering the data.|
|Prettify or Format| To make the XML file easier to read for the user by managing the indentation and spacing of all elements.|
|Convert to JSON| To convert the XML file to another useful format, which is JSON.|
|Compress| To reduce the file size by using a lossless compression algorithm.|
|Decompress| To restore a compressed file to its original form.|

## Users Network Analysis:
In this part we have a users network in the form of XML input and we want to perform certain operation and extract few metrics from the files, which are:

|Users Network Operation| Explanation|
|----|---|
|Visualize| To take the users XML file and convert it to a connected graphs format in the GUI.|
|Most influencer user| Find the user with the most followers in this network.|
|Most active user| Find the user with the most connections in this network.|
|Mutual followers between 2 users| Finds the mutual followers between any given 2 users in the GUI Input.|
|User suggestions| Suggest a list of users a given user can follow (the followers of his followers).|
|Post search| To search for the user who has posted a post with a body or topic containing the specified input.|

## GUI:
The GUI of our choice was Qt.
It consists of a main screen where the user can input a file from his PC of write it manually, and an output window.

There is are undo and redo buttons to get the last state of the 2 windows, and an option to save the file if the user wants or to swap his old input with the current output.

For every operation in the XML parsing section, there is a button to perform this operation on the given input and to see the output directly.

For the users network analysis part, there is a button that opens a window dedicated for it. and for every operation in this section there is a button to perform it, just like the XML parsing part.

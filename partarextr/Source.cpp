#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;


struct tarhdr {
	char filename[100];
	char filemode[8];
	char ownersID[8];
	char groupID[8];
	char filesize[12];
	char modifyTime[12];
	char checksum[8];
	char linkIndicator;
	char linkedFileName[100];
	char unused[255];
};

int main() {
	/*
	* declare necessary variables.
	*  infile -- the input file stream associated with the tar file.
	*  myhdr  -- the header from the tar file as a tarhdr structure.
	*  block  -- a pointer to characters -- will be used to step through
	*            tarhdr structure one character at a time.
	*  filename -- the name of the file from the tar header
	*  ownersID -- the owners ID as an integer
	*  groupID  -- the group ID as an integer
	*  filesize -- the size of the file in bytes.
	*  modifyTime -- the modification time of the file as an integer
	*  checksum -- the checksum that was read from the header
	*  i        -- an index for arrays/loops
	*  computedChecksum -- the checksum computed by this program to compare
	*                      with the one in the tar header.
	*/
	ifstream infile;
	struct tarhdr myhdr;
	string filename;
	int ownersID, groupID, filesize, modifyTime, checksum;
	int i;
	unsigned int computedChecksum;
	char * block;
	/*
	* open the tar file and read in the header.
	*/
	infile.open("open");
	if (infile.fail()) {
		cerr << "Couldn't open input file -- exitting" << endl;
		return EXIT_FAILURE;
	}
	infile.read((char *)&myhdr, sizeof(myhdr));

	/*
	* all items are stored as c strings and can be converted
	* to C++ strings through assignment.
	*/
	filename = myhdr.filename;
	cout << "Filename = " << filename << endl;
	/*
	* strtol will parse a string and convert the value to an integer.
	* the 8 in the last argument says to assume it is an octal value
	* stored in the string.
	*/
	ownersID = strtol(myhdr.ownersID, NULL, 8);
	groupID = strtol(myhdr.groupID, NULL, 8);
	cout << "Owner ID = " << ownersID
		<< "Group ID = " << groupID << endl;
	filesize = strtol(myhdr.filesize, NULL, 8);
	cout << "Filesize = " << filesize << endl;
	checksum = strtol(myhdr.checksum, NULL, 8);
	cout << "Checksum = " << checksum << endl;

	// Put spaces in the checksum area before we compute it.
	for (i = 0; i < 8; i++) {
		myhdr.checksum[i] = ' ';
	}
	computedChecksum = 0;   // initially zero
							/*
							* get each character in the header block and sum them together.
							*/
	block = (char *)&myhdr;
	for (int i = 0; i < sizeof(myhdr); i++) {
		computedChecksum += block[i];
	}
	cout << "Computed Checksum = " << computedChecksum << endl;
	infile.close();
	return EXIT_SUCCESS;
}

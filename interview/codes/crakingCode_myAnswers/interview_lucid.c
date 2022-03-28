Coding Problem



Given a file and assume that you can only read the file using a given method read4, implement a method read to read n characters. Your method read may be called multiple times.
 
Method read4: 
The API read4 reads 4 consecutive characters from the file, then writes those characters into the buffer array buf.
The return value is the number of actual characters read.
Note that read4() has its own file pointer, much like FILE *fp in C.
Definition of read4:
    Parameter:  char[] buf
    Returns:    int

Note: buf[] is destination not source, the results from read4 will be copied to buf[]

Below is a high level example of how read4 works:
File file("abcdefghijk"); // File is "abcdefghijk", initially file pointer (fp) points to 'a'
char[] buf = new char[4]; // Create buffer with enough space to store characters
read4(buf); // read4 returns 4. Now buf = "abcd", fp points to 'e'
read4(buf); // read4 returns 4. Now buf = "efgh", fp points to 'i'
read4(buf); // read4 returns 3. Now buf = "ijk", fp points to end of file

 
Method read:
By using the read4 method, implement the method read that reads n characters from the file and store it in the buffer array buf. Consider that you cannot manipulate the file directly.
The return value is the number of actual characters read.
Definition of read: 
    Parameters:	char[] buf, int n
    Returns:	int

Note: buf[] is destination not source, you will need to write the results to buf[]

 
Example 1:
File file("abc");
Solution sol;
// Assume buf is allocated and guaranteed to have enough space for storing all characters from the file.
sol.read(buf, 1); // After calling your read method, buf should contain "a". We read a total of 1 character from the file, so return 1.
sol.read(buf, 2); // Now buf should contain "bc". We read a total of 2 characters from the file, so return 2.
sol.read(buf, 1); // We have reached the end of file, no more characters can be read. So return 0.

Example 2:
File file("abc");
Solution sol;
sol.read(buf, 4); // After calling your read method, buf should contain "abc". We read a total of 3 characters from the file, so return 3.
sol.read(buf, 1); // We have reached the end of file, no more characters can be read. So return 0.
/* Calls from the Application 
  read(A, 10);
 read(B, 255);
  read(C, 1);
  read(D, 5);
*/

/*
 using read4() to imple. 

Note that read4() has its own file pointer, much like FILE *fp in C.
Definition of read4:
   Parameter:  char[] buf
    Returns:    int

Note: buf[] is destination not source, the results from read4 will be copied to buf[]
Int read4(char[] buf)

*/
uint32_t read(char* buff, uint32_t n)
{
    int num_read = 0; //already read
    int idx = 0;	//the data position of buf
    char *buff_read4 = NULL;

    while(num_read = read4(buf_read4))
    {
        //save buf_read4 to buf[]
        strcat(Buff[idx], buff_read4);
        idx += num_read;
    }
    return idx;
}


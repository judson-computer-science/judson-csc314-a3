# Assignment 3 - Data Marshaling
In this assignment you will build define and populate a structure that represents a car.  You will then copy it into a buffer removing all slack bytes and then reverse the process.

The program will be written in C.

## Input
None.  All values in this assignment will be hard-coded.  Be sure to keep the values that you select within the appropriate range for each field.

## Output
Your program should produce the following output (Note: your output may vary depending on the values used):


	Vehicle Inforamtion
	-------------------
	Type:  01 (1)
	Year:  07d7 (2007)
	Make:  4e697373616e00 (Nissan)
	Model: 416c74696d6100 (Altima)
	Miles: 0003e738 (255800)

	24 bytes in struct (24 byte buffer):

	0000  01 00 00 00 d7 07 4e 69   73 73 61 6e 00 41 6c 74 
	0010  69 6d 61 00 38 e7 03 00 

	20 bytes packed (24 byte buffer):

	0000  47 d7 4e 69 73 73 61 6e   00 41 6c 74 69 6d 61 00 
	0010  f9 ce 3f ff 00 00 00 00 

	24 bytes unpacked (24 byte buffer):

	0000  01 00 00 00 d7 07 4e 69   73 73 61 6e 00 41 6c 74 
	0010  69 6d 61 00 38 e7 03 00 


## Implementation
Your program will define the following macros, enum and structure

	#define BUFF_SIZE 24
	#define NAME_SIZE 7

	typedef enum {
	        CAR,
	        TRUCK,
	        SUV,
	        OTHER
	} VehicleType;

	struct Vehicle {
	        VehicleType type;       //  2 LSB used
	        uint16_t year;          // 14 LSB used, 2 MSB unused
	        char make[NAME_SIZE];   // 10 bytes
	        char model[NAME_SIZE];  // 10 bytes
	        uint32_t miles;         // 18 LSB used, 14 MSB unused
	};

NOTE:
 - LSB = Least Significant Bits
 - MSB = Most Significant Bits

Your program should assign values to the fields in the structure but you must be sure that the values you assign do not exceed the max value that should be contained in each based on the number of bits being used.  Specifically, the range of values for each field are listed below:

	Field	| Range
	--------+------------------------------------------
	type	| any VehicleType value from the enum
	year	| 0 to 16,383 (14 bits)
	make	| 6 characters (7th is the null terminator)
	model	| 6 characters (7th is the null terminator)
	miles	| 0 to 262,143 (18 bits) 

Note that the **year** and **miles** fields have data types that will allow a larger number of bits than what is specified above.  However, you will only use the number of bits specified above when the data is compressed into the buffer (see below).

After populating the structure, you will `memcpy` the structure into the buffer and print it.  You will then overwrite the buffer with the packed data and print it again.  Finally, you will unpack the data into a new instance of the structure, copy it into the buffer and print it once more.  The buffer must be of size `BUFF_SIZE` and must contain unsigned characters.  The packed data shall conform to the format below:


	        |12345678 12345678 12345678 12345678 12345678 12345678 12345678 12345678
	    	+--------+--------+--------+--------+--------+--------+--------+--------
	 1 to  8|TTYYYYYY YYYYYYYY AAAAAAAA AAAAAAAA AAAAAAAA AAAAAAAA AAAAAAAA AAAAAAAA
	 9 to 16|AAAAAAAA OOOOOOOO OOOOOOOO OOOOOOOO OOOOOOOO OOOOOOOO OOOOOOOO OOOOOOOO
	16 to 24|MMMMMMMM MMMMMMMM MMxxxxxx xxxxxxxx uuuuuuuu uuuuuuuu uuuuuuuu uuuuuuuu

where,
 - T = the 2 bits of the 'type' field
 - Y = the 14 bits of the 'year' field
 - A = the 7 bytes (56 bits) of the 'make' field
 - O = the 7 bytes (56 bits) of the 'model' field
 - M = the 18 bits of the 'miles' field
 - x = 14 bits each set to binary '1'
 - u = 4 bytes (32 bits) set to binary '0'

### Functions
Your program MUST include implementations for the functions corresponding to each function prototype listed here:

 - `int pack_message(unsigned char * dest, struct Vehicle * src)`
   - This function packs the buffer from the structure provided
   - **Returns**:  the number of bytes packed into the buffer
   - **Parameters**:
      1. The buffer to be packed
      2. The populated structure

 - `void unpack_message(struct Vehicle * dest, unsigned char * src)`
   - This function unpacks the buffer into the structure provided
   - **Returns**:  Nothing
   - **Parameters**:
      1. The structure to be populated from the buffer
      2. The buffer to be unpacked

 - `void print_bytes(const char * label, unsigned char * buff, int length)`
   - This function is responsible for printing the contents of the buffer that is passed as the second parameter along with the title (label) passed as the first parameter.  Note that the leftmost column on each line shows the byte offset of that line in hexadecimal format.  This function is responsible for generating the output shown in the __Function Output Examples__ section below.
   - **Returns**:  Nothing
   - **Parameters**:
      1. The title to be printed
      2. The buffer to be printed
      3. The length of the buffer to the printed

 - `void print_struct(struct Vehicle * car)`
   - This function is responsible for printing the details of the structure fields in both hex and decimal.  It is the function responsible for generating the output shown in the __Function Output Examples__ section below:
   - **Returns**:  Nothing
   - **Parameters**:
      1. The address of the populated Vehicle structure

### Function Output Examples

`print_bytes()` function output

	24 bytes in struct (24 byte buffer):

	0000  01 00 00 00 d7 07 4e 69   73 73 61 6e 00 41 6c 74
	0010  69 6d 61 00 38 e7 03 00

`print_struct()` function output

	Vehicle Information
	-------------------
	Type:  01 (1)
	Year:  07d7 (2007)
	Make:  4e697373616e00 (Nissan)
	Model: 416c74696d6100 (Altima)
	Miles: 0003e738 (255800)

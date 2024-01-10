#define BUFF_SIZE 24
#define NAME_SIZE 7

typedef enum {
	CAR,
	TRUCK,
	SUV,
	OTHER
} VehicleType;

struct Vehicle {
	VehicleType type;	//  2 bits
	uint16_t year;		// 14 bits
	char make[NAME_SIZE];   // 10 bytes
	char model[NAME_SIZE];  // 10 bytes
	uint32_t miles;		// 18 bits
				// 14 slack bits
};


int pack_message(unsigned char * dest, struct Vehicle * src);
void unpack_message(struct Vehicle * dest, unsigned char * src);
void print_bytes(const char * label, unsigned char * buff, int length);
void print_struct(struct Vehicle * car);

int main() {

	unsigned char buffer[BUFF_SIZE];
	unsigned char pbuffer[BUFF_SIZE];
	unsigned char upbuffer[BUFF_SIZE];

	// Insert code here

	return 0;

}

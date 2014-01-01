#define BULK_TIMEOUT 100
#define VFS0050_FRAME_SIZE 200
#define VFS0050_IMG_WIDTH 100
#define EP1_OUT 0x01
#define EP1_IN  0x81
#define EP2_OUT 0x02
#define EP2_IN  0x82
#define EP3_OUT 0x03
#define EP3_IN  0x83

struct vfs0050_dev {
    int init1_offset;
    int init2_offset;
    char tmpbuf[100];
};

struct vfs0050_line {
	unsigned char _0x01;
	unsigned char _0xfe;
	unsigned char _low;
	unsigned char _high;
	unsigned char _0x08;
	unsigned char _0xb8; //not sure what this is for
	unsigned char _0x00;
	unsigned char _counter; //not sure what this is either.
	unsigned char row[100]; //grayscale data
	unsigned char mag[32]; //magnified portion of scan
	unsigned char sums[8];
};

static unsigned char vfs0050_init1[] =
{
	0x36, 0x38, 0x2b, 0x5c, 0x70, 0xac, 0x73, 0x69,
	0x12, 0xc9, 0xe0, 0xbc, 0xfa, 0x88, 0x10, 0xc7,
	0x98, 0xbf, 0x52, 0xe3, 0xd5, 0xbc, 0x99, 0x9f,
	0x73, 0x48, 0x06, 0xba, 0xe0, 0x11, 0x0e, 0x87,
	0x87, 0xb5, 0x18, 0x95, 0x63, 0x98, 0xae, 0x00,
	0xc2, 0x67, 0xd5, 0x05, 0x5d, 0x66, 0xd6, 0xb3,
	0x3f, 0xb7, 0xa7, 0xa0, 0x61, 0x5b, 0x1d, 0xa0,
	0x36, 0xc6, 0xe1, 0x78, 0x0d, 0x86, 0x72, 0x84, //end block 1
	0xd2, 0xf3, 0xd9, 0xb9, 0x78, 0xd8, 0xde, 0xad,
	0x7a, 0x45, 0x3c, 0x96, 0x08, 0x2d, 0xc6, 0xae,
	0xc3, 0x3d, 0x8c, 0x6e, 0x5a, 0xfd, 0x91, 0x90,
	0x0d, 0x78, 0x98, 0xf1, 0x28, 0x67, 0x15, 0x80,
	0xea, 0x7b, 0xa9, 0xbd, 0xe0, 0x4b, 0x54, 0x8f,
	0x91, 0xea, 0x2a, 0x99, 0x38, 0xaf, 0x52, 0x11,
	0xc8, 0x34, 0x17, 0x42, 0xb8, 0xea, 0xd3, 0x8e,
	0xbc, 0x6a, 0xaa, 0x54, 0x3e, 0x77, 0x44, 0xd6, //end block 2
	0x4a, 0x46, 0x04, 0xa5, 0x33, 0xe1, 0x86, 0xfd,
	0xed, 0x80, 0xa8, 0x12, 0x3a, 0xc2, 0x29, 0x3e,
	0xce, 0x9e, 0x00, 0xe7, 0xb3, 0xb5, 0x11, 0x2b,
	0x50, 0x6c, 0x2c, 0x5e, 0x33, 0x17, 0xf5, 0x8b,
	0xc4, 0x0f, 0x25, 0x65, 0x87, 0x0d, 0x88, 0x3c,
	0x30, 0xad, 0x9b, 0x40, 0x8a, 0x6c, 0x60, 0xc9,
	0xf4, 0x03, 0xc1, 0x0f, 0x0e, 0x08, 0xa1, 0x81,
	0x5e, 0x6a, 0x79, 0x3f, 0x7a, 0xf6, 0x18, 0x7e, //end block 3
	0x30, 0x98, 0xf1, 0x25, 0xcb, 0xbd, 0xb9, 0xae,
	0x5b, 0xeb, 0xa7, 0xea, 0x7c, 0xb6, 0x6f, 0x06,
	0x0f, 0xaa, 0xe5, 0xd6, 0xe3, 0x46, 0x83, 0xa3,
	0xe1, 0x66, 0x38, 0x70, 0xb0, 0x5c, 0x3e, 0xe3,
	0xe0, 0x50, 0x25, 0x60, 0x98, 0x08, 0xa8, 0x86,
	0xc9, 0xdc, 0xbc, 0xaf, 0x02, 0x54, 0xfc, 0xad,
	0x8d, 0x9f, 0x87, 0x5a, 0x2f, 0x4a, 0xea, 0x92,
	0x71, 0x5d, 0x88, 0x64, 0xeb, 0xb0, 0x98, 0x27, //end block 4
	0x96, 0xd5, 0x1f, 0x80, 0x44, 0xe3, 0x0f, 0x95,
	0x95, 0xcb, 0x43, 0xb0, 0xca, 0xbf, 0xac, 0xd9,
	0x70, 0xe8, 0xc6, 0xf9, 0x4a, 0x94, 0xf7, 0x6c,
	0x8d, 0x46, 0x97, 0x63, 0x85, 0xb9, 0x85, 0xae,
	0x3c, 0xe0, 0xa2, 0xad, 0xd7, 0x36, 0x27, 0xcf,
	0xa1, 0x1f, 0x18, 0x34, 0xf9, 0xff, 0x52, 0xc7,
	0xae, 0x60, 0x2d, 0xa5, 0x76, 0x79, 0x42, 0xfb,
	0xa8, 0x52, 0xa8, 0x08, 0x37, 0x79, 0x96, 0x7e, //end block 5
	0x33, 0x1d, 0xd0, 0x6f, 0xc6, 0x13, 0x43, 0xdb,
	0xb0, 0xa9, 0xdd, 0x1c, 0x7a, 0x8a, 0xce, 0xe8,
	0xb6, 0xf9, 0x23, 0x43, 0x47, 0x1d, 0xd8, 0xbf,
	0xb3, 0x68, 0x66, 0x55, 0x92, 0xae, 0x7a, 0x76,
	0x54, 0xcf, 0x2c, 0xfc, 0x11, 0xf1, 0xd2, 0x08,
	0x27, 0xd9, 0x23, 0x5c, 0x3c, 0x0a, 0xde, 0x7c,
	0xd9, 0x26, 0x4b, 0x24, 0x5d, 0xc2, 0xbf, 0xe9,
	0x50, 0x87, 0xda, 0x2d, 0xfd, 0x5e, 0x20, 0x66, //end block 6
	0x08, 0x9d, 0xe2, 0xa6, 0xc1, 0xc7, 0x0e, 0x86,
	0xcb, 0xe0, 0xe7, 0x56, 0x82, 0xf1, 0x7e, 0x7e,
	0x4a, 0xb3, 0x42, 0x8d, 0x25, 0xec, 0x1e, 0xb1,
	0x44, 0x17, 0xdf, 0xb3, 0x06, 0xf4, 0x60, 0x3d,
	0x68, 0x36, 0x45, 0xa5, 0xee, 0x5b, 0xea, 0xc3,
	0x5d, 0x67, 0x51, 0x14, 0xdc, 0xcc, 0x6b, 0x9d,
	0xd3, 0x01, 0xdb, 0x99, 0xc7, 0x85, 0x15, 0x68,
	0xe5, 0x04, 0xe4, 0x12, 0xd4, 0x83, 0x44, 0x7d, //end block 7
	0xe8, 0x7c, 0x6c, 0xaa, 0xaa, 0xd2, 0x97, 0x5b,
	0xae, 0xac, 0x03, 0xac, 0x3c, 0x73, 0xd6, 0x16,
	0x72, 0x29, 0xc7, 0x2a, 0x57, 0xbc, 0x3e, 0xdc,
	0x2e, 0xaf, 0xd2, 0x1a, 0x03, 0x76, 0x39, 0x9d,
	0x3f, 0x66, 0xe5, 0xcc, 0x32, 0x0d, 0xd8, 0x58,
	0x4b, 0xa4, 0xa2, 0x39, 0xe2, 0xe8, 0xb7, 0x44,
	0x33, 0xab, 0x7c, 0x49, 0xf6, 0xe4, 0x24, 0xc4,
	0x7c, 0xa9, 0x07, 0x31, 0x93, 0x16, 0xb4, 0x31, //end block 8
	0x38, 0x5d, 0x13, 0x0b, 0x8f, 0x46, 0xa8, 0x77,
	0xb2, 0x86, 0x15, 0x2c, 0xa7, 0x6a, 0x04, 0xb1,
	0x4c, 0xdd, 0xc8, 0xe0, 0x26, 0xc5, 0xa3, 0x4d,
	0x6a, 0x94, 0x57, 0x1f, 0x85, 0x83, 0x8f, 0x05,
	0xe3, 0xd9, 0x3d, 0x3c, 0x54, 0x96, 0x05, 0xec,
	0xf8, 0x25, 0xea, 0x84, 0x9f, 0x5d, 0x3f, 0x4a,
	0xa1, 0x89, 0x86, 0x9f, 0xb7, 0x73, 0x49, 0x6c,
	0x8e, 0xcf, 0x9c, 0x88, 0xb6, 0xce, 0x18, 0x15, //end block 9
	0x93, 0xe0, 0x17, 0x9a, 0x69, 0x57, 0xd1, 0xb6,
	0x25, 0xf9, 0x62, 0xd2, 0xba, 0x2c, 0xcb, 0xe6,
	0x5f, 0xe5, 0xb4, 0x18, 0xe8, 0x65, 0x46, 0x7d,
	0x06, 0x36, 0x85, 0x74, 0xc4, 0x1d, 0x62, 0xf1,
	0x50, 0x54, 0x9a, 0x02, 0xda, 0x4b, 0x67, 0x70,
	0xfd, 0x00
};
static unsigned char vfs0050_init2[] = 
{
	0x02, 0x94, 0x00, 0x64, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x2c, 0x03, 0x00, 0x30, 0x1b, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x20, 0x03, 0x00,
	0x30, 0x3d, 0x10, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x18, 0x03, 0x00, 0x30, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x24, 0x03, 0x00,
	0x30, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x28, 0x03, 0x00, 0x30, 0x08, 0x00, 0x00, //end block 1
	0x00, 0x20, 0x00, 0x08, 0x00, 0x30, 0x03, 0x00,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x38, 0x03, 0x00, 0x30, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x3c, 0x03, 0x00,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x44, 0x03, 0x00, 0x30, 0x14, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x48, 0x03, 0x00,
	0x30, 0x01, 0x04, 0x02, 0x00, 0x20, 0x00, 0x08, //end block 2
	0x00, 0x4c, 0x03, 0x00, 0x30, 0x01, 0x0c, 0x02,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x54, 0x03, 0x00,
	0x30, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x5c, 0x03, 0x00, 0x30, 0x90, 0x01, 0x02,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x60, 0x03, 0x00,
	0x30, 0x2c, 0x01, 0x19, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x64, 0x03, 0x00, 0x30, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x6c, 0x03, 0x00, //end block 3
	0x30, 0x1e, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x70, 0x03, 0x00, 0x30, 0x21, 0x80, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x78, 0x03, 0x00,
	0x30, 0x09, 0x00, 0x02, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x7c, 0x03, 0x00, 0x30, 0x0b, 0x00, 0x19,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x80, 0x03, 0x00,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x84, 0x03, 0x00, 0x30, 0x3a, 0x00, 0x00, //end block 4
	0x00, 0x20, 0x00, 0x08, 0x00, 0x88, 0x03, 0x00,
	0x30, 0x14, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x8c, 0x03, 0x00, 0x30, 0x02, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x90, 0x03, 0x00,
	0x30, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x94, 0x03, 0x00, 0x30, 0x08, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x98, 0x03, 0x00,
	0x30, 0x00, 0x00, 0xa1, 0x01, 0x20, 0x00, 0x08, //end block 5
	0x00, 0x9c, 0x03, 0x00, 0x30, 0x00, 0x00, 0xa1,
	0x01, 0x20, 0x00, 0x08, 0x00, 0xa8, 0x03, 0x00,
	0x30, 0x64, 0x01, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0xac, 0x03, 0x00, 0x30, 0x64, 0x01, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0xb0, 0x03, 0x00,
	0x30, 0x00, 0x01, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0xb4, 0x03, 0x00, 0x30, 0x00, 0x01, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0xb8, 0x03, 0x00, //end block 6
	0x30, 0x05, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0xbc, 0x03, 0x00, 0x30, 0x05, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0xc0, 0x03, 0x00,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x84, 0x03, 0x00, 0x30, 0x3b, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x08, 0x07, 0x00,
	0x30, 0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x0c, 0x07, 0x00, 0x30, 0x00, 0x00, 0x00, //end block 7
	0x00, 0x20, 0x00, 0x08, 0x00, 0x14, 0x07, 0x00,
	0x30, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x1c, 0x07, 0x00, 0x30, 0x1a, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x70, 0x0d, 0x00,
	0x30, 0x01, 0x00, 0x00, 0x00, 0x25, 0x00, 0x28,
	0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //end block 8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x00, 0x90, 0x00, 0x00, 0x00, 0x2b,
	0xff, 0x2b, 0xff, 0x2b, 0xed, 0x00, 0x00, 0x2b,
	0xfb, 0x00, 0x00, 0x2b, 0xc5, 0x00, 0x00, 0x2b,
	0x05, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x24, 0xd3, 0x2e, 0xc0, 0x2c, 0x3b, 0x08,
	0xf0, 0x3b, 0x09, 0x24, 0xbb, 0x3b, 0x0b, 0x24, //end block 9
	0xaa, 0x3b, 0x1f, 0xf8, 0x00, 0x3b, 0x3f, 0xf0,
	0x00, 0x3b, 0x35, 0xc0, 0x00, 0x38, 0x80, 0x2c,
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38,
	0x80, 0x2c, 0x70, 0x00, 0x00, 0x00, 0x00, 0xc0,
	0x3a, 0x80, 0x2c, 0x70, 0x00, 0x00, 0x00, 0x00,
	0xc0, 0x3b, 0x0a, 0x80, 0x2e, 0x83, 0x24, 0xdb,
	0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x2c,
	0x31, 0x83, 0x2c, 0x70, 0x00, 0x00, 0x00, 0x00, //end block 10
	0xcb, 0x33, 0x1b, 0x83, 0x2c, 0x70, 0x00, 0x00,
	0x00, 0x00, 0xcb, 0x31, 0x83, 0x2c, 0x70, 0x00,
	0x00, 0x00, 0x00, 0xcb, 0x00, 0x33, 0x1e, 0x83,
	0x2e, 0x25, 0xff, 0xc4, 0x00, 0x2f, 0x06, 0x84,
	0x2e, 0x00, 0x00, 0x10, 0x20, 0x29, 0x00, 0x04,
	0x00, 0x10, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00,
	0x00, 0x21, 0x00, 0x10, 0x00, 0x48, 0x03, 0x00,
	0x30, 0xff, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, //end block 11
	0x00, 0x00, 0x04, 0x00, 0x00, 0x21, 0x00, 0x10,
	0x00, 0x4c, 0x03, 0x00, 0x30, 0xff, 0xf0, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00,
	0x00, 0x21, 0x00, 0x10, 0x00, 0x20, 0x03, 0x00,
	0x30, 0x7f, 0x00, 0xfc, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x10, 0x00, 0x00, 0x20, 0x00, 0x08,
	0x00, 0x24, 0x03, 0x00, 0x30, 0x04, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x1c, 0x07, 0x00, //end block 12
	0x30, 0x1a, 0x00, 0x00, 0x00, 0x21, 0x00, 0x10,
	0x00, 0x20, 0x03, 0x00, 0x30, 0xc3, 0xff, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x20, 0x00, 0x08, 0x00, 0x80, 0x03, 0x00,
	0x30, 0x01, 0x00, 0x00, 0x00
};

static unsigned char vfs0050_activate1[] =
{
      0x39, 0x20, 0xbf, 0x02, 0x00, 0xf4, 0x01, 0x00,
      0x00, 0x01, 0xd1, 0x00, 0x20, 0xd1, 0xd1, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0xf4, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
      0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00,
      0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //end block 1
      0x00, 0xf4, 0x01, 0x00, 0x00, 0x02, 0xd1, 0x00,
      0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char vfs0050_activate2[] =
{
      0x02, 0x94, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x2c, 0x03, 0x00, 0x30, 0x1b, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x20, 0x03, 0x00,
      0x30, 0x3d, 0x10, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x18, 0x03, 0x00, 0x30, 0x00, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x24, 0x03, 0x00,
      0x30, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x28, 0x03, 0x00, 0x30, 0x08, 0x00, 0x00, //end block 1
      0x00, 0x20, 0x00, 0x08, 0x00, 0x30, 0x03, 0x00,
      0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x38, 0x03, 0x00, 0x30, 0x00, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x3c, 0x03, 0x00,
      0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x44, 0x03, 0x00, 0x30, 0x14, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x48, 0x03, 0x00,
      0x30, 0x01, 0x04, 0x02, 0x00, 0x20, 0x00, 0x08, //end block 2
      0x00, 0x4c, 0x03, 0x00, 0x30, 0x01, 0x0c, 0x02,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x54, 0x03, 0x00,
      0x30, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x5c, 0x03, 0x00, 0x30, 0x90, 0x01, 0x02,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x60, 0x03, 0x00,
      0x30, 0x2c, 0x01, 0x19, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x64, 0x03, 0x00, 0x30, 0x00, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x6c, 0x03, 0x00, //end block 3
      0x30, 0x1e, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x70, 0x03, 0x00, 0x30, 0x21, 0x80, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x78, 0x03, 0x00,
      0x30, 0x09, 0x00, 0x02, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x7c, 0x03, 0x00, 0x30, 0x0b, 0x00, 0x19,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x80, 0x03, 0x00,
      0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x84, 0x03, 0x00, 0x30, 0x3a, 0x00, 0x00, //end block 4
      0x00, 0x20, 0x00, 0x08, 0x00, 0x88, 0x03, 0x00,
      0x30, 0x14, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x8c, 0x03, 0x00, 0x30, 0x02, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x90, 0x03, 0x00,
      0x30, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x94, 0x03, 0x00, 0x30, 0x08, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x98, 0x03, 0x00,
      0x30, 0x00, 0x00, 0xa1, 0x01, 0x20, 0x00, 0x08, //end block 5
      0x00, 0x9c, 0x03, 0x00, 0x30, 0x00, 0x00, 0xa1,
      0x01, 0x20, 0x00, 0x08, 0x00, 0xa8, 0x03, 0x00,
      0x30, 0x64, 0x01, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0xac, 0x03, 0x00, 0x30, 0x64, 0x01, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0xb0, 0x03, 0x00,
      0x30, 0x00, 0x01, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0xb4, 0x03, 0x00, 0x30, 0x00, 0x01, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0xb8, 0x03, 0x00, //end block 6
      0x30, 0x05, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0xbc, 0x03, 0x00, 0x30, 0x05, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0xc0, 0x03, 0x00,
      0x30, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x84, 0x03, 0x00, 0x30, 0x3b, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x08, 0x07, 0x00,
      0x30, 0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x0c, 0x07, 0x00, 0x30, 0x00, 0x00, 0x00, //end block 7
      0x00, 0x20, 0x00, 0x08, 0x00, 0x14, 0x07, 0x00,
      0x30, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x1c, 0x07, 0x00, 0x30, 0x1a, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x70, 0x0d, 0x00,
      0x30, 0x01, 0x00, 0x00, 0x00, 0x25, 0x00, 0x28,
      0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //end block 8
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x02, 0x00, 0x90, 0x00, 0x00, 0x00, 0x2b,
      0xff, 0x2b, 0xff, 0x2b, 0xed, 0x00, 0x00, 0x2b,
      0xfb, 0x00, 0x00, 0x2b, 0xc5, 0x00, 0x00, 0x2b,
      0x05, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x24, 0xd3, 0x2e, 0xc0, 0x2c, 0x3b, 0x08,
      0xf0, 0x3b, 0x09, 0x24, 0xbb, 0x3b, 0x0b, 0x24, //end block 9
      0xaa, 0x3b, 0x1f, 0xf8, 0x00, 0x3b, 0x3f, 0xf0,
      0x00, 0x3b, 0x35, 0xc0, 0x00, 0x38, 0x80, 0x2c,
      0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38,
      0x80, 0x2c, 0x70, 0x00, 0x00, 0x00, 0x00, 0xc0,
      0x3a, 0x80, 0x2c, 0x70, 0x00, 0x00, 0x00, 0x00,
      0xc0, 0x3b, 0x0a, 0x80, 0x2e, 0x83, 0x24, 0xdb,
      0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x2c,
      0x31, 0x83, 0x2c, 0x70, 0x00, 0x00, 0x00, 0x00, //end block 10
      0xcb, 0x33, 0x1b, 0x83, 0x2c, 0x70, 0x00, 0x00,
      0x00, 0x00, 0xcb, 0x31, 0x83, 0x2c, 0x70, 0x00,
      0x00, 0x00, 0x00, 0xcb, 0x00, 0x33, 0x1e, 0x83,
      0x2e, 0x25, 0xff, 0xc4, 0x00, 0x2f, 0x06, 0x84,
      0x2e, 0x00, 0x00, 0x10, 0x20, 0x29, 0x00, 0x04,
      0x00, 0x10, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00,
      0x00, 0x21, 0x00, 0x10, 0x00, 0x48, 0x03, 0x00,
      0x30, 0xff, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, //end block 11
      0x00, 0x00, 0x04, 0x00, 0x00, 0x21, 0x00, 0x10,
      0x00, 0x4c, 0x03, 0x00, 0x30, 0xff, 0xf0, 0xff,
      0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00,
      0x00, 0x21, 0x00, 0x10, 0x00, 0x20, 0x03, 0x00,
      0x30, 0x7f, 0x00, 0xfc, 0xff, 0x00, 0x00, 0x00,
      0x00, 0x80, 0x10, 0x00, 0x00, 0x20, 0x00, 0x08,
      0x00, 0x24, 0x03, 0x00, 0x30, 0x04, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x1c, 0x07, 0x00, //end block 12
      0x30, 0x1a, 0x00, 0x00, 0x00, 0x21, 0x00, 0x10,
      0x00, 0x20, 0x03, 0x00, 0x30, 0xc3, 0xff, 0xff,
      0xff, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00,
      0x00, 0x20, 0x00, 0x08, 0x00, 0x80, 0x03, 0x00,
      0x30, 0x02, 0x00, 0x00, 0x00, 0x24, 0x00, 0x8c,
      0x00, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, //end block 13
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, //end block 14
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
      0x77, 0x77, 0x77, 0x77, 0x77, 0x26, 0x00, 0x28,
      0x00, 0xff, 0x00, 0x0f, 0x00, 0xf0, 0xf0, 0x0f, //end block 15
      0x00, 0x20, 0x00, 0x00, 0x00, 0x30, 0x01, 0x02,
      0x00, 0x2c, 0x01, 0x28, 0x00, 0x20, 0x80, 0x00,
      0x00, 0x0a, 0x00, 0x02, 0x00, 0x0b, 0x00, 0x19,
      0x00, 0x40, 0x1f, 0x10, 0x27, 0x00, 0x0f, 0x03,
      0x00
};


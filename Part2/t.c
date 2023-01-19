/* sample code for Part 2 */

#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct partition {
	u8 drive;             // drive number FD=0, HD=0x80, etc.

	u8  head;             // starting head
	u8  sector;           // starting sector
	u8  cylinder;         // starting cylinder

	u8  sys_type;         // partition type: NTFS, LINUX, etc.

	u8  end_head;         // end head
	u8  end_sector;       // end sector
	u8  end_cylinder;     // end cylinder

	u32 start_sector;     // starting sector counting from 0
	u32 nr_sectors;       // number of of sectors in partition
};

char *dev = "vdisk";
int fd;

// read a disk sector into char buf[512]
int calc_end( struct partition *p)
{
    (p->start_sector + p->nr_sectors) - 1;
}

int main()
{
 struct partition *p;
  char buf[512];

  fd = open(dev, O_RDONLY);   // open dev for READ
  //read(fd, buf, 512);         // read 512 bytes of fd into buf[ ] 
  read_sector(fd, 0, buf);    // read in MBR at sector 0 

    // set the value of the partition we are currently on
    int partNum = 1;

    // Write C code to let p point at Partition 1 in buf[ ];
    // cast into a pointer
    p = (struct partition *)&buf[0x1BE];

    printf("            |start sector|    |end sector|    |nr_sector|      |sys type| \n");

    // print P1's start_sector, nr_sectors, sys_type;
        // Write code to print all 4 partitions;
    while(p->sys_type != 0)
    {
        // print partitions
        printf("vdisk%d :           ", partNum);
        printf("%d            ", p->start_sector);
        printf("%d              ", (p->start_sector + p->nr_sectors) - 1);
        printf("%d                 ", p->nr_sectors);
        printf("%x\n", p->sys_type);
        // check for the extended partitions
        if(p->sys_type == 5)
        {
            printf("-------------------Extended Partitions------------------\n");
            // in order to  let  int extStart = P4's start_sector
            // lets define extStart as the start sector
            int extStart = p->start_sector;
            // print extStart to see it;
            //printf("extStart: %d\n", extStart);
            // set local MBR to extStart per the instructions
            int localMBR = extStart;
            // print to see
            //printf("next localMBR sector= %d\n", localMBR);

            // extra variables
            int entryCount = 1;
            // increase our number of partitions now that we are in extended
            ++partNum;
            // loop:
            while(p->sys_type != 0)
            {
                // read the sector
                read_sector(fd, localMBR, buf);
                // point p are partition 1
                p = (struct partition *)&buf[0x1BE];
                // print the entry count
                printf("vdisk%d:                    |\n", partNum);
                printf("Entry%d: Start Sector= %d | nr_sectors= %d\n", entryCount, p->start_sector + localMBR, p->nr_sectors);
                // increase our number of entrys6
                entryCount++;
                // increase the partition count
                ++partNum;
                // move to next address
                ++p;
                // find the next localMBR by adding our extStart with the starting sector of p
                localMBR = extStart +  p->start_sector;
                // print out the next localMBR
                //printf("Next local MBR sector: %d + %d = %d\n",extStart, p->start_sector, localMBR);
            }
        }
        // move to the next address
        // and increase the partition count
        ++partNum;
        ++p;
    }
    
}
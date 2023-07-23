/* circular buffer (The buffer size must be limited to a power of two.) */
#define CIRC_INDEX(new_index, buffer_size) ((new_index) & ((buffer_size) - 1))
#define CIRC_CNT(head, tail, buffer_size) (((head) - (tail)) & ((buffer_size) - 1))
#define CIRC_SPACE(head, tail, buffer_size) (((tail) - (head) - 1) & ((buffer_size) - 1))

/*
 * print ether_addr macro
 * ex) struct ether_addr mac = {{0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6}};
 *     printf("mac address is " ETHER_ADDR_FMT "\n", ETHER_ADDR_PTR(&mac));
 */
#define ETHER_ADDR_FMT "%02X:%02X:%02X:%02X:%02X:%02X"
#define ETHER_ADDR_PTR(addr) (addr)->ether_addr_octet[0], (addr)->ether_addr_octet[1], (addr)->ether_addr_octet[2], (addr)->ether_addr_octet[3], (addr)->ether_addr_octet[4], (addr)->ether_addr_octet[5]

/* IOCTL */
#define IOCTL_PCM_START	_IO('a', 0)
#define IOCTL_PCM_STOP	_IO('a', 1)

#define MTU					1500
#define NM_BUFSZ			2048
#define NM_NUM_SLOTS		1024
#define AOE_NUM_SLOTS		1024
#define AOE_BUF_SIZE		(NM_BUFSZ*NM_NUM_SLOTS*2)
#define HW_RXRING_IDX0		2
#define HOST_TXRING_IDX0	7170
#define AOE_LUT_INDEX		100000

/*
 * The AoE Sound Driver uses the size of the ether header
 * or aoe header to calculate the memory address.
 */
#ifdef CONFIG_SMPD_OPTION_AOE
#define ETH_ALEN       6
struct ether_header
{
  uint8_t  ether_dhost[ETH_ALEN];	/* destination eth addr	*/
  uint8_t  ether_shost[ETH_ALEN];	/* source ether addr	*/
  uint16_t ether_type;		        /* packet type ID field	*/
} __attribute__ ((__packed__));
#endif

struct aoe_header {
	uint16_t u16key;	/* session key */
	uint8_t  u8cmd;		/* command */
	uint8_t  u8sub;		/* sub command */
	uint32_t u32opt1;	/* option 1 */
	uint32_t u32opt2;	/* option 2 */
	uint16_t u16len;
	uint16_t u16sum;
} __attribute__ ((__packed__));

struct slot {
	uint32_t buf_idx;	/* buffer index */
};
enum DMAStatus	{ACTIVE, INACTIVE};
struct ext_slot {
	struct slot slot[AOE_NUM_SLOTS];
	int head;
	int cur;
	int tail;
	int unarrived_dreq_packets;
	int num_slots;
	enum DMAStatus stat;
};

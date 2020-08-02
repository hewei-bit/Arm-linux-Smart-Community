#include "readrfidid.h"


void init_tty(int fd)
{
	//设置原有的串口参数
	struct termios old_cfg,new_cfg;
	
	if(tcgetattr(fd,&old_cfg) != 0)
	{
		perror("tcgetattr");
		exit(0);
	}
	
	// #include <strings.h>

    //   void bzero(void *s, size_t n); //将以s为内存首地址，设置为0，该内存的大小为n字节

	bzero(&new_cfg,sizeof(new_cfg));
	
	new_cfg = old_cfg;
	
	cfmakeraw(&new_cfg);
	
	//设置串口波特率:输入和输出
	// int cfsetispeed(struct termios *termios_p, speed_t speed);
     //int cfsetospeed(struct termios *termios_p, speed_t speed);

	cfsetispeed(&new_cfg,B9600); //波特率的设置要跟具体的项目来设置
	cfsetospeed(&new_cfg,B9600);
	
	new_cfg.c_cflag  |=  CLOCAL | CREAD; //开启本地模式
	
	//设置数据位8位，无奇偶校验位，停止位1位
	new_cfg.c_cflag &= ~CSIZE; /* 用数据位掩码清空数据位设置 */
	new_cfg.c_cflag |= CS8;
	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_cflag &= ~CSTOPB; /* 将停止位设置为一个比特 */
	
	//清空串口缓冲区
	new_cfg.c_cc[VTIME] = 0;
	new_cfg.c_cc[VMIN]   = 1;
	//int tcflush(int fd, int queue_selector);
   tcflush(fd, TCIFLUSH);
   
   //判断串口是否初始化完成
    // int tcsetattr(int fd, int optional_actions,
    //                 const struct termios *termios_p);

    if(tcsetattr(fd,TCSANOW,&new_cfg) != 0)
	{
		perror("tcsetattr");
		exit(0);
	}
	
}
unsigned char calBCC(unsigned char* buf,int n)
{
	
	int i = 0;
	unsigned char bcc = 0;
	
	for(;i<n;i++)
	{
		bcc ^= *(buf+i);
	}
	
	return (~bcc);
}

int PiccRequest(int fd)
{
	//完成数据的写入和读取两个操作
	//数据帧的封装：字符数组或者结构体都可以
	unsigned char WBuf[128],RBuf[128];
	fd_set rfds; //select监听多个IO，它会把这个监听的结果存放在fd_set（文件描述符集合中）
    struct timeval timeout;
    int retval;

	//       void *memset(void *s, int c, size_t n); //以s为首的内存地址，用c来进行初始化，内存大小为n
	memset(WBuf,0,128);
	memset(RBuf,0,128);
	
	//数据帧为ISO14443A标准的请求命令
	WBuf[0] = 0x07;
	WBuf[1] = 0x02;
	WBuf[2] = 'A';
	WBuf[3] = 0x01;
	WBuf[4] = 0x52;
	WBuf[5] = calBCC(WBuf,WBuf[0]-2);
	WBuf[6] = 0x03;
	
	/* Watch serial(fd) to see when it has data. */
	FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

     /* Wait up to 300 seconds. */
    timeout.tv_sec = 300;
    timeout.tv_usec = 0;

	write(fd,WBuf,7);
	
	//因为串口也是IO设备，可以使用select来完成监听
	//int select(int nfds, fd_set *readfds, fd_set *writefds,
      //            fd_set *exceptfds, struct timeval *timeout);

	 retval = select(fd+1, &rfds, NULL, NULL, &timeout);
	 printf("PiccRequest----------");
	 
	 switch(retval)
	 {
		 case -1:
		 perror("PiccRequest select");
		 break;
		 case 0:
		  perror("PiccRequest select timeout");
		 break;
		 default:
		  //监听成功，读取串口从机返回的值
		  retval = read(fd,RBuf,8);
		  if(retval < 0)
		  {
			  printf("PiccRequest retval = %d\n",retval);
			  break;
		  }
		  if(RBuf[2] == 0x00)
		  {
			  printf("PiccRequest sucess\n");
			  return 0;
		  }
		 break;
	 }

     FD_CLR(fd, &rfds);

	return 1;
}

//防碰撞，获取范围内最大的ID，该ID值就是一个电子标签的ID值
int PiccAnticoll(int fd)
{
	unsigned char WBuf[128],RBuf[128];
	fd_set rfds; 
    struct timeval timeout;
    int retval;
	
	unsigned int ID; //卡的ID
	
	memset(WBuf,0,128);
	memset(RBuf,0,128);
	
	WBuf[0] = 0x08; //帧长
	WBuf[1] = 0x02; // ISO14443A 标准的命令
	WBuf[2] = 'B'; //防碰撞命令
	WBuf[3] = 0x02; //信息长度 = 2
	WBuf[4] = 0x93; //防碰撞 一级碰撞
	WBuf[5] = 0X00;
	WBuf[6] = calBCC(WBuf,WBuf[0]-2);
	WBuf[7] = 0x03;
	
	/* Watch serial(fd) to see when it has data. */
	FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

     /* Wait up to 300 seconds. */
    timeout.tv_sec = 300;
    timeout.tv_usec = 0;

	write(fd,WBuf,8);
	
	
	 retval = select(fd+1, &rfds, NULL, NULL, &timeout);
	 printf("PiccAnticoll----------");
	 
	 switch(retval)
	 {
		 case -1:
		 perror("PiccAnticoll select");
		 break;
		 case 0:
		  perror("PiccAnticoll select timeout");
		 break;
		 default:
		  //监听成功，读取串口从机返回的值
		  retval = read(fd,RBuf,10);
		  if(retval < 0)
		  {
			  printf("PiccAnticoll retval = %d\n",retval);
			  break;
		  }
		  //应答帧为0，则表示 成功
		  if(RBuf[2] == 0x00)
		  {
			printf("PiccAnticoll sucess\n");
			  //获取ID，返回的ID的值存放在RBuf[4] RBuf[5] RBuf[6] RBuf[7]
			  ID = (RBuf[7]<<24) | (RBuf[6]<<16) | (RBuf[5]<<8) | (RBuf[4]);
			  printf("PiccAnticoll The Card ID is %x\n",ID);
			  return 0;
		  }
		 break;
	 }

     FD_CLR(fd, &rfds);

	return 1;
}

//读卡的ID
int readCardId()
{
	
	//[1] 打开串口
	int fd = open(USART1,O_RDWR | O_NOCTTY);
	if(fd == -1)
	{
		perror("open");
		return fd;
	}
	//[2]初始化串口配置
	init_tty(fd);
	
	//[3]应需求的要求，主机向从机发起请求(request ---- 先写入数据--write，然后再read数据)
	if(PiccRequest(fd)) //请求成功，则返回0，否则，非零
	{
		printf("request fail\n");
		return -1;
	}
	//[4]根据设备的流程图，进行防碰撞
	if(PiccAnticoll(fd))
	{
		printf("Anticoll fail\n");
		return -1;
	}
	//[4] 关闭串口
}
#if 0
int main(void)
{
	//读取RFID的ID值
	
	while(1)
	{
		
		readCardId();
		sleep(1);
	}
	
	return 0;
}
#endif

#define DATA_REBUF (unsigned char *)&transmit_buffer[28]
void main(void)
{
	unsigned long a;//定义几个临时变量
	/***********
	一些初始化等操作在此处进行，这里省略
	************/
	for(a = 10000000; a > 0; a--);//延时
	printf("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\nSend ARP request ... ");
	//用串口打印一串字符，这是根据自己的处理器自行添加的函数，用于查看调试信息
	//首先通过arp协议寻找上位机
	while(1)
	{
		arp_request();//发出arp请求
		while(/*等待中断标志或某种标识来判断是否有数据包被接收到，没有数据包时为真，有数据包收到时为假*/);
		//上面的语句会根据不同的网卡芯片和不同的处理器，判断方式会有所不同。
		tem = receivepacket();
		if(tem == 0x0806)//判断是否是arp协议
		{
			if(ARP_SAVETHEREPLY == arp_process(receive_packet_length))break;
			//判断是否是arp应答，如果是则存储上位机mac地址后退出循环
		}
		for(a = 5000000; a > 0; a--);//适当的延时1秒左右
	}
	
	printf("Received ARP replay\r\n----------------------------\r\n\r\n");
	//打印ARP通讯完成信息。以上是ARP通讯，与之前的一样，下面开始接收udp包
	while(1)
	{
		printf("Waiting for a new packet : \r\n\t");//打印正在等待接收数据包
		while(/*等待中断标志或某种标识来判断是否有数据包被接收到，没有数据包时为真，有数据包收到时为假*/);
		a = receivepacket(re_data);//读取数据包信息，返回协议类型（ip协议或arp协议）
		if(a == ETHTYPE_IP) //判断是否是ip协议包
		{
			a = ip_process(); //处理ip协议，返回ip协议中承载的协议类型
			if(a == IP_UDP) //判断是否是udp协议包
			{
				printf("Received a udp packet ( %d ) bytes )", receive_packet_length - 8);
				//打印udp包数据，数据长度需减去8个字节的udp首部
				for(a = 0; a < (receive_packet_length - 8); a++)
				{
					printf("%d ",DATA_REBUF[a]);//从接收数据缓存中读取数据并打印
				}
				printf("\r\n\r\n\r\n\r\n"); 
				break;//成功接收到一个udp包后便跳出循环停止程序
			}
			else if(a == IP_NOTMYIP)printf("Received but not my IP Packet\r\n");
			else if(a == IP_BED_PACKET)printf("Received my IP Packet but not valid yet\r\n");
			else printf("Error!\r\n");//非正常ip协议包的其它情况打印输出
		}
		else
		{
			printf("Received but not a IP Packet!\r\n");//非ip协议包情况打印输出
			continue;
		}
	}
	
	while(1);//程序停止，查看结果
}


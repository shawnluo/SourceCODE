#define DATA_REBUF (unsigned char *)&transmit_buffer[28]
void main(void)
{
	unsigned long a;//���弸����ʱ����
	/***********
	һЩ��ʼ���Ȳ����ڴ˴����У�����ʡ��
	************/
	for(a = 10000000; a > 0; a--);//��ʱ
	printf("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\nSend ARP request ... ");
	//�ô��ڴ�ӡһ���ַ������Ǹ����Լ��Ĵ�����������ӵĺ��������ڲ鿴������Ϣ
	//����ͨ��arpЭ��Ѱ����λ��
	while(1)
	{
		arp_request();//����arp����
		while(/*�ȴ��жϱ�־��ĳ�ֱ�ʶ���ж��Ƿ������ݰ������յ���û�����ݰ�ʱΪ�棬�����ݰ��յ�ʱΪ��*/);
		//�����������ݲ�ͬ������оƬ�Ͳ�ͬ�Ĵ��������жϷ�ʽ��������ͬ��
		tem = receivepacket();
		if(tem == 0x0806)//�ж��Ƿ���arpЭ��
		{
			if(ARP_SAVETHEREPLY == arp_process(receive_packet_length))break;
			//�ж��Ƿ���arpӦ���������洢��λ��mac��ַ���˳�ѭ��
		}
		for(a = 5000000; a > 0; a--);//�ʵ�����ʱ1������
	}
	
	printf("Received ARP replay\r\n----------------------------\r\n\r\n");
	//��ӡARPͨѶ�����Ϣ��������ARPͨѶ����֮ǰ��һ�������濪ʼ����udp��
	while(1)
	{
		printf("Waiting for a new packet : \r\n\t");//��ӡ���ڵȴ��������ݰ�
		while(/*�ȴ��жϱ�־��ĳ�ֱ�ʶ���ж��Ƿ������ݰ������յ���û�����ݰ�ʱΪ�棬�����ݰ��յ�ʱΪ��*/);
		a = receivepacket(re_data);//��ȡ���ݰ���Ϣ������Э�����ͣ�ipЭ���arpЭ�飩
		if(a == ETHTYPE_IP) //�ж��Ƿ���ipЭ���
		{
			a = ip_process(); //����ipЭ�飬����ipЭ���г��ص�Э������
			if(a == IP_UDP) //�ж��Ƿ���udpЭ���
			{
				printf("Received a udp packet ( %d ) bytes )", receive_packet_length - 8);
				//��ӡudp�����ݣ����ݳ������ȥ8���ֽڵ�udp�ײ�
				for(a = 0; a < (receive_packet_length - 8); a++)
				{
					printf("%d ",DATA_REBUF[a]);//�ӽ������ݻ����ж�ȡ���ݲ���ӡ
				}
				printf("\r\n\r\n\r\n\r\n"); 
				break;//�ɹ����յ�һ��udp���������ѭ��ֹͣ����
			}
			else if(a == IP_NOTMYIP)printf("Received but not my IP Packet\r\n");
			else if(a == IP_BED_PACKET)printf("Received my IP Packet but not valid yet\r\n");
			else printf("Error!\r\n");//������ipЭ��������������ӡ���
		}
		else
		{
			printf("Received but not a IP Packet!\r\n");//��ipЭ��������ӡ���
			continue;
		}
	}
	
	while(1);//����ֹͣ���鿴���
}


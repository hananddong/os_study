__asm void PendSV_Handler(void)
{
	IMPORT _block_ptr      // IMPORT�� �����������һ���ⲿ�����ı�ţ������ڱ�������� 
                           // EXPORT�� ����Ϊ���ڻ�����������÷��ſ��Ա��ⲿģ��ʹ�ã�������C�е�extern����
	
	LDR R0, =_block_ptr    // LDRαָ���ָ����ŵ�ֵ����r0
	LDR R0, [R0]           // LDRָ����洢����ַΪR0�������ݶ���Ĵ���R0. (ͨ�׽��ͣ���R0�Ĵ���ָ��ĵ�ַ��ȡ��һ���ֵ����ݣ��洢��R1�Ĵ�����)
	LDR R0, [R0]

	STMDB	R0!, {R4-R11}  // ���Ĵ���ѹջ������Ĵ�����ֵ��
	
	LDR R1, =_block_ptr
	LDR R1, [R1]
	STR R0, [R1]           // 
	
	ADD R4, R4, #1
	ADD R5, R5, #1
	
	LDMIA   R0!, {R4-R11}  // �Ĵ�������ջ���ָ��Ĵ�����ֵ��
	
	BX LR
}


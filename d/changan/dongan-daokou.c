//Room: dongan-daokou.c

inherit ROOM;
void create ()
{
	set ("short", "��������");
	set ("long", @LONG
�������Թ��Ƿ���ʤ�أ�Ϊ�����ʳ�����֮�أ���Ϊ���̴������
�����󸻼������¡�����������һ����ͨ�˴��·�ڣ�������һ����·
ͨ����ڼ���������ǳ��������ţ��ϱ����������´���� 
LONG);
	set("exits",([//sizeof() == 5
		"south" : __DIR__"liande-dadao4",
		"north" : __DIR__"liande-dadao3",
		"west" : __DIR__"dongan-dadao",
		"east" : __DIR__"dong-chengmen",
		"southwest" : __DIR__"bingying6",
	]));

	set("outdoors", "changan");
	setup();
}
	
//Room: beian-daokou.c

inherit ROOM;

void create ()
{
	set ("short", "��������");
	set ("long", @LONG
�������Թ��Ƿ���ʤ�أ�Ϊ�����ʳ�����֮�أ���Ϊ���̴������
�����󸻼������¡�����������һ����ͨ�˴��·�ڣ���������ͨ����
��֣������ǳ��������ţ��Ϸ���һ����·ͨ���ʻʹ��Ľ�ˮ�š� 
LONG);
	set("exits",([//sizeof() == 4
		"south" : __DIR__"beian-dadao",
		"north" : __DIR__"bei-chengmen",
		"west" : __DIR__"qixiang3",
		"east" : __DIR__"qixiang4",
		"southeast" : __DIR__"bingying1",
		"southwest" : __DIR__"bingying2",
	]));

	set("outdoors", "changan");
	setup();
}

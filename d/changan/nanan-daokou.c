//Room: nanan-daokou.c

inherit ROOM;

void create ()
{
	set ("short", "�ϰ�����");
	set ("long", @LONG
�������Թ��Ƿ���ʤ�أ�Ϊ�����ʳ�����֮�أ���Ϊ���̴������
�����󸻼������¡��ϰ�������һ����ͨ�˴��·�ڣ���������ͨ����
��֣������ǳ����ϳ��ţ�������һ����·ͨ���ʻʹ��Ľ�ˮ�š� 
LONG);
	set("exits",([//sizeof() == 4
		"south" : __DIR__"nan-chengmen",
		"north" : __DIR__"nanan-dadao",
		"west" : __DIR__"huarui3",
		"east" : __DIR__"huarui4",
		"northeast" : __DIR__"bingying4",
		"northwest" : __DIR__"bingying5",
	]));

	set("outdoors", "changan");
	setup();
}
	
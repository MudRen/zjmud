//Room: xian-daokou.c

inherit ROOM;
void create ()
{
	set ("short", "��������");
	set ("long", @LONG
�������Թ��Ƿ���ʤ�أ�Ϊ�����ʳ�����֮�أ���Ϊ���̴������
�����󸻼������¡�����������һ����ͨ�˴��·�ڣ�������һ����·
ͨ��������������ǳ��������ţ��ϱ���������̩����� 
LONG);
	set("exits",([//sizeof() == 5
		"south" : __DIR__"yongtai-dadao4",
		"north" : __DIR__"yongtai-dadao3",
		"west" : __DIR__"xi-chengmen",
		"east" : __DIR__"xian-dadao",
		"southeast" : __DIR__"bingying3",
	]));

	set("outdoors", "changan");
	setup();
}
	
//Room: qixiang4.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ����
�֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱��ڶ�
����������һ��Ǯׯ�������������������Ľ���������
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"qunyulou",
		"north" : __DIR__"bank",
		"west" : __DIR__"beian-daokou",
		"east" : __DIR__"qixiang5",
	]));

	set("outdoors", "changan");
	setup();
}

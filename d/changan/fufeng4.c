//Room: fufeng4.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�
LONG);
	set("exits", 
	([ //sizeof() == 2
		"north" : __DIR__"fufeng3",
		"south" : __DIR__"fufeng5",
	]));

	set("outdoors", "changan");
	setup();
}

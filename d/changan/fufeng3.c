//Room: fufeng3.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������һ����·ͨ������
�ǵ������š�
LONG);
	set("exits", 
	([ //sizeof() == 3
		"north" : __DIR__"fufeng2",
		"south" : __DIR__"fufeng4",
		"west" : __DIR__"xian-dadao",
	]));

	set("outdoors", "changan");
	setup();
}

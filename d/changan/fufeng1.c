//Room: fufeng1.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء������ǰ׻��֡�
LONG);
	set("exits", 
	([ //sizeof() == 3
		"south" : __DIR__"fufeng2",
		"east" : __DIR__"baihu1",
	]));

	set("outdoors", "changan");
	setup();
}

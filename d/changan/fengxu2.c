//Room: fengxu2.c

inherit ROOM;

void create ()
{
	set ("short", "��ڼ��");
	set ("long", @LONG
��ڼ���ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�
LONG);
	set("exits", 
	([ //sizeof() == 2
		"north" : __DIR__"fengxu1",
		"south" : __DIR__"fengxu3",
	]));

	set("outdoors", "changan");
	setup();
}

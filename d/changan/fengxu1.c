//Room: fengxu1.c

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
		"west" : __DIR__"baihu3",
		"south" : __DIR__"fengxu2",
	]));

	set("outdoors", "changan");
	setup();
}

//Room: fengxu4.c

inherit ROOM;

void create ()
{
	set ("short", "��ڼ��");
	set ("long", @LONG
��ڼ���ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء����������̸�
LONG);
	set("exits", 
	([ //sizeof() == 3
		"north" : __DIR__"fengxu3",
		"south" : __DIR__"fengxu5",
		"east" : __DIR__"lingyange",
	]));

	set("outdoors", "changan");
	setup();
}

//Room: fengxu3.c

inherit ROOM;

void create ()
{
	set ("short", "��ڼ��");
	set ("long", @LONG
��ڼ���ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·������
�ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������һ����·ͨ������
�ǵĶ����š�
LONG);
	set("exits", 
	([ //sizeof() == 3
		"north" : __DIR__"fengxu2",
		"south" : __DIR__"fengxu4",
		"east" : __DIR__"dongan-dadao",
	]));

	set("outdoors", "changan");
	setup();
}

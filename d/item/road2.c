// road2.c С��

inherit ROOM;

void create()
{
	object ob;

	set("short", "С��");
	set("long", @LONG
����һ�����ѵ�С������������ͨ��ɽ�·���Ϲ⻬ƽʵ��������
�����������������ܷǳ����������Զ�����԰�廧��
LONG );

	set("exits", ([
		"westdown" : __DIR__"road1",
		"eastdown" : __DIR__"road3",
	]));
	set("outdoors", "suzhou");
	setup();
}

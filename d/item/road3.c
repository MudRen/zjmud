// road3.c С��

inherit ROOM;

void create()
{
	object ob;

	set("short", "С��");
	set("long", @LONG
����һ�����ѵ�С������������ͨ��ɽ�·���Ϲ⻬ƽʵ��������
�����������������ܷǳ����������Զ�����԰�廧����ʱ��������������
�ද�˵���С�
LONG );

	set("exits", ([
		"westup"    : __DIR__"road2",
		"northeast" : __DIR__"road4",
	]));
	set("outdoors", "suzhou");
	setup();
}

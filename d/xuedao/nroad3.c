// nroad3.c

inherit ROOM;
void create()
{
	set("short", "��ѩɽ��´");
	set("long", @LONG
����ɽ�Ʊȴ�ѩɽ�����Ի���Ҳ����ʮ�ֵ��Ϻ���ɽ�����Գ���
��ϡϡ������һЩҰ�ݡ����º����˼���ֻ�м�ֻͺӥ�ڸߴ�������
������ããѩɽ��
LONG );
	set("exits", ([
		"south"     : __DIR__"nroad4",
		"eastdown"  : __DIR__"nroad2",
	]));
	set("objects", ([
		__DIR__"npc/eagle" : 2,
	]));
	set("outdoors", "xuedao");
	setup();
}


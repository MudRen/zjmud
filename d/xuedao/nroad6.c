// nroad6.c
inherit ROOM;
void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һɽ·�ϣ�������һ����Сɽ��Զ�����Կ��������ѩ
��ɽ�⡣��Χ�������Ѿ����ѿ��õ��ˡ�
LONG );
	set("exits", ([
		"north"   : __DIR__"nroad7",
		"southup" : __DIR__"nroad5",
	]));

	set("outdoors", "xuedao");
	setup();
}


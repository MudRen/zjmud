// tianshan: /d/xingxiu/shanjiao.c
inherit ROOM;
void create()
{
	set("short", "��ɽ����");
	set("long", @LONG
��������ɽ���£������Ǹ������Ƶ���ɽ�������ʱ����Կ���ɽ��
�ϵı�����һ����ɽ�������Ϊ���롣�������������ľ۾������Ͻ���
�ޱߵ���������ɴ�ɳĮ��
LONG );
	set("exits", ([
	    "westup" : __DIR__"tianroad1",
	    "east"  : __DIR__"kedian",
	    "north" : __DIR__"beijiang",
	    "southwest" : __DIR__"nanjiang",
	    "southeast" : __DIR__"silk4",
	]));

	set("objects", ([
		__DIR__"npc/trader" : 1
	]));

	set("outdoors", "xiyu");

	setup();
}

int valid_leave(object me, string dir)
{
	if (! userp(me) && dir == "southwest")
		return 0;

	return ::valid_leave(me, dir);
}

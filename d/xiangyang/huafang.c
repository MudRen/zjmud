// Room: /d/xiangyang/huafang.c  ����
// Date: Jan. 28 2002 by Pound

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "����");
	set("long", @LONG
������ֲ���ݵĻ��������Ÿ��ָ����Ļ��ݡ�������������ζ��Ũ��
������ҩ��������������ʼ�ղ����Ҷ��������ڵ������Ϸ��ż������裬
����ȥ�м������軹û���֣����ÿ��������ֻ���zhonghua����
LONG );

	set("exits", ([
	    "north" : __DIR__"maoshe",
	]));

	set("objects", ([
	    __DIR__"obj/tihuxiang" : 1,
	    __DIR__"obj/shuitong"  : 1,
	]));

	setup();
}
void init()
{
	object me, ob;
	me = this_player();

	if (! objectp(ob = present("qixin haitang", me)) && me->query("yaowang/qxht/have"))
	    me->delete("yaowang/qxht");
	if (! objectp(ob = present("haitang candle", me)) && me->query("yaowang/candle/using"))
	    me->delete("yaowang/candle");
}
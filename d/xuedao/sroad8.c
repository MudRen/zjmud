// sroad8.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��ѩɽɽ��");
	set("long", @LONG
һ�����ɽ�ȣ�Ⱥɽ���ƣ�ɽ����ȫ�ǰ������Ļ�ѩ��ɽ���Ϸ���
����ɽ���������м���˵����ʲô���ֵĹ�����������һЩ���߰����
����(mash)�Ѱ��������֪�����涼��ʲô��
LONG );
	set("exits", ([
		"enter"  : __DIR__"shandong1",
		"north"  : __DIR__"wangyougu",
		"northup": __DIR__"sroad7",
	]));
	set("outdoors", "xuedao");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter(string arg)
{
	object me;

	me = this_player();
	if (arg != "mash")
		return notify_fail("��Ҫ����ʲô��\n");

	if (me->query("family/family_name") != "Ѫ����")
		return notify_fail("�㷭��һ����Щ���飬ֻ����"
				   "һ��Ѫ������ӿ������ֱ��Ż�¡�\n");

	message("vision", me->name() + "�ߵ�һ�߲�֪���ڹ������ĸ�Щ"
		"ʲô...ͻȻ�˲����ˣ�\n", this_object(), ({ me }));
	tell_object(me, "��������ŵ��ƿ���Щ���飬Խ����"
		    "ȥ��ֻ�����ܵ��������ݶ�ȥ��\n");
	me->move("/d/city/datiepu");
	return 1;
}

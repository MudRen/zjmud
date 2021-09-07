// Room: xiaoting

#include <ansi.h>
inherit ROOM;

void init();
int do_tap(string);
int do_sit(string);
void delete_served(object);

void create()
{
	set("short", "������");
	set("long", @LONG
����һ��С��,���䲻��,���õ�Ҳ���¡������ķ��㣬������Ƣ��
ֻ��ǽ�Ϲ��ż�������,������Ϊ����,���ڲ�ס��������֮����������
�ܾ��ɵذ���Щ����(table)������(chair)��
LONG );
	set("exits", ([
	    "west" : __DIR__"qinyun",
	    "east" : __DIR__"cuixia",
	    "north" : __DIR__"xiaojing",
	    "south" : __DIR__"chufang",
	]));

	set("item_desc", ([
	    "table" : "һ�ŵ��ŵ���ľС�����������ˮ���̺��������ߡ�\n",
	    "chair" : "һֻ������ƵĿ��Σ�����ȥҡҡ�λΣ������Ү��\n",
	]));

	set("objects",([
	      __DIR__"npc/susu" : 1,
	      __DIR__"obj/gao" : 2,
	      __DIR__"obj/cha" : 1,
	]));
	setup();
}

void init()
{
	add_action("do_tap", "tap");
	add_action("do_tap", "knock");
	add_action("do_sit", "sit");
}

int do_tap(string arg)
{

	object me;
	object susu;

	if (arg != "desk" && arg != "table")
		return notify_fail("��Ҫ��ʲô��\n");

	me = this_player();
	if (! objectp(susu = present("su su", environment(me))))
		return notify_fail("�����������ӣ�ȴ����û�����㡣��ͻȻ"
				   "�о��Լ������ġ�\n");

	if (! me->query_temp("marks/sit"))
		return notify_fail("�����������ӣ�ȴ�������ؿ�����ֱЦ��"
				   "��ͻȻ�о��Լ����޴���\n");

	if (susu->query_temp("marks/served"))
	{
	    message_vision("���ز��ͷ��ض�$N˵����������æ���أ�\n", me);
	    return 1;
	}

	message_vision("$N��������ǰ��������������棬����һЦ�������к���\n", me);

	susu->serve_tea(me);

	susu->set_temp("marks/served", 1);
	call_out("delete_served", 5, susu);

	return 1;
}


void delete_served(object me)
{
	if (objectp(me))
		me->delete_temp("marks/served");
}


int do_sit(string arg)
{

	if (arg != "chair")
		return notify_fail("��Ҫ��ʲô���棿\n");

	if (this_player()->query_temp("marks/sit"))
		return notify_fail("���Ѿ����˸���λ�ˡ�\n");

	this_player()->set_temp("marks/sit", 1);
	write("�����˸���λ���£������ϲ衣\n");
	return 1;
}


int valid_leave(object me,string dir)
{
	me->delete_temp("marks/sit");
	me->delete_temp("tea_cup");
	return::valid_leave(me,dir);
}


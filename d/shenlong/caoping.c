#include <ansi.h>

inherit ROOM;

string flower()
{
	int n;

	n = random(300);
	if (n == 88) return __DIR__"obj/hua4";
	if (n < 50)  return __DIR__"obj/hua";
	if (n < 80)  return __DIR__"obj/hua2";
	return __DIR__"obj/hua3";
}

void create()
{
	set("short", "��ƺ");
	set("long", @LONG
������һƬ����Ĳ�ƺ�����ܿ����˸�ɫ���ʻ���һ�����紵
�������µĿ����д������Ƶ����Ļ��㡣
LONG );
	set("exits", ([
		"east" : __DIR__"kongdi",
	]));
	set("objects", ([
		flower() : 1,
		flower() : 1,
		flower() : 1,
	]));
	set("outdoors", "shenlong");
	setup();
}

void init()
{
	object me = this_player();

	if (objectp(present("duanchang hua", environment(me)))) 
	{
		me->apply_condition("flower_poison", 30 +
				    (int)me->query_condition("flower_poison"));

		write(HIG "��ֻ��һ�ɵ���Ϯ������ʱ����һ����ľ��"NOR"\n");
	}
}

void reset()
{
	object ob;

	set("objects", ([
		flower() : 1,
		flower() : 1,
		flower() : 1,
	]));

	delete_temp("objects");
	foreach (ob in all_inventory())
		if (! interactive(ob) && ! ob->is_character())
			destruct(ob);

	::reset();
}

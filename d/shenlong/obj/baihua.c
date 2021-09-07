#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_use", "use");
}

void create()
{
	set_name("�ٻ����߸�", ({"baihua gao", "gao","baihua"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ö");
		set("long", "����һö���İٻ����߸ࡣ\n");
		set("value", 20000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->improve_neili(30 + random(30)))
	{
		me->set("neili", me->query("max_neili"));
		message_vision(HIY "$N" HIY "����һö�ٻ����߸࣬��Ȼ��ֻ"
			       "��һ������֮��ֱ���ķ�..."NOR"\n", this_player());
	}
	else
		message_vision(HIY "$N" HIY "����һö�ٻ����߸࣬���Ǻ���"
			       "ûʲô�á�"NOR"\n", this_player());

	destruct(this_object());
	return 1;
}

int do_use(string arg)
{

	object obj, weapon;
	object me = this_player();
	
	if (! arg || ! id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("�����������²��аɣ�\n");

	message_vision(HIY "$Nȡ��һö�ٻ����߸࣬����Ĩ�ڱ��м�����֮�ϡ�"NOR"\n", me);
	message_vision(HIY "$Nʹ�õİٻ����߸�ҩЧ��ʼ����."NOR"\n", me);
	obj = new("/d/shenlong/obj/usedgao");
	obj->move(me, 1);
	destruct(this_object());
	return 1;
}

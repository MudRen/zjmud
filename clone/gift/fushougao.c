// tianxiang.c ������¶

#include <ansi.h>

inherit ITEM;

void setup()
{
}

void create()
{
	set_name(HIW "���ٸ�" NOR, ({"fushou gao", "fushou", "gao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIY "һ��ںڵ�ҩ���������󣬾�˵�������˾���ٱ���\n");
		set("value", 200000);
		set("yuanbao", 20);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	string force;

	message_vision(HIC"$N�ͳ�һ֧��ǹ�����������һ��"
		       NOR HIW"���ٸ࣬"NOR HIC"��������ƮƮ���ɣ�����¶�������"
		       "���顣"NOR"\n",
		       me);
	if (me->improve_jingli(50 + random(50)))
		me->set("jingli", me->query("max_jingli"));
	destruct(this_object());
	return 1;
}
int query_autoload() { return 1; }

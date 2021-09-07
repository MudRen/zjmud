// tea_leaf.c
 
#include <weapon.h>
#include <ansi.h>

inherit THROWING;
 
void create()
{
	set_name(HIG "��Ҷ" NOR, ({ "tea leaf", "tea" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "�Ųɵ��²裬����һ�ɵ�����������\n");
		set("unit", "��");
		set("base_unit", "Ƭ");
		set("base_weight", 1);
		set("base_value", 1);
		set("material", "wood");
		set("wield_msg", "$NѸ�ٵشӰ��������ͳ�һЩ��Ҷ���������оʹ�������\n");
		set("unwield_msg", "$N������ʣ�µĲ�Ҷ�����Żذ������С�\n");
		set("only_do_effect", 1);
	}
	set_amount(50);
	init_throwing(1);
	setup();
}

int do_effect(object me)
{
	if (query_amount() < 1)
		return 0;

	add_amount(-1);
	write("����˼��ڲ�Ҷ�����ÿ��д���һ�����㣬�����ɵ�һ��\n");
	me->receive_heal("jing", 1 + random(2));
	me->start_busy(1);
	return 1;
}


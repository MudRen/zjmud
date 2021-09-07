
#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(MAG"������"NOR, ({"laba zhou"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�����͵����Ƶ������࣬��˵�����������������ֵ��\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		set("no_put", 1);
		set("no_get", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_beg", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	int num1,num2,num3,num4;

	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		return notify_fail("����ս���У�����ʹ��"+ name() +"��\n");

	num1=50+random(50);
	me->add("max_neili",num1);

	message_vision("$N����һ" + query("unit") + name() + "��\n", me);
	write(YEL"��ϲ����������"+num1+"��������"NOR"\n");
	add_amount(-1);
	me->save();
	return 1;

}

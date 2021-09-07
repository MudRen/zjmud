
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
	set_name("Ԫ�����", ({"yuanxiao libao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "Ԫ�������ָ��mudף��ҽ��տ��֣�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		set("yuanbao", 10);
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

	num1=5000+random(5000);
	me->add("combat_exp",num1);
	num2=5000+random(5000);
	me->add("potential",num2);
	num3=5000+random(5000);
	me->add("experience",num3);
	num4=360+random(360);
	me->add("zjvip/times",24*3600);

	message_vision("$N����һ" + query("unit") + name() + "��\n", me);
	write(YEL"��ϲ���������"+num1+"�㾭�顣"NOR"\n");
	write(YEL"��ϲ���������"+num2+"��Ǳ�ܡ�"NOR"\n");
	write(YEL"��ϲ���������"+num3+"��ʵս��ᡣ"NOR"\n");
	write(YEL"��ϲ���������1���Աʱ����"NOR"\n");
	add_amount(-1);
	me->save();
	return 1;

}

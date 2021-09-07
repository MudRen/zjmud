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
	set_name(HIY"���鵤"NOR, ({"xuanling dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("yuanbao", 100);
        set("no_get", 1);
        set("no_give", 1);
        set("no_drop", 1);
        set("no_sell", 1);
        set("no_steal", 1);
        set("no_beg", 1);
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 10000);
		set("long","����һ�����鵤����������һСʱ������ʱ�䣨��ʦ��������Ч��Ч�����Ժ����鵤���ӣ���\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	object ob1;

	me->apply_condition("db_exp2", 360+me->query_condition("db_exp2"));

	write(YEL"�����һ��"HIY"���鵤"YEL"���پ�������ˬ��˼ά����!"NOR"\n");
	add_amount(-1);
	return 1;
}


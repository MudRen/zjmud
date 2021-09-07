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
	set_name(HIY"Ԫ��Ʊ"NOR, ({"yuanbao piao"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 100);
		set("yuanbao", 10);
        set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 100);
		set("long","����һ��Ԫ��Ʊ����������12000��Ԫ����\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
      if (me->is_busy())
                return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		    return notify_fail("����ս���У�����ʹ��"+name()+"��\n");
	write(YEL"��ʹ����һ��"+name()+YEL+"��"NOR"\n");
	me->add("yuanbao",12000);
	write(YEL"�����12000��Ԫ����"NOR"\n");
	me->add("yuanbao",1000);
	write(YEL"�����1000��Ԫ����"NOR"\n");
	me->add("zjvip/all_pay",1000);
	write(YEL"�����1000�����ף�"NOR"\n");
	

	add_amount(-1);
	return 1;
}
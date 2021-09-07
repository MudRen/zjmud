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
	set_name(HIR"�������֥"NOR, ({"huo lingzhi"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("yuanbao", 200);
        set("no_sell",1);
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		set("long","����һ���������֥����������1000���������ޣ�ÿ��ֻ��ʹ��һ�Ρ�\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	object ob1;
	int times;

	times = time();
	if(me->query("day_item/huolingzhi/last_time")&&same_week(times,me->query("day_item/huolingzhi/last_time")))
	{
		tell_object(me,"�㱾���Ѿ�ʹ�ù�"+query("name")+"�ˡ�"NOR"\n");
		return 1;
	}

	me->set("day_item/huolingzhi/last_time",times);
	me->add("day_item/huolingzhi/times",1);

	me->add("zjvip/huolingzhi_num",1);
	me->add("max_neili", 1000);
	message_vision(YEL+me->query("name")+"����һ��"HIR"�������֥"YEL"���پ�����������"NOR"\n",me);

	add_amount(-1);
	return 1;
}


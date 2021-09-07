
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
	set_name(HIG"�ش���"NOR, ({"huichun dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�������ҩ�裬��˵�ܷ��Ϲ�ͯ��\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		set("yuanbao", 10);
        set("no_sell", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
    int var;

    if (me->is_busy())
            return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		    return notify_fail("����ս���У�����ʹ��"+ name() +"��\n");

    if (me->query("mud_age")<86400*18)
            return notify_fail("��Ŀǰ����ʹ��"+ name() +"��\n");
    else {
        var=86400*3;
        me->add("mud_age",-var);
		me->add("dan/huichun",1);
        message_vision("$NС�ķ�����һ" + query("unit") + name() + "���ƺ�������һЩ��\n", me);
	    add_amount(-1);
        return 1;
    }

}

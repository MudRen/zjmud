// thousand.c

#include <ansi.h>

inherit MONEY;

void create()
{
        set_name(HIY "ҼǪ����Ʊ" NOR, ({"thousand-gold"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "thousand-cash");
                set("long", "һ�����ֵһǧ���ƽ����Ʊ��\n");
                set("unit", "��");
                set("base_value", 10000000);
                set("base_unit", "��");
                set("base_weight", 5);
		    set("material", "paper");
        }
        set_amount(1);
}

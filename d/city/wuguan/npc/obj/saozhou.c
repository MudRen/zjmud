//saozhou.c 
#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("ɨ��", ({ "sao zhou", "sao", "club" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��ɨ�㣬��ͨ���յ��ճ���Ʒ��\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N�ó�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n���ڼ��ϡ�\n");
        }
        init_club(4);
        setup();
}

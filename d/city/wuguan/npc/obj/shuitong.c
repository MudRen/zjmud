//shuitong.c

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("ˮͰ", ({ "shui tong", "tong", "hammer"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
                set("long", "����һֻˮͰ����ͨ���յ��ճ���Ʒ��\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N�ó�һֻ$n���ڼ��С�\n");
                set("unwield_msg", "$N�����ϵ�$n����������\n");
        }
        init_hammer(10);
        setup();
}

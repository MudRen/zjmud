//chutou.c
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("��ͷ", ({ "chu tou", "tou", "staff" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ѳ�ͷ����ͨ���յ��ճ���ũ��Ʒ��\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N�ó�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n���ڼ��ϡ�\n");
        }
        init_staff(4);
        setup();
}

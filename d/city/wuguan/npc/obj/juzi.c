//juzi.c

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("����", ({ "ju zi", "ju", "blade" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ������ľͷ�ľ��ӣ���ͨ���յ��ճ���Ʒ��\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N�ó�һ��$n�������С�\n");
                set("unwield_msg", "$N�����еĿ��ڼ��ϡ�\n");
        }
        init_blade(4);
        setup();
}

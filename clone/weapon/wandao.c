// weapon: /z/xingxiu/npc/obj/wandao.c
// Jay 3/17/96

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("�������䵶", ({ "wandao" }));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����λεİ������䵶�����������״�����ж�"
"��������ı��С�\n");
		set("value", 500);
		set("icon", "05070");
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	}
	init_blade(35);
	setup();
}


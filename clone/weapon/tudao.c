// tudao.c

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("����", ({ "knife" }));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һѪ���ܵ�������\n");
	      set("icon", "05038");
		set("value", 200);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	}
	init_blade(30);
	setup();
}

// jpn-dao

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("����", ({ "sword", "jian" }));
	set_weight(4500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
	      set("icon","05057");
		set("long", "����һ��ϸ���ĳ�������������ʿ���õ�������\n");
		set("value", 4000);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	}
	init_sword(55);
	setup();
}

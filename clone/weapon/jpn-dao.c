// jpn-dao

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("����", ({ "blade", "dao" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
	      set("icon","05038");
		set("long", "����һ��ϸ������Ķ��󳤵�����״���죬�ƽ��Ƶ���\n");
		set("value", 5000);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	}
	init_blade(50);
	setup();
}

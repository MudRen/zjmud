// gangjian.c

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("�ֽ�", ({ "iron sword", "jian", "sword" }));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
	      set("icon","05035");
		set("long", "����һ�������Ƴɵĸֽ������ֽ��ڽ���֮��ǳ����С�\n");
		set("value", 400);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
	}
	init_sword(25);
	setup();
}

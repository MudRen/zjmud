// green sword.c

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
	set_name(HIG"��ˮ��"NOR, ({ "green sword", "jian" }) );
	set_weight(7000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon","05068");
		set("long", "����һ��ͨ�徧Ө��͸�Ľ�������֮����\n");
		set("value", 400);
		set("material", "crimsonsteel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��������Ľ��ʡ�\n");
	}
	init_sword(20);
	setup();
}

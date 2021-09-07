// jitui.c ����

#include <weapon.h>

inherit HAMMER;
inherit F_FOOD;

void create()
{
	set_name("������", ({ "jitui", "tui" }) );
	set_weight(350);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ֦����������ļ��ȡ�\n");
		set("unit", "��");
		set("value", 80);
		set("food_remaining", 4);
		set("food_supply", 15);
		set("wield_msg", "$Nץ��һ��$n���������е�������\n");
		set("material", "bone");
	}
	init_hammer(1);
	setup();
}

int finish_eat()
{
	object ob;
	ob = new("/d/city/obj/bone");
	ob->move(environment(this_object()));
	destruct(this_object());
	return 1;
}

// ITEM Made by player(����:sun1903) /data/item/s/sun1903-you.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb  3 15:59:48 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[36m����[2;37;0m", ({ "you" }));
	set_weight(1750);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ��ָ�ס�
[36m����˫�ִ���������롣[2;37;0m
ָ��Ե�Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "[33m$N[33mװ��[2;37;0m[36m����[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[2;37;0m[36m����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return query("long") + item_long(); }

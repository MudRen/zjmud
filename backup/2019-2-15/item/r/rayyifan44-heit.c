// ITEM Made by player(�ɺ�:rayyifan44) /data/item/r/rayyifan44-heit.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan 14 13:11:54 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("�������[2;37;0m", ({ "heit" }));
	set_weight(2250);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ˫���ơ�
����Ե�Ͽ���һ��С�֣��ɺ�(rayyifan44)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "[33m$N[33mװ���������[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˺������[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }

// ITEM Made by player(����:tcawjf) /data/item/t/tcawjf-meng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 12:49:09 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mһ��ǧ��[2;37;0m", ({ "meng" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[1;35m����[2;37;0m���ƶ��ɵ�һ˫���ơ�
ǧ���һ˲���������е�ָһ�Ӽ�[2;37;0m
����Ե�Ͽ���һ��С�֣�����(tcawjf)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wear_msg", "�����[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;34mһ��ǧ��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }

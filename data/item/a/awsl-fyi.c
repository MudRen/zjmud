// ITEM Made by player(��������:awsl) /data/item/a/awsl-fyi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  9 18:58:00 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[30m����[2;37;0m", ({ "fyi" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ�Ż��ס�
[30mһ��˧���ķ���[2;37;0m
����Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "����[2;37;0m\n");
	set("remove_msg", "����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }

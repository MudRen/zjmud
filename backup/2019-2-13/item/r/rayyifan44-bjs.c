// ITEM Made by player(�κ�:rayyifan44) /data/item/r/rayyifan44-bjs.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan  4 22:12:32 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("������[2;37;0m", ({ "bjs" }));
	set_weight(1050);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m����˿[2;37;0m���ƶ��ɵ�һ�Ż��ס�
����Ե�Ͽ���һ��С�֣��κ�(rayyifan44)
");
	set("value", 2100000);
	set("point", 176);
	set("material", "silk");
	set("wear_msg", "[33m$N[33mװ��������[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˰�����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }

// ITEM Made by player(����:zjzs123) /data/item/z/zjzs123-dyll.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 30 12:42:32 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("��Ҷ�����[2;37;0m", ({ "dyll" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[33m�ڽ�˿[2;37;0m���ƶ��ɵ�һ�Ż��ס�
��ͨ��һ��[2;37;0m
����Ե�Ͽ���һ��С�֣�����(zjzs123)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "silk");
	set("wear_msg", "��������[2;37;0m\n");
	set("remove_msg", "[33m$N[33m�����˴�Ҷ�����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }

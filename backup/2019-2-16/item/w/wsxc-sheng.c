// ITEM Made by player(����:wsxc) /data/item/w/wsxc-sheng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb 10 16:36:41 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36mʥ������[2;37;0m", ({ "sheng" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ�Ż��ס�
������ʥ��������[2;37;0m
����Ե�Ͽ���һ��С�֣�����(wsxc)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "[1;33mʥ������ҫ��[2;37;0m\n");
	set("remove_msg", "[1;33m��˵���Ҳ�����ƽ�[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }

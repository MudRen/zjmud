// ITEM Made by player(����:q2870406595) /data/item/q/q2870406595-ylx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb  3 10:57:50 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m��������[2;37;0m", ({ "ylx" }));
	set_weight(45000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[36m����[2;37;0m���ƶ��ɵ�һ�Ż��ס�
�һ��������������������ٻ��߿ɽ��������ٻ����������ʯ֮�������������ܻ�֮����������ɺ��壬��Ϊ������ʿ������������[2;37;0m
����Ե�Ͽ���һ��С�֣�����(q2870406595)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "$n���壬һ����ž��ž���죬����������[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;31m��������[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }

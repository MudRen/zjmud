// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-men.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 13 16:54:39 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("���۲�[2;37;0m", ({ "men" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ��ͷ����
��ħ���ֵ�һ�����ڵ��Լ����۾����������۲������Ǳ�Ҫ�Ķ�����[2;37;0m
ͷ��Ե�Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "[33m$N[33mװ�����۲�[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m���������۲�[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }

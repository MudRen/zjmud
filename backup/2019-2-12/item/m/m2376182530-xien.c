// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-xien.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 11 11:37:47 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("а�ܻ���[2;37;0m", ({ "xien" }));
	set_weight(700);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[1;37m����˿[2;37;0m���ƶ��ɵ�һ�����ӡ�
а����һ�ֿ��µ����������γɵĻ������������ꡣ[2;37;0m
����Ե�Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 2100000);
	set("point", 110);
	set("material", "silk");
	set("wear_msg", "��¶�Ļ���ȼ�գ����Ǹо��Լ������·����Ť����ա�[2;37;0m\n");
	set("remove_msg", "а�ܻ���Ϩ���ˣ���ħ���ֿ�������Щ������[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }

// ITEM Made by player(����:wentianaa) /data/item/w/wentianaa-zhang.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:25:39 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m��������[2;37;0m", ({ "zhang" }));
	set_weight(2250);
	set("item_make", 1);
	set("unit", "˫");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ˫���ơ�
[1;33mһ�Ƴ��������ˡ�[2;37;0m
����Ե�Ͽ���һ��С�֣�����(wentianaa)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "$n[1;33m�������[2;37;0m\n");
	set("remove_msg", "$n[1;33m��ʧ����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }

// ITEM Made by player(��������:awsl) /data/item/a/awsl-sss.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 17:47:56 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mŮ��Ĺ��[2;37;0m", ({ "sss" }));
	set_weight(1750);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ��ָ�ס�
[1;31m����������Ů��˹߯ŵ���裩������[2;37;0m
ָ��Ե�Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "����[2;37;0m\n");
	set("remove_msg", "ȡ��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return query("long") + item_long(); }

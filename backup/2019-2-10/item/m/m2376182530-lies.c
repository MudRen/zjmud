// ITEM Made by player(������:m2376182530) /data/item/m/m2376182530-lies.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Dec 19 17:34:15 2018
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("����ս��[2;37;0m", ({ "lies" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ������
��ħ�����±�������[2;37;0m
�����Ͽ���һ��С�֣�������(m2376182530)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "ս�г���[2;37;0m\n");
	set("unwield_msg", "�ջ���ս�С�[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }

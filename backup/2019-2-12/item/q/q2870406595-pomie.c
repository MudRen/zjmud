// ITEM Made by player(�ΰ�:q2870406595) /data/item/q/q2870406595-pomie.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 27 12:52:55 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("����[2;37;0m", ({ "pomie" }));
	set_weight(1575);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m����[2;37;0m���ƶ��ɵ�һ��ָ�ס�
������գ������Ҳ̫��С������Ե�����Ե����������ҵ�����[2;37;0m
ָ��Ե�Ͽ���һ��С�֣��ΰ�(q2870406595)
");
	set("value", 700000);
	set("point", 66);
	set("material", "iron");
	set("wear_msg", "$N���ϳ�һ���������Ϣ��˫��һ��$n��������[2;37;0m\n");
	set("remove_msg", "[33m$N[33m����������[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return query("long") + item_long(); }

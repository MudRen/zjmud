// ITEM Made by player(����:sun1903) /data/item/s/sun1903-loser.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 17:28:54 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[31m����[2;37;0m", ({ "loser" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ��ͷ����
[1;36mһ�����Ŷ�ëñ�¿�ü���ۣ�������ɣ����ٶ�룬��֮����[2;37;0m
ͷ��Ե�Ͽ���һ��С�֣�����(sun1903)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "[33m$N[33mװ��[2;37;0m[31m����[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[2;37;0m[31m����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }

// ITEM Made by player(��ħ:l3440039129) /data/item/l/l3440039129-lsz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  1 00:14:02 2019
#include <ansi.h>
#include <weapon.h>

inherit STAFF;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m��������[2;37;0m", ({ "lsz" }));
	set_weight(6750);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m����[2;37;0m���ƶ��ɵ�һ���ȡ�
�ȱ��Ͽ���һ��С�֣���ħ(l3440039129)
");
	set("value", 700000);
	set("point", 66);
	set("material", "iron");
	set("wield_msg", "[1;36m$N[1;36mһ����Х������һ��[1;36m$n[1;36m��[2;37;0m\n");
	set("unwield_msg", "$N����һĨ��������$n��\n");
	if (! check_clone()) return;
	restore();
	init_staff(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }

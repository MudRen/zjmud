// ITEM Made by player(ִ��:meng6666666) /data/item/m/meng6666666-jian.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 17 19:40:31 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m����[2;37;0m", ({ "jian" }));
	set_weight(45000);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[36m����[2;37;0m���ƶ��ɵ�һ������
[1;37m���߳���[2;37;0m
�����Ͽ���һ��С�֣�ִ��(meng6666666)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "$N����һ��$n��������[2;37;0m\n");
	set("unwield_msg", "$N����һ��$n��ʧ����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }

// ITEM Made by player(��������:awsl) /data/item/a/awsl-yxx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 17:51:14 2019
#include <ansi.h>
#include <weapon.h>

inherit XSWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m����[2;37;0m", ({ "yxx" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "֧");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ֧�
[1;31m��֪�������������������[2;37;0m
����Ͽ���һ��С�֣���������(awsl)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "����[2;37;0m\n");
	set("unwield_msg", "����[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_xsword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }

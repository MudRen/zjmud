// ITEM Made by player(����:wsxc) /data/item/w/wsxc-sgsp.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Feb 14 22:38:30 2019
#include <ansi.h>
#include <weapon.h>

inherit HAMMER;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33mʥ������[2;37;0m", ({ "sgsp" }));
	set_weight(17500);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[37m�Ϲź���[2;37;0m���ƶ��ɵ�һ�Ѵ���
[1;33m����ʥ��ʿ������˵�������[2;37;0m
�����Ͽ���һ��С�֣�����(wsxc)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "[1;33mΪ��ʥ�������㡣[2;37;0m\n");
	set("unwield_msg", "[1;33m$N���˲�ս���ϵ�Ѫ�����߸߾�����ս��������������ҫ��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_hammer(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
